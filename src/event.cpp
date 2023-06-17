#include "../include/event.hpp"

BattleEvent::~BattleEvent() {}

AttackEvent::AttackEvent(Soldado* actor, Soldado* target, float damage) : damage(damage)
{
	this->actor = actor;
	this->target = target;
}

DoubleAttackEvent::DoubleAttackEvent(Soldado* actor, Soldado* target, float damageFirstAttack, float damageSecondAttack) : damageFirstAttack(damageFirstAttack), damageSecondAttack(damageSecondAttack) 
{
	this->actor = actor;
	this->target = target;
}

HealthRestoredEvent::HealthRestoredEvent(Soldado* actor, float healthRestored) : healthRestored(healthRestored)
{
	this->actor = actor;
}

MissedAttackEvent::MissedAttackEvent(Soldado* actor)
{
	this->actor = actor;
}

PowerDebuffEvent::PowerDebuffEvent(Soldado* actor, Soldado* target, float debuff) : debuff(debuff)
{
	this->actor = actor;
	this->target = target;
}

DodgeEvent::DodgeEvent(Soldado* actor, Soldado* target)
{
	this->actor = actor;
	this->target = target;
}

CounterAttackEvent::CounterAttackEvent(Soldado* actor, Soldado* target, float damage) : damage(damage)
{
	this->actor = actor;
	this->target = target;
}

EventListener::~EventListener() {}