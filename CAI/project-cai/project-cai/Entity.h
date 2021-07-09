#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class Entity
{
public:

	Entity();
	Entity(float _health);
	virtual ~Entity();

	void Damage(float dmgAmount);
	void Heal(float healAmount);

	void Die();

protected:

	bool alive;
	float maxHealth;
	float health;
};

#endif // !ENTITY_H
