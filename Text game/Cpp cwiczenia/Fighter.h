#pragma once
#include "Human.h"

class Fighter:public Human
{
	float dmg_reduction;
	int block_duration;
	const char* offensive_skill_name;
	const char* personal_skill_name;
	
public:
	float get_dmg_reduction() const;
	int get_block_duration() const;
	void take_dmg(Weapon weapon) override;
	void take_dmg(int dmg) override;
	void skill() override;
	void skill(Etnity* enemy) override;
	void ai(Etnity* enemy) override;
	void show_status() const;
	std::ofstream& SaveToFile(std::ofstream& ofs) const;
	std::ifstream& LoadFromFile(std::ifstream& ifs) override;

	Fighter(float dmg_reduction = 1, int block_duration = 0, const char* skill_name = "blok",
		const char* skill_name_2 = "og³uszaj¹ce uderzenie",
		Armor* armor = new Armor(None, 0, 0), Weapon* weapon = new Weapon(Fist, 10),
		int max_sp = 5, int sp = 5);
};

