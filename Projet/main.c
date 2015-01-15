#include "header.h"

param_structure * param = NULL;
// Valeur de état :
// 0:pas de partie
// 1:partie en cours
// 2:quitter et sauvegarder
// 3:pause
// 4:quitter
// 5:coup gagnant
// 6:coup valide

int etat_jeu=0;
sem_t sem_etat;
sem_t sem_synch_jeu;
sem_t sem_synch_temps;

int main()
{
param = malloc(sizeof(param_structure));
param->debut_jeu=NULL;
param->fin_jeu=NULL;

if (sem_init(&sem_etat,0,1)==-1)
    {
    perror("Problème initialisation du sémaphore de protection de la variable état : ");
    sleep(3);
    return -1;
    }

if (sem_init(&sem_synch_jeu,0,0)==-1)
    {
    perror("Problème initialisation du sémaphore de synchronisation jeu : ");
    sleep(3);
    return -1;
    }

if (sem_init(&sem_synch_temps,0,0)==-1)
    {
    perror("Problème initialisation du sémaphore de synchronisation temps : ");
    sleep(3);
    return -1;
    }

thread_menu();

return 0;
}
