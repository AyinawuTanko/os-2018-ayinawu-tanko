#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
        if(argc==1){
                exit(1);
        }

        else{

                for(int i=1; i<argc;i++){
                        FILE *file;
                        char lines[500];


                        file = fopen(argv[i], "r");

                        if(file==NULL){
                                printf("my-cat:cannot open file\n");
                                exit(1);
                        }

                        else{

                                printf("Output of my-cat command\n");
                                   while(fgets(lines,500,file)!=NULL){
                                        printf("%s\n", lines);
                                }
                                }
                                fclose(file);

                }
        }

        return 0;
}
