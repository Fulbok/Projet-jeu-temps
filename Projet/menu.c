#include "header.h"


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

    int choix,error=1,restant;
    while(1)
        {

        system("clear");

        printf("\t Menu du jeu : \n");
        printf("1. Nouvelle partie\n");
        printf("2. Charger une partie\n");
        printf("3. Interrompre la partie & Sauvegarder\n");
        printf("4. Pause\n");
        printf("5. Reprendre la partie\n");
        printf("6. Historique\n");
        printf("7. Quitter l'application\n\n");

        if(error==0)
        {
        printf("\n\nTu ne sais pas lire abruti ?...\n\n");
        error=1;
        }

        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar();

        switch(choix)
            {
            case 1 : Nvlle_partie();break;
            case 2 : recup_chemin(CHARGER);break;
            case 3 : sauvegarder(restant);break;
            case 4 : pause();break;
            case 5 : resume();break;
            case 6 : recup_chemin(HISTORIQUE);break;
            case 7 : quitter();break;
            default :error=0;
            }


        }





    }




void Nvlle_partie(){

    char joueur1[8]="", joueur2[8];
    int tps_global, tps_joueur;
    int error1=1, error2=1, error_timeG=1, error_timeJ=1;
    char test_time[4]; /*pour détecter erreur saisie temps */
    int i=0, cond=1;

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

    //Saisie différents temps de jeu.
   /* while(error_timeG)*/
    {
        printf("Définir le temps de la partie (en secondes):");
        scanf("%d", &tps_global);
      /*  sprintf(test_time, "%d", tps_global);
        while(i < 4 && cond)
            {
            if((test_time[i]-30 < 0) && (test_time[i]-40 < 0))
                {
                error_timeG = 0;
                i++;
                }

            else
                {
                error_timeG = 1;
                cond = 0;
                }

            }
            */


    }

        printf("Le temps de la partie est de %d secondes\n", tps_global);


    /*while(error_timeJ)*/
    {
        printf("Définir le temps pour un coup (en secondes):");
        scanf("%d", &tps_joueur);
    }

        printf("Le temps par coup est de %d secondes\n", tps_joueur);


        printf("\t Début de la partie\n");



<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes



}

void pause(){}
void resume(){}
void quitter (){
exit(1);
}


