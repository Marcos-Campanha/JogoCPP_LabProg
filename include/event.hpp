#pragma once

#ifndef EVENT_HPP
#define EVENT_HPP

class Soldado; // Forward declaration

// Keep track of battle actions (damage dealt, hp restored...)
// -----------------------------------------------------------
class BattleEvent
{
public:
	Soldado* actor;
	Soldado* target;

	virtual ~BattleEvent();
};

class AttackEvent : public BattleEvent
{
public:
	float damage;

	AttackEvent(Soldado* actor, Soldado* target, float damage);
};

class DoubleAttackEvent : public BattleEvent
{
public:
	float damageFirstAttack;
	float damageSecondAttack;

	DoubleAttackEvent(Soldado* actor, Soldado* target, float damageFirstAttack, float damageSecondAttack);
};

class HealthRestoredEvent : public BattleEvent
{
public:
	float healthRestored;

	HealthRestoredEvent(Soldado* actor, float healthRestored);
};

class MissedAttackEvent : public BattleEvent
{
public:
	MissedAttackEvent(Soldado* actor);
};

class PowerDebuffEvent : public BattleEvent
{
public:
	float debuff;

	PowerDebuffEvent(Soldado* actor, Soldado* target, float debuff);
};

class DodgeEvent : public BattleEvent
{
public:
	DodgeEvent(Soldado* actor, Soldado* target);
};

class CounterAttackEvent : public BattleEvent
{
public:
	float damage;

	CounterAttackEvent(Soldado* actor, Soldado* target, float damage);
};

class EventListener
{
public:
	virtual ~EventListener();

	virtual void onEvent(const BattleEvent& event) = 0;
};

#endif