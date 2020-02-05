#pragma once
#include "Compte.h"
class Compte_enfant : public Compte {
	int identifiant_adult;
private:
	std::string Avoir_le_mois_currant() {
		t = time(0);
		localtime_s(&now, &t);
		return std::to_string(now.tm_mon + 1);
	}
	//////// cette fonction va vérifier le montant retéri aujourd'hui
	bool vérifier_si_retrait_par_jour_infa10(float & a) {
		std::string today = get_current_date_for_transaction();
		float montant_de_transaction_daujourdhui = 0;
		for (auto & z : Add_delete_date_sold) {
			if (z.first == today) {
				montant_de_transaction_daujourdhui += z.second;
			}
		}
		if (abs(montant_de_transaction_daujourdhui) + a <= 10) {
			return true;
		}
		else
		{
			std::cout << "\033[31;1moperation impossible limit retrait par jour est de 10$\033[0m \n";
			return false;
		}
	}//////////////////////////////////////////////////////////////////////
	///////cette fonction va vérifier le montant retéri pendant le mois curant 
	bool vérifier_si_retrait_par_mois_inf50(float & a) {
		std::string le_mois_currant = Avoir_le_mois_currant();
		std::string getmouth_of_transaction;
		float montant_transaction_par_mois = 0;
		std::vector<int> adp;
		int i = 0;
		for (auto & oklm : Add_delete_date_sold) {
			i = 0;
			while (i < oklm.first.size())
			{
				if (oklm.first[i] == '-') {
					adp.push_back(i);
				}
				i++;
			}
			getmouth_of_transaction = oklm.first.substr(adp[0] + 1, (adp[1] - adp[0] - 1));
			adp.clear();
			if (getmouth_of_transaction == le_mois_currant) {
				montant_transaction_par_mois += oklm.second;
			}
		}
		if (abs(montant_transaction_par_mois) + a <= 50) {
			return true;
		}
		else
		{
			std::cout << "\033[31;1moperation impossible limit retrait par mois est de 50$ est vous etes à " << montant_transaction_par_mois << "\033[0m \n";
			return false;
		}
	}
	////////////////////////////////////////////////////////
public:
	Compte_enfant(std::string & ligne) : Compte(ligne) {
		identifiant_adult = std::stoi(infos[5]);
		solde = std::stod(infos[6]);
	}
	Compte_enfant(int a, const std::string & c, const std::string & d, struct tm & adp, int k) : Compte(a, c, d, adp) {
		identifiant_adult = k;
		acccount_type = "E";
	}
	virtual void afficher_balance() {
		std::cout << std::fixed << numero_du_compte << " " << acccount_type << " " << Nom << " " << prénome << " " << date_naissance << " " << identifiant_adult << " " << std::setprecision(2) << solde << datetransaction(' ') << '\n';
	}
	virtual std::string representer_data_CSV() {
		stream << std::fixed << std::setprecision(2) << solde;
		std::string sold_tos = stream.str();
		stream.str("");
		std::string alpha = std::to_string(numero_du_compte) + "," + acccount_type + "," + Nom + "," + prénome + "," + date_naissance + "," + std::to_string(identifiant_adult) + "," + sold_tos + datetransaction(',') + '\n';
		return alpha;
	}
	virtual void retrait_argent(float a) {
		if (a > 10) {
			std::cout << "\033[1;mOperation impossible limit de retrait par jour est de 10$\033[0m \n";
		}
		else
		{
			if (check(a) && vérifier_si_retrait_par_jour_infa10(a) && vérifier_si_retrait_par_mois_inf50(a)) {
				solde -= a;
				Add_delete_date_sold.emplace(get_current_date_for_transaction(), -a);
				std::cout << "\033[1;mmontant retirer votre nouveau sold est : \033[0m" << solde << "\n";
			}
		}
	}
	virtual ~Compte_enfant() {}
};