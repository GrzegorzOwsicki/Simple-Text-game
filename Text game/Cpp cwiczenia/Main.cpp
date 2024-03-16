#include <iostream>
#include <conio.h>
#include "Game.h"

int main() {
	int wybor = 0;
	while (true)
	{
		std::cout << "   Menu" << std::endl;
		switch (wybor)
		{
		case 0:
			std::cout << " < Nowa Gra >\n" 
					  << "   Wczytaj \n"
					  << "   Wyjdz"  << std::endl;
			break;
		case 1:
			std::cout << "   Nowa Gra \n" 
					  << " < Wczytaj >\n"
					  << "   Wyjdz " << std::endl;
			break;
		case 2:
			std::cout << "   Nowa Gra \n"
					  << "   Wczytaj \n"
					  << " < Wyjdz >" << std::endl;
			break;
		default:
			break;
		}

		char key = _getch();
		switch (key)
		{
		case 'w':
			if (wybor == 0) wybor = 2;
			else wybor--;
			break;
		case 's':
			if (wybor == 2) wybor = 0;
			else wybor++;
			break;
		default:
			break;
		case '\r':
			switch (wybor)
			{
			case 0:
				character_select();
				return 0;
				break;
			case 1:
				load_game();
				return 0;
				break;
			default:
				return 0;
				break;
			}
			break;
		}
		system("CLS");
	}
    return 0;
}
