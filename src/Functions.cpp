#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>
#include "headers/Directory.h"
#include "headers/Functions.h"

/* Ansi Color codes */
#define COLOR_BLUE "\e[1;34m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m" //used to reset the color

info 
parse_command_line(int argc, char **argv)
{
	struct info optinfo {NULL, NULL};
	int opt;
	
	while ((opt = getopt(argc, argv, "e:p:h")) != -1)
	{
		switch (opt) {
			case 'e': 
				optinfo.editor = optarg;
				break;
			case 'p':
				optinfo.path = optarg;
				break;
			case 'h':
				std::cout << "A simple program for navigating directories and outputting files.\n";
				std::cout << "Optional switches [-p PATH] [-e EDITOR]\n";
				exit(1);
			default:
				exit(1);
		}
	}
	return optinfo;
}

std::vector<std::string>
display_directory_content()
{
	Directory dir( get_current_dir_name() );
	int count=1;
	
	std::vector<std::string> file_name_v;
	std::cout << "* Viewing contents of " << COLOR_GREEN << get_current_dir_name() << COLOR_RESET << " *\n\n";
	
	while ((dir.read()) != NULL)
	{
		if (dir.type() == Types::DIR) 
		{
			std::string dir_name = "/" + dir.name() + "/";
			
			std::cout << "* " << count << ": " << COLOR_BLUE << dir_name.c_str() << COLOR_RESET << "\n";
			file_name_v.push_back(dir_name);
		} 									
		else if (dir.type() == Types::FILE) 
		{
			std::cout << "* " << count << ": " << dir.name() << '\n';
			file_name_v.push_back( dir.name() );
		}
		count++;
	}
	
	return file_name_v;
}

void 
display_file_content(const std::string file_name) /* Displays the content of a file */
{
	std::cout << "* Viewing contents of " << COLOR_GREEN << file_name << COLOR_RESET << " *\n\n";
	std::ifstream file(file_name);
	
	if (file)
	{
		std::string line;
		while (getline(file, line))
			std::cout << line << "\n";
	}
	else std::cerr << "* Error viewing contents of " << file_name << " *\n";
}

