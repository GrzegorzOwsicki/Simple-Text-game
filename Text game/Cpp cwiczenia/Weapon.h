#pragma once
#include "utlis.h"
#include "Armor.h"
class  Weapon
{
	Wepon_Type type;
	int dmg;
public:
	Wepon_Type get_type() const;
	int get_dmg() const;
	void set_weapon_dmg(int n_dmg);

	int operator-(const Armor& armor) const;
	Weapon operator*(float multipler) const;
	void show_stats() const;

	Weapon();
	Weapon(Wepon_Type n_type, int n_dmg);
	Weapon(const Weapon& weapon);
	~Weapon();
};
