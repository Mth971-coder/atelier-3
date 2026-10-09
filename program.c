#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Procédure pour afficher le texte correspondant au choix numérique
void afficher_choix(int choix)
{
    switch (choix)
    {
        case 1:
            printf("Pierre");
            break;
        case 2:
            printf("Feuille");
            break;
        case 3:
            printf("Ciseaux");
            break;
        case 4:
            printf("Lézard");
            break;
        case 5:
            printf("Spock");
            break;
        default:
            printf("Inconnu");
            break;
    }
}

// Fonction qui retourne true si la partie doit continuer
bool partie_en_cours(int manche, int scoreJoueur, int scoreOrdi)
{
    return (manche <= 7 && scoreJoueur - scoreOrdi < 2 && scoreOrdi - scoreJoueur < 2);
}

// Fonction qui gère la saisie sécurisée du joueur et retourne son choix
int saisie_joueur()
{
    int choixJoueur;
    bool incorrect;
    do
    {
        printf("Faites votre choix :\n");
        for (int i = 1; i <= 5; i++)
        {
            printf("%d = ", i);
            afficher_choix(i);
            printf("\n");
        }
        printf("Votre choix (1-5) : ");
        scanf("%d", &choixJoueur);
        
        incorrect = choixJoueur < 1 || 5 < choixJoueur;
        if(incorrect) {
            printf("Non valide, valeurs de 1 à 5 acceptées\n");
        }
    } while (incorrect);
    
    return choixJoueur;
}

// Fonction qui détermine si le premier joueur gagne face au second
bool joueur1_gagne(int c1, int c2)
{
    return (c1 == 1 && (c2 == 3 || c2 == 4)) ||
           (c1 == 2 && (c2 == 1 || c2 == 5)) ||
           (c1 == 3 && (c2 == 2 || c2 == 4)) ||
           (c1 == 4 && (c2 == 2 || c2 == 5)) ||
           (c1 == 5 && (c2 == 1 || c2 == 3));
}

// Procédure pour afficher le bilan de la partie
void afficher_bilan(int scoreJoueur, int scoreOrdi)
{
    printf("=== FIN DE LA PARTIE ===\n");
    printf("Score final -> Vous : %d | Ordi : %d\n", scoreJoueur, scoreOrdi);
    
    if (scoreJoueur > scoreOrdi)
    {
        printf("Bravo, vous avez gagné la partie !\n");
    }
    else if (scoreOrdi > scoreJoueur)
    {
        printf("Dommage, vous avez perdu la partie !\n");
    }
    else
    {
        printf("Match nul !\n");
    }
}

int main()
{
    int scoreJoueur = 0;
    int scoreOrdi = 0;
    int manche = 1;
    int choixJoueur;
    int choixOrdi;
    
    printf("=== PIERRE, FEUILLE, CISEAUX, LEZARD, SPOCK (7 Manches / avantage décisif de 2) ===\n");
    
    // Utilisation de la fonction partie_en_cours
    while (partie_en_cours(manche, scoreJoueur, scoreOrdi))
    {
        printf("--- Manche %d/7 ---\n", manche);
        
        // Utilisation de la fonction saisie_joueur
        choixJoueur = saisie_joueur();
        
        // Choix aléatoire de l'ordinateur (1, 2, 3, 4 ou 5)
        choixOrdi = (rand() % 5) + 1;
        printf("L'ordinateur a choisi : ");
        afficher_choix(choixOrdi);
        printf("\n");
        
        // Détermination du gagnant de la manche
        if (choixJoueur == choixOrdi)
        {
            printf("Égalité !\n");
        }
        else if (joueur1_gagne(choixJoueur, choixOrdi)) // Utilisation de joueur1_gagne
        {
            printf("Vous gagnez cette manche !\n");
            scoreJoueur = scoreJoueur + 1;
        }
        else
        {
            printf("L'ordinateur gagne cette manche !\n");
            scoreOrdi = scoreOrdi + 1;
        }
        
        printf("Score actuel -> Vous : %d | Ordi : %d\n\n", scoreJoueur, scoreOrdi);
        manche = manche + 1;
    }
    
    // Bilan de la partie via la fonction dédiée
    afficher_bilan(scoreJoueur, scoreOrdi);
    
    return 0;
}