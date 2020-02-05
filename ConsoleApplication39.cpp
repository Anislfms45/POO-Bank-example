#include "pch.h"
#include <iostream>
#include <string> 
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctime>
#include <regex>
#include "Compte.h"
#include "Compte_enfant.h"
#include "Compte_adulte.h"
#include "Compte_epargne.h"
// find the type of the account in the CSV File
//////////////Valider les entré
void check_int(int & i) {

	std::cin >> i;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(1, '\n');
		std::cin >> i;
	}
}
void check_float(float & i) {

	std::cin >> i;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(1, '\n');
		std::cin >> i;
	}
}
/////// check identifiant parent 
bool check_parrent(std::vector<Compte * > & adp, int id_parent) {
	int k;
	for (auto &z : adp) {

		if (z->getter_identifian() == id_parent && z->getter_type_compte() == "A")
		{
			return true;
		}
	}
	return false;
}
//////////////////////////////////////////////
///////regex fonction check if the name and the surname doesn't contain numbers or special caractéres
bool check_with_regex(const std::string & alpha, const std::string & beta) {
	std::regex re("[A-Za-z]+");
	if (std::regex_match(alpha, re) && std::regex_match(beta, re)) {
		return true;
	}
	std::cout << "\033[31;1mUn nom ou un prenom ils ne peuvent pas contenir un nombre ou un caractere speciale ! \033[0m\n";
	return false;
}
///////////////////////////////////////////
Compte * Factory(std::string a ) {
	int i = 0 , k=0;
	char identifiant;
	while (i++<a.size())
	{
		if(a[i] == ',') {
			k++;
		}
		if(k==2) {
			identifiant = a[i-1];
			break;
		}
	}
	switch (identifiant)
	{
	case 'A' :
		return new Compte_adulte(a);
		break;
	case 'R' :
		return new Compte_epargne(a);
		break;
	
	case 'E' :
		return new Compte_enfant(a);
		break;
	default:
		std::cout << "\033[31;1mBOOM FATAL ERREUR dans le fichier CSV \033[0m";
		break;
	}
}
int Creat_new_identifiant(std::vector<Compte*> & adp) {
	bool check;
	int new_id;
	do {
		new_id = rand() % 1000000000;
		check = true;
		for (auto & z : adp) {
			if (z->getter_identifian() == new_id) {
				check = false;
			}
		}

	} while (!check);
	return new_id;
}
 Compte * Deuxieme_Factory(std::vector<Compte *> & adp,char & id ,const std::string & nom , const std::string & prenom , struct tm & adp2) {
	 int Id_Parent = 0;
	 int oklm_id = Creat_new_identifiant(adp);
	 switch (id)
	 {
	 case 'A':
		 std::cout << "\033[1mCompte creer avec succés \033[0m \n";
		 return new Compte_adulte(oklm_id, nom, prenom, adp2);
		 break;
	 case 'R' : 
		 std::cout << "\033[1mCompte creer avec succés \033[0m \n";
		 return new Compte_epargne(oklm_id, nom, prenom, adp2);
		 break;
	 case 'E':
		 std::cout << "\033[1mun compte enfant va étre créer veullier entrer l'identifiant de votre Parent : \n \033[0m";
		 check_int(Id_Parent);
		 if (check_parrent(adp, Id_Parent)) {
			 std::cout << "\033[1mCompte creer avec succés \033[0m \n";
			 return new Compte_enfant(oklm_id, nom, prenom, adp2, Id_Parent);
		 }
		 else
		 {
			 std::cout << "\033[31;1mIdentifiant du compte parent Non identifier \033[0m \n";
		 }
		 break;
	 default:
		 std::cout << "BOOM";
		 break;
	 }
}
/////////////cette fonction va afficher le Menu Bar
void  menu_principal() {
	const std::string check[] = {
		"\t \033[1;4mEntrer Votre choix entre 1 - 4\033[0m\n",
		"\t\t 1-afficher les comptes\n",
		"\t\t 2-Effectuer des modifications sur un compte (depot , retrait , Afficher Solde)\n",
		"\t\t 3-Ajouter un compte\n ",
		"\t\t 4-Enregistrer les modifications et quitter l'application\n"
	};
		for (const std::string & adp : check) {
			std::cout << adp;
		}
}
/////////////////////////////////////////////////////////////
void menu_fair_des_modifications_sur_un_compte() {
	const std::string check[] = {

		"\t \033[1;4mEntrer Votre choix entre 1-3\033[0m\n",
		"\t\t 1)-Retrait\n",
		"\t\t 2)-depot\n",
		"\t\t 3)-Afficher Sold \n"
	};
	for (const std::string & adp : check) {
		std::cout << adp;
	}
}
///////////////////////Afficher information
void afficher_information(std::vector<Compte * > & adp) {

	int i = 0;
	for (auto & alpha : adp) {
		i++;
		std::cout << i << "- ";
		alpha->afficher_balance();
	}
}
///////////////////////////////////////////////////////
///////////////Valider la date de naissance
bool Verifier_date(struct tm * adp) {
	if (adp->tm_mday > 31 || adp->tm_mday < 1 || adp->tm_mon < 1 || adp->tm_mon > 12 || adp->tm_year < 1910 || adp->tm_year>2016) {
		std::cout << "\033[31;1mErreur Dans La date de naissance veullier revérifier Merci ! \033[0m \n";
		return false;
	}
		return true;
}
////////////Creer Un nouveau Compte 
void creer_compte(std::vector<Compte * > & adp) {
	std::cin.ignore(123, '\n');
	struct tm date_naissance;
	struct tm current_year;
	time_t t = time(0);
	localtime_s(&current_year, &t);
	int Id_Parent,check;
	std::string nom, prenom;
	char id = ' ';
	do {
		std::cout << "entrer votre Nom :";
		std::getline(std::cin, nom);
		std::cout << "entrer votre Prenom :";
		std::getline(std::cin, prenom);
	} while (!check_with_regex(nom,prenom));
	do
	{
		std::cout << "entre votre date de naissance : \n";
		std::cout << "Annee :";
		check_int(date_naissance.tm_year);
		std::cout << "Mois de naissance :";
		check_int(date_naissance.tm_mon);
		std::cout << "jour de naissance :";
		check_int(date_naissance.tm_mday);
	} while (!Verifier_date(&date_naissance));
	if ((current_year.tm_year+1900) - date_naissance.tm_year <= 10) {
		id = 'E';
	}
	else
	{
		do {
			std::cout << "\033[1m1 Pour compte adulte et 0 Pour compte Epargne \033[0m \n";
			check_int(check);
		} while (check != 1 && check !=0);
		if (check == 1) {
			id = 'A';
		}
		else
		{
			id = 'R';
		}
	}
	if (id != ' ') {
		adp.push_back(Deuxieme_Factory(adp, id, nom, prenom, date_naissance));
	}
	else
	{
		std::cout << "\033[31;1mFATAL ERREUR \033[0m\n";  // presque impossible de ce produire 
	}
}
/////////////////////////////////////////////////*/
void choix_de_modification(int & a , std::vector<Compte *> & adp) {
	a--;
	menu_fair_des_modifications_sur_un_compte();
	int identifiant_operation;
	float Montant;
	check_int(identifiant_operation);
	switch (identifiant_operation)
	{
	case 1 :
		std::cout << "vous avez choisie de faire un retrait \033[1mEntrer le montant :\033[0m \n";
		check_float(Montant);
		if (Montant > 0) {
			adp[a]->retrait_argent(Montant);
		}
		else
		{
			std::cout << "\033[31;1mEntrer une valeur positive s'il vous plait \033[0m\n";
		}
		break;
	case 2 :
		std::cout << "Vous avez choisie de faire un depot \033[1mEntrer le montant :\033[0m \n";
		check_float(Montant);
		if (Montant > 0) {
			adp[a]->depot_argent(Montant);
		}
		else
		{
			std::cout << "\033[31;1mEntrer une valeur positive s'il vous plait \033[0m\n";
		}
		break;
	case 3 : 
		std::cout << "Le sold de ce compte et de : " << adp[a]->getter_Solde() << "$ \n";
		break;
	default:
		std::cout << "\033[31;1merreur d'enter\033[0m \n";
		break;
	}
}
void enregistrer_modification(std::vector<Compte * > & adp) {
	std::ofstream NewCsv("Banque.csv");
	if (NewCsv) {
		for (auto & z : adp) {
			NewCsv << z->representer_data_CSV();
		}
	}
	std::cout << "\033[1mModification enregistrer \033[0m \n";
}
int main()
{
	std::vector<Compte * > list_of_accounts;
	std::ifstream csv("banque.csv");
	std::string ligne;
	std::string * adp;
	int i,y;
	if (csv) {
		while (std::getline(csv , ligne))
		{
			list_of_accounts.push_back(Factory(ligne));
		}
	}
	do
	{
		menu_principal();
		std::cout << "\t Entrer votre choix \n";
		check_int(i);
		switch (i)
		{
		case 1 :
			afficher_information(list_of_accounts);
			break;
		case 2 :
			std::cout << "\t \033[1mEntrer le numero de compte ou vous vouliez effectuer des modifications entre 1 et " << list_of_accounts.size() << "\033[0m\n";
			check_int(y);
			if (y<=0 || y > list_of_accounts.size()) {
				std::cout << "\033[31;1mErreur entrer une valeur entre 1-" << list_of_accounts.size() << "\033[0m\n";
			}
			else
			{
				choix_de_modification(y, list_of_accounts);
			}
			break;
		case 3 :
			creer_compte(list_of_accounts);
			break;
		case 4 :
			enregistrer_modification(list_of_accounts);
			break;
		default:
			std::cout << "\033[31;1mEntre 1-4 s'il vous plait ! \033[0m\n";
			break;
		}
	} while (i != 4);
	return 0;
}