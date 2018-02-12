#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <dirent.h>

enum class Types
{
	DIR,
	FILE,
};

class Directory
{
private:
	DIR *dir;
	const std::string pathname_m;
	dirent *ent;
public:
	Directory(std::string pathname);
	~Directory();
	
	/* Class functions */
	dirent* read();
	std::string name();
	Types type();
};

#endif

