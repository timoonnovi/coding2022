#pragma once

#include <iostream>
#include <map>
#include <cstdlib>

class Phonebook
{
private:
	std::map<std::string, std::string> pb;

public:
	void print_all()
	{
		for (auto& note : pb)
			std::cout << "Name: " << note.first << " Number: " << note.second << '\n';
		std::cout << '\n';
	}

	void print_rnd()
	{
		int tmp = rand() % pb.size();
		for (auto& note : pb)
		{
			if (tmp == 0)
			{
				std::cout << "Name: " << note.first << " Number: " << note.second << '\n';
				break;
			}
			else tmp -= 1;
		}
	}

	void find(std::string name)
	{
		if (pb.find(name) != pb.end())
			std::cout << "Name: " << name << " Number: " << pb[name] << '\n';
		else
			std::cout << "No number found for \"" << name << "\".\n";
	}

	void set(std::string name, std::string number)
	{
		pb[name] = number;
	}

	void rnd_fill()
	{
		for (int i = 0; i < 10; i++)
		{
			std::string name;
			for (int j = 0; j < 11; j++)
			{
				name += rand() % 26 + 97;
			}

			std::string number = "8";
			for (int j = 0; j < 10; j++)
			{
				number += rand() % 10 + 48;
			}

			pb[name] = number;
		}
	}
};