#include "../../include/ArmyBuilding/armyBuilder.hpp"

ArmyBuilder::ArmyBuilder() {}

ClassesSoldadoBem ArmyBuilder::stringToEnumBem(const std::string& type)
{
    static std::unordered_map<std::string, ClassesSoldadoBem> converter =
    {
        {"Elfo", ClassesSoldadoBem::Elfo},
        {"Anao", ClassesSoldadoBem::Anao},
        {"Humano", ClassesSoldadoBem::Humano},
        {"Mago", ClassesSoldadoBem::Mago},
        {"Druid", ClassesSoldadoBem::Druid},
    };

    return converter[type];
}

ClassesSoldadoMal ArmyBuilder::stringToEnumMal(const std::string& type)
{
    static std::unordered_map<std::string, ClassesSoldadoMal> converter =
    {
        {"Sauron", ClassesSoldadoMal::Sauron},
        {"Orc", ClassesSoldadoMal::Orc},
        {"Jester", ClassesSoldadoMal::Jester},
        {"BloodMagician", ClassesSoldadoMal::BloodMagician},
    };

    return converter[type];
}

std::vector<SoldadoBem*> ArmyBuilder::buildArmyBem(const std::string& filename, BattlePrinter& printer)
{
    std::vector<SoldadoBem*> army;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Falha ao abrir o arquivo " << filename << std::endl;
        return army;
    }

    std::unordered_map<ClassesSoldadoBem, int> counter;

    std::string type;
    float saude;
    float poder;
    int quantity;

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string type, saude_str, poder_str, quantity_str;

        std::getline(iss, type, '/');
        std::getline(iss, saude_str, '/');
        std::getline(iss, poder_str, '/');
        std::getline(iss, quantity_str);

        float saude = std::stof(saude_str);
        float poder = std::stof(poder_str);
        int quantity = std::stoi(quantity_str);

        ClassesSoldadoBem classType = stringToEnumBem(type);

        for (int i = 0; i < quantity; ++i)
        {
            SoldadoBem* soldado = factory.createSoldadoBem(type, type + " " + std::to_string(counter[classType]++ + 1), saude, poder, printer.logger);
            soldado->addListener(&printer);

            army.push_back(soldado);
        }
    }

    return army;
}

std::vector<SoldadoMal*> ArmyBuilder::buildArmyMal(const std::string& filename, BattlePrinter& printer)
{
    std::vector<SoldadoMal*> army;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Failed to open the file " << filename << std::endl;
        return army;
    }

    std::unordered_map<ClassesSoldadoMal, int> counter;

    std::string type;
    float saude;
    float poder;
    int quantity;

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string type, saude_str, poder_str, quantity_str;

        std::getline(iss, type, '/');
        std::getline(iss, saude_str, '/');
        std::getline(iss, poder_str, '/');
        std::getline(iss, quantity_str);

        float saude = std::stof(saude_str);
        float poder = std::stof(poder_str);
        int quantity = std::stoi(quantity_str);

        ClassesSoldadoMal classType = stringToEnumMal(type);

        for (int i = 0; i < quantity; ++i)
        {
            SoldadoMal* soldado = factory.createSoldadoMal(type, type + " " + std::to_string(counter[classType]++ + 1), saude, poder, printer.logger);
            soldado->addListener(&printer);

            army.push_back(soldado);
        }
    }

    return army;
}