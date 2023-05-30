#include "Fileopen.h"
#include <fstream>
#include <stdio.h>


std::ifstream Fileopen(std::string& Path, Tables& AllTable) {
	std::ifstream file;
	file.open(Path);
	if (!file) {
		std::cout << "Enter path:" << std::endl;

		std::cin >> Path;
		if (Path == "0")
			return file;
		if (AllTable.IsPart(Path)) {
			while (AllTable.IsPart(Path)) {
				std::cout << "File already loaded, enter again (0 to exit):" << std::endl;
				std::cin >> Path;
				if (Path == "0")
					return file;
			
			}

		}
		file.open(Path);
	}
	
	while (!file) {
		std::cout << "Invalid path, enter again (0 to exit):" << std::endl;
		std::cin >> Path;
		
		if (Path == "0")
			return file;
		file.open(Path);
	}
	if (file) {
		std::cout << "Successful opening" << std::endl;
	}

	return file;


}