#pragma once
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <math.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Compte
{
protected : 
	////////////////VARIABLS
	time_t t;
	struct tm now;
	int numero_du_compte,k;
	double solde;
	std::string Nom, prénome , acccount_type,ligne,date_naissance;
	std::multimap<std::string, float> Add_delete_date_sold;
	std::vector<std::string> infos; 
	std::stringstream stream;
	/////////// transformé la ligne du CSV en data 
	virtual void transferm_lign_to_data() {
		std::string part = "";
		this->ligne += '\n';
		for (char z : this->ligne) {
			if (z == ',' || z == '\n') {
				if (part != "") {
					
					infos.push_back(part);
				}
				part = "";
				continue;
			}
			part += z;
		}
	}
	////////////////////////////////////////////////////////
	////////CETTE PARTIE VA NOUS DONNER LE TEMPS CORRANT
	std::string get_current_date_for_transaction() {
		t = time(0);
		localtime_s(&now, &t);
		 return std::to_string(now.tm_year + 1900) + "-" + std::to_string(now.tm_mon + 1) + "-" + std::to_string(now.tm_mday);
	}
	////////////////////////////////////////////////////////
	////////////////vérifier si on peut retirer un montant x  (fonction qui va étre partager par tous les sous classes car ils ont tous le méme fonctionnement de retrait)
	bool check(float & a) {
		if (solde - a >= 0) {
			return true;
		}
		else
		{
			std::cout << "\033[31;1mimpossible de retirer ce montant car vous disposer seulement de "<< solde <<"\033[0m \n";
			return false;
		}
	}
	//////////////////////////////////////////////////////////
	//////////////////////////////////cette Partie va nous donner un string représentant les transactions 
	std::string datetransaction(char adp) {
		std::string hah , tight="" , left="";	
		if (adp == ' ') {
			tight = "(";
			left = ")";
		}
		for (auto & ze : Add_delete_date_sold) {
			stream << std::fixed << std::setprecision(2) << ze.second;
			hah += adp +tight+ ze.first + adp + stream.str() + left;
			stream.str("");
		}
		return hah;
	}
public:
	/// ce constructeur est utilisé pour construire les objet deja définis dans CSV FILE
	Compte(std::string & ligne) : ligne(ligne) {
		transferm_lign_to_data();
		numero_du_compte = std::stoi(infos[0]);
		acccount_type = infos[1];
		Nom = infos[2];
		prénome = infos[3];
		date_naissance = infos[4];
		solde = std::stof(infos[5]);
		if (acccount_type == "E") {
			k = 7;
		}
		else
		{
			k = 6;
		}
		while (k < infos.size())
		{
			Add_delete_date_sold.insert(std::pair<std::string, double>(infos[k],std::stof(infos[k+1])));
			k += 2;
		}
	}
	//////////////////////////
	//////////////////////////////////////// ce constructeur sera utilisé pour construire les nouveau comptes 
	Compte(int numero_compte,const std::string & c, const std::string & n , struct tm & adp ) : numero_du_compte(numero_compte),Nom(c),prénome(n) {
		solde = 0;
		this->date_naissance = (std::to_string(adp.tm_year) + "-" + std::to_string(adp.tm_mon) + "-" +std::to_string(adp.tm_mday));
	}
	/////////////////// virtual pure 
	virtual void retrait_argent(float a) = 0;
	 ///////////////////////////////////////////////////////////////////////////////////////
	/////////Afficher in information du compte et représnter data CSV est le méme pour compte adulte at compte epargne donc c'est pas la pain de le mettre Pure car on va seulement le redéfinir dans la classe-enfant
	virtual void afficher_balance() {
		std::cout << std::fixed << numero_du_compte << " " << acccount_type << " " << Nom << " " << prénome << " " << date_naissance << " " << std::setprecision(2) << solde << datetransaction(' ') << '\n';
	};
	virtual std::string representer_data_CSV() {
		stream << std::fixed << std::setprecision(2) << solde;
		std::string sold_tos = stream.str();
		stream.str("");
		std::string alpha = std::to_string(numero_du_compte) + "," + acccount_type + "," + Nom + "," + prénome + "," + date_naissance + ",," + sold_tos + datetransaction(',') + '\n';
		return alpha;
	}
	/////////////tous les sous-compte ont la méme facon d'ajouter de l'argent 
	void depot_argent(float & a ) {
		 if (a > 0) {
             solde += a;
			 Add_delete_date_sold.insert(std::pair<std::string, float >(get_current_date_for_transaction(), a));
			 std::cout << "montant " << a << " ajouter au compte \n ";
		 }
		 else
		 {
			 std::cout << "\033[31;1mErreur dans l'entre veullier revérifier \033[0m \n ";
		 }
	 }
	//////////////////////////////////////////////////////////////////////////////////
	/////////// GETTERS
	int getter_identifian() {
		return this->numero_du_compte;
	}
	 std::string getter_type_compte() {
		return this->acccount_type; 
	}
	 float getter_Solde() {
		 return this->solde;
	 }
	 /////////////////////////////////
	virtual ~Compte(){}
};

