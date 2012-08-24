#include "entity.h"

int Entity::id_next = 0;

Entity::Entity() {
	this->id    = id_next++;
	printf("default Constructor\n");
}

/*Entity::Entity(Entity &e) {
	this->id    = id_next++;
	printf("Copy Constructor\n");
}*/