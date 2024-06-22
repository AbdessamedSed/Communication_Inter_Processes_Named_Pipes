#include "calcul.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#define PIPE_NAME_IN_1 "pipe_in_1"
#define PIPE_NAME_OUT_1 "pipe_out_1"
#define PIPE_NAME_IN_2 "pipe_in_2"

long int factoriel(int n){
 long int r;
 int x=n;
 if (n<=1) r=1;
    else r= n*factoriel(n-1);
 return (r);
}

int main(){
        int stop = 0;
        int fd_in1, fd_out1, fd_in2;
        int data[3];
        mkfifo(PIPE_NAME_IN_1, 0666);
        mkfifo(PIPE_NAME_OUT_1, 0666);
        mkfifo(PIPE_NAME_IN_2, 0666);

        do {
                fd_in1 = open(PIPE_NAME_OUT_1, O_RDONLY);
                read(fd_in1, data, 3 * sizeof(int));
                printf("Message recu : %ld", data);
                fd_out1 = open(PIPE_NAME_IN_1, O_WRONLY);
                int operation = data[2];

                switch(operation){
                        case 0: {
                                stop = 1;
                                break;
                        }
                        case 1: {
                                int sum = data[0]+data[1];
                                write(fd_out1, &sum, sizeof(int));
                                close(fd_out1);

                                fd_in2 = open(PIPE_NAME_IN_2, O_WRONLY);
                                write(fd_in2, data, 3 * sizeof(int));
                                close(fd_in2);
                                break;
                        }
                        case 2: {
                                int prod = data[0]*data[1];
                                write(fd_out1, &prod, sizeof(int));
                                close(fd_out1);

                                fd_in2 = open(PIPE_NAME_IN_2, O_WRONLY);
                                write(fd_in2, data, 3 * sizeof(int));
                                close(fd_in2);
                                break;
                        }
                        case 3: {
                                int fact = factoriel(data[0]);
                                write(fd_out1, &fact, sizeof(int));
                                close(fd_out1);

                                fd_in2 = open(PIPE_NAME_IN_2, O_WRONLY);
                                write(fd_in2, data, 3 * sizeof(int));
                                close(fd_in2);
                                break;
                        }
                }
        } while (!stop);
}
