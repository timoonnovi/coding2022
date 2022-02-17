// 2-2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>>
#include "Phonebook.h"

int main()
{
	Phonebook pb;

	pb.rnd_fill();

	pb.set("pyaterochka", "88005553535");

	pb.print_all();
	pb.print_rnd();
	pb.find("pyaterochka");
	pb.find("obama");

	return 0;
}
