#pragma once
#include "Human.h"
class Wizard:public Human
{
	const char* offensive_skill_name;
	const char* personal_skill_name;
public:
	void skill(Etnity* enemy) override;
	void skill() override;
	void set_armor(Armor* new_armor) override;
	void ai(Etnity* enemy) override;
	std::ofstream& SaveToFile(std::ofstream& ofs) const;
	std::ifstream& LoadFromFile(std::ifstream& ifs) override;

	Wizard(const char* skill_name = "Kula ognia", const char* skill_name_2 = "Medytacja",
		Armor* armor = new Armor(None, 0, 0), Weapon* weapon = new Weapon(Fist, 10), int max_sp = 3, int sp =3);
};

