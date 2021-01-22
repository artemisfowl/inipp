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

#ifndef REGEX_OPTION_NAME
#define REGEX_OPTION_NAME "[a-zA-Z0-9]+."
#endif

#ifndef OPTION_DELIMITER
#define OPTION_DELIMITER "="
#endif

// not sure how to handle the misformed section issue
enum ErrorCode { FILE_NOT_FOUND, MISFORMED_SECTION };

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
};

class Ini_parser
{
	public:
		Ini_parser();
		Ini_parser(std::string fp);
		bool set_filepath(std::string fp);
		int parse();

	private:
		std::string fpath;
		std::vector<Section> sections;

		bool chk_file_exists();
};

#endif
