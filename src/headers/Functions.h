/* Function declarations */
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct info
{
    const char *path;
    const char *editor;
};

extern info parse_command_line(int argc, char **argv);

extern std::vector<std::string> display_directory_content();

extern void display_file_content(const std::string file_name);

#endif
