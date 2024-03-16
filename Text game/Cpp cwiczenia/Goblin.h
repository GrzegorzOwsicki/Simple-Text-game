#pragma once
#include "Etnity.h"
class Goblin: public Etnity
{
	Weapon* weapon;
	Armor* armor;
public:
	void attack(Etnity* enemy) override;
	void take_dmg(Weapon weapon) override;
	void take_dmg(int dmg) override;
	void set_armor(Armor* armor) override;
	void set_weapon(Weapon* new_weapon) override;
	void show_status() const override;
	void controls(char key,Etnity* enemy) override;
	void ai(Etnity* enemy) override;
	Weapon* get_weapon();
	Armor* get_armor();
	std::ofstream& SaveToFile(std::ofstream& ofs) const;
	std::ifstream& LoadFromFile(std::ifstream& ifs) override;

	Goblin(Armor* armor = new Armor(None, 0, 0), Weapon* weapon = new Weapon(Fist, 10),
		int hp = 50, int max_hp = 50, bool poison_effect = false,
		int poison_duration = 0, bool stunn_effect = false, int stunn_duration = 0);
	~Goblin() override;
};

