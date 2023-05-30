#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <string>




class DataBase {

	std::vector <std::string> Records;
	std::string Path;
public:
	DataBase(std::ifstream *File,std::string pPath);
	DataBase();
	DataBase(std::string pPath);
	~DataBase();
	void Print() const;
	void Add();
	void Remove();
	void Edit();
	friend class Tables;

};

