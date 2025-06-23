#include "Enemy.h"

void Enemy::reset_poss_after_strike() {
	poss.set_xy(start_poss_x, start_poss_y);
}
