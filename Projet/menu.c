#include "header.h"

extern param_structure * param;

void thread_time( int tps_global,int tps_joueur)
    {


    //récup temps
    time_t t;
    char *date;
    t = time(NULL);
    date = ctime(&t);
    printf("%s\n", date);

    }

int thread_menu()
    {

    int choix;
    while(1)
        {

        system("clear");

        printf("\t\t Menu du jeu : \n\n");
        printf("\t1. Nouvelle partie\n");
        printf("\t2. Charger une partie\n");
        printf("\t3. Interrompre la partie & Sauvegarder\n");
        printf("\t4. Pause\n");
        printf("\t5. Reprendre la partie\n");
        printf("\t6. Historique\n");
        printf("\t7. Quitter l'application\n\n\n");


        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar();

        switch(choix)
            {
            case 1 : Nvlle_partie();break;
            case 2 : recup_chemin(CHARGER);break;
            case 3 : sauvegarder();break;
            case 4 : pause();break;
            case 5 : resume();break;
            case 6 : recup_chemin(HISTORIQUE);break;
            case 7 : quitter();break;
            default :printf("\n\nMauvaise saisie.\n\n");;
            }

        }



    }




void Nvlle_partie(){

    char joueur1[8]="", joueur2[8]="";
    int tps_global=0, tps_joueur=0;
    int error1=1, error2=1,retour; /* retour du scanf*/
    int cond=0;

    printf("\n\n\t >>>>Nouvelle partie<<<< \n");

    //saisie des noms des 2 joueurs
    while(error1)
    {
        printf("Nom joueur 1 (doit être inférieur à 8 caractères):");
        scanf("%s", joueur1);
        getchar();

        if((strlen(joueur1) >= 1) && (strlen(joueur1) <= 8) )
            {
            error1=0;
            }

     /*le nom ne doit pas dépasser 8 caractères, si c'est le cas recommence la saisie*/
     }
    strcpy(param->joueur1,joueur1);

     while(error2)
    {
        printf("Nom joueur 2 (doit être inférieur à 8 caractères):");
        scanf("%s", joueur2);
        if((strlen(joueur2) >= 1) && (strlen(joueur2) <= 8))
            {
            error2=0;
            }
        if(strcmp(joueur1,joueur2)==0)
            {
            printf("Euuh, c'est un jeu pour 2 joueurs, tu ne peux pas jouer contre toi-même.\n");
            error2=1;
            }
     /*le nom ne doit pas dépasser 8 caractères, si c'est le cas, recommence la saisie*/
     }
     strcpy(param->joueur2,joueur2);

    //Saisie différents temps de jeu.
   /* while(error_timeG)*/
    {
        printf("Définir le temps de la partie (en secondes):");


    while (!cond)
        {

            retour = scanf("%d%*[^\n]", &tps_global);
        printf("retour : %d\n", retour);
        if ( !retour )
            {
            /* erreur de saisie, on vide le flux */
            purger();

            printf("on vous a demande de saisir un nombre\n");
            printf("veuillez recommencer :\n");
            }
        else
            {
            /* reussite de la saisie */
            getchar(); /* on enleve le '\n' restant */

            printf("saisie acceptee\n");
            cond = 1;  /* sort de la boucle */
    }

  }

            printf("Le temps de la partie est de %d secondes\n", tps_global);
            param->tps_global=tps_global;
            cond=0; /* réinitialise cond*/



        printf("Définir le temps pour un coup (en secondes):");

    while (!cond){

    retour = scanf("%d%*[^\n]", &tps_joueur);
    printf("retour : %d\n", retour);
    if ( !retour )
        {
        /* erreur de saisie, on vide le flux */
      purger();

      printf("on vous a demande de saisir un nombre\n");
      printf("veuillez recommencer :\n");
        }
    else
        {
        /* reussite de la saisie */
        getchar(); /* on enleve le '\n' restant */

        printf("saisie acceptee\n");
        cond = 1;  /* sort de la boucle */
        }

        }

        printf("Le temps par coup est de %d secondes\n", tps_joueur);
        param->tps_joueur=tps_joueur;


        printf("\n\n\t\t Début de la partie\n");
        sleep(1);

    }

    // On initialise le thread temps avec le temps de la partie puis on lance le jeu
    init_temps(-1);

}

void purger()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}
void interruption(){}
void resume(){}
void quitter ()
{
// Gérer la libération mémoire =======================

exit(1);
}

