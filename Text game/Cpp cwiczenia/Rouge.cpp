#include "Rouge.h"

void Rouge::skill()
{
	std::cout << this->get_name() << " probuje unikac atakow" << std::endl;
	this->dodge_chance = 3;
	this->doge_duration = 2;
	this->change_sp(false);
}

void Rouge::skill(Etnity* enemy)
{
	this->attack(enemy);
	std::cout << this->get_name() << " zatrowa przeciwnika" << std::endl;
	enemy->set_poison_status(true);
	enemy->set_poison_duration(3);
	this->change_sp(false);
}

bool Rouge::doge()
{
	if (rand() % 10 + 1 < this->dodge_chance) return true;
	return false;
}

void Rouge::set_weapon(Weapon* new_weapon)
{
	if (new_weapon->get_type() == Mace) {
		std::cout << "zmiana niedozwolaona" << std::endl;
	}
	else {
		this->set_weapon2(new_weapon);
	}
}

void Rouge::take_dmg(int dmg)
{
	if (this->doge() == false) {
		if (dmg - this->get_armor()->get_def() <= 0) return;
		set_hp(get_hp() - (dmg - this->get_armor()->get_def()));
	}
	this->doge_duration--;
	if (this->doge_duration <= 0) {
		this->dodge_chance = 0;
	}
}

void Rouge::take_dmg(Weapon weapon)
{
	if (this->doge() == false){
		if (weapon - *this->get_armor() <= 0) return;
		int dmg_taken = weapon - *this->get_armor();
		set_hp(get_hp() - dmg_taken);
	}
	this->doge_duration--;
	if (this->doge_duration <= 0) {
		this->dodge_chance = 0;
	}
}

void Rouge::ai(Etnity* enemy)
{
	if (this->get_sp() > 0) {
		if (this->get_hp() > this->get_max_hp() * 0.3) {
			if (this->doge_duration <= 0) {
				this->skill();
			}
			else if(!enemy->get_poison_status()){
				this->skill(enemy);
			}
			else
			{
				this->attack(enemy);
			}
		}
	}
	else{
		this->run();
	}
}

void Rouge::show_status() const
{
	std::cout << this->get_name() << std::endl;;
	std::cout << "hp:" << get_hp() << "/" << get_max_hp() << std::endl;
	std::cout << "sp:" << get_sp() << "/" << get_max_sp() << std::endl;
	std::cout << "bron: " << weapon_names[this->get_weapon()->get_type()] << " obrazenia: " << this->get_weapon()->get_dmg() << std::endl;
	std::cout << "Pancerz: " << armor_names[this->get_armor()->get_type()] << " ochrona: " << this->get_armor()->get_def()
		<< " bonusowe hp: " << this->get_armor()->get_bonus_hp() << std::endl;
	if (this->get_poison_status()) std::cout << "Zatruty na " << this->get_poison_duration() << std::endl;
	if (this->get_stunn_status()) std::cout << "Ogluszony na" << this->get_stunn_duration() << std::endl;
	if (this->doge_duration > 0) std::cout << "Probuje uniknac " << this->doge_duration << " nastepnych atakow" << std::endl;
}

std::ofstream& Rouge::SaveToFile(std::ofstream& ofs) const
{
	ofs << "Lotrzyk" << std::endl;
	ofs << this->get_hp() << std::endl;
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
	ofs << this->dodge_chance << std::endl;
	ofs << this->doge_duration << std::endl;

	return ofs;
}

std::ifstream& Rouge::LoadFromFile(std::ifstream& ifs)
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
	this->dodge_chance = input;
	ifs >> input;
	this->doge_duration = input;
	this->set_armor(armor);
	this->set_weapon(weapon);

	return ifs;
}

Rouge::Rouge(int doge_chance, int doge_duration, const char* skill_name, const char* skill_name_2, Armor* armor, Weapon* weapon,
	int max_sp, int sp):
	offensive_skill_name(skill_name),
	personal_skill_name(skill_name_2),
	dodge_chance(doge_chance),
	doge_duration(doge_duration)
{
	set_name("Lotrzyk");
	set_armor(armor);
	set_weapon(weapon);
	set_sp(sp);
	set_max_sp(max_sp);
}

