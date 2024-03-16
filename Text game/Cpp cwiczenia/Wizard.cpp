#include "Wizard.h"

void Wizard::skill(Etnity* enemy){
	std::cout << this->get_name() << " ciska kule ognia" << std::endl;
	enemy->take_dmg(*this->get_weapon()* 2);
	this->change_sp(false);
}

void Wizard::skill(){
	std::cout << this->get_name() << " medytuje" << std::endl;
	if (this->get_sp() < get_max_sp()){
		this->change_sp(true);
	}
	else
	{
		std::cout << "maksymalne sp" << std::endl;
	}
}

void Wizard::set_armor(Armor* new_armor){
	if (new_armor->get_type() == Heavy) {
		std::cout << "zmiana niedozwolona" << std::endl;
		return;
	}
	this->set_armor2(new_armor);
}

void Wizard::ai(Etnity* enemy)
{
	if (this->get_hp() > this->get_max_hp() * 0.5) {
		if (this->get_sp() > 0) {
			this->skill(enemy);
		}
		else
		{
			this->skill();
		}
	}
	else
	{
		this->attack(enemy);
	}
}

std::ofstream& Wizard::SaveToFile(std::ofstream& ofs) const
{
	ofs << "Mag" << std::endl;
	ofs << this->get_max_hp() << std::endl;
	ofs << this->get_hp() << std::endl;
	ofs << this->get_max_sp() << std::endl;
	ofs << this->get_sp() << std::endl;
	ofs << this->get_poison_status() << std::endl;
	ofs << this->get_poison_duration() << std::endl;
	ofs << this->get_stunn_status() << std::endl;
	ofs << this->get_stunn_duration() << std::endl;
	ofs << this->get_weapon()->get_type() << std::endl;
	ofs << this->get_weapon()->get_dmg() << std::endl;
	ofs << this->get_armor()->get_type() << std::endl;
	ofs << this->get_armor()->get_def() << std::endl;
	ofs << this->get_armor()->get_bonus_hp() << std::endl;

	return ofs;
}

std::ifstream& Wizard::LoadFromFile(std::ifstream& ifs)
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
	ifs >> input;
	ifs >> input;
	this->set_armor(armor);
	this->set_weapon(weapon);

	return ifs;
}

Wizard::Wizard(const char* skill_name, const char* skill_name_2 , Armor* armor,
	Weapon* weapon,int max_sp, int sp)
	:offensive_skill_name(skill_name),
	personal_skill_name(skill_name_2)
{
	set_name("Mag");
	set_armor(armor);
	set_weapon(weapon);
	set_sp(sp);
	set_max_sp(max_sp);
};
