/* Program to navigate directories */
#include <iostream>
#include <fstream> //file I/O
#include <string>
#include <map>
#include <unistd.h> //for get_current_dir() and chdir()
#include "Directory.h"

typedef std::string str_t;
typedef std::pair<int, str_t> pair_t;
typedef std::map<int, str_t> pairmap_t;

/* Clearing the tty */
#define CLEAR (std::cout << "\033[2J\033[;H") // \033[2J\033[;H is an ANSI escape sequence to clear the screen, ANSI is supported on most OS's


pairmap_t /* Returns a std::map, constructed like the following: <index, file_name>*/
display_directory_content()
{
	//chdir(path.c_str());
	Directory dir(get_current_dir_name());
	int count=1;
	
	pairmap_t content_map;
	std::cout << "* Viewing contents of " << get_current_dir_name() << " *\n\n";
	
	while ((dir.read()) != NULL)
	{
		if (dir.type() == Types::DIR) 
		{
			str_t dir_name = "/" + dir.name() + "/";
			std::cout << "* " << count << ": " << dir_name << '\n'; /* Prepend directories with slash */
			content_map.insert(pair_t( count, dir_name ));
		} 									
		else if (dir.type() == Types::FILE) 
		{
			std::cout << "* " << count << ": " << dir.name() << '\n';
			content_map.insert(pair_t( count, dir.name() ));
		}
		count++;
	}
	
	return content_map;
}

void 
display_file_content(const str_t file_name) /* Displays the content of a file */
{
	std::cout << "* Viewing contents of " << file_name << " *\n\n";
	std::ifstream file(file_name);
	
	if (file)
	{
		str_t line;
		while (getline(file, line))
			std::cout << line << "\n";
	}
	else std::cerr << "* Error viewing contents of " << file_name << " *\n";
}

int
main(int argc, char *argv[])
{
	if (!argv[1])
		chdir( get_current_dir_name() ) ; /* If argv is not specified we will then view the contents of current working directory */
	else chdir(argv[1]);
	
	CLEAR;
	pairmap_t map = display_directory_content();
	
	/* Program loop */
	while (true)
	{
		std::cout << "\nNavigate directory (0 to quit): ";
		unsigned option;
		std::cin >> option;
		
		if ( option == 0 ) break;
		if ( option > map.size() ) {std::cerr << "Invalid input"; continue;}
		
		if ( map[option][0] != '/' ) { /* If it doesn't start with a '/', we know it's a file */
			CLEAR;
			display_file_content(map[option]);
			
			{
				str_t temp;
				std::cout << "Return (\\n)";
				std::cin.ignore(); //Flush newline char
				getline(std::cin, temp);
			}
			
			CLEAR;
			display_directory_content();
			continue;
		}
		else 
		{
			str_t path = get_current_dir_name() + map [option]; chdir( path.c_str() ); //Change current directory
			CLEAR;
			map = display_directory_content();
		}
	}
	
	return 0;
}
