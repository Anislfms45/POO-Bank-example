#pragma once
#include "Compte.h"
class demander_permission {
protected:
	bool permission() {
		int check = rand() % 10;
		if (check > 5) {
			std::cout << "\033[1mPermission de la part du directeur accordée \033[0m \n";
			return true;
		}
		else
		{
			std::cout << "\033[31;1mPermission de la part directeur NON accordée\n\033[0m";
			return false;
		}
	}
	virtual ~demander_permission() {};
};