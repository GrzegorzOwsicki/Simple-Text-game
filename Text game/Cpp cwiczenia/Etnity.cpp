#include "Etnity.h"

void Etnity::set_hp(int new_hp) 
{
	hp = new_hp;
}

int Etnity::get_hp() const 
{
	return hp;
}

int Etnity::get_max_hp() const
{
	return max_hp;
}

void Etnity::set_max_hp(int new_hp) 
{
	max_hp = new_hp;
}

void Etnity::return_to_fight()
{
	this->in_combat = true;
}

void Etnity::die()
{
	if (this->get_hp() <= 0) {
		this->alive = false;
		this->in_combat = false;
	}
}

bool Etnity::check_if_dead()
{
	return this->alive;
}

bool Etnity::check_if_in_combat()
{
	return this->in_combat;
}

bool Etnity::get_stunn_status() const 
{
	return this->stunn_effect;
}
int Etnity::get_stunn_duration() const 
{
	return this->stunn_duration;
}

void Etnity::set_stunn_status(bool new_state) 
{
	this->stunn_effect = new_state;
}

void Etnity::set_stunn_duration(int new_duration) 
{
	this->stunn_duration = new_duration;
}

bool Etnity::get_poison_status() const
{
	return this->poison_effect;
}

int Etnity::get_poison_duration() const
{
	return this->poison_duration;
}

void Etnity::set_poison_status(bool new_status)
{
	this->poison_effect = new_status;
}

void Etnity::set_poison_duration(int new_duration)
{
	this->poison_duration = new_duration;
}

void Etnity::stunn() 
{
	if (this->get_stunn_status() == 1) {
		if (this->get_stunn_duration() == 0) this->set_stunn_status(false);
		else this->set_stunn_duration(this->get_stunn_duration() - 1);
	}
}

void Etnity::poison()
{
	if (this->get_poison_status() == 1) {
		this->set_hp(this->get_hp() - (this->get_poison_duration() * 3));
		this->set_poison_duration(this->get_poison_duration() - 1);
		if (this->get_poison_duration() == 0) set_poison_status(false);
	
	}
}

void Etnity::run()
{
	if(rand() % 10 +1 > 3) this->in_combat = false;
}

std::string Etnity::get_name() const
{
	return this->name;;
}

void Etnity::set_name(const char* new_name)
{
	delete this->name;
	this->name = new char[strlen(new_name)];
	strcpy(this->name, new_name);
}

Etnity::Etnity(int hp, bool poison_effect, int poison_duration, bool stunn_effect, int stunn_duration, bool alive, bool incombat) :
	max_hp(hp),
	hp(hp),
	poison_effect(poison_effect),
	poison_duration(poison_duration),
	stunn_effect(stunn_effect),
	stunn_duration(stunn_duration),
	alive(alive),
	in_combat(incombat)
{}

Etnity::~Etnity()
{
}

std::ofstream& operator<<(std::ofstream& os, const Etnity& entity)
{
	return entity.SaveToFile(os);
}