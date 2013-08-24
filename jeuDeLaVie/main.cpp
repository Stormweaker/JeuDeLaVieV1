#include <iostream>
#include <ctime>
#include <cstdlib>
#include<windows.h>

using namespace std;

void firstGen(int gen[79][20]) //creation de la grille initiale, proba de 0.5
{
    for(int i(0); i < 79; i++)
    {
        for(int j(0); j < 20; j++)
        {
            gen[i][j] = rand() % 2;
        }
    }
}

void affichage(int grille[79][20]) //affichage ligne par ligne de la grille en lisant le tableau
{
    string ligne("");
    for(int i(0); i < 20; i++)
    {
        ligne = "";
        for(int j(0); j < 79; j++)
        {
            if(grille[j][i] == 0)
            {
                ligne += "=";
            }else if(grille[j][i] == 1)
            {
                ligne += "O";
            }
        }
        cout << ligne << endl;
    }
}

int checkAlive(int grille[79][20], int i, int j) //trouver le nombre de cases "en vie" autour de celle en position (i,j)
{
    int alive(0);
    for(int k(i-1); k <= i+1; k++)
    {
        for(int l(j-1); l <= j+1; l++)
        {
            if(grille[k][l] == 1)
            {
                alive++;
            }
        }
    }
    if(grille[i][j] == 1)
    {
        alive--;
    }

    return alive;
}

void evolve(int grilleT[79][20], int grilleT1[79][20]) //generer la grille suivante d'apres les regles
{                                                      //lecture case par case de la grille a l'instant t (grilleT)
    int alive(0);                                      //puis enregistrement du nouvel etat de la case a l'instant t+1 (grilleT1)
    for(int i(0); i < 79; i++)
    {
        for(int j(0); j < 20; j++)
        {
            if(grilleT[i][j] == 0)
            {
                alive = checkAlive(grilleT, i, j);
                if(alive == 3)
                {
                    grilleT1[i][j] = 1;
                }
            }else if(grilleT[i][j] == 1)
            {
                alive = checkAlive(grilleT, i, j);
                if(alive < 2 || alive > 3)
                {
                    grilleT1[i][j] = 0;
                }
            }
        }
    }
}

void egal(int grilleT[79][20], int grilleT1[79][20]) //egaliser les deux tableaux
{
    for(int i(0); i < 79; i++)
    {
        for(int j(0); j < 20; j++)
        {
            grilleT[i][j] = grilleT1[i][j];
        }
    }
}

int main()
{
    srand(time(NULL));
    int grilleT[79][20], grilleT1[79][20]; //grilles a l'instant t et a l'instant t+1
    int nbEvolve(1), nbEv(0);   //nombre d'evolutions souhaitees et nombre d'evoltuions faites
    char cont('O');

    firstGen(grilleT);
    affichage(grilleT);

    while(cont == 'O') //boucle pour continuer en donnant le nombre d'evolutions a faire d'une traite
    {
        cout << "Combien d'evolutions voulez vous faire?" << endl;
        cin >> nbEvolve;

        for(int i(0); i < nbEvolve; i++)
        {
            evolve(grilleT, grilleT1);
            nbEv++;
            egal(grilleT, grilleT1);

            affichage(grilleT);
            cout << nbEv << endl << endl << endl;
            Sleep(400);   //pause dans le programme pour voir les cases vivre
        }

        cout << "Continuer?" << endl;
        cin >> cont;
    }
    return 0;
}
