#pragma once
#include "Human.h"
class Cleric: public Human
{
	const char* offensive_skill_name;
	const char* personal_skill_name;
public:
	void skill() override;
	void skill(Etnity* enemy) override;
	void set_weapon(Weapon* new_weapon) override;
	void ai(Etnity* enemy) override;
	std::ofstream& SaveToFile(std::ofstream& ofs) const;
	std::ifstream& LoadFromFile(std::ifstream& ifs) override;

	Cleric(const char* skill_name = "Brak", const char* skill_name_2 = "Leczenie",
		Armor* armor = new Armor(None, 0, 0), Weapon* weapon = new Weapon(Fist, 10),
		int max_sp = 5, int sp = 5);
};

