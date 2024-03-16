#include "Plant.h"

void Plant::attack(Etnity* enemy)
{
	std::cout << this->get_name() << " atakuje przeciwnika" << std::endl;
	enemy->take_dmg(*this->vines);
}

void Plant::take_dmg(Weapon weapon)
{
	if (weapon.get_dmg() - this->defence <= 0) return;
	int dmg_taken = weapon.get_dmg() - this->defence;
	set_hp(get_hp() - dmg_taken);
}

void Plant::take_dmg(int dmg)
{
	if (dmg - this->defence <= 0) return;
	int dmg_taken = dmg - this->defence;
	set_hp(get_hp() - dmg_taken);
}

void Plant::set_armor(Armor* armor)
{
	this->defence = armor->get_def();
	delete armor;
}

void Plant::set_weapon(Weapon* new_weapon)
{
	delete this->vines;
	this->vines = new Weapon(*new_weapon);
}

void Plant::show_status() const
{
	std::cout << this->get_name() << std::endl;
	std::cout << "hp:" << get_hp() << "/" << get_max_hp() << std::endl;
	std::cout << "Posiada pnacza zadaj¹ce " << this->vines->get_dmg() << " obrazen" << std::endl;
	std::cout << "Ochrona: " << this->defence << std::endl;
	if (this->get_stunn_status()) std::cout << "Og³uszony na" << this->get_stunn_duration() << std::endl;
}

void Plant::poison(){
	if (this->get_poison_status()) std::cout << "Roslina jest odporna na trucizne" << std::endl;
	this->set_poison_status(false);
	this->set_poison_status(0);
}

void Plant::run(){
	std::cout << "Roslina nie jest w stanie uciec" << std::endl;
}

void Plant::controls(char key, Etnity* enemy){}

void Plant::ai(Etnity* enemy)
{
	this->attack(enemy);
}

std::ofstream& Plant::SaveToFile(std::ofstream& ofs) const
{
	ofs << "Golem" << std::endl;
	ofs << this->get_max_hp() << std::endl;
	ofs << this->get_hp() << std::endl;
	ofs << this->get_poison_status() << std::endl;
	ofs << this->get_poison_duration() << std::endl;
	ofs << this->get_stunn_status() << std::endl;
	ofs << this->get_stunn_duration() << std::endl;
	ofs << this->vines->get_type() << std::endl;
	ofs << this->vines->get_dmg() << std::endl;
	ofs << this->defence << std::endl;
	return ofs;
}

std::ifstream& Plant::LoadFromFile(std::ifstream& ifs)
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

Plant::Plant(Armor* armor, Weapon* weapon, int hp, int max_hp, bool poison_effect, int poison_duration, bool stunn_effect, int stunn_duration)
{
	this->set_name("Agresyna roslina");
	set_armor(armor);
	set_weapon(weapon);
	set_hp(hp);
	set_max_hp(max_hp);
	set_poison_duration(poison_duration);
	set_poison_status(poison_effect);
	set_stunn_duration(stunn_duration);
	set_stunn_status(stunn_effect);
}

Plant::~Plant()
{
	delete vines;
}

