#pragma once
// For the glory of mankind (c) YoRHa squadron

#include <iostream>
#include <map>

struct Human
{
	std::string name;
	std::string surname;
	std::string sex;
	std::string age;

	friend std::istream& operator>>(std::istream& istr, Human& h)
	{
		std::string str;
		std::cout << "Enter name:\n";
		istr >> str;
		h.name = str;
		std::cout << "Enter surname:\n";
		istr >> str;
		h.surname = str;
		std::cout << "Enter sex:\n";
		istr >> str;
		h.sex = str;
		std::cout << "Enter age:\n";
		istr >> str;
		h.age = str;

		return istr;
	}
};

void struct_to_map(Human& h, std::map<std::string, std::string>& mp)
{
	mp["name"] = h.name;
	mp["surname"] = h.surname;
	mp["sex"] = h.sex;
	mp["age"] = h.age;
}