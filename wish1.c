#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>


//Prints the one and only error message
void print_error(){
	char error_message[30] = "An error has occurred\n";
	write(STDERR_FILENO, error_message, strlen(error_message));
}

//getline reads a line a character at a time
char *allocate_buffer(void)
{
        char *buffer = NULL;
        ssize_t size = 0;
        getline(&buffer, &size, stdin);
        return buffer;
}

char *sanitize(char *ch)
{
    int n = strlen(ch);
    for (int i=0; i<n;i++){
    	if (ch[i] == '\n' || ch[i] == ' '){
    		ch[i] = '\0';
    	}   
    }
    return ch;
}

//returns list containing all the tokens separated by "&"
volatile int count = 0; //counts number of arguments
char **argList(char *c){
	const char *s = "&\t\r\n";
	int size = 16;
	char **store = malloc(size * sizeof(char*));;
	char *token;
    token = strtok(c, s);
    while( token != NULL ) {
      store[count] = token;
      //printf("%s\n", store[count]);
      count = count+1;
      if (count>= size) {
            size = (int) (size * 1.5);
            store = realloc(token, size * sizeof(char*));
        }
      token = strtok(NULL, s);
    }
    return store;
}


//Parses the input line into constituent pieces
int len = 0;
int rfound = 0;
char *files = "";

char **divide_buffer(char *buffer)
{
    int size = 16;
    char **alloc_buffer = malloc(size * sizeof(char*));

    char *assignor = " \t\r\n";
    char *alloc_buffers = strtok(buffer, assignor);
    while (alloc_buffers != NULL) {
    	if (strcmp(alloc_buffers, ">") !=0){
    		alloc_buffer[len] = alloc_buffers;
    	}
    	else{
    		rfound = 1;
    		len++;
    		alloc_buffers = strtok(NULL, assignor);
    		files = alloc_buffers;
    	}
        len++;

        if (len>= size) {
            size = (int) (size * 1.5);
            alloc_buffer = realloc(alloc_buffers, size * sizeof(char*));
        }

        alloc_buffers = strtok(NULL, assignor);
    }
    alloc_buffer[len] = NULL;
    return alloc_buffer;
}


char *paths[10];
//Executes all commands
int exec_everything()
{
		paths[0] ="/bin/";
		paths[1] ="/usr/bin/";
		int countpaths = 2;
		do{
	        printf("wish> ");
	          		
	        char *buffer=allocate_buffer();
	        int i; 
			char **store;
			store = argList(buffer);
			
			 for (i = 0; i < count; i++){
			 		char **array =divide_buffer(store[i]);
				    if(strcmp(array[0],"cd")==0){
						if(array[1]==NULL){
						    print_error();

						}else{
						        if(chdir(array[1]) == 0){
						                printf("%s\n", "You have entered the folder");
						        }
						   }
					}
					else if(strcmp(array[0],"exit")==0){
						exit(0);
					}
					else if(strcmp(array[0],"path")==0){
						countpaths = 0;
						for(int i=1;i<len;i++){
							paths[i-1] = malloc(strlen(array[i])+1);
							strcpy(paths[i-1], array[i]);
							countpaths++;
						}
					}else{
						pid_t pid;

		                for (int i=0;i<countpaths;i++){
		                        char *path = paths[i];
		                        char *path1 = malloc(strlen(path)+strlen(array[0])+1);
		                        strcat(path1, path);
		                        strcat(path1, array[0]);
		                        if(access(path1, F_OK)==0){
		                                pid=fork();
		                                if(pid==0){
		                                    char *a[]={path1, array[1], array[2], array[3], array[4], array[5], array[6], array[7], array[8], NULL};
		                                    if (rfound ==1){
		                                    	FILE* file = fopen(files, "w+");
											   dup2(fileno(file), fileno(stdout));
											   dup2(fileno(file), fileno(stderr));
											   fclose(file);
		                                    }
		                                    execv(path1, a);
		                                    print_error();
		                                }
		                                    pid=wait(NULL);
		                        }
		                }

				}		len = 0;
			 }
			 count =0;
	        
		}while(1);
}




//Reads input from a batch file
int exec_batch(char *filename){
     char *buffer = NULL;
     ssize_t size = 0;
     FILE *file;
     file = fopen(filename,"r");
     if(file == NULL){
          print_error();
     	  //printf("Error while trying to open batch file\n");
          exit(1);
     }
     while(getline(&buffer, &size, file)!=-1){

     		int i; 
			char **store;
			store = argList(buffer);
			
			 for (i = 0; i < count; i++){
				 char **array =divide_buffer(store[i]);

	     		//char **array =divide_buffer(buffer);
			    if(strcmp(array[0],"cd")==0){
				   if(array[1]==NULL){
				    print_error();

				   }
				   else{
				        if(chdir(array[1]) == 0){
				                printf("%s\n", "You have entered the folder");
				        }
				   }
				}
				else{
						pid_t pid;

				        char *path="/bin/";
				        char *secondpath="/usr/bin/";

				        char *path1 = malloc(strlen(path)+strlen(array[0])+1);
				        char *path2 = malloc(strlen(secondpath)+strlen(array[0])+1);
				        strcat(path1, path);
				        strcat(path1, array[0]);
				        strcat(path2, secondpath);
				        strcat(path2, array[0]);

				        if(access(path1, F_OK)==0){
				        pid=fork();
				                if(pid==0){
				                        char *a[]={path1, array[1], array[2], array[3], array[4], array[5], array[6], array[7], array[8], NULL};
				                        execv(path1, a);
				                        print_error();
				                }
				        pid=wait(NULL);

				        }else if(access(path2, F_OK)==0){
				            pid=fork();
				                if(pid==0){
				                        char *a[]={path2, array[1], array[2], array[3], array[4], array[5], array[6], array[7], array[8], NULL};
				                        execv(path2, a);
				                        print_error();
				                pid=wait(NULL);
				        }
					}
					len =0;
			    }
			}
			count =0;
	}
}



//Runs all commands
int main(int argc, char **argv)
{
int rc;
if(argc==1){
        exec_everything();
}else if(argc==2){
        exec_batch(argv[1]);
}else{
	print_error();
	printf("Too many command line arguments \n");
	exit(0);
}
return 0;
}
