#include "header.h"


void * jeu(void * retour)
{

afficher_menu(JEU_);

// On lance les chronos
sem_post(&sem_synch_temps);

// On vide le buffer
    char saisie[11];
    scanf("%10s",saisie);
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
    else if (strcmp(saisie,"MAUVAIS")==0)
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
