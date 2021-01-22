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

void Section::set_option(Option option)
{
	this->options.push_back(option);
}

std::string Section::get()
{
	return this->name;
}

std::vector<Option> Section::get_options()
{
	return this->options;
}

/*
 * Option class
 */
Option::Option()
{
	/* default constructor */
}

Option::~Option()
{
	/* default destructor */
}

Option::Option(std::string k, std::string v)
{
	this->set(k, v);
}

void Option::set(std::string k, std::string v)
{
	if (!k.empty() && !v.empty()) {
		this->key = k;
		this->value = v;
	}
}

std::string Option::get_key()
{
	return this->key;
}

std::string Option::get_value()
{
	return this->value;
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

	Section section;
	bool insection = false;
	while (std::getline(i, t)) {
		// ignore the lines which are empty or having ';' at the start of the line
		// these lines with ';' at the start are comments
		if (!(*t.begin() == ';') && !t.empty()) {
			if (std::regex_search(t, m, std::regex(REGEX_SECTION))) {
				// first push the earlier section
				if (insection) {
					sections.push_back(section);
					insection = false;
				}
				insection = true;
				for (auto x : m) {
					if ((size_t)x.length() != t.length())
						return MISFORMED_SECTION;
					else
						section.set_name(x);
				}
			} else if (std::regex_search(t, m, std::regex(REGEX_OPTION)) && insection) {
				Option option;
				std::string key, value;
				for (auto x : m) {
					std::string f{x};

					std::regex_search(f, m, std::regex(REGEX_OPTION_NAME));
					for (auto kn : m)
						key = kn;

					/* now to get the value from the string */
					std::size_t found = t.find_first_of(OPTION_DELIMITER);
					if (found != std::string::npos) {
						value = t.substr(found + 1);

						// removing trailing and leading whitespace
						if (*value.begin() == ' ')
							value.erase(value.begin());
						if (*value.end() == ' ')
							value.erase(value.end());
					}


					/* put this key value pair inside the option object */
					option.set(key, value);
					section.set_option(option);
					//sections.push_back(section);
				}
			}
			// push the section in the list of sections
		}
	}

	// push in the last section
	sections.push_back(section);
	i.close();
	return 100;
}

bool Ini_parser::chk_file_exists()
{
	struct stat buffer;
	return (stat(fpath.data(), &buffer) == 0);
}

