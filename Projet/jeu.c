#include "header.h"


void * jeu(void * retour)
{
// On affiche le menu
afficher_menu(JEU_);

// On libère le thread temps
sem_post(&sem_synch_temps);

    while (1)
    {
        // Saisie des instructions
        char saisie[11];
        int i;

        scanf("%10s",saisie);
        purger();

        for (i=0;saisie[i]!='\0';i++) // Passage en majuscule
        {
            saisie[i] = toupper(saisie[i]);
        }

        if (strcmp(saisie,"2")==0) // Pause
        {
            sem_wait(&sem_etat);
            etat_jeu=3;
            sem_post(&sem_etat);
            saisie[0]=pause_jeu();
            saisie[1]='\0';
            afficher_menu(JEU_);
            sem_post(&sem_synch_temps);
        }

        if (strcmp(saisie,"1")==0 ) // Sauvegarde
        {
            sem_wait(&sem_etat);
            etat_jeu=2;
            sem_post(&sem_etat);
            return NULL;
        }
        else if (strcmp(saisie,"3")==0) // Quitter
        {
            sem_wait(&sem_etat);
            etat_jeu=4;
            sem_post(&sem_etat);
            return NULL;
        }
        else if (strcmp(saisie,"/GAGNANT")==0) // Coup gagnant
        {
            sem_wait(&sem_etat);
            etat_jeu=5;
            sem_post(&sem_etat);
            return NULL;
        }
        else if (strcmp(saisie,"/VALIDE")==0) // Coup valide
        {
            sem_wait(&sem_etat);
            etat_jeu=6;
            sem_post(&sem_etat);

            int j;
            for(j=0;j<strlen(saisie)-1;j++) // On retire le / devant la commande
            {
                saisie[j]=saisie[j+1];
            }
            saisie[strlen(saisie)-1]='\0';

            // On attend l'allocation de la liste puis l'on saisie le coup
            sem_wait(&sem_synch_jeu);
            strcpy(param->fin_jeu->coup,saisie);
            sem_post(&sem_synch_temps);
            afficher_menu(JEU_);
            sem_wait(&sem_synch_jeu);
        }
        else if (strcmp(saisie,"/MAUVAIS")==0) // Coup invalide
        {
            afficher_menu(JEU_);
            printf("%c7\x1b[8;19H", '\x1b');
            printf("Ce coup n'est pas autorisé.%c8", '\x1b');
            fflush(stdout);
        }
        else if (strcmp(saisie,"2")!=0) // Toute commande différente de la reprise ou des autres commandes
        {
            afficher_menu(JEU_);
            printf("%c7\x1b[8;19H", '\x1b');
            printf("Saisie incorrecte.%c8", '\x1b');
            fflush(stdout);
        }
    }

}

char pause_jeu()
{
int erreur=0;
char saisie;

while (1)
{
    afficher_menu(PAUSE_);

    if(erreur)
    {
        printf("%c7\x1b[8;18H", '\x1b');
        printf(" Erreur de saisie.%c8", '\x1b');
        fflush(stdout);
        erreur=0;
    }

    scanf("%c",&saisie);
    purger();

    if (saisie=='1' || saisie=='2' || saisie=='3') // Si une commande est tapé
    {
        return saisie;
    }
    else
    {
        erreur=1;
    }
}
}
