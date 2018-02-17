#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <map>
#include <fstream>
#include <unistd.h>
#include "Directory.h"

struct info
{
	const char *path;
	const char *editor;
};

info 
parse_command_line(int argc, char **argv)
{
	info optinfo {NULL, NULL};
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

std::map<int, std::string> /* Returns a std::map, constructed like the following: <index, file_name>*/
display_directory_content()
{
	Directory dir( get_current_dir_name() );
	int count=1;
	
	std::map<int, std::string> content_map;
	std::cout << "* Viewing contents of " << get_current_dir_name() << " *\n\n";
	
	while ((dir.read()) != NULL)
	{
		if (dir.type() == Types::DIR) 
		{
			std::string dir_name = "/" + dir.name() + "/";
			std::cout << "* " << count << ": " << dir_name << '\n'; /* Prepend directories with slash */
			content_map.insert(std::pair<int, std::string>( count, dir_name ));
		} 									
		else if (dir.type() == Types::FILE) 
		{
			std::cout << "* " << count << ": " << dir.name() << '\n';
			content_map.insert(std::pair<int, std::string>( count, dir.name() ));
		}
		count++;
	}
	
	return content_map;
}

void 
display_file_content(const std::string file_name) /* Displays the content of a file */
{
	std::cout << "* Viewing contents of " << file_name << " *\n\n";
	std::ifstream file(file_name);
	
	if (file)
	{
		std::string line;
		while (getline(file, line))
			std::cout << line << "\n";
	}
	else std::cerr << "* Error viewing contents of " << file_name << " *\n";
}

#endif
