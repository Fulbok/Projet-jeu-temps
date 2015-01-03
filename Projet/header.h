#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>


#define CHARGER 1
#define HISTORIQUE 2
#define SAUVEGARDER 3

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED


//Structure étapes parties
typedef struct etape{
    int restant;
    char joueur1[9];
    char joueur2[9];
    char coup[40];
    struct etape * ptsuiv;
}etape;

typedef struct param_structure{
    char joueur1[9];
    char joueur2[9];
    int tps_global;
    int tps_joueur;
}param_structure;

// Variable globales
extern param_structure * param;
extern sem_t sem_etat;
extern int etat_jeu;

//thread time
void * init_temps(void * restant);
void thread_time(int tps_global, int tps_joueur);

//Menu
int thread_menu();
void Nvlle_partie();
void interruption();
void resume();
void quitter ();
void jeux();


//Ouvreur
void recup_chemin(int nb);
void charger(FILE* fic,char* ligne);
void historique(FILE* fic,char* ligne);
void sauvegarder(int restant);













#endif
