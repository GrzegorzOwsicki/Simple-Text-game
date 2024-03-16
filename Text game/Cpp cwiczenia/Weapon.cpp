#include "weapon.h"

Weapon::Weapon(){
	dmg = 10;
	type = Fist;
}

Weapon::Weapon(Wepon_Type n_type, int n_dmg){
	dmg = n_dmg;
	type = n_type;
}

Wepon_Type Weapon::get_type() const{
	return this->type;
}

int Weapon::get_dmg() const{
	return this->dmg;
}

void Weapon::set_weapon_dmg(int n_dmg) {
	this->dmg = n_dmg;
}
int Weapon::operator-(const Armor& armor) const {
	int calculated_dmg = this->get_dmg() - armor.get_def();
	if (calculated_dmg <= 0) return 0;
	if (this->type - armor.get_def() < 0)  return calculated_dmg /= 2;
	return calculated_dmg;
}

Weapon Weapon::operator*(float multipler) const{
	Weapon tmp(*this);
	tmp.set_weapon_dmg(ceil(tmp.get_dmg() * multipler));
	return tmp;
}

void Weapon::show_stats() const
{
	std::cout << "Typ: " << weapon_names[this->get_type()];
	std::cout << "Dmg: " << this->get_dmg();
}

Weapon::Weapon(const Weapon& weapon) {
	this->dmg = weapon.get_dmg();
	this->type = weapon.get_type();
}

Weapon::~Weapon(){}
