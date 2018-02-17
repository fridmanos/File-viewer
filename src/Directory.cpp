#include "headers/Directory.h"

Directory::Directory(std::string pathname)
	: pathname_m(pathname)
{
	dir = opendir(pathname_m.c_str());
}
Directory::~Directory()
{
	closedir(dir);
}
dirent* Directory::read()
{
	ent = readdir(dir); return ent;
}
std::string Directory::name() 
{	
	return ent->d_name;
}
Types Directory::type() 
{
	return ((ent->d_type == 4) ? Types::DIR : Types::FILE);
}


