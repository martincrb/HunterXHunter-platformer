#include "Entity.h"


Entity::Entity()
{

}


Entity::~Entity()
{
}

void Entity::Kill() {
	bicho->alive = false;
}

void Entity::Hurt() {
	bicho->Hurt();
}