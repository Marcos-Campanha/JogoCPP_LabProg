#pragma once

#ifndef ARMYBUILDER_HPP
#define ARMYBUILDER_HPP

#include "soldadoFactory.hpp"
#include "../soldado.hpp"
#include "../PrintingFiles/battleprinter.hpp"

#include <vector>
#include <fstream>
#include <unordered_map>

enum class ClassesSoldadoBem
{
	Elfo,
	Anao,
	Humano,
	Mago,
	Druid
};

enum class ClassesSoldadoMal
{
	Sauron,
	Orc,
	Jester,
	BloodMagician
};

class ArmyBuilder
{
private:
	SoldadoFactory factory;

	ClassesSoldadoBem stringToEnumBem(const std::string& type);
	ClassesSoldadoMal stringToEnumMal(const std::string& type);

public:
	ArmyBuilder();

	std::vector<SoldadoBem*> buildArmyBem(const std::string& filename, BattlePrinter& printer);
	std::vector<SoldadoMal*> buildArmyMal(const std::string& filename, BattlePrinter& printer);
};

#endif