#include "Human.h"
#include "utlis.h"

Armor* Human::get_armor() const{
	return this->used_armor;
};
Weapon* Human::get_weapon() const{
	return this->used_wepon;
};

void Human::take_dmg(Weapon weapon){
	if (weapon - *this->get_armor() <= 0) return;
	int dmg_taken = weapon - *this->get_armor() ;
	set_hp(get_hp() - dmg_taken);
}

void Human::take_dmg(int dmg){
	if (dmg - this->get_armor()->get_def() <= 0) return;
	set_hp(get_hp() - (dmg - this->used_armor->get_def()));
}

void Human::set_weapon(Weapon* new_weapon)
{
	delete this->used_wepon;
	this->used_wepon = new Weapon;
	this->used_wepon = new_weapon;
}

void Human::set_armor(Armor* new_armor) {
	set_max_hp(get_max_hp() - this->get_armor()->get_bonus_hp());
	delete this->used_armor;
	this->used_armor = new Armor;
	this->used_armor = new_armor;
	set_max_hp(get_max_hp() + this->get_armor()->get_bonus_hp());
}

void Human::set_weapon2(Weapon* new_weapon)
{
	delete this->used_wepon;
	this->used_wepon = new Weapon;
	this->used_wepon = new_weapon;
}

void Human::set_armor2(Armor* new_armor)
{
	set_max_hp(get_max_hp() - this->get_armor()->get_bonus_hp());
	delete this->used_armor;
	this->used_armor = new Armor;
	this->used_armor = new_armor;
	set_max_hp(get_max_hp() + this->get_armor()->get_bonus_hp());
}

void Human::show_status() const{
	std::cout << this->get_name() << std::endl;;
	std::cout << "hp:" << get_hp() << "/" << get_max_hp() << std::endl;
	std::cout << "sp:" << get_sp() << "/" << get_max_sp() << std::endl;
	std::cout << "bron: " << weapon_names[this->used_wepon->get_type()] << " obrazenia: " << this->used_wepon->get_dmg() << std::endl;
	std::cout << "Pancerz: " << armor_names[this->used_armor->get_type()] << " ochrona: " << this->used_armor->get_def()
	<< " bonusowe hp: " << this->used_armor->get_bonus_hp() << std::endl;
	if (this->get_poison_status()) std::cout << "Zatruty na " << this ->get_poison_duration() << std::endl;
	if (this->get_stunn_status()) std::cout << "Ogluszony na" << this -> get_stunn_duration() <<std::endl;
}

void Human::attack(Etnity* enemy) {
	std::cout << this->get_name() << " atakuje przeciwnika" << std::endl;
	enemy->take_dmg(*this->get_weapon());
}

void Human::controls(char key, Etnity* enemy)
{
	if (key == 'a') {
		this->attack(enemy);
		return;
	}
	if (key == 's') {
		if (this->get_sp() > 0) {
			this->skill();
			return;
		}
		std::cout << "Brak sp" << std::endl;
		char key = _getch();
		this->controls(key, enemy);
		return;
	}
	if (key == 'q') {
		if (this->get_sp() > 0) {
			this->skill(enemy);
			return;
		}
		std::cout << "Brak sp" << std::endl;
		char key = _getch();
		this->controls(key, enemy);
		return;
	}

	if (key == 'r') {
		std::cout << "Gracz probuje uciec" << std::endl;
		this->run();
		return;
	}
}

Human::Human(Armor* armor, Weapon* weapon, int max_sp, int sp, int hp,int max_hp):used_armor(armor),
	used_wepon(weapon),
	max_sp(max_sp),
	sp(sp)
{
	this->set_hp(hp);
	this->set_max_hp(max_hp);
}


Human::~Human()
{
	delete used_armor;
	delete used_wepon;
}

int Human::get_sp() const {
	return this->sp;
}

int Human::get_max_sp() const {
	return max_sp;
}

void Human::change_sp(bool add) {
	if (add == 0) this->sp--;
	else sp++;
}

void Human::set_max_sp(int sp)
{
	this->max_sp = sp;
}

void Human::set_sp(int sp)
{
	this->sp = sp;
}
