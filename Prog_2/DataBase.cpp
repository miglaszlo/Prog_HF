#include "DataBase.h"
#include "MyException.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <istream>
#include <iomanip>
#include <vector>
#include <exception>



DataBase::DataBase(std::ifstream* File, std::string pPath) : Path(pPath) {
	//inicializalasok
	Path = pPath;
	std::string strbuff;
	while (*File >> strbuff) {
		Records.push_back(strbuff);
	}
	File->close();

}

DataBase::DataBase(std::string pPath)  {
	Path = pPath;
	std::string strbuff;
	std::ifstream File(pPath);
	while (File >> strbuff) {
		Records.push_back(strbuff);
	}
	if (Records.empty()) {
		throw MyException();
	}
	File.close();
}


DataBase::~DataBase() {	

	/* Kiirja a rekordokat a tabla fajljaba, kiuriti a record vektort */

	std::ofstream File (Path);
	unsigned i = 0;
	for (std::vector<std::string>::iterator it = Records.begin(); it != Records.end(); ++it){
		
		File << *it << " ";
		i++;
		if (i % 5 == 0 && i != 0) {
			File << std::endl;
		}
	}
	Records.clear();
}

DataBase::DataBase() {


}


void DataBase::Print() const {		//stdoutputra kiírja a tablat
	for (auto i = 0; i < Records.size(); i++) {
		if ((i % 5) == 0 && i != 0) {
			std::cout << std::endl;
		}
		std::cout << std::setw(20) << Records[i];

	}
	std::cout << std::endl;


}




void DataBase::Add() {
	/* Hozzaad egy rekordot a tablahoz  */

	std::vector<std::string>::iterator it = Records.begin();
	std::vector<std::string> vec_buff;
	std::string Buff;
	

	// Records.push_back(std::to_string(id));
	++it;
	for (unsigned i = 0; i < 4; i++) {
		std::cout << "Enter " << *it << std::endl;
		std::cin >> Buff;
		vec_buff.push_back(Buff);
		++it;
	}

	unsigned id = 0;
	id = Records.size() / 5;
	Buff = std::to_string(id);
	Records.push_back(Buff);
	for (unsigned i = 0; i < 4; i++) {
		Records.push_back(vec_buff.front());
		vec_buff.erase(vec_buff.begin());
	}
}

void DataBase::Remove() {

	/*Eltavolit egy rekordot a tablabol, szimplan vektor muvelet segitsegevel */

	int Record_id = -1;
	std::vector<std::string> Vec_buff;
	unsigned j = 0;

	Print();
	std::cout << "Which records woudl you like to remove?" << std::endl << "Enter Record id (0 to exit): ";
	std::cin >> Record_id;
	if (Record_id == 0) {
		return;
	}
	while (Record_id == -1) {
		std::cout << std::endl << "Invalid id, enter again: ";
		std::cin >> Record_id;
		if (Record_id == 0) {
			return;
		}

	}
	Record_id *= 5;
	
	Records.erase(Records.begin() + Record_id, Records.begin() + (Record_id + 5));


}

void DataBase::Edit() {

	/* Modosit egy rekordot a tablaban, std inputrol bevett adatbol */

	int Record_id = -1;
	std::vector<std::string> vec_buff;
	std::string str_buff;
	Print();
	std::cout << "Which Record would you like to edit? Enter Id (0 to exit): "; std::cin >> Record_id;
	if (Record_id == 0)
		return;
	while (Record_id < 0) {
		std::cout << "Invalid record id, enter again (0 to exit): "; std::cin >> Record_id;
		if (Record_id == 0)
			return;
	}
	vec_buff.push_back(std::to_string(Record_id));
	for (std::vector<std::string>::iterator it = Records.begin()+1; it != (Records.begin() + 5); ++it) {
		std::cout << "Enter " << *it << std::endl;
		std::cin >> str_buff;
		vec_buff.push_back(str_buff);
	}
	for (std::vector<std::string>::iterator it = Records.begin() + (Record_id * 5); it != Records.begin() + (Record_id * 5) + 5; ++it) {
		if (vec_buff.front() == "\n") {
			++it;
		}
		else {
			*it = vec_buff.front();
			vec_buff.erase(vec_buff.begin());
		}
	}
}