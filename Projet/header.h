#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>


#define CHARGER_ 1
#define HISTORIQUE_ 2
#define SAUVEGARDER_ 3

#define MENU_ 1
#define JEU_ 2
#define PAUSE_ 3

#define ERREUR 0
#define OK 1

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED


// Structure étapes parties
typedef struct etape{
    int restant;
    char joueur[9];
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
int pause();


// Menu
int thread_menu();
void Nvlle_partie();
void afficher_menu(int type);
void purger();
void liberer();
void quitter ();


// Ouvreur
int recup_chemin(int type);
int sauvegarder();




#endif
