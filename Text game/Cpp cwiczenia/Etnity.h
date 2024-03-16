#pragma once
#include "Armor.h"
#include "Weapon.h"
class Etnity
{	
	int max_hp;
	int hp;
	char* name;
	bool stunn_effect;
	int stunn_duration;
	bool poison_effect;
	int poison_duration;
	bool alive;
	bool in_combat;
public:
	
	virtual void attack(Etnity* enemy) = 0;
	virtual void take_dmg(Weapon weapon) = 0;
	virtual void take_dmg(int dmg) = 0;
	virtual void set_armor(Armor* armor) = 0;
	virtual void set_weapon(Weapon* new_weapon) = 0;
	virtual void show_status() const = 0;
	virtual void stunn();
	virtual void poison();
	virtual void run();
	virtual void controls(char key, Etnity* enemy) = 0;
	virtual void ai(Etnity* enemy) = 0;

	void return_to_fight();
	void die();
	bool check_if_dead();
	bool check_if_in_combat();
	bool get_stunn_status() const;
	int get_stunn_duration() const;
	void set_stunn_status(bool new_state);
	void set_stunn_duration(int new_duration);

	bool get_poison_status() const;
	int get_poison_duration() const;

	void set_poison_status(bool new_status);
	void set_poison_duration(int new_duration);

	int get_hp() const;
	int get_max_hp() const;

	void set_hp(int new_hp);
	void set_max_hp(int new_hp);

	std::string get_name() const;
	void set_name(const char* new_name);
	
	virtual std::ofstream& SaveToFile(std::ofstream& ofs) const = 0;
	virtual std::ifstream& LoadFromFile(std::ifstream& ifs) = 0;

	friend std::ofstream& operator<<(std::ofstream& os, const Etnity& entity);
	
	Etnity( int hp = 50, bool poison_effect = false, int poison_duration = 0, bool stunn_effect = false, int stunn_duration = 0, bool alive = true, bool incombat = true);
	virtual ~Etnity();
};
