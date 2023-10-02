# LOTR Project in C++, LabProg I

This repository contains an implementation of a random auto-battler in OOP C++. The battle happens between two armies: Good and Evil, each of which contains different classes and soldiers who fight each other in turns.

## Army creation

The soldiers for the Good and Evil Armies are created, respectively, by reading the files *data/army_bem.txt* and *data/army_mal.txt*, as follows:

### **Name of the class/Health Points/Power/Quantity**

- Example: **Sauron/100/10/2** creates 2 Saurons with 100 HP and 10 Power each.

> **Note**: The file paths are relative to the directory LOTR_LabProg_I (In Visual Studio, by default, the path is relative to the .sln file).
> To avoid file reading issues, just configure the paths in your IDE, or modify the paths in the main() function located in *src/main.cpp*.

> std::vector<SoldadoBem*> armyBem = builder.buildArmyBem("data/army_bem.txt", printer);
> 
> std::vector<SoldadoMal*> armyMal = builder.buildArmyMal("data/army_mal.txt", printer);

## Types of classes (Good vs. Evil)

Good Army classes are: ***Elfo***, ***Anão***, ***Humano***, ***Mago*** e ***Druid*** (***Elf***, ***Dwarf***, ***Human***, ***Wizard***, ***Druid***).

Evil Army classes are: ***Sauron***, ***Orc***, ***Jester*** e ***BloodMagician*** (***Sauron***, ***Orc***, ***Jester***, ***BloodMagician***).

## Battle between armies

Before each fight, each army's state (alive soldiers, HP and Power) are printed on the screen and a new fight is announced between a good soldier and an evil soldier.

After the end of the fight, a new fight is announced, prioritizing the soldiers who haven't fought yet, until one of the armies is completely eliminated.

Actions from each turn are also displayed on the screen.

> All actions and the entire battle information are saved in the file *data/battle_log.txt*.
