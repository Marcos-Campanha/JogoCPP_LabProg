#include "../../include/ArmyBuilding/soldadoFactory.hpp"

SoldadoBem* SoldadoFactory::createSoldadoBem(const std::string& type, const std::string& nome, float saude, float poder, LoggerInterface& logger)
{
	if (type == "Elfo")
	{
		return new Elfo(nome, saude, poder, logger);
	}
	else if (type == "Anao")
	{
		return new Anao(nome, saude, poder, logger);
	}
	else if (type == "Humano")
	{
		return new Humano(nome, saude, poder, logger);
	}
	else if (type == "Mago")
	{
		return new Mago(nome, saude, poder, logger);
	}
	else if (type == "Druid")
	{
		return new Druid(nome, saude, poder, logger);
	}
	else
	{
		return nullptr;
	}
}

SoldadoMal* SoldadoFactory::createSoldadoMal(const std::string& type, const std::string &nome, float saude, float poder, LoggerInterface& logger)
{
	if (type == "Sauron")
	{
		return new Sauron(nome, saude, poder, logger);
	}
	else if (type == "Orc")
	{
		return new Orc(nome, saude, poder, logger);
	}
	else if (type == "Jester")
	{
		return new Jester(nome, saude, poder, logger);
	}
	else if (type == "BloodMagician")
	{
		return new BloodMagician(nome, saude, poder, logger);
	}
	else
	{
		return nullptr;
	}
}
