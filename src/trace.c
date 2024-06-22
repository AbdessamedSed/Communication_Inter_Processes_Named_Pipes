#include <stdio.h>
#include "trace.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#define PIPE_NAME_IN_2 "pipe_in_2"
#define PIPE_NAME_IN_3 "pipe_in_3"
#define OUTPUT_FILE "equations.txt"

int main(){
        FILE *output = fopen(OUTPUT_FILE, "a");
        int stop = 0, fd_in2, fd_in3;
        int data[3];
        char chaine[1000] = "";

        mkfifo(PIPE_NAME_IN_2, 0666);
        mkfifo(PIPE_NAME_IN_3, 0666);

        do {
                fd_in2 = open(PIPE_NAME_IN_2, O_RDONLY);
                read(fd_in2, data, 3 * sizeof(int));
                printf("data = %d %d ", data[0], data[1]);
                for (int i = 0; i < 3 ; i++) {
                        char entier[20];
                        sprintf(entier, "%d", data[i]);
                        strcat(chaine, entier);
                        strcat(chaine, " ");
                }
                fprintf(output, "%s", chaine);
                fprintf(output, "%s", "\n");

                fgets(chaine, 1000, output);
                fd_in3 = open(PIPE_NAME_IN_3, O_WRONLY);
                write(fd_in3, chaine, 1000 * sizeof(char));
                close(fd_in3);
        } while (!stop);

        fclose(output);
}
