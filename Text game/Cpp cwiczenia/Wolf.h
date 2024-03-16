#pragma once
#include "Etnity.h"
class Wolf: public Etnity
{
	int defense;
	Weapon* fangs;
public:
	
	void attack(Etnity* enemy) override;
	void take_dmg(Weapon weapon) override;
	void take_dmg(int dmg) override;
	void show_status() const override;
	void set_armor(Armor* armor) override;
	void set_weapon(Weapon* weapon) override;
	void ai(Etnity* enemy) override;
	void controls(char key, Etnity* enemy) override;
	std::ofstream& SaveToFile(std::ofstream& ofs) const;
	std::ifstream& LoadFromFile(std::ifstream& ifs) override;

	Wolf(Armor* armor = new Armor(None, 0, 0), Weapon* weapon = new Weapon(Fist, 10),
	 int hp = 50, int max_hp = 50, bool poison_effect = false,
	int poison_duration = 0, bool stunn_effect = false, int stunn_duration = 0);
	~Wolf() override;
};

