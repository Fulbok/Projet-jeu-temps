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

#define MENU 1
#define JEU 2
#define PAUSE 3

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED


// Structure étapes parties
typedef struct etape{
    int restant;
    char joueur1[9];
    char joueur2[9];
    char coup[11];
    struct etape * ptsuiv;
}etape;

typedef struct param_structure{
    char joueur1[9];
    char joueur2[9];
    int tps_global;
    int tps_joueur;
    etape *debut_jeu;
    etape *fin_jeu;
}param_structure;

// Variable globales
extern param_structure * param;
extern sem_t sem_etat;
extern sem_t sem_synch_jeu;
extern sem_t sem_synch_temps;
extern int etat_jeu;

// Gestion du temps
void init_temps();

// Thread Jeu
void * jeu(void * retour);

// Menu
int thread_menu();
void Nvlle_partie();
void afficher_menu(int type);
void purger();
void liberer()
void quitter ();




// Ouvreur
void recup_chemin(int nb);
void charger(FILE* fic,char* ligne);
void historique(FILE* fic,char* ligne);
void sauvegarder();




#endif
