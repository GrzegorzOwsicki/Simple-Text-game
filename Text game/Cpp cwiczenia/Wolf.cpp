#include "Wolf.h"

Wolf::Wolf(Armor* armor, Weapon* weapon, int hp, int max_hp, bool poison_effect, int poison_duration, bool stunn_effect, int stunn_duration)
{
	set_name("Wilk");
	set_armor(armor);
	set_weapon(weapon);
	set_hp(hp);
	set_max_hp(max_hp);
	set_poison_duration(poison_duration);
	set_poison_status(poison_effect);
	set_stunn_duration(stunn_duration);
	set_stunn_status(stunn_effect);
}

Wolf::~Wolf(){
	delete fangs;
}


void Wolf::attack(Etnity* enemy)
{
	std::cout << this->get_name() << " atakuje przeciwnika" << std::endl;
	enemy->take_dmg(*this->fangs);
}



void Wolf::take_dmg(Weapon weapon)
{
	if (weapon.get_dmg() - this->defense > 0) {
		this->set_hp(this->get_hp() - this->defense - weapon.get_dmg());
	}
}

void Wolf::take_dmg(int dmg)
{
	if (this->defense - dmg > 0) {
		this->set_hp(this->get_hp() - this->defense - dmg);
	}
}

void Wolf::show_status() const{
	std::cout << this->get_name() << std::endl;
	std::cout << "hp:" << get_hp() << "/" << get_max_hp() << std::endl;
	std::cout << "Posiada kly zadaj¹ce " << this->fangs->get_dmg() << " obrazen" << std::endl;
	std::cout << "Ochrona: " << this->defense << std::endl;
	if (this->get_poison_status()) std::cout << "Zatruty na " << this->get_poison_duration() << std::endl;
	if (this->get_stunn_status()) std::cout << "Og³uszony na" << this->get_stunn_duration() << std::endl;
}

void Wolf::set_armor(Armor* armor){
	this->defense = armor->get_def();
	delete armor;
}

void Wolf::set_weapon(Weapon* weapon){
	this->fangs = weapon;
}

void Wolf::ai(Etnity* enemy)
{
	this->attack(enemy);
}

void Wolf::controls(char key, Etnity* enemy){}

std::ofstream& Wolf::SaveToFile(std::ofstream& ofs) const
{
	ofs << "Wilk" << std::endl;
	ofs << this->get_hp() << std::endl;
	ofs << this->get_poison_status() << std::endl;
	ofs << this->get_poison_duration() << std::endl;
	ofs << this->get_stunn_status() << std::endl;
	ofs << this->get_stunn_duration() << std::endl;
	ofs << this->fangs->get_type() << std::endl;
	ofs << this->fangs->get_dmg() << std::endl;
	ofs << this->defense << std::endl;

	return ofs;
}

std::ifstream& Wolf::LoadFromFile(std::ifstream& ifs)
{
	Wepon_Type weapon_type;

	int input;
	ifs >> input;
	this->set_hp(input);
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
	Armor* armor = new Armor(None, input, 0);
	this->set_armor(armor);
	this->set_weapon(weapon);

	return ifs;
}

