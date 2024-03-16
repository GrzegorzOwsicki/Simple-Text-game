#include "Golem.h"

void Golem::attack(Etnity* enemy)
{
	std::cout << this->get_name() << " atakuje przeciwnika" << std::endl;
	enemy->take_dmg(this->dmg);
}

Armor* Golem::get_armor()
{
	return this->rocks;
}

std::ofstream& Golem::SaveToFile(std::ofstream& ofs) const
{
	ofs << "Golem" << std::endl;
	ofs << this->get_hp() << std::endl;
	ofs << this->get_poison_status() << std::endl;
	ofs << this->get_poison_duration() << std::endl;
	ofs << this->get_stunn_status() << std::endl;
	ofs << this->get_stunn_duration() << std::endl;
	ofs << this->dmg << std::endl;
	ofs << this->rocks->get_type() << std::endl;
	ofs << this->rocks->get_def() << std::endl;
	ofs << this->rocks->get_bonus_hp() << std::endl;
	return ofs;
}

std::ifstream& Golem::LoadFromFile(std::ifstream& ifs)
{
	Armor_Type armor_type;

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
	Weapon* weapon = new Weapon(Fist, input);
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

Golem::Golem(Armor* armor, Weapon* weapon, int hp, int max_hp, bool poison_effect, int poison_duration, bool stunn_effect, int stunn_duration)
{
	this->set_name("Golem");
	set_armor(armor);
	set_weapon(weapon);
	set_hp(hp);
	set_max_hp(max_hp);
	set_poison_duration(poison_duration);
	set_poison_status(poison_effect);
	set_stunn_duration(stunn_duration);
	set_stunn_status(stunn_effect);
}

Golem::~Golem()
{
	delete rocks;
}
void Golem::take_dmg(Weapon weapon)
{
	if (weapon - *this->get_armor() <= 0) return;
	int dmg_taken = weapon - *this->get_armor();
	set_hp(get_hp() - dmg_taken);
}

void Golem::take_dmg(int dmg)
{
	if (dmg - this->get_armor()->get_def() <= 0) return;
	int dmg_taken = dmg - this->get_armor()->get_def();
	set_hp(get_hp() - dmg_taken);
}

void Golem::set_armor(Armor* armor)
{
	this->rocks = armor;
}

void Golem::set_weapon(Weapon* new_weapon)
{
	this->dmg = new_weapon->get_dmg();
	delete new_weapon;
}

void Golem::show_status() const
{
	std::cout << this->get_name() << std::endl;;
	std::cout << "hp:" << get_hp() << "/" << get_max_hp() << std::endl;
	std::cout << "Zadaje " << this->dmg << "obrazen" << std::endl;
	std::cout << "Posiada  " << armor_names[this->rocks->get_type()] << " pnacerz z kamieni o ochronie" << this->rocks->get_def()<< std::endl;
}

void Golem::ai(Etnity* enemy)
{
	this->attack(enemy);
}

void Golem::stunn()
{
	if (this->get_stunn_status()) std::cout << "Golem jest odporny na ogluszenie" << std::endl;
	this->set_stunn_status(false);
	this->set_stunn_duration(0);
}

void Golem::poison()
{
	if (this->get_poison_status()) std::cout << "Golem jest odporny na trucizne" << std::endl;
	this->set_poison_status(false);
	this->set_poison_duration(0);
}

void Golem::controls(char key, Etnity* enemy){}
