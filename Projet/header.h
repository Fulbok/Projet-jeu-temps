#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

//Structure étapes parties
typedef struct etape{
    double restant;
    char joueur[15];
    char coup[40];
    struct etape * ptsuiv;
}etape;

//thread time
void thread_time(int tps_global, int tps_joueur);


//Menu
int thread_menu();
void Nvlle_partie();
void interrupt();
void pause();
void resume();
void quitter ();


//Ouvreur
void recup_chemin(int nb);
void charger(char* chemin,FILE* fic);
void historique(char* chemin,FILE* fic);














#endif
