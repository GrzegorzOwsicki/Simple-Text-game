#pragma once
#include "Etnity.h"
#include "Armor.h"
#include "Weapon.h"
class Human:public Etnity
{
	Armor* used_armor;
	Weapon* used_wepon;
	int max_sp;
	int sp;
public:
	Armor* get_armor() const;
	Weapon* get_weapon() const;
	virtual void skill() = 0;
	virtual void skill(Etnity* enemy) = 0;

	void take_dmg(Weapon weapon) override;
	void take_dmg(int dmg) override;
	void set_weapon(Weapon* new_weapon) override;
	void set_armor(Armor* new_armor) override;
	void set_weapon2(Weapon* new_weapon);
	void set_armor2(Armor* new_armor);
	void show_status() const override;
	void attack(Etnity* enemy) override;
	void controls(char key, Etnity* enemy);
	int get_sp() const;
	int get_max_sp() const;
	void change_sp(bool add);
	void set_max_sp(int sp);
	void set_sp(int sp);

	Human(Armor* armor = new Armor(None,0,0), Weapon* weapon = new Weapon(Fist, 10), int max_sp = 3, int sp = 3, int hp = 100, int max_hp = 100);
	~Human() override;
};
