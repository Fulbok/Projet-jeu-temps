#include "header.h"



void init_temps(int restant)
{
if(restant==-1)
{
restant=param->tps_global;
}
void * retour=NULL;

// On prépare la liste chainé qui sa faire l'historique de la partie
etape * nouveau=malloc(sizeof(etape));
param->debut_jeu=nouveau;
param->fin_jeu=nouveau;
nouveau->ptsuiv=NULL;

// Début du jeu
etat_jeu=1;


pthread_t IDjeu;
pthread_create(&IDjeu,NULL,jeu,retour);

// On attend que le thread jeu affiche le menu.
sem_wait(&sem_synch_temps);


// Initialisation ncurses
//WINDOW* mywin;
//  cbreak();
//  keypad(stdscr, TRUE);

 // initscr();


time_t temps_coup=time(NULL);
time_t temps_partie=time(NULL);
int cond=1,actuel=0;
double last=0;

while (cond)
    {
    sem_wait(&sem_etat);

        if (etat_jeu==5) // Sasie des instructions en cours
        {
          // gérer sauvegarde et retour du thread jeu.
          pthread_join(IDjeu,retour);
        }

        while(last>difftime(time(NULL),temps_coup)){usleep(100000);}
        actuel=difftime(time(NULL),temps_partie);

        if (actuel>=param->tps_joueur)
        {
        // A faire arret thread jeu
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

        printf("%c7", 27);

        printf("\x1b[9;0H", 27);
        printf("Temps : %0.0lf\n",last);
        printf("%c8", 27);

        last+=1;


        sem_post(&sem_etat);
        usleep(500000);


    }

}
