/* Program to navigate directories */
#include <iostream>
#include <string>
#include <map>
#include <unistd.h> //for get_current_dir() and chdir()
#include "headers/Functions.h"

typedef std::string str_t;

/* Clearing the tty */
#define CLEAR (std::cout << "\033[2J\033[;H") //ANSI escape sequence to clear tty

int
main(int argc, char *argv[])
{
	struct info prog_info = parse_command_line(argc, argv); /* Structure defined in headers/Functions.h */
	
	if ( chdir(prog_info.path) != 0) /* Changing directory was not succesful */
		chdir( get_current_dir_name() );
		
	CLEAR;
	std::map<int, str_t> map = display_directory_content();
	
	/* Program loop */
	for(;;)
	{	
		std::cout << "\nNavigate directory (0 to quit): ";
		unsigned option;
		std::cin >> option;
		
		if ( option == 0 ) break;
		if ( option > map.size() ) {std::cerr << "Invalid input"; continue;}
		
		if ( map[option][0] != '/' ) /* If it doesn't start with a '/', we know it's a file */
		{ 
			if (prog_info.editor != NULL) {
				CLEAR;
				str_t command = str_t(prog_info.editor) + " " + str_t(map[option]);
				if ( system(command.c_str()) == -1 ) /* If opening file with specified editor failed, break */
					break;
			}
			
			{
				CLEAR;
				display_file_content(map[option]);
				
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
