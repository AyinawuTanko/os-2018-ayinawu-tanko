#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
        FILE *file;
        char lines[100];


        file = fopen(argv[1], "r");

        if(file==NULL){
                printf("my-cat:cannot open file\n");
                exit(1);
        }

        printf("Output of my-cat command\n");

        while(fscanf(file, "%[^\n]\n", lines)!=EOF)
        {
                printf("%s\n", lines);

        }

        fclose(file);
        return 0;
}
