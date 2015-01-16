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

// Début du jeu
etat_jeu=1;

// Création du thread de saisie
pthread_t IDjeu;
pthread_create(&IDjeu,NULL,jeu,NULL);

// On attend que le thread jeu affiche le menu.
sem_wait(&sem_synch_temps);

// On initialise les timers
time_t temps_coup=time(NULL);
time_t temps_partie=time(NULL);
int actuel=0;
double affiche=0,retard_global=0,retard_coup=0,retard=0;

while (1)
    {
    sem_wait(&sem_etat);

        if (etat_jeu==2) // Sauvegarde et fin de partie
        {
            time_t temps_retard=time(NULL);
            pthread_join(IDjeu,NULL);
            // En cas d'erreur on relance le thread jeu sinon le jeu se termine
            if(sauvegarder()==ERREUR)
            {
                pthread_create(&IDjeu,NULL,jeu,NULL);
                sem_wait(&sem_synch_temps);
                etat_jeu=1;

                // On prend en compte le temps passer à essayer de sauvegarder
                retard=difftime(time(NULL),temps_retard);
                retard_coup=retard_coup+retard;
                retard_global=retard_global+retard;
            }
            else
            {
                etat_jeu=0;
                sem_post(&sem_etat);
                return;
            }
        }
        else if(etat_jeu==4)// Quitter
        {
            pthread_join(IDjeu,NULL);
            quitter();
        }
        else if(etat_jeu==3)// Pause
        {
            // On lance le timer de retard
            time_t temps_retard=time(NULL);
            sem_wait(&sem_synch_temps);

            // On réaffiche le temps pour éviter d'avoir des zones vides
            printf("%c7\x1b[9;0H", '\x1b');
            if (restant-(actuel - retard_global)>=60)
            {
                int minute=(restant-(actuel - retard_global))/60;
                printf("Temps restant pour la partie : %d min %0.0lf sec\n",minute,(restant-(actuel - retard_global))-minute*60);
            }
            else
            {
                printf("Temps restant pour la partie : %0.0lf sec\n",restant-(actuel - retard_global));
            }

            if (param->tps_joueur - affiche +1 >restant-(actuel - retard_global))
            {
                printf("Temps restant pour le coup: %0.0lf sec\n",restant-(actuel - retard_global));
            }
            else
            {
                printf("Temps restant pour le coup: %0.0lf sec\n",param->tps_joueur - affiche +1 );
            }

            if(tour%2)
            {
                printf("\n%8s : ",param->joueur1);
            }
            else
            {
                printf("\n%8s : ",param->joueur2);
            }

            printf("%c8", '\x1b');
            fflush(stdout);

            // On calcul les retards
            retard=difftime(time(NULL),temps_retard);
            retard_coup=retard_coup+retard;
            retard_global=retard_global+retard;
            etat_jeu=1;
        }
        else if(etat_jeu==5)// gagnant
        {
            system("clear");
            if(tour%2)
            {
                printf("\n\n\n\n\n\n\n\n\t\t   %s tu as gagné FELICITATIONS !",param->joueur1);
            }
            else
            {
                printf("\n\n\n\n\n\n\n\n\t\t   %s tu as gagné FELICITATIONS !",param->joueur2);
            }
            printf("\n\n\t\t   Appuyer sur Entrée pour continuer");
            purger();
            liberer();
            etat_jeu=0;
            sem_post(&sem_etat);
            return;
        }
        else if(etat_jeu==6)// valide
        {
            // Allocation du prochain élément de la liste
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

            // On écrit le nom du joueur en cours
            if(tour%2)
            {
                strcpy(nouveau->joueur,param->joueur1);
            }
            else
            {
                strcpy(nouveau->joueur,param->joueur2);
            }

            // On écrit le temps restant
            nouveau->restant=restant - (difftime(time(NULL),temps_partie) - retard_global);

            // On donne la main au thread jeu pour qu'il écrive le coup puis l'on reprend l'éxecution.
            sem_post(&sem_synch_jeu);

            sem_wait(&sem_synch_temps);

            // On réinitialise les variables et on relance la boucle
            tour++;
            affiche=0;
            retard_coup=0;
            etat_jeu=1;
            temps_coup=time(NULL);

            sem_post(&sem_synch_jeu);
        }
        else
        {

        // On s'assure qu'une seconde s'est écoulée depuis le dernier affichage
        while(affiche > (difftime(time(NULL),temps_coup) - retard_coup) )
        {usleep(100000);}

        actuel=difftime(time(NULL),temps_partie);

        if (affiche>=param->tps_joueur) // Si le joueur à trop attendu pour son tour
        {
            pthread_cancel(IDjeu);
            system("clear");
            // On détecte quel joueur joue à partir de la parité du tour
            if(tour%2)
            {
                printf("\n\n\n\n\n\n\n\n\t%s tu n'as pas joué avant la fin de ton temps tu as perdu !",param->joueur1);
            }
            else
            {
                printf("\n\n\n\n\n\n\n\n\t%s tu n'as pas joué avant la fin de ton temps tu as perdu !",param->joueur2);
            }
            printf("\n\n\t\t   Appuyer sur Entrée pour continuer");
            purger();
            liberer();
            etat_jeu=0;
            sem_post(&sem_etat);
            return;
        }
        else if ((actuel - retard_global)>=restant)// S'il n'y a plus de temps pour la partie
        {
            pthread_cancel(IDjeu);
            system("clear");
            // On détecte quel joueur joue à partir de la parité du tour
            if(tour%2)
            {
                printf("\n\n\n\n\n\n\n\n\t%s il n'y a plus de temps pour la partie tu as perdu !",param->joueur1);
            }
            else
            {
                printf("\n\n\n\n\n\n\n\n\t%s il n'y a plus de temps pour la partie tu as perdu !",param->joueur2);
            }
            printf("\n\n\t\t   Appuyer sur Entrée pour continuer");
            purger();
            liberer();
            etat_jeu=0;
            sem_post(&sem_etat);
            return;
        }

        // Affichage des comptes à rebours et du nom
        printf("%c7\x1b[9;0H", '\x1b');
        if (restant-(actuel - retard_global)>=60)
        {
            int minute=(restant-(actuel - retard_global))/60;
            printf("Temps restant pour la partie : %d min %0.0lf sec\n",minute,(restant-(actuel - retard_global))-minute*60);
        }
        else
        {
            printf("Temps restant pour la partie : %0.0lf sec\n",restant-(actuel - retard_global));
        }

        if (param->tps_joueur - affiche>restant-(actuel - retard_global))
        {
            printf("Temps restant pour le coup: %0.0lf sec\n",restant-(actuel - retard_global));
        }
        else
        {
            printf("Temps restant pour le coup: %0.0lf sec\n",param->tps_joueur - affiche);
        }

        if(tour%2)
        {
            printf("\n%8s : ",param->joueur1);
        }
        else
        {
            printf("\n%8s : ",param->joueur2);
        }

        printf("%c8", '\x1b');
        fflush(stdout);

        affiche++;

        }

        // Libération du sémaphore pour laisser le temps au thread jeu de le modifier si nécessaire
        sem_post(&sem_etat);
        usleep(600000);

    }

}

