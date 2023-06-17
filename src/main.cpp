#include "../include/soldado.hpp"
#include "../include/PrintingFiles/battleprinter.hpp"
#include "../include/ArmyBuilding/armyBuilder.hpp"
#include "../include/battlefield.hpp"

int main() {
	// Setar a seed para o programa
	srand(static_cast<unsigned>(time(NULL)));

	BattlePrinter printer;
	ArmyBuilder builder;

	std::vector<SoldadoBem*> armyBem = builder.buildArmyBem("data/army_bem.txt", printer);
	std::vector<SoldadoMal*> armyMal = builder.buildArmyMal("data/army_mal.txt", printer);
	
	Battlefield battlefield(printer, armyBem, armyMal);

	battlefield.battle();

	return 0;
}