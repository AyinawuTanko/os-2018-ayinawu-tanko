
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
// The main program have as parameters argc and argv
// argv is a one dimensional array of strings
// argc contains the number of aguments passed to the program
int main(int argc, char *argv[])
{
	// If the name of the file is invoked without a file
	// exit
	if(argc==1){
		exit(1);
	}
	//else loop through the file(s) and print it's contents
	else{
		for(int i=1;i<argc;i++){
        	FILE *file;
        	char lines[500];

       		 //Reading the file pointer
       		 file = fopen(argv[2], "r");
        	if(argc==0){
               		printf("my-grep:searchterm [file...]");
        	}
		if(argc==1){
			printf("my-grep:cannot open file");
		}

        // Comparing the words in each line by reading the lines
       		 while(fgets(lines,500,file)!=	NULL)
        	{
                	if(strstr(lines, argv[1])==NULL)
                	{
                        	printf(" ");
                	}
                	if(strstr(lines, argv[1]) !=NULL)
                	{

                        	printf("%s\n",lines);
                	}
                	else
                	{
                        	continue;
                	}
        	}
	

	// close the file(s)
         fclose(file);
	}
}
	return 0;
}




