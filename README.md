# LOTR Project in C++, LabProg I

This repository contains an implementation of a random auto-battler in C++. The battle happens between two armies: Good and Evil, each of which contains different classes and soldiers who fight each other in turns.

## Army creation

Os soldados são criados a partir da leitura dos arquivos *data/army_bem.txt* e *data/army_mal.txt*, seguindo o seguinte padrão:
The soldiers for the Good and Evil Armies are created, respectively, by reading the files *data/army_bem.txt* and *data/army_mal.txt*, as follows:

### **Name of the class/Health Points/Power/Quantity**

- Example: **Sauron/100/10/2** creates 2 Saurons with 100 HP and 10 Power each

> **Note**: The file paths are relative to the directory LOTR_LabProg_I (In Visual Studio, by default, the path is relative to the .sln file).
> To avoid problems related to file reading, just configure the paths on your IDE or change the paths in main() function, at *src/main.cpp*

> std::vector<SoldadoBem*> armyBem = builder.buildArmyBem("data/army_bem.txt", printer);
> 
> std::vector<SoldadoMal*> armyMal = builder.buildArmyMal("data/army_mal.txt", printer);

## Types of classes (Good x Evil)

Good Army classes are: ***Elfo***, ***Anão***, ***Humano***, ***Mago*** e ***Druid***

Evil Army classes are: ***Sauron***, ***Orc***, ***Jester*** e ***BloodMagician***

## Battle between armies

Before each fight, each army's state (alive soldiers, HP e Power) are printed on the screen and a new fight is announced between a good soldier and an evil soldier.

After the end of the fight, a new fight is announced, prioritizing the soldiers who haven't fought yet, until one of the armies gets completely eliminated.

Each turn's actions are also presented on the screen.

> All actions and the whole battle informations are saved on the file *data/battle_log.txt*
