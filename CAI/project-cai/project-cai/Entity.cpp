#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(float _health)
{
	alive = true;
	maxHealth = _health;
	health = maxHealth;
}

Entity::~Entity()
{
}

void Entity::Damage(float dmgAmount)
{
	health -= dmgAmount;
	if (health <= 0) Die();
}

void Entity::Heal(float healAmount)
{
	health += healAmount;
	if (health > maxHealth) health = maxHealth;
}

void Entity::Die()
{
	alive = false;

	delete this;
}
