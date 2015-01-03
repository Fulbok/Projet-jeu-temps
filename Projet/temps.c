#include "header.h"



void * init_temps(void * restant)
{
system("clear");

        printf("\t\t Menu du jeu : \n\n");
        printf("\t1. Nouvelle partie\n");
        printf("\t2. Charger une partie\n");
        printf("\t3. Interrompre la partie & Sauvegarder\n");
        printf("\t4. Pause\n");
        printf("\t5. Reprendre la partie\n");
        printf("\t6. Historique\n");
        printf("\t7. Quitter l'application\n\n\n");

// Initialisation ncurses
//WINDOW* mywin;
//  cbreak();
//  keypad(stdscr, TRUE);

 // initscr();

printf("Partie en cours : \n");
time_t temps_coup=time(NULL);
time_t temps_partie=time(NULL);
int cond=1;
double actuel,last=0;

while (cond)
    {
    sem_wait(&sem_etat);

        if (etat_jeu==2) // Changement de joueur
        {
        temps_coup=time(NULL);
        }
        else if (etat_jeu==5) // Pause
        {
        // Attente signal de reprise
        }
        else if (etat_jeu==6) // Fin de partie
        {
        etat_jeu=0;
        }

        while(last>difftime(time(NULL),temps_coup)){usleep(100000);}
        actuel=difftime(time(NULL),temps_partie);

        if (actuel>=param->tps_joueur)
        {
        etat_jeu=3;
        cond=0;
        printf("plus de temps coup");
        }
        else if (last>=param->tps_global)
        {
        etat_jeu=4;
        cond=0;
        printf("plus de temps partie");
        }

        printf("%c8\x1b[13;0H", '\x1b');
        printf("Temps : %0.0lf\n",last);


        last+=1;


        sem_post(&sem_etat);
        usleep(500000);


    }
fflush(stdout);
pthread_exit(1);
}
