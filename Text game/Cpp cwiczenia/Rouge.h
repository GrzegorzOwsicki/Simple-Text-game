#pragma once
#include "Human.h"
class Rouge: public Human
{
	int dodge_chance;
	int doge_duration;
	const char* offensive_skill_name;
	const char* personal_skill_name;
public:
	void skill() override;
	void skill(Etnity* enemy) override;
	bool doge();
	void set_weapon(Weapon* new_weapon) override;
	void take_dmg(int dmg) override;
	void take_dmg(Weapon weapon) override;
	void ai(Etnity* enemy) override;
	void show_status() const override;
	std::ofstream& SaveToFile(std::ofstream& ofs) const;
	std::ifstream& LoadFromFile(std::ifstream& ifs) override;

	Rouge(int doge_chance = 0, int doge_duration = 0, const char* skill_name = "Trucizna", const char* skill_name_2 = "Unik",
		Armor* armor = new Armor(None, 0, 0), Weapon* weapon = new Weapon(Fist, 10),
		int max_sp = 3, int sp = 3);
};

