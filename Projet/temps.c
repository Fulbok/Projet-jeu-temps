#include "header.h"



void init_temps()
{
int restant=0,tour=1; // Tour du joueur 1 : tour%2=1 sinon tour%2=0
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
        tour=2;
    }

}
void * retour=NULL;

// Début du jeu
etat_jeu=1;

// Création du thread de saisie
pthread_t IDjeu;
pthread_create(&IDjeu,NULL,jeu,retour);

// On attend que le thread jeu affiche le menu.
sem_wait(&sem_synch_temps);

// On initialise les timers
time_t temps_coup=time(NULL);
time_t temps_partie=time(NULL);
int cond=1,actuel=0;
double affiche=0,retard_global=0,retard_coup=0,retard=0;

while (cond)
    {
    sem_wait(&sem_etat);

        if (etat_jeu==2) // Sauvegarde et fin de partie
        {
            pthread_join(IDjeu,NULL);
            sauvegarder();
            etat_jeu=0;
            sem_post(&sem_etat);
            return;
        }
        else if(etat_jeu==4)// Quitter
        {
            pthread_join(IDjeu,NULL);
            quitter();
        }
        else if(etat_jeu==3)// Pause
        {
        time_t temps_retard=time(NULL);
        sem_wait(&sem_synch_temps);
        retard=difftime(time(NULL),temps_retard);

        retard_coup+=retard;
        retard_global+=retard;
        }
        else if(etat_jeu==5)// gagnant
        {
            system("clear");
            if(tour%2)
            {
            printf("\n\n\n\n\n\n\n\n\t\t\t%s a gagné FELICITATION !",param->joueur1);
            }
            else
            {
            printf("\n\n\n\n\n\n\n\n\t\t\t%s a gagné FELICITATION !",param->joueur2);
            }
            printf("\n\n\t\t\tAppuyer sur Entrée pour continuer");
            purger();
            liberer();
            etat_jeu=0;
            sem_post(&sem_etat);
            return;
        }
        else if(etat_jeu==6)// valide
        {
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

            if(tour%2)
            {
                strcpy(nouveau->joueur,param->joueur1);
            }
            else
            {
                strcpy(nouveau->joueur,param->joueur2);
            }

            nouveau->restant=restant - (difftime(time(NULL),temps_partie) - retard_global);
            sem_post(&sem_synch_jeu);
            sem_wait(&sem_synch_temps);

            tour++;
            affiche=0;
            retard_coup=0;
            temps_coup=time(NULL);
            continue;
        }


        while(affiche > (difftime(time(NULL),temps_coup) - retard_coup) )
        {usleep(100000);}

        actuel=difftime(time(NULL),temps_partie);

        if (affiche>=param->tps_joueur)
        {
        // A faire arret thrlastead jeu free mémoire et annoncer loser

        }
        else if ((actuel - retard_global)>=restant)
        {
        // A faire arret thrlastead jeu free mémoire et annoncer loser
        }

//        printf("%c7", 27);
        // A MODIFIER METTRE LE TEMPS RESTANT PAR COUP
        printf("%c7\x1b[9;0H", '\x1b');
        printf("Temps restant pour la partie : %0.0lf\n",restant-(actuel - retard_global));
        printf("Temps restant pour le coup: %0.0lf\n",param->tps_joueur - affiche);
        printf("%c8", '\x1b');
        fflush(stdout);

        affiche++;


        sem_post(&sem_etat);
        usleep(600000);


    }

}
