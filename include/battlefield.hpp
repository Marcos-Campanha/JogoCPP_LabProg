#pragma once

#ifndef BATTLEFIELD_HPP
#define BATTLEFIELD_HPP

#include <vector>
#include "../include/PrintingFiles/battleprinter.hpp"
#include "../include/soldado.hpp"

class Battlefield
{
private:
	std::vector<SoldadoBem*> armyBem;
	std::vector<SoldadoMal*> armyMal;
	
	std::vector<SoldadoBem*> armyBemUsed;
	std::vector<SoldadoMal*> armyMalUsed;

	std::mt19937 gen;

	BattlePrinter& printer;
	
	static int turn;

	void removeDeadSoldiersFromClassVectors();
public:
	Battlefield(BattlePrinter& printer, std::vector<SoldadoBem*> armyBem, std::vector<SoldadoMal*> armyMal);

	void battle();
};

#endif