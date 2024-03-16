#include "Fighter.h"

float Fighter::get_dmg_reduction() const{
	return this->dmg_reduction;
}
int Fighter::get_block_duration() const{
	return this->block_duration;
}

void Fighter::skill(){
	std::cout << this->get_name() << " Zaslania sie tarcza" << std::endl;
	if (this->get_sp() > 0) {
		this->dmg_reduction = 0.7;
		block_duration += 2;
		this->change_sp(false);
	}
	else std::cout << "Brak sp";
}

void Fighter::skill(Etnity* enemy) {
	std::cout << this->get_name() << " probuje ogluszyc przeciwnika" << std::endl;
	enemy->take_dmg(*this->get_weapon() * 0.2);
	if (rand() % 5 > 1) {
		enemy->set_stunn_status(true);
		enemy->set_stunn_duration(2);
	}
	this->change_sp(false);
}

void Fighter::ai(Etnity* enemy)
{
	if (!enemy->get_stunn_status()) {
		if (this->get_sp() > 0) {
			if (this->block_duration <= 0) this->skill();
			else this->skill(enemy);
		}
		else this->attack(enemy);
	}
	else
	{
		this->attack(enemy);
	}
}

void Fighter::show_status() const
{
	std::cout << this->get_name() << std::endl;;
	std::cout << "hp:" << get_hp() << "/" << get_max_hp() << std::endl;
	std::cout << "sp:" << get_sp() << "/" << get_max_sp() << std::endl;
	std::cout << "bron: " << weapon_names[this->get_weapon()->get_type()] << " obrazenia: " << this->get_weapon()->get_dmg() << std::endl;
	std::cout << "Pancerz: " << armor_names[this->get_armor()->get_type()] << " ochrona: " << this->get_armor()->get_def()
	<< " bonusowe hp: " << this->get_armor()->get_bonus_hp() << std::endl;
	if (this->get_poison_status()) std::cout << "Zatruty na " << this->get_poison_duration() << std::endl;
	if (this->get_stunn_status()) std::cout << "Ogluszony na" << this->get_stunn_duration() << std::endl;
	if (this->block_duration > 0) std::cout << "Zablokuje " << this->block_duration << " nastepnych atakow" << std::endl;
}

std::ofstream& Fighter::SaveToFile(std::ofstream& ofs) const
{
	ofs << "Wojownik" << std::endl;
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
	ofs << this->dmg_reduction << std::endl;
	ofs << this->block_duration << std::endl;
	return ofs;
}

std::ifstream& Fighter::LoadFromFile(std::ifstream& ifs)
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
	this->dmg_reduction = input;
	ifs >> input;
	this->block_duration = input;
	this->set_armor(armor);
	this->set_weapon(weapon);

	return ifs;
}
void Fighter::take_dmg(Weapon weapon){
	if (weapon - *get_armor() <= 0) return;
	int dmg_taken = std::floor((weapon - *this->get_armor())*this->get_dmg_reduction());
	set_hp(get_hp() - dmg_taken);
	this->block_duration--;
	if (block_duration <= 0) {
		this->dmg_reduction = 1;
	}
}

void Fighter::take_dmg(int dmg) {
	if (dmg - this->get_armor()->get_def() <= 0) return;
	set_hp(get_hp() - std::floor(dmg - (this->get_armor()->get_def()))*this->get_dmg_reduction());
	this->block_duration--;
	if (block_duration <= 0) {
		this->dmg_reduction = 1;
	}
}

Fighter::Fighter(float dmg_reduction, int block_duration, const char* skill_name, const char* skill_name_2, Armor* armor, Weapon* weapon,
	int max_sp, int sp):
	offensive_skill_name(skill_name),
	personal_skill_name(skill_name_2),
	dmg_reduction(dmg_reduction),
	block_duration(block_duration)
{
	set_name("Wojownik");
	set_armor(armor);
	set_weapon(weapon);
	set_sp(sp);
	set_max_sp(max_sp);
}
