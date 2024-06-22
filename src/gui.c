#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "calcul.h"
#include <fcntl.h>
#include <sys/stat.h>
#define MAX_SIZE 3
#define PIPE_NAME_IN_1 "pipe_in_1"
#define PIPE_NAME_OUT_1 "pipe_out_1"
#define PIPE_NAME_IN_3 "pipe_in_3"
#define PIPE_NAME_OUT_3 "pipe_out_3"

int afichmenu();
void execomnd(int com);
void affichtable(tabl t);
int buf[3];

int main(void){
 int choix;

  do{
     choix=afichmenu();
     execomnd(choix);

  }while (choix!=0);

 return 0;
}

int afichmenu(){
        int chx;
        printf("=================\n");
        printf("0: quitter\n");
        printf("1: Somme\n");
        printf("2: Produit\n");
        printf("3: Factoriel\n");
        printf("4: Trace\n");
        printf("=================\n");
        scanf("%d",&chx);
  return chx;

}

void execomnd(int com){
        int a,b;
        int fd_in, fd_out;
        int data[3];
        tabl trc;
         mkfifo(PIPE_NAME_OUT_1, 0666);
         mkfifo(PIPE_NAME_IN_1, 0666);
         mkfifo(PIPE_NAME_IN_3, 0666);
         mkfifo(PIPE_NAME_IN_3, 0666);

        switch (com){
        case 0:{
                data[0] = 0;
                data[1] = 0;
                data[2] = 0;
                fd_out = open(PIPE_NAME_OUT_1, O_WRONLY);
                write(fd_out, data, 3 * sizeof(int));
                close(fd_out);
                break;
        }
         case 1: { printf("introduire les deux nombres à additionner :\n");
                scanf("%d %d",&a,&b);
                data[0] = a;
                data[1] = b;
                data[2] = 1;

                fd_out = open(PIPE_NAME_OUT_1, O_WRONLY);
                write(fd_out, data, 3 * sizeof(int));
                close(fd_out);

                fd_in = open(PIPE_NAME_IN_1, O_RDONLY);
                int sum;
                read(fd_in,&sum, sizeof(int));
                printf("resultat dans gui : %d \n", sum);
                close(fd_in);

          break;
        }
         case 2: { printf("introduire les deux nombres à multiplier: \n");
                scanf("%d %d",&a,&b);
                data[0] = a;
                data[1] = b;
                data[2] = 2;

                fd_out = open(PIPE_NAME_OUT_1, O_WRONLY);
                write(fd_out, data, 3 * sizeof(int));
                close(fd_out);

                fd_in = open(PIPE_NAME_IN_1, O_RDONLY);
                int sum;
                read(fd_in,&sum, sizeof(int));
                printf("resultat dans gui : %d \n", sum);
                close(fd_in);

          break;
        }
         case 3: { printf("introduire le nombre :\n");
                scanf("%d",&a);
                data[0] = a;
                data[1] = 0;
                data[2] = 3;

                fd_out = open(PIPE_NAME_OUT_1, O_WRONLY);
                write(fd_out, data, 3 * sizeof(int));
                close(fd_out);

                fd_in = open(PIPE_NAME_IN_1, O_RDONLY);
                int sum;
                read(fd_in,&sum, sizeof(int));
                printf("resultat dans gui : %d \n", sum);
                close(fd_in);

          break;
        }
         case 4: {
                fd_in = open(PIPE_NAME_IN_3, O_RDONLY);
                char trace[1000];
                read(fd_in,trace, 1000 * sizeof(char));
                printf("resultat dans gui : %s \n", trace);
                close(fd_in);

          break;
        }
        }
}
