/* blazerid: thalluri
   Name: Yeshwanth Thalluri
   project: CS 332/532-1G-Systems Programming HW3
  
  Compile: make

   Execute as:

	./search -S projects
	./search -f .c 3 projects
	./search -s 1024 projects
	./search -t d projects
	./search -t f projects
	./search -S -s 1024 -f .c 3 -t f projects
	./search -s 1024 -e "ls -l" projects
	./search -f docx 3 -E "tar cvf docx.tar" projects
	./search -s 1024 -f jpg 3 -e "wc -l" projects
*/
# include "fileinfo.h"

extern struct FileProperties fileProperties;

int main (int argc, char **args) { 
  char *currentPath="./";
  fileProperties.argno=0;
  fileProperties.arguments = malloc(sizeof(char *)*100);
  DIR *directory; 
  int index = 1;
  struct stat directoryInfo;

  /* if only one argument is passed */
    
  if(argc>1) 
  {
	   /* process options*/
		processCommandLineOptions(argc,args);
	    
	    /*process remaining options*/
	  while(index<argc)
    {
        if (stat(args[index], &directoryInfo) == 0)
        {
            if (S_ISDIR(directoryInfo.st_mode))
            {
                currentPath = args[index];
            }
        }
        index++;
    }
	    	  
  }

  directory = opendir(currentPath);
  if (directory == NULL) { 
    printf ("\n Unable to open directory [ %s ]", args[1]); 
    exit (-5);
  } 

   
  printDirectoryList(currentPath,0);
  
  if(fileProperties.E == 1){
    //arguments[argno++] = NULL;
	  commandLineArgExecute(fileProperties.arguments[0],fileProperties.arguments);
  }
  
  closedir (directory); 
  return 0; 
} 

