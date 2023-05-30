#include "Tables.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <exception>



#include "Fileopen.h"
#include "MyException.h"

Tables::Tables(){
	Table = nullptr;
	NumberOfTables = 0;

}

void Tables::Remove() {
	/* Kivalszt a felhasznalo egy tablat, majd atmasdolja a tablakat egy vektorba, kitorli a kivalasztott tablat, majd ujra helyet foglal a -1 db szamu tablanak */
	unsigned select = 0;
	std::vector<DataBase> Buff;

	PrintAll();
	std::cout << std::endl << "Which table would you like to remove?" << std::endl << "Enter serial of table (Enter 0 to exit):" << std::endl;
	std::cin >> select;
	if (select == 0) {
		return;
	}
	else {
		for (unsigned i = 0; i < NumberOfTables; i++) {
			Buff.push_back(Table[i]);
		}

		if (Buff.size() >= select) {
			std::vector<DataBase>::iterator it = Buff.begin() + (select - 1);
			Buff.erase(it);
		}
	
		delete[] Table;
		NumberOfTables--;
		Table = new DataBase[NumberOfTables];
		if (Table == nullptr) {
			throw MyException();
		}
		for (unsigned i = 0; i < NumberOfTables ; i++) {
			
				Table[i] = Buff.front();
				Buff.erase(Buff.begin());
			
		}
	}
	std::cout << "Table removed succesfully" << std::endl;

}

Tables::~Tables(){

	/* Kiirja fajlba a tablak eleresi utjat, majd felszabadítja a foglalt helyet */

	std::ofstream File(Path_AllTables);
	if (!File) {
		
	}
	for (unsigned i = 0; i < NumberOfTables; i++) {
		File << Table[i].Path << std::endl;
	}
	delete [] Table;

}

void Tables::Add(DataBase& pdb) {

	/* Hozza ad egy tablat a tables-hoz, majd ujra foglal teruletet +1 db szamu tablanak */

	std::vector<DataBase> Buff;

	if (NumberOfTables == 0) {
		Table = new DataBase[1];
		NumberOfTables++;
		Table[0] = pdb;
	}

	else {
		for (unsigned i = 0; i < NumberOfTables; i++) {

			Buff.push_back(Table[i]);
		}
		Buff.push_back(pdb);
		NumberOfTables++;
		delete[] Table;
		Table = new DataBase[NumberOfTables];
		if (Table == nullptr)
			throw MyException();
		for (unsigned i = 0; i < NumberOfTables; i++) {
			Table[i] = Buff.front();
			Buff.erase(Buff.begin());
		}
	}
}



void Tables::PrintAll()const  {
	/* Kirajzolja a tablakat */

	if (NumberOfTables != 0) {
		std::cout << std::endl << "Printing all tables:" << std::endl << std::endl;
		for (unsigned i = 0; i < NumberOfTables; i++) {
			std::cout <<"Table #"<< i+1 << std::endl;
			Table[i].Print();
			std::cout << std::endl;
		}
	}
	else {
		std::cout << "No tables loaded" << std::endl;
	}
}

bool Tables::IsPart(std::string& ppath)const {

	/* Eleresiut alapjan megmondja, hogy a Table tartalmazza-e a tablat */
	for (unsigned i = 0; i < NumberOfTables; i++) {
		if (ppath == Table[i].Path)
			return true;
	}
	return false;
}

void Tables::Print()const {
	/* Kirajzol egy kivalaszott tablat */

	unsigned select;
	std::cout << std::endl << "Which table would you like to print?" << std::endl;
	std::cin >> select;
	select--;
	Table[select].Print();
}

void Tables::setPath_AllTables(std::string& Buff) {
	/* Beallítja az osszes tabla utjat tartalmazo fajl utjat  */

	Path_AllTables = Buff;
}

void Tables::Load() {
	/* Betolti a tablakat fajlbol */

	std::ifstream File(Path_AllTables);
	std::string PathBuff;
	std::vector <std::string> Buff;
	std::vector <DataBase> DB;

	if (!File) {
		std::cout << " Enter path for file containing paths:" << std::endl;
		std::cin >> PathBuff;
		File = Fileopen(PathBuff, *this);
		if (File) {
			setPath_AllTables(PathBuff);
		}
	}
	
	while (File >> PathBuff) {
		Buff.push_back(PathBuff);
	}
	while (Buff.empty()) {
		std::cout << "There are no paths in the file, enter path(0 to exit): ";
		std::cin >> PathBuff;
		if (PathBuff == "0")
			return;
		File = Fileopen(PathBuff, *this);
		while (File >> PathBuff) {
			Buff.push_back(PathBuff);
		}
		
	}
	



	for (unsigned i = 0; i <= Buff.size(); i++) {
		DB.push_back(DataBase(Buff.front()));

		Buff.erase(Buff.begin());
	}
	for (std::vector<DataBase>::iterator it = DB.begin(); it != DB.end(); ++it) {
		this->Add(*it);

	}
	

}

void Tables::AddRecord()const {

	/* Hozzaad egy rekordot egy kivalasztott tablahoz */

	unsigned i = 0;
	PrintAll();
	std::cout << "To which table would you like to add record?" << std::endl;
	std::cin >> i;
	if (i > NumberOfTables) {
		throw MyException();
	}
	Table[i-1].Add();
}

void Tables::DeleteRecord()const {

	/* Eltavolit egy rekordot egy kivalasztott tablabol,  */


	unsigned i = 0;
	PrintAll();
	std::cout << "From which table would you like to remove record?" << std::endl;
	std::cin >> i;
	if (i > NumberOfTables)
		throw MyException();
	i--;
	Table[i].Remove();
}
void Tables::Edit() {


	/* Modosit egy rekordot egy kivalasztott tablaban */

	int i = -1;
	PrintAll();
	std::cout << "Which Tables would you like to edit? Enter id (0 to exit): "; std::cin >> i;
	while (i < -1 || i > NumberOfTables) {
		std::cout << "Invalid id, enter again (0 to exit):  "; std::cin >> i;

	}
	i--;
	try {
		Table[i].Edit();
	}
	catch (const MyException& e) { std::cout << e.what(); };
}


void Tables::operator+(DataBase& db) {
	Add(db);
}

	