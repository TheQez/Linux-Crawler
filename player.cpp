#include "player.h"

Player::Player (int x, int y, int current, int max, int dam) {
    xPos = x;
    yPos = y;
    currentHitpoints = current;
    maxHitpoints = max;
    meleeDamage = dam;
}
