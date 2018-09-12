
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{

        FILE *file;
        char lines[100];

        //Reading the file pointer
        file = fopen(argv[2], "r");
        if(file==NULL){
                printf("my-grep:searchterm [file...]\n");
        }

        // Comparing the words in each line by reading the lines
        while(fscanf(file, "%[^\n]\n",lines)!=EOF)
        {
                if(strstr(lines, argv[1])==NULL)
                {
                        printf(" \n");
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

         fclose(file);
}

