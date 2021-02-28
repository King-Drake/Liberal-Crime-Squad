#pragma once
/* attack handling for each side as a whole */
void youattack();
void enemyattack();
/* kills the specified creature from the encounter, dropping loot */
void delenc(short e, char loot);
/* pushes people into the current squad (used in a siege) */
void autopromote(int loc);
