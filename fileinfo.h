#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h> 
# include <malloc.h>
# include <string.h>
#include <time.h>
#include <sys/wait.h>



struct FileProperties
{
	int length;
	int filePermissions;
	int minimumSize;
	int index;
	char subString[50];
	int childDirectoryPath;
	int maxdepth;
	char *cmdName;
	char **arguments;
	int argno;
	int E;
	int e;
	int t;
	char targ;
};


void copy(char *childDir, char *startDir, char *dirName);
void processCommandLineOptions(int argc, char **args);
void fileAlignment(int fileLength);
void getFileProperties(struct stat properties);
void printDirectoryList(char *startDir,int directoryLevels);
/*void fileLink(struct stat st, char *filePath); */
void commandLineArgExecute(char *cmdName, char **arguments);
