#include "../include/soldado.hpp"

// std::clamp requer C++17, no mínimo. Logo, façamos nossa própria clamp
template<typename T>
T clamp(const T& value, const T& low, const T& high)
{
	return std::max(low, std::min(value, high));
}

// Soldado
// -------
Soldado::Soldado(std::string nome, float saude, float poder, LoggerInterface& logger) : nome(nome), saude(saude), poder(poder), logger(logger) {}

void Soldado::addListener(EventListener* listener)
{
	listeners.push_back(listener);
}

void Soldado::notifyObservers(const BattleEvent& event)
{
	for (EventListener* listener : listeners)
	{
		listener->onEvent(event);
	}
}

std::pair<float, DefenseOutcome> Soldado::performAttack(Soldado& soldado)
{
	float std_dev = (poder * 0.15f) / 1.645f; // Garantir que 90% dos ataques estejam na margem de +-15% do poder
	dist.param(std::normal_distribution<>::param_type(poder, std_dev));

	float damage = dist(gen);
	damage = clamp(damage, 0.0f, poder * 2.0f);

	DefenseOutcome defenseOutcome = soldado.defender(damage);

	return std::make_pair(damage, defenseOutcome);
}

float Soldado::atacar(Soldado& soldado) {
	std::pair<float, DefenseOutcome> attackOutcome = performAttack(soldado);

	float damage = attackOutcome.first;
	DefenseOutcome defenseOutcome = attackOutcome.second;

	if (defenseOutcome == DefenseOutcome::Hit)
	{
		AttackEvent event(this, &soldado, damage);
		notifyObservers(event);
	}
	else if (defenseOutcome == DefenseOutcome::Dodge)
	{
		DodgeEvent event(this, &soldado);
		notifyObservers(event);

		damage = 0.0f;
	}
	else if (defenseOutcome == DefenseOutcome::CounterAttack)
	{
		CounterAttackEvent event(this, &soldado, damage);
		notifyObservers(event);

		if (this->saude > damage)
		{
			this->saude -= damage;
		}
		else
		{
			this->saude = 0.0f;
		}

		damage = 0.0f;
	}

	return damage;
}

DefenseOutcome Soldado::defender(float damage) {
	if (saude > damage)
	{
		saude -= damage;
	}
	else
	{
		saude = 0.0f;
	}

	return DefenseOutcome::Hit;
}

void Soldado::imprimir() {
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(2) << nome << ": Saude " << saude << " e Poder " << poder;
	logger.logToFileAndConsole(ss.str());
}

std::string Soldado::getNome() const {
	return nome;
}

float Soldado::getSaude() const
{
	return saude;
}

float Soldado::getPoder() const
{
	return poder;
}

void Soldado::setPoder(float new_poder)
{
	poder = (new_poder < 0) ? 0 : new_poder;
}

Soldado& Soldado::batalhar(Soldado& soldado)
{
	int i = 1;
	std::uniform_int_distribution<> dist(0, 1);
	bool turn = dist(gen);

	logger.logToFileAndConsole("\n### Batalha entre " + this->getNome() + " e " + soldado.getNome() + " ###");
	logger.logToFileAndConsole("\n*** Estado inicial ***");
	logger.logToFileAndConsoleNoBreak(" - "); this->imprimir();
	logger.logToFileAndConsoleNoBreak(" - ");  soldado.imprimir();

	while (this->saude > 1e-3 && soldado.saude > 1e-3)
	{
		std::ostringstream ss;
		ss << "\n*** Resumo do turno " << i++ << " ***";
		logger.logToFileAndConsole(ss.str());

		if (turn) {
			this->atacar(soldado);
		}
		else {
			soldado.atacar(*this);
		}

		logger.logToFileAndConsoleNoBreak(" - "); this->imprimir();
		logger.logToFileAndConsoleNoBreak(" - "); soldado.imprimir();

		turn = !turn;
	}

	logger.logToFileAndConsole("\n*** Resultados apos a batalha ***");
	logger.logToFileAndConsoleNoBreak(" - "); this->imprimir();
	logger.logToFileAndConsoleNoBreak(" - ");  soldado.imprimir();

	logger.logToFileAndConsoleNoBreak("\n*** O vencedor eh ");

	if (this->saude > 1e-3)
	{
		logger.logToFileAndConsoleNoBreak(this->getNome());
	}
	else
	{
		logger.logToFileAndConsoleNoBreak(soldado.getNome());
	}

	logger.logToFileAndConsole(" ***");

	return this->saude > 1e-3 ? *this : soldado;
}

std::mt19937 Soldado::gen(std::random_device{}());

// Classes do bem
// --------------
int SoldadoBem::motivacao = 0;

SoldadoBem::SoldadoBem(std::string nome, float saude, float poder, LoggerInterface& logger) : Soldado(nome, saude, poder, logger) {}

// Elfo
Elfo::Elfo(std::string nome, float saude, float poder, LoggerInterface& logger) : SoldadoBem(nome, saude, poder + 1, logger) {}

DefenseOutcome Elfo::defender(float damage)
{
	std::uniform_int_distribution<> dist(0, 100);
	int swift = dist(gen);

	if (swift <= 30)
	{
		motivacao++;
		return DefenseOutcome::Dodge;
	}
	else
	{
		return Soldado::defender(damage / pow(1.005f, motivacao));
	}
}

// Anao
Anao::Anao(std::string nome, float saude, float poder, LoggerInterface& logger) : SoldadoBem(nome, saude, poder + 20, logger) {}

float Anao::atacar(Soldado& soldado) {
	std::uniform_int_distribution<> dist(0, 100);
	int missChance = dist(gen);

	if (missChance <= 40) {
		MissedAttackEvent event(this);
		notifyObservers(event);

		return 0.0f;
	}
	else {
		return Soldado::atacar(soldado);
	}
}

DefenseOutcome Anao::defender(float damage)
{
	std::uniform_int_distribution<> dist(0, 100);
	int counterChance = dist(gen);

	if (counterChance <= 65)
	{
		motivacao++;
		return DefenseOutcome::CounterAttack;
	}
	else
	{
		return Soldado::defender(damage / pow(1.005f, motivacao));
	}
}

// Humano
Humano::Humano(std::string nome, float saude, float poder, LoggerInterface& logger) : SoldadoBem(nome, saude, poder, logger) {}

float Humano::atacar(Soldado& soldado) {
	std::uniform_int_distribution<> dist(0, 100);
	int doubleAttack = dist(gen);

	if (doubleAttack <= 10) {
		motivacao++;

		float damageFirstAttack = this->performAttack(soldado).first;
		float damageSecondAttack = this->performAttack(soldado).first;

		DoubleAttackEvent event(this, &soldado, damageFirstAttack, damageSecondAttack);
		notifyObservers(event);

		return damageFirstAttack + damageSecondAttack;
	}
	else {
		return Soldado::atacar(soldado);
	}
}

// Mago
Mago::Mago(std::string nome, float saude, float poder, LoggerInterface& logger) : SoldadoBem(nome, saude, poder, logger) {}

float Mago::atacar(Soldado& soldado) {
	std::uniform_int_distribution<> dist(0, 100);
	int regen = dist(gen);

	if (regen <= 40) {
		motivacao++;
	
		saude += pow(1.005f, motivacao) * poder;

		HealthRestoredEvent event(this, saude * 0.2f);
		notifyObservers(event);

		return 0.0f;
	}
	else
	{
		return Soldado::atacar(soldado);
	}
}

// Classe do bem adicional
// Druid
std::vector<Druid*> Druid::druids = {};

Druid::Druid(std::string nome, float saude, float poder, LoggerInterface& logger) : SoldadoBem(nome, saude, poder, logger)
{
	druids.push_back(this);
}

Druid::~Druid()
{
	druids.erase(std::remove(druids.begin(), druids.end(), this), druids.end());
}

float Druid::atacar(Soldado& soldado)
{
	std::uniform_int_distribution<> dist(0, 100);
	int combinedAttack = dist(gen);

	if (combinedAttack <= 10)
	{
		logger.logToFileAndConsole("Os druidas fizeram um ataque em conjunto!");

		motivacao++;

		float totalDamage = 0.0f;

		for (Druid* druid : druids)
		{
			totalDamage += druid->Soldado::atacar(soldado);
		}

		return totalDamage;
	}

	return Soldado::atacar(soldado);
}

DefenseOutcome Druid::defender(float damage)
{
	// Druids have a hard, stone-like skin, and take less damage from attacks
	return Soldado::defender(damage / (1.5f * pow(1.005f, motivacao)));
}

// Classes do mal
// --------------
int SoldadoMal::malicia = 0;

SoldadoMal::SoldadoMal(std::string nome, float saude, float poder, LoggerInterface& logger) : Soldado(nome, saude, poder, logger) {}

// Sauron
Sauron::Sauron(std::string nome, float saude, float poder, LoggerInterface& logger) : SoldadoMal(nome, saude * 10, poder, logger) {}

float Sauron::atacar(Soldado& soldado) {
	std::uniform_int_distribution<> dist(0, 100);
	int doubleDamage = dist(gen);

	if (doubleDamage <= 30)
	{
		poder++;

		float damage = 2 * pow(1.005f, malicia) * Soldado::atacar(soldado);

		return damage;
	}
	else {
		return Soldado::atacar(soldado);
	}
}

// Orc
Orc::Orc(std::string nome, float saude, float poder, LoggerInterface& logger) : SoldadoMal(nome, saude, poder, logger) {}

float Orc::atacar(Soldado& soldado) {
	std::uniform_int_distribution<> dist(0, 100);
	int twice11Damage = dist(gen);

	if (twice11Damage <= 20) {
		return 1.1 * pow(1.005f, malicia) * Soldado::atacar(soldado) + 1.1 * pow(1.005f, malicia) * Soldado::atacar(soldado);
	}
	else {
		return Soldado::atacar(soldado);
	}
}

// Orc's too bulky! Be careful, as it may counter-attack you...
DefenseOutcome Orc::defender(float damage)
{
	std::uniform_int_distribution<> dist(0, 100);
	int swift = dist(gen);

	if (swift <= 40)
	{
		malicia++;

		return DefenseOutcome::CounterAttack;
	}
	else
	{
		return Soldado::defender(damage);
	}
}

// Classes do mal adicionais
// -------------------------
// Jester
Jester::Jester(std::string nome, float saude, float poder, LoggerInterface& logger) : SoldadoMal(nome, saude, poder, logger) {}

// Jester's humiliate is unavoidable. Beware the clown's laugh and feel miserable!
void Jester::humiliate(Soldado& soldado)
{
	float std_dev = (0.1f * soldado.getPoder() * 0.15f) / 1.645f;
	dist.param(std::normal_distribution<>::param_type(0.075f * soldado.getPoder(), std_dev));

	float debuff = dist(gen);
	debuff = clamp(debuff, 0.0f, soldado.getPoder()) * pow(1.05f, malicia);

	soldado.setPoder(soldado.getPoder() - debuff);

	PowerDebuffEvent event(this, &soldado, debuff);
	notifyObservers(event);
}

float Jester::atacar(Soldado& soldado)
{
	std::uniform_int_distribution<> dist(0, 100);
	int humiliateProb = dist(gen);

	if (humiliateProb <= 45 && soldado.getPoder() > 0)
	{
		this->humiliate(soldado);

		return 0.0f;
	}

	return Soldado::atacar(soldado);
}

// BloodMagician
BloodMagician::BloodMagician(std::string nome, float saude, float poder, LoggerInterface& logger) : SoldadoMal(nome, saude, poder, logger), thirst(1.0f) {}

std::tuple<float, DefenseOutcome, bool> BloodMagician::performAttackBlood(Soldado& soldado)
{
	std::uniform_int_distribution<> distProb(0, 100);
	int prob = distProb(gen);

	if (prob <= 25)
	{
		float std_dev = (1.2f * poder * 0.15f) / 1.645f; // Garantir que 90% dos ataques estejam na margem de +-15% de 120% do poder
		dist.param(std::normal_distribution<>::param_type(1.2f * poder, std_dev));

		float damage = dist(gen);
		damage = clamp(damage, 0.0f, poder * 2.0f);

		DefenseOutcome defenseOutcome = soldado.defender(damage);

		return std::make_tuple(damage, defenseOutcome, true);
	}
	else if (prob <= 75)
	{
		float std_dev = (0.9f * poder * 0.15f) / 1.645f; // Garantir que 90% dos ataques estejam na margem de +-15% de 90% do poder
		dist.param(std::normal_distribution<>::param_type(0.9f * poder, std_dev));

		float damage = dist(gen);
		damage = clamp(damage, 0.0f, poder * 2.0f);

		DefenseOutcome defenseOutcome = soldado.defender(damage);

		return std::make_tuple(damage, defenseOutcome, false);
	}

	float std_dev = (0.9f * poder * 0.15f) / 1.645f; // Garantir que 90% dos ataques estejam na margem de +-15% de 90% do poder
	dist.param(std::normal_distribution<>::param_type(0.9f * poder, std_dev));

	float damage = dist(gen);
	damage = clamp(damage, 0.0f, poder * 2.0f);

	DefenseOutcome defenseOutcome = soldado.defender(damage);

	return std::make_tuple(damage, defenseOutcome, false);
}

float BloodMagician::atacar(Soldado& soldado) {
	std::tuple<float, DefenseOutcome, bool> attackOutcome = performAttackBlood(soldado);

	float damage = std::get<0>(attackOutcome);
	DefenseOutcome defenseOutcome = std::get<1>(attackOutcome);

	if (defenseOutcome == DefenseOutcome::Hit)
	{
		AttackEvent event(this, &soldado, damage);
		notifyObservers(event);
		
		bool perfect = std::get<2>(attackOutcome);

		if (perfect)
		{
			++malicia;
			saude += damage * thirst * pow(1.005f, malicia);

			HealthRestoredEvent event(this, damage * thirst);
			notifyObservers(event);

			thirst = 1.0f;
		}
		else
		{
			thirst *= 1.2f;

			saude += 0.7f * damage * pow(1.005f, malicia);

			HealthRestoredEvent event(this, 0.7f * damage);
			notifyObservers(event);
		}
	}
	else if (defenseOutcome == DefenseOutcome::Dodge)
	{
		DodgeEvent event(this, &soldado);
		notifyObservers(event);

		damage = 0.0f;
	}

	return damage;
}