#include "header.h"


void * jeu(void * retour)
{

afficher_menu(JEU_);

sem_post(&sem_synch_temps);

    while (1)
    {

        char saisie[11];
        int i;

        scanf("%10s",saisie);
        purger();

        for (i=0;saisie[i]!='\0';i++)
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
        else if (strcmp(saisie,"/GAGNANT")==0)
        {
            sem_wait(&sem_etat);
            etat_jeu=5;
            sem_post(&sem_etat);
            return NULL;
        }
        else if (strcmp(saisie,"/VALIDE")==0)
        {
            sem_wait(&sem_etat);
            etat_jeu=6;
            sem_post(&sem_etat);

            int j;
            for(j=0;j<strlen(saisie)-1;j++)
            {
                saisie[j]=saisie[j+1];
            }

            // On attend l'allocation de la liste puis l'on saisie le coup
            sem_wait(&sem_synch_jeu);
            strcpy(param->fin_jeu->coup,saisie);
            sem_post(&sem_synch_temps);
            afficher_menu(JEU_);
            sem_wait(&sem_synch_jeu);
        }
        else if (strcmp(saisie,"/MAUVAIS")==0)
        {
            afficher_menu(JEU_);
            printf("%c7\x1b[8;19H", '\x1b');
            printf("Ce coup n'est pas autorisé.%c8", '\x1b');
            fflush(stdout);
        }
        else if (strcmp(saisie,"2")!=0)
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

    if (saisie=='1' || saisie=='2' || saisie=='3')
    {
        return saisie;
    }
    else
    {
        erreur=1;
    }
}
}
