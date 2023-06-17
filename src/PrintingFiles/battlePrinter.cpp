#include "../../include/PrintingFiles/battleprinter.hpp"

void BattlePrinter::onEvent(const BattleEvent& event)
{
	if (const AttackEvent* attackEvent = dynamic_cast<const AttackEvent*>(&event))
	{
		std::stringstream ss; float damage = std::round(attackEvent->damage * 100) / 100; ss << std::fixed << std::setprecision(2) << damage; std::string damage_str = ss.str();
		logger.logToFileAndConsole(attackEvent->actor->getNome() + " atacou " + attackEvent->target->getNome() + " para um total de " + damage_str + " de dano");
	}
	else if (const DoubleAttackEvent* dAttackEvent = dynamic_cast<const DoubleAttackEvent*>(&event))
	{
		std::stringstream ss; float damage = std::round((dAttackEvent->damageFirstAttack + dAttackEvent->damageSecondAttack) * 100) / 100; ss << std::fixed << std::setprecision(2) << damage; std::string damage_str = ss.str();
		logger.logToFileAndConsole(dAttackEvent->actor->getNome() + " realizou um ataque duplo em " + dAttackEvent->target->getNome() + " para um total de " + damage_str + " de dano");
	}
	else if (const HealthRestoredEvent* healthEvent = dynamic_cast<const HealthRestoredEvent*>(&event))
	{
		std::stringstream ss; float healthRestored = std::round(healthEvent->healthRestored * 100) / 100; ss << std::fixed << std::setprecision(2) << healthRestored; std::string healthRestored_str = ss.str();
		logger.logToFileAndConsole(healthEvent->actor->getNome() + " recuperou " + healthRestored_str + " pontos de vida");
	}
	else if (const MissedAttackEvent* missedEvent = dynamic_cast<const MissedAttackEvent*>(&event))
	{
		logger.logToFileAndConsole(missedEvent->actor->getNome() + " errou o ataque");
	}
	else if (const PowerDebuffEvent* pDebuffEvent = dynamic_cast<const PowerDebuffEvent*>(&event))
	{
		std::stringstream ss; float debuff = std::round(pDebuffEvent->debuff * 100) / 100; ss << std::fixed << std::setprecision(2) << debuff; std::string debuff_str = ss.str();
		logger.logToFileAndConsole(pDebuffEvent->actor->getNome() + " reduziu o poder de " + pDebuffEvent->target->getNome() + " em " + debuff_str);
	}
	else if (const DodgeEvent* dodgeEvent = dynamic_cast<const DodgeEvent*>(&event))
	{
		logger.logToFileAndConsole("Ops! " + dodgeEvent->target->getNome() + " desviou do ataque de " + dodgeEvent->actor->getNome() + " e nao tomou dano");
	}
	else if (const CounterAttackEvent* counterAttackEvent = dynamic_cast<const CounterAttackEvent*>(&event))
	{
		std::stringstream ss; float damage = std::round(counterAttackEvent->damage * 100) / 100; ss << std::fixed << std::setprecision(2) << damage; std::string damage_str = ss.str();
		logger.logToFileAndConsole(counterAttackEvent->target->getNome() + " bloqueou o ataque de " + counterAttackEvent->actor->getNome() + " e o contra-atacou, causando " + damage_str + " de dano");
	}
}