#include "Armor.h"

Armor::Armor() {
	type = None;
	def = 0;
	bonus_hp = 0;
}

Armor::Armor(Armor_Type n_type, int n_def, int n_bonus_hp):type(n_type),
	def(n_def),
	bonus_hp(n_bonus_hp){}

Armor::Armor(const Armor& armor)
{
	this->def = armor.get_def();
	this->bonus_hp = armor.get_bonus_hp();
	this->type = armor.get_type();
}

Armor::~Armor(){}

Armor_Type Armor::get_type() const {
	return this->type;
}

int Armor::get_def() const {
	return this->def;
}

int Armor::get_bonus_hp() const {
	return this->bonus_hp;
}

void Armor::show_stats() const
{
	std::cout << "Typ: " << armor_names[this->get_type()] << std::endl;
	std::cout << "def: " << this->get_def() << std::endl;
	std::cout << "bonus hp: " << this->get_bonus_hp() << std::endl;
}
