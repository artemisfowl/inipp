/**
 * @file main.cpp
 * @author sb
 * @date Tue, 22 Dec 2020 23:12:30 +0530
 * @brief creating a library to parse ini files
 */

#include <iostream>
#include <string>

#include "../inc/inipp.hpp"

#ifndef MIN_ARGC
#define MIN_ARGC 2
#endif

#ifndef MAJOR_VERSION
#define MAJOR_VERSION 0
#endif

#ifndef MINOR_VERSION
#define MINOR_VERSION 1
#endif

int show_help()
{
	std::cout << "Program Usage:\n" << "<program_name> -i <input_file>\n" << "-i : input flag\n"
		<< "<input_file> : Provide the path to the input file\n"
		<< "-h : Show the help information for the program\n"
		<< "-v : version information of the program\n";
	return 0;
}

int show_version()
{
	std::cout << "inipp v" << MAJOR_VERSION << "." << MINOR_VERSION << std::endl;
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc < MIN_ARGC) {
		std::cout << "Number of arguments are less than required\n";
		return show_help();
	}

	// increment argv to point to the first argument
	argv++;
	std::string _fpath;

	while (--argc > 0) {
		std::string _t{*argv};
		if (_t == "-v") {
			return show_version();
		} else if (_t == "-h") {
			return show_help();
		} else if (_t == "-i") {
			_fpath = *(++argv);
			argc--;
		} else {
			argv++;
		}
	}

	// send the filepath to the inipp processor
	Ini_parser parser{_fpath};

	// later will integrate this call in the param constructor itself
	unsigned int r = parser.parse();
	if (r == FILE_NOT_FOUND)
		std::cerr << "File not found in specified location\n";
	else if (r == MISFORMED_SECTION)
		std::cerr << "Improper section present in input file, kindly check\n";
	else
		std::cout << "Parsing complete\n";

	// check the sections that are parsed
	auto sections= parser.get_sections();
	std::cout << "Sections parsed :" << std::endl;
	for (auto section : sections) {
		std::cout << section << std::endl;

		// check the options corresponding to each of the sections
		auto options = parser.get_options(section);
		for (auto option : options)
			std::cout << "\t" << option << " : " << parser.get_value(section, option) << std::endl;
	}


	return 0;
}
