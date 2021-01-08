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

// not sure how to handle the misformed section issue
enum ErrorCode { FILE_NOT_FOUND, MISFORMED_SECTION };

class Section
{
	private:
		std::string name;

	public:
		Section();
		~Section();
		Section(std::string n);

		void set_name(std::string n);
		std::string get();
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
