#include "../include/battlefield.hpp"

int Battlefield::turn = 1;

void Battlefield::removeDeadSoldiersFromClassVectors()
{
    // Só os druidas têm tal funcionalidade, por ora
    std::vector<Druid*>::iterator druidIt;
    for (druidIt = Druid::druids.begin(); druidIt != Druid::druids.end();)
    {
        if ((*druidIt)->getSaude() <= 1e-3)
        {
            druidIt = Druid::druids.erase(druidIt);
        }
        else
        {
            ++druidIt;
        }
    }
}

Battlefield::Battlefield(BattlePrinter& printer, std::vector<SoldadoBem*> armyBem, std::vector<SoldadoMal*> armyMal)
    : printer(printer), armyBem(armyBem), armyMal(armyMal), gen(std::random_device{}()) {}

void Battlefield::battle()
{
    while (!armyBem.empty() && !armyMal.empty())
    {
        if (turn > 1)
        {
            printer.logger.logToFileAndConsoleNoBreak("\n");
        }

        printer.logger.logToFileAndConsole("##### Composicao dos Exercitos #####");

        printer.logger.logToFileAndConsole("\n### Exercito do Bem ###");
        std::vector<SoldadoBem*>::iterator itArmyBem;
        for (itArmyBem = armyBem.begin(); itArmyBem != armyBem.end(); ++itArmyBem)
        {
            (*itArmyBem)->imprimir();
        }
        for (itArmyBem = armyBemUsed.begin(); itArmyBem != armyBemUsed.end(); ++itArmyBem)
        {
            (*itArmyBem)->imprimir();
        }

        printer.logger.logToFileAndConsole("\n### Exercito do Mal");
        std::vector<SoldadoMal*>::iterator itArmyMal;
        for (itArmyMal = armyMal.begin(); itArmyMal != armyMal.end(); ++itArmyMal)
        {
            (*itArmyMal)->imprimir();
        }
        for (itArmyMal = armyMalUsed.begin(); itArmyMal != armyMalUsed.end(); ++itArmyMal)
        {
            (*itArmyMal)->imprimir();
        }

        std::uniform_int_distribution<> distBem(0, armyBem.size() - 1);
        std::uniform_int_distribution<> distMal(0, armyMal.size() - 1);
        int idxBem = distBem(gen);
        int idxMal = distMal(gen);

        SoldadoBem* soldadoBem = armyBem[idxBem];
        SoldadoMal* soldadoMal = armyMal[idxMal];

        armyBem.erase(armyBem.begin() + idxBem);
        armyMal.erase(armyMal.begin() + idxMal);
        armyBemUsed.push_back(soldadoBem);
        armyMalUsed.push_back(soldadoMal);

        printer.logger.logToFileAndConsoleNoBreak("\n##### Confronto " + std::to_string(turn++) + " #####");

        Soldado* winner = &(soldadoBem->batalhar(*soldadoMal));
        
        if (winner == soldadoBem)
        {
            armyMalUsed.pop_back();
            removeDeadSoldiersFromClassVectors();
        }
        else
        {
            armyBemUsed.pop_back();
            removeDeadSoldiersFromClassVectors();
        }

        if (armyBem.empty())
        {
            armyBem = armyBemUsed;
            armyBemUsed.clear();
        }
        if (armyMal.empty())
        {
            armyMal = armyMalUsed;
            armyMalUsed.clear();
        }
    }

    if (!armyBem.empty())
    {
        printer.logger.logToFileAndConsole("\n### O Exercito do Bem venceu a batalha! ###");
    }
    else
    {
        printer.logger.logToFileAndConsole("\n### O Exercito do Mal venceu a batalha! ###");
    }
}