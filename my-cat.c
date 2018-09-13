#include<stdio.h>
#include<stdlib.h>
// The main program have as parameters argc and argv
// argv is a one dimensional array of strings
// argc contains the number of aguments passed to the program
int main(int argc, char *argv[])
{
        // If the name of the file is invoked without a file(s)
        // exit
        if(argc==1){
                exit(1);
        }
        
        // else loop through the file(s) and print its contents
        else{

                for(int i=1; i<argc;i++){
                        FILE *file;
                        char lines[500];

                        // Opens the file(s) and reads them
                        file = fopen(argv[i], "r");

                        if(file==NULL){
                                printf("my-cat:cannot open file\n");
                                exit(1);
                        }

                        else{

                                printf("Output of my-cat command\n");
                                
                                // gets the contents of the files and prints them
                                   while(fgets(lines,500,file)!=NULL){
                                        printf("%s\n", lines);
                                }
                                }
                                
                                // Closes the file(s)
                                fclose(file);

                }
        }

        return 0;
}
