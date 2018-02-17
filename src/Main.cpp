/* Program to navigate directories */
#include <iostream>
#include <string>
#include <vector>
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
	std::vector<std::string> file_v = display_directory_content();
	
	/* Program loop */
	for(;;)
	{	
		std::cout << "\nNavigate directory (0 to quit): ";
		unsigned option;
		std::cin >> option;
		
		if ( option == 0 ) break;
		if ( option > file_v.size() ) {std::cerr << "Invalid input"; continue;}
		
		if ( file_v[option][0] != '/' ) /* If it doesn't start with a '/', we know it's a file */
		{ 
			if (prog_info.editor != NULL) {
				CLEAR;
				str_t command = str_t(prog_info.editor) + " " + str_t(file_v[option]);
				if ( system(command.c_str()) == -1 ) /* If opening file with specified editor failed, break */
					break;
			}
			else
			{
				CLEAR;
				display_file_content(file_v[option]);
				
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
			str_t path = get_current_dir_name() + file_v[option]; chdir( path.c_str() ); //Change current directory
			CLEAR;
			file_v = display_directory_content();
		}
	}
	
	return 0;
}

