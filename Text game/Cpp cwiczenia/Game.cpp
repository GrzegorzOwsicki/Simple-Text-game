#include "Game.h"

void character_select() {
	int n = 0;
	while (true)
	{
		system("CLS");
		switch (n)
		{
		case 0:
			std::cout << "< Wojownik >\n"
				<< "  Mag\n"
				<< "  Kleryk\n"
				<< "  Lotrzyk";
			break;
		case 1:
			std::cout << "  Wojownik \n"
				<< "< Mag >\n"
				<< "  Kleryk\n"
				<< "  Lotrzyk";
			break;
			break;
		case 2:
			std::cout << "  Wojownik \n"
				<< "  Mag\n"
				<< "< Kleryk >\n"
				<< "  Lotrzyk";
			break;
		case 3:
			std::cout << "  Wojownik \n"
				<< "  Mag\n"
				<< "  Kleryk \n"
				<< "< Lotrzyk  >";
			break;
		default:
			break;

		}
			char key = _getch();
			switch (key)
			{
			case 'w':
				if (n == 0) n = 3;
				else n--;
				break;
			case 's':
				if (n == 3) n = 0;
				else n++;
				break;
			default:
				break;
			case '\r':
				Etnity * player = nullptr;
				switch (n)
				{
				case 0:
					player = new Fighter;

					break;
				case 1:
					player = new Wizard;
					break;
				case 2:
					player = new Cleric;
					break;
				case 3:
					player = new Rouge;
					break;
				default:
					player = nullptr;
					break;
				}
				Etnity* enemy = choose_enemy();
				simulate_game(player,enemy, 0);
				delete player;
				return;
				break;
			}
	}
}

void simulate_game(Etnity* player,Etnity* enemy, int score){
	system("CLS");
	std::cout << "Poczatek walki z " << enemy->get_name() << std::endl;
	player->show_status();
	std::cout << std::endl;
	std::cout << std::endl;
	enemy->show_status();

	while (true)
	{		
		char key = _getch();
		system("CLS");
		if (key == 27) {
			delete enemy;
			return;
		}
		if (key == 'p') {
			std::ofstream file("file.txt");
			file << *player;
			file << std::endl;
			file << score << std::endl;
			file << std::endl;
			file << *enemy;
			file.close();
			delete enemy;
			return;
		}
		player->stunn();
		player->poison();
		player->die();

		if (!player->check_if_in_combat()) {
			system("CLS");
			if (player->check_if_dead()) {
				std::cout << "Gracz uciekl z walki" << std::endl;
				_getch();
				delete enemy;
				player->return_to_fight();
				Etnity* enemy = choose_enemy();
				simulate_game(player, enemy, score);
				return;
			}
			else
			{
				std::cout << "Gracz zgina\n KONIEC GRY" << std::endl;
				_getch();
				delete enemy;
				return;
			}
		}

		if (!player->get_stunn_status()) {
			player->controls(key, enemy);
		}
		enemy->poison();
		enemy->die();
		if (!enemy->check_if_in_combat()) {
			system("CLS");
			if (!enemy->check_if_dead()) {
				delete enemy;
				score++;
				std::cout << "Przeciwnik zabity" << std::endl;
				if (rand() % 2 == 0) {
					Weapon* n_weapon = generate_weapon(score);
					std::cout << "Zdobyta bron" << std::endl;
					n_weapon->show_stats();
					std::cout << "Zamienic bron? y/n" << std::endl;
					while (key != 'y' && key != 'n')
					{
						key = _getch();
					}
					if(key == 'y') player->set_weapon(n_weapon);
				}
				else
				{
					Armor* n_armor = generate_armor(score);
					std::cout << "Zdobyty pancerz" << std::endl;
					n_armor->show_stats();
					std::cout << "Zamienic pancerz? y/n" << std::endl;
					while (key != 'y' && key != 'n')
					{
						key = _getch();
					}
					if (key == 'y') player->set_armor(n_armor);
				}
				Etnity* enemy = choose_enemy();
				simulate_game(player,enemy, score);
				return;
			}
			else
			{
				std::cout << "Przeciwnik uciekl" << std::endl;
				_getch();
				delete enemy;
				Etnity* enemy = choose_enemy();
				simulate_game(player,enemy, score);
				return;
			}
		}
		enemy->stunn();
		if (!enemy->get_stunn_status()) {
			enemy->ai(player);
		}

		std::cout << std::endl;
		player->show_status();
		std::cout << std::endl;
		
		enemy->show_status();
	

		
	}
	
}

Etnity* choose_enemy()
{
	system("CLS");
	std::cout << "Wybierz przeciwnika:\n" <<
		"1) Wilk\n" <<
		"2) Goblin\n" <<
		"3) Roslina\n" <<
		"4) Golem\n" <<
		"5) Wojownik\n" <<
		"6) Mag\n" <<
		"7) Kleryk\n" <<
		"8) Lotrzyk\n" << std::endl;

	char i = _getch();
	switch (i)
	{
	case '1':
		return  new Wolf;
		break;
	case '2':
		return  new Goblin;
		break;
	case '3':
		return  new Plant;
		break;
	case '4':
		return  new Golem;
		break;
	case '5':
		return new Fighter;
		break;
	case '6':
		return new Wizard;
		break;
	case '7':
		return new Cleric;
		break;
	case '8':
		return new Rouge;
		break;
	default:
		return choose_enemy();
		break;
	}
}

Weapon* generate_weapon(int score)
{
	Wepon_Type type;
	int dmg;
	if (rand() % 2 == 0) {
		type = Sword;
	}
	else
	{
		type = Mace;
	}
	dmg = rand() % 10 + 10 * score;
	Weapon* weapon = new Weapon(type, dmg);
	return weapon;
}

Armor* generate_armor(int score)
{
	Armor_Type type;
	int def;
	int bonus_hp;

	if (rand() % 2 == 0) {
		type = Light;
	}
	else
	{
		type = Heavy;
	}
	def = rand() % 10 + 10 * score;
	bonus_hp = rand() % 10 + 10 * score;
	Armor* armor = new Armor(type,def,bonus_hp);
	return armor;
}

void load_game() {
	std::ifstream file("file.txt");
	char line[20];
	file >> line;
	Etnity* player;
	if (!strcmp(line , "Mag")) player = new Wizard;
	else if(!strcmp(line, "Wojownik")) player = new Fighter;
	else if (!strcmp(line, "Kleryk")) player = new Cleric;
	else if (!strcmp(line, "Lotrzyk")) player = new Rouge;
	else {
		std::cout << "Nieprawid³owe dane w pliku" << std::endl;
		return;
	}

	player->LoadFromFile(file);
	
	int score;
	file >> score;
	file >> line;

	Etnity* enemy;
	if (!strcmp(line, "Mag")) enemy = new Wizard;
	else if (!strcmp(line, "Wojownik")) enemy = new Fighter;
	else if (!strcmp(line, "Kleryk")) enemy = new Cleric;
	else if (!strcmp(line, "Lotrzyk")) enemy = new Rouge;
	else if (!strcmp(line, "Goblin")) enemy = new Goblin;
	else if (!strcmp(line, "Golem")) enemy = new Golem;
	else if (!strcmp(line, "Agresyna roslina")) enemy = new Plant;
	else if (!strcmp(line ,"Wilk")) enemy = new Wolf;
	else {
		std::cout << "Nieprawid³owe dane w pliku" << std::endl;
		delete player;
		return;
	}
	enemy->LoadFromFile(file);
	file.close();
	simulate_game(player, enemy, score);

	delete player;

}