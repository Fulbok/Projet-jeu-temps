#include "header.h"


void * jeu(void * retour)
{
system("clear");

        printf("\t\t Menu du jeu : \n\n");
        printf("\t1. Interrompre la partie & Sauvegarder\n");
        printf("\t2. Pause\n");
        printf("\t7. Quitter l'application\n\n\n");

printf("Partie en cours : \n\n");

// On lance les chronos
sem_post(&sem_synch_temps);

// On vide le buffer
    char saisie[11];
    scanf("%10c",saisie);
    getchar();
//getchar();
//purger();

// On récupère le sémaphore pour modifier l'état
sem_wait(&sem_etat);
etat_jeu=5;
sem_post(&sem_etat);

while (1)
{

//    purger();

    int i;
    for (i=0;saisie[i]!='\0';i++)
    {
        saisie[i] = toupper(saisie[i]);
    }

    printf("\nSaisie : %s\n",saisie);

    if (saisie[1]=='\0' && (saisie[0]==1 || saisie[0]==2 || saisie[0]==7))
    {
        return (void *) saisie[0];
    }
    else if (strcmp(saisie,"GAGNANT")==0)
    {
        return (void *) 3;
    }
    else if (strcmp(saisie,"VALIDE")==0)
    {
        return (void *) 4;
    }
    else if (strcmp(saisie,"NON VALIDE")==0)
    {
        printf("Coup non valide.\n");
    }
    else
    {
        printf("Saisie incorrecte.\n");
    }

    scanf("%10s",saisie);
    getchar();
}

}
