#include <iostream>

#include "NeuralNet.h"
#include "FileReader.h"
#include "Menu.h"

int main()
{
	Menu menu;
	
	while (menu.exit() != 1) { menu.ui(); }
	
	return 0;
}








