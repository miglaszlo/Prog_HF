#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>

#include "MyException.h"
#include "DataBase.h"
#include "Tables.h"
#include "Fileopen.h"
#include "isPart.h"
#include "input.h"







using namespace std;





int main() {
	Tables AllTable;
	unsigned menuselect = 0;
	ifstream pFile;
	istringstream iss;
	try {
		while (true) {
			/*Menu:*/

			cout << "Menu:" << endl;
			cout << "1. Add Table" << endl;
			cout << "2. Delete Table" << endl;
			cout << endl << "___________________" << endl;

			cout << "3. Show Table" << endl;
			cout << "4. Show all Table" << endl;
			cout << endl << "___________________" << endl;

			cout << "5. Add Record to table" << endl << endl;
			cout << "6. Delete Record from table" << endl;
			cout << "7. Edit Record in table" << endl;
			cout << endl << "___________________" << endl;

			cout << "8. Load tables" << endl;
			cout << "10. Exit" << endl << endl;

			/*Ha hibas az input nem engedi tovabb menni, es nem kerul loop ba se */

			while (!my_input(menuselect)) {
				cout << "Invalid input" << endl;
			}

			/* Megnyit egy fajlt, rekordokat beraja a db vektoraba, a + operator hozzaadja a AllTable Table-jehez */

			if (menuselect == 1) {
				string PathBuff;
				pFile = Fileopen(PathBuff, AllTable);
				DataBase d(&pFile, PathBuff);
				try {
					AllTable + d;
				}
				catch (const MyException& e) { std::cout << e.what(); };
			}

			/*Eltavolit egy majd kivalasztasra kerulo tablat */

			else if (menuselect == 2) {
				try {
					AllTable.Remove();
				}
				catch (const MyException& e) { std::cout << e.what(); };
			}
			/*Kirajzol egy tablat*/

			else if (menuselect == 3) {
				AllTable.Print();

			}
			/* Kirajzolja az osszes tablat */

			else if (menuselect == 4) {
				AllTable.PrintAll();
			}

			/* Hozzaad egy rekordot egy tablahoz */

			else if (menuselect == 5) {
				try {
					AllTable.AddRecord();
				}
				catch (const MyException& e) { std::cout << e.what(); };
			}

			/* KItorol egy rekordot egy tablabol */


			else if (menuselect == 6) {
				try {
					AllTable.DeleteRecord();
				}
				catch (const MyException& e) { std::cout << e.what(); };
			}

			/* Modosit egy rekordot egy tablabol */


			else if (menuselect == 7) {
				try {
					AllTable.Edit();
				}
				catch (const MyException& e) { std::cout << e.what(); };
			}
			

			/* Betolti a fajbol a tablakat */

			else if (menuselect == 8) {
				try {
					AllTable.Load();
				}
				catch (const MyException& e) { std::cout << e.what(); };
			}

			/* Kilep */

			else if (menuselect == 10) {
				cout << "Exiting..." << endl;
				return 0;
			}

		}
	}
	catch (...) {
		cout << "Unexpected error, exiting :/" << endl;
	} /* ha nem kapna el barmelyik masik,catch, itt biztosan elkapodik*/
		return 0;
}
