#pragma once
#include <iostream>
#include "Cleric.h"
#include"Fighter.h"
#include"Rouge.h"
#include"Wizard.h"
#include"Goblin.h"
#include"Golem.h"
#include"Plant.h"
#include"Wolf.h"

void character_select();

void simulate_game(Etnity* player, Etnity* enemy,int score);

Etnity* choose_enemy();

Weapon* generate_weapon(int score);
Armor* generate_armor(int score);
void load_game();