#include "header.h"



void init_temps()
{
int restant=0,tour=0; // Tour du joueur 1 : tour%2=0 sinon tour%2=1
etape * nouveau;

if(param->fin_jeu==NULL)
{
    restant=param->tps_global;
}
else
{
    restant=param->fin_jeu->restant;

    // Si le dernier à avoir joué est le joueur 1 c'est au joueur 2
    if(strcmp(param->joueur1,param->fin_jeu->joueur)==0)
    {
        tour=1;
    }

}
void * retour=NULL;

// On prépare la liste chainé qui sa faire l'historique de la partie
//etape * nouveau=malloc(sizeof(etape));
//param->debut_jeu=nouveau;
//param->fin_jeu=nouveau;
//nouveau->ptsuiv=NULL;

// Début du jeu
etat_jeu=1;

// Création du thread de saisie
pthread_t IDjeu;
pthread_create(&IDjeu,NULL,jeu,retour);

// On attend que le thread jeu affiche le menu.
sem_wait(&sem_synch_temps);


// Initialisation ncurses
//WINDOW* mywin;
//  cbreak();
//  keypad(stdscr, TRUE);

 // initscr();

// On initialise les timers
time_t temps_coup=time(NULL);
time_t temps_partie=time(NULL);
int cond=1,actuel=0;
double last=0,retard_global=0,retard_coup=0;

while (cond)
    {
    retard_coup=0;
    sem_wait(&sem_etat);

        if (etat_jeu==5) // Sasie des instructions en cours
        {
            time_t temps_retard=time(NULL);
          // gérer sauvegarde et retour du thread jeu.
            pthread_join(IDjeu,retour);

            if (param->debut_jeu==NULL)
            {
                nouveau=malloc(sizeof(etape));
                param->debut_jeu=nouveau;
                param->fin_jeu=nouveau;
                nouveau->ptsuiv=NULL;
            }
            else
            {
                param->fin_jeu->ptsuiv=malloc(sizeof(etape));
                param->fin_jeu=param->fin_jeu->ptsuiv;
                param->fin_jeu->ptsuiv=NULL;
                nouveau=param->fin_jeu;
            }


            retard_global+=difftime(time(NULL),temps_retard);
        }

        while(last>difftime(time(NULL),temps_coup)){usleep(100000);}
        actuel=difftime(time(NULL),temps_partie);

        if (actuel>=param->tps_joueur)
        {
        // A faire arret thread jeu free mémoire et annoncer loser
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

//        printf("%c7", 27);
        // A MODIFIER METTRE LE TEMPS RESTANT PAR COUP
        printf("%c7\x1b[9;0H", '\x1b');
        printf("Temps restant pour la partie : %0.0lf\n",last);
        printf("Temps restant pour le coup: %0.0lf\n",last);
        printf("%c8", '\x1b');
        fflush(stdout);

        last+=1;


        sem_post(&sem_etat);
        usleep(600000);


    }

}
