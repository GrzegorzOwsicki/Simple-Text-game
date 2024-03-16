#include "Cleric.h"

void Cleric::skill() {
	std::cout << this->get_name() << " leczy sie" << std::endl;
	if (this->get_hp() + std::ceil(this->get_max_hp() * 0.1) > this->get_max_hp()) this->set_hp(this->get_max_hp());
	else this->set_hp(this->get_hp() + ceil(this->get_max_hp() * 0.1));
	this->change_sp(false);
}

void Cleric::skill(Etnity* enemy) {
	std::cout << "Kleryk odmawia u¿ycia swojej umiejêtnoœci do walki" << std::endl;
}

Cleric::Cleric(const char* skill_name, const char* skill_name_2,
	Armor* armor , Weapon* weapon,
	int max_sp, int sp):
	offensive_skill_name(skill_name),
	personal_skill_name(skill_name_2)
{
	set_name("Kleryk");
	set_armor(armor);
	set_weapon(weapon);
	set_sp(sp);
	set_max_sp(max_sp);
}

void Cleric::ai(Etnity* enemy)
{
	if(this->get_hp() < this->get_max_hp() * 0.5 && this->get_sp() > 0) {
		this->skill();
	}
	else
	{
		this->attack(enemy);
	}
}




std::ofstream& Cleric::SaveToFile(std::ofstream& ofs) const
{
	ofs << "Kleryk" << std::endl;
	ofs << this->get_hp() << std::endl;
	ofs << this->get_sp() << std::endl;
	ofs << this->get_poison_status() << std::endl;
	ofs << this->get_poison_duration()<< std::endl;
	ofs << this->get_stunn_status() << std::endl;
	ofs << this->get_stunn_duration() << std::endl;
	ofs << this->get_weapon()->get_type() << std::endl;
	ofs << this->get_weapon()->get_dmg() << std::endl;
	ofs << this->get_armor()->get_type() << std::endl;
	ofs << this->get_armor()->get_def() << std::endl;
	ofs << this->get_armor()->get_bonus_hp() << std::endl;

	return ofs;
}

std::ifstream& Cleric::LoadFromFile(std::ifstream& ifs)
{
	Wepon_Type weapon_type;
	Armor_Type armor_type;

	int input;
	ifs >> input;
	this->set_hp(input);
	ifs >> input;
	this->set_sp(input);
	ifs >> input;
	this->set_poison_status(input);
	ifs >> input;
	this->set_poison_duration(input);
	ifs >> input;
	this->set_stunn_status(input);
	ifs >> input;
	this->set_stunn_duration(input);
	ifs >> input;
	weapon_type = static_cast<Wepon_Type>(input);
	ifs >> input;
	Weapon* weapon = new Weapon(weapon_type, input);
	ifs >> input;
	armor_type = static_cast<Armor_Type>(input);
	ifs >> input;
	int bonus_hp;
	ifs >> bonus_hp;
	Armor* armor = new Armor(armor_type, input, bonus_hp);
	this->set_armor(armor);
	this->set_weapon(weapon);

	return ifs;
}

void Cleric::set_weapon(Weapon* new_weapon) {
	if (new_weapon->get_type() == Sword) {
		std::cout << "zmiana niedozwolona" << std::endl;
		return;
	}
	this->set_weapon2(new_weapon);
}
