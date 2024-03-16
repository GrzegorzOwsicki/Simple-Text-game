#pragma once
#include "utlis.h"
class Armor
{
	Armor_Type type;
	int def;
	int bonus_hp;

public:
	Armor_Type get_type() const;
	int get_def() const;
	int get_bonus_hp() const;
	void show_stats() const;
	Armor();
	Armor(Armor_Type n_type, int n_def, int n_bonus_hp);
	Armor(const Armor& armor);
	~Armor();
};
