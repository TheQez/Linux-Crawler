#include "entity.h"

void Entity::damage(int damage) {
    currentHitpoints -= damage;
    if(currentHitpoints <= 0) {
	isDead = true;
    }
}
