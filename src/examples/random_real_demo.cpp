// Created by Felice Serena 2016

#include "random_real.h"
#include <iostream>

int main(int argc, char *argv[]) {
	croc::random_real<> real;

	std::cout << "A random number when it has never been accessed: ";
	std::cout << real << std::endl;

	real[4];

	std::cout << "fith block has been accessed: ";
	std::cout << real << std::endl;

	croc::random_real<> real2;
	real2[2];

	std::cout << "another real: ";
	std::cout << real2 << std::endl;

	return 0;
}
