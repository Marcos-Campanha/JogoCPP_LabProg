#pragma once

#ifndef SOLDADOFACTORY_HPP
#define SOLDADOFACTORY_HPP

#include <string>
#include "../soldado.hpp"

class SoldadoFactory
{
public:
	SoldadoBem* createSoldadoBem(const std::string& type, const std::string& nome, float saude, float poder, LoggerInterface& logger);
	SoldadoMal* createSoldadoMal(const std::string& type, const std::string& nome, float saude, float poder, LoggerInterface& logger);
};

#endif