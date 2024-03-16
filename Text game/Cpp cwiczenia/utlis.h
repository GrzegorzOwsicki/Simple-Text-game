#pragma once
#include <iostream>
#include <random>
#include <iomanip>
#include <map>
#include <string>
#include <conio.h>
#include <fstream>

enum Armor_Type
{
	None = 0,
	Light = 1,
	Heavy = 2
};

enum Wepon_Type
{
	Fist = 0,
	Sword = 1,
	Mace = 2
};

enum Profesions {
};

extern std::map <Armor_Type, const char*> armor_names;
extern std::map <Wepon_Type, const char*> weapon_names;
