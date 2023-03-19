

#include "fileinfo.h"

int fileTabs=1;

struct FileProperties fileProperties;


void commandLineArgExecute(char *cmdName, char **argument)
{
    pid_t pid;
	int status;
	
	pid = fork();
	if (pid == 0) { 
        execvp(cmdName,argument);
    } else if (pid > 0) { 
        wait(&status); 
        if (WIFEXITED(status)) { 
        } else { 
            printf("child process not ended successfully\n");
          
        }
    } else { 
        perror("fork"); 
        exit(EXIT_FAILURE);
    }
}

/*This function process options passed at command line*/
void processCommandLineOptions(int argc, char **args){
	int cLineOption;
	char *elem;
	while((cLineOption = getopt(argc, args, "Ss:f:e:E:t:")) != -1) {
		
		if(cLineOption == 's'){ 
			fileProperties.minimumSize = atoi(optarg);
			fileProperties.length = 1;
		}else if(cLineOption == 'S'){ 
			fileProperties.filePermissions = 1;
		}else if(cLineOption == 'f'){ 
			strcpy(fileProperties.subString, args[optind-1]); 
			fileProperties.maxdepth = atoi(args[optind]);
			fileProperties.index = 1;
		}else if(cLineOption == 't'){ 
			fileProperties.targ = optarg[0];
			fileProperties.t = 1; 
		}else if(cLineOption == 'e'){
			elem = strdup(optarg);
			elem = strtok(elem, " ");
			while (elem != NULL){
				fileProperties.arguments[fileProperties.argno++]=elem;
				elem = strtok(NULL, " ");
			} 	
			fileProperties.e = 1;
		}
		else if(cLineOption == 'E'){
			elem = strdup(optarg);
			elem = strtok(elem, " ");
			while (elem != NULL){
				fileProperties.arguments[fileProperties.argno++]=elem;
				elem = strtok(NULL, " ");
			} 	
			fileProperties.E = 1;
		}
	 }
}

/*This function for printing tab spaces*/
void fileTabSpace(int tabs) {
	int tab=0;
	printf("\n");
	while(tab < tabs) {
 		printf("\t");
		tab++;
	}
}


/*prints file properties*/
void getFileProperties(struct stat properties)
{
	
	char fileCreateDateTime[60];
	char prop[20];
	printf(" (%ld, ", properties.st_size);
	
	if (properties.st_mode & R_OK)
        strcpy(prop,"-r-");
    if (properties.st_mode & W_OK)
       strcpy(prop,"-w-");
    if (properties.st_mode & X_OK)
        strcpy(prop,"-e-");
    
    printf("%s", prop);
    
    strcpy(fileCreateDateTime, ctime(&properties.st_atime));
    
    fileCreateDateTime[strlen(fileCreateDateTime)-1]='\0';
	printf(",  %s)", fileCreateDateTime);
	
}

void copy(char *childDir, char *startDir, char *dirName){
		strcpy(childDir,startDir);
  		strcat(childDir,"/");
     	strcat(childDir,dirName);
}
/* This function prints parent and child directories list */
void printDirectoryList(char *startDir,int directoryLevels)
{
	struct dirent *directoryInfo;
	int printstate;
	char childDir[150];
	DIR *dir= opendir(startDir);
	struct stat fileStat;
  	while((directoryInfo = readdir( dir)) != NULL){ 
		printstate = 0;
     	copy(childDir, startDir, (*directoryInfo).d_name);
      	if(strcmp((*directoryInfo).d_name, "..")==0 || strcmp((*directoryInfo).d_name, ".")==0 ) {
	  	
	  			/* these are not directories therefore skip */
	  	}
	  	else {
		  	 stat(childDir, &fileStat) ;
		  	/*go to next level of directory*/
		  	 if (S_ISDIR(fileStat.st_mode)) {

				if((fileProperties.E != 1 && fileProperties.e != 1) && (fileProperties.t==0 || (fileProperties.t==1 && fileProperties.targ=='d'))){
				
					fileTabSpace(directoryLevels);
					
					printf ("%s",  (*directoryInfo).d_name); 
					
					if(fileProperties.filePermissions==1){
							printf(" [ 0 ]");
					}
				}        
		       
		        if(fileProperties.index == 1 && directoryLevels>=fileProperties.maxdepth){			
		        	return;
		        }
				
				/*goes to next child directory*/
		        printDirectoryList(childDir,directoryLevels+1);
	           
	    	} else {
	    		if( fileProperties.index == 0 && fileProperties.length == 1) {
				
				if(fileStat.st_size<=fileProperties.minimumSize) {
					printstate = 1;
				}
			} else if(fileProperties.length==0 && fileProperties.index==1){ 
	    			if (strstr((*directoryInfo).d_name, fileProperties.subString) != NULL) {
						printstate = 1;
					}
				}
				else if(fileProperties.length==1 && fileProperties.index==1){
					if(fileStat.st_size<=fileProperties.minimumSize && strstr((*directoryInfo).d_name, fileProperties.subString) != NULL){
						printstate = 1;
					}
				}
				else{  
					printstate = 1;
				}

				if(printstate == 1 && (fileProperties.E != 1 && fileProperties.e != 1) && (fileProperties.t==0 || (fileProperties.t==1 && fileProperties.targ=='f'))){
					fileTabSpace(directoryLevels);
					printf ("%s", (*directoryInfo).d_name);
					if(fileProperties.filePermissions==1) {
	    				getFileProperties(fileStat);
	    			}
				}
				
				if(fileProperties.E == 1 && printstate == 1){
					if(childDir != NULL){
						fileProperties.arguments[fileProperties.argno++]=strdup(childDir);
					}
				}
				else if(fileProperties.e == 1 && printstate == 1){
					if(childDir != NULL){
						fileProperties.arguments[fileProperties.argno]=strdup(childDir);
						commandLineArgExecute(fileProperties.arguments[0],fileProperties.arguments);
					}
				}
				
		/*	fileLink(&fileStat, childDir);*/
	   }
  	} 
}
}




