#pragma once
#include "Compte.h"
class Compte_adulte : public Compte {
public:
	Compte_adulte(std::string & ligne) : Compte(ligne) {}
	Compte_adulte(int a, const std::string & c, const std::string & d, struct tm & adp) : Compte(a, c, d, adp) {
		solde = 0;
		acccount_type = "A";
	}
	virtual void retrait_argent(float a) {
		if (check(a)) {
			solde -= a;
			Add_delete_date_sold.emplace(get_current_date_for_transaction(), -a);
			std::cout << "\033[1;mmontant retirer votre nouveau sold est : \033[0m \n" << solde << "\n";
		}
	}
	virtual ~Compte_adulte() {}
};
