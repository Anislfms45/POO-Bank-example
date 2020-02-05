#pragma once
#include "Compte.h"
#include "demander_permission.h"
class Compte_epargne : public Compte, public demander_permission {
public:
	Compte_epargne(std::string & ligne) : Compte(ligne) {}
	Compte_epargne(int a, const std::string & c, const std::string & d, struct tm & adp) : Compte(a, c, d, adp) {
		solde = 0;
		acccount_type = "R";
	}
	virtual void retrait_argent(float a) {
		if (check(a) && permission()) {
			solde -= a;
			Add_delete_date_sold.emplace(get_current_date_for_transaction(), -a);
			std::cout << "\033[1;mmontant retirer votre nouveau sold est : \033[0m" << solde << "\n";
		}
	}
	virtual ~Compte_epargne() {}
};