#pragma once
#include "Etnity.h"
class Golem: public Etnity
{
	Armor* rocks;
	int dmg;
public:
	void attack(Etnity* enemy) override;
	void take_dmg(Weapon weapon) override;
	void take_dmg(int dmg) override;
	void set_armor(Armor* armor) override;
	void set_weapon(Weapon* new_weapon) override;
	void show_status() const override;
	void ai(Etnity* enemy) override;
	void stunn() override ;
	void poison() override;
	void controls(char key, Etnity* enemy) override;
	Armor* get_armor();
	std::ofstream& SaveToFile(std::ofstream& ofs) const;
	std::ifstream& LoadFromFile(std::ifstream& ifs) override;

	Golem(Armor* armor = new Armor(None, 0, 0), Weapon* weapon = new Weapon(Fist, 10),
		int hp = 100, int max_hp = 100, bool poison_effect = false,
		int poison_duration = 0, bool stunn_effect = false, int stunn_duration = 0);
	~Golem() override;
};

