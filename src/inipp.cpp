#include "../inc/inipp.hpp"
#include <iostream>
#include <regex>

/*
 * Section class
 */
Section::Section()
{
	/* default constructor */
}

Section::~Section()
{
	/* default destructor */
}

Section::Section(std::string n)
{
	set_name(n);
}

void Section::set_name(std::string n)
{
	if (!n.empty())
		this->name = n;
}

/*
 * Ini_parser class
 */
Ini_parser::Ini_parser()
{
	/* default constructor */
}

Ini_parser::Ini_parser(std::string fp)
{
	this->set_filepath(fp);
}

bool Ini_parser::set_filepath(std::string fp)
{
	if (!fp.empty())
		this->fpath = fp;
	return true;
}

int Ini_parser::parse()
{
	if (fpath.empty())
		return false;

	// read the file and then start working parsing the information
	if (!chk_file_exists())
		return FILE_NOT_FOUND;

	std::string t;
	std::smatch m;
	std::ifstream i{fpath};

	while (std::getline(i, t)) {
		// ignore the lines which are empty or having ';' at the start of the line
		// these lines with ';' at the start are comments
		if (!(*t.begin() == ';') && !t.empty()) {
			if (std::regex_search(t, m, std::regex(REGEX_SECTION))) {
				for (auto x : m) {
					/*std::cout << "Length of matched substring : "
						<< x.length() << " and length of entire string : "
						<< t.length() << std::endl;*/

					if ((size_t)x.length() != t.length())
						return MISFORMED_SECTION;
				}
			}
		}
	}

	i.close();
	return 100;
}

bool Ini_parser::chk_file_exists()
{
	struct stat buffer;
	return (stat(fpath.data(), &buffer) == 0);
}

