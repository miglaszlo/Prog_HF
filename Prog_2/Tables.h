#pragma once 
#include <iostream>
#include <stdio.h>
#include <string>
#include "DataBase.h"
#include <vector>


static std::string Path_AllTables = "";

class Tables {

	DataBase* Table;
	unsigned NumberOfTables;
public:
	Tables();
	~Tables();

	static void setPath_AllTables(std::string& Buff);
	void Add(DataBase& pdb);
	void Remove();
	bool IsPart(std::string& ppath)const;
	void AddRecord()const;
	void DeleteRecord()const;

	void Print()const;
	void PrintAll()const;
	void Load(); 
	void Edit();
	void operator+(DataBase& db);
	//virtual void main(){};  

};