#pragma once

#ifndef SOLDADO_HPP
#define SOLDADO_HPP

#include "event.hpp"
#include "PrintingFiles/loggerInterface.hpp"

#include <iostream>
#include <string>
#include <random>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <tuple>
#include <cmath>

enum class DefenseOutcome
{
	Hit,
	Dodge,
	CounterAttack
};

// Soldado genérico
// ----------------
class Soldado
{
protected:
	std::string nome;
	float saude, poder;

	static std::mt19937 gen;
	std::normal_distribution<> dist;

	std::vector<EventListener*> listeners;

	LoggerInterface& logger;

	virtual std::pair<float, DefenseOutcome> performAttack(Soldado& soldado);

public:
	Soldado(std::string nome, float saude, float poder, LoggerInterface& logger);

	void addListener(EventListener* listener);

	void notifyObservers(const BattleEvent& event);

	virtual float atacar(Soldado& soldado);

	virtual DefenseOutcome defender(float damage);

	void imprimir();

	std::string getNome() const;

	float getSaude() const;

	float getPoder() const;

	void setPoder(float new_poder);

	Soldado& batalhar(Soldado& soldado);
};

// Classes do bem
// --------------
class SoldadoBem : public Soldado {
protected:
	static int motivacao;
public:
	SoldadoBem(std::string nome, float saude, float poder, LoggerInterface& logger);
};

class Elfo : public SoldadoBem {
public:
	Elfo(std::string nome, float saude, float poder, LoggerInterface& logger);

	DefenseOutcome defender(float damage) override;
};

class Anao : public SoldadoBem {
public:
	Anao(std::string nome, float saude, float poder, LoggerInterface& logger);

	float atacar(Soldado& soldado) override;

	DefenseOutcome defender(float damage) override;
};

class Humano : public SoldadoBem {
public:
	Humano(std::string nome, float saude, float poder, LoggerInterface& logger);

	float atacar(Soldado& soldado) override;
};

class Mago : public SoldadoBem {
public:
	Mago(std::string nome, float saude, float poder, LoggerInterface& logger);

	float atacar(Soldado& soldado) override;
};

// Classe do bem adicional
class Druid : public SoldadoBem
{
public:
	static std::vector<Druid*> druids;

	~Druid();

	Druid(std::string nome, float saude, float poder, LoggerInterface& logger);

	float atacar(Soldado& soldado) override;

	DefenseOutcome defender(float damage) override;
};

// Classes do mal
// --------------
class SoldadoMal : public Soldado
{
protected:
	static int malicia;
public:
	SoldadoMal(std::string nome, float saude, float poder, LoggerInterface& logger);
};

// Sauron
class Sauron : public SoldadoMal {
public:
	Sauron(std::string nome, float saude, float poder, LoggerInterface& logger);

	float atacar(Soldado& soldado) override;
};

// Orc
class Orc : public SoldadoMal {
public:
	Orc(std::string nome, float saude, float poder, LoggerInterface& logger);

	float atacar(Soldado& soldado) override;

	DefenseOutcome defender(float damage) override;
};

// Classes do mal adicionais
// -------------------------
// Jester
class Jester : public SoldadoMal
{
public:
	Jester(std::string nome, float saude, float poder, LoggerInterface& logger);

	void humiliate(Soldado& soldado);

	float atacar(Soldado& soldado) override;
};

// BloodMagician
class BloodMagician : public SoldadoMal
{
private:
	float thirst;

	std::tuple<float, DefenseOutcome, bool> performAttackBlood(Soldado& soldado);

public:
	BloodMagician(std::string nome, float saude, float poder, LoggerInterface& logger);

	float atacar(Soldado& soldado) override;
};

#endif