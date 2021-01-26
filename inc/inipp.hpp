#ifndef INIPP_HPP
#define INIPP_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sys/stat.h>

#ifndef COMMENT
#define COMMENT ';'
#endif

#ifndef REGEX_SECTION
#define REGEX_SECTION "\\[[a-zA-Z0-9]+\\]"
#endif

#ifndef REGEX_OPTION
#define REGEX_OPTION "(?!\\[)[a-zA-Z0-9]+.=(?!\\])"
#endif

// this one will take the ending character as well, need to work on that one
#ifndef REGEX_WORD
#define REGEX_WORD "[a-zA-Z0-9]+"
#endif

#ifndef OPTION_DELIMITER
#define OPTION_DELIMITER "="
#endif

// not sure how to handle the misformed section issue
enum ErrorCode { FILE_NOT_FOUND, MISFORMED_SECTION, DUPLICATE_SECTION };

class Option
{
	private:
		std::string key, value;

	public:
		Option();
		~Option();
		Option(std::string k, std::string v);
		void set(std::string k, std::string v);
		std::string get_key();
		std::string get_value();
};

class Section
{
	private:
		std::string name;
		std::vector<Option> options;

	public:
		Section();
		~Section();
		Section(std::string n);

		void set_name(std::string n);
		void set_option(Option option);
		std::string get();
		std::vector<Option> get_options();
		void clear_options();
};

class Ini_parser
{
	public:
		Ini_parser();
		Ini_parser(std::string fp);
		bool set_filepath(std::string fp);
		int parse();

		// this function would be returning the section names
		std::vector<std::string> get_sections();
		std::vector<std::string> get_options(std::string section);
		std::string get_value(std::string section_name, std::string option_name);

	private:
		std::string fpath;
		std::vector<Section> sections;

		bool chk_file_exists();
};

#endif
