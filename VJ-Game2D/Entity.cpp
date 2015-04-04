#include "Entity.h"


Entity::Entity()
{
	killsPlayer = true;
}


Entity::~Entity()
{
}

void Entity::Kill() {
	bicho->dying = true;
	killsPlayer = false;
}

void Entity::Hurt() {
	bicho->Hurt();
}