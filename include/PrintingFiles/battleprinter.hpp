#pragma once

#ifndef BATTLEPRINTER_HPP
#define BATTLEPRINTER_HPP

#include "../soldado.hpp"
#include "fileLogger.hpp"

class BattlePrinter : public EventListener
{
public:
	FileLogger logger;

	void onEvent(const BattleEvent& event) override;
};

#endif