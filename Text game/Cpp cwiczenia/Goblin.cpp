#include "Goblin.h"

void Goblin::attack(Etnity* enemy)
{
	std::cout << this->get_name() << " atakuje przeciwnika" << std::endl;
	enemy->take_dmg(*this->weapon);
}

void Goblin::take_dmg(Weapon weapon)
{
	if (weapon - *this->get_armor() <= 0) return;
	int dmg_taken = weapon - *this->get_armor();
	set_hp(get_hp() - dmg_taken);
}

void Goblin::take_dmg(int dmg)
{
	if (dmg - this->get_armor()->get_def() <= 0) return;
	int dmg_taken = dmg - this->get_armor()->get_def();
	set_hp(get_hp() - dmg_taken);
}

void Goblin::set_armor(Armor* armor)
{
	delete this->armor;
	this->armor = new Armor;
	this->armor = armor;
}

void Goblin::set_weapon(Weapon* new_weapon)
{
	delete this->weapon;
	this->weapon = new Weapon;
	this->weapon = new_weapon;
}

void Goblin::show_status() const
{
	std::cout << this->get_name() << std::endl;;
	std::cout << "hp:" << get_hp() << "/" << get_max_hp() << std::endl;
	std::cout << "bron: " << weapon_names[this->weapon->get_type()] << " obrazenia: " << this->weapon->get_dmg() << std::endl;
	std::cout << "Pancerz: " << armor_names[this->armor->get_type()] << " ochrona: " << this->armor->get_def()
		<< " bonusowe hp: " << this->armor->get_bonus_hp() << std::endl;
	if (this->get_poison_status()) std::cout << "Zatruty na " << this->get_poison_duration() << std::endl;
	if (this->get_stunn_status()) std::cout << "Og³uszony na" << this->get_stunn_duration() << std::endl;
}

void Goblin::controls(char key, Etnity* enemy){}

void Goblin::ai(Etnity* enemy)
{
	if (this->get_hp() < this->get_max_hp() * 0.3){
		std::cout << "Goblin probuje uciec" << std::endl;
		this->run();
	}
	else{
		this->attack(enemy);
	}
}

Weapon* Goblin::get_weapon()
{
	return this->weapon;
}

Armor* Goblin::get_armor()
{
	return this->armor;
}

std::ofstream& Goblin::SaveToFile(std::ofstream& ofs) const
{
	ofs << "Goblin" << std::endl;
	ofs << this->get_hp() << std::endl;
	ofs << this->get_poison_status() << std::endl;
	ofs << this->get_poison_duration() << std::endl;
	ofs << this->get_stunn_status() << std::endl;
	ofs << this->get_stunn_duration() << std::endl;
	ofs << this->weapon->get_type() << std::endl;
	ofs << this->weapon->get_dmg() << std::endl;
	ofs << this->armor->get_type() << std::endl;
	ofs << this->armor->get_def() << std::endl;
	ofs << this->armor->get_bonus_hp() << std::endl;

	return ofs;
}

std::ifstream& Goblin::LoadFromFile(std::ifstream& ifs)
{
	Wepon_Type weapon_type;
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

Goblin::Goblin(Armor* armor, Weapon* weapon, int hp, int max_hp, bool poison_effect,
	int poison_duration, bool stunn_effect, int stunn_duration)
{
	this->set_name("Goblin");
	set_armor(armor);
	set_weapon(weapon);
	set_hp(hp);
	set_max_hp(max_hp);
	set_poison_duration(poison_duration);
	set_poison_status(poison_effect);
	set_stunn_duration(stunn_duration);
	set_stunn_status(stunn_effect);
}

Goblin::~Goblin()
{
	delete this->armor;
	delete this->weapon;
}
