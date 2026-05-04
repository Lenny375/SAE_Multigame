#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

// Met en minuscules et nettoie la saisie
std::string normaliserChoix(std::string input)
{
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());

    if (input == "p" || input == "pierre") return "Pierre";
    if (input == "f" || input == "feuille") return "Feuille";
    if (input == "c" || input == "ciseau" || input == "ciseaux") return "Ciseau";
    return "";
}

std::string choixBotAleatoire()
{
    int bot = std::rand() % 3;
    switch(bot)
    {
        case 0: return "Pierre";
        case 1: return "Feuille";
        default: return "Ciseau";
    }
}

// Renvoie 1 si victoire, -1 si défaite, 0 si égalité
int resultatManche(const std::string& joueur, const std::string& bot)
{
    if (joueur == bot) return 0;
    if ((joueur == "Pierre" && bot == "Ciseau") ||
        (joueur == "Feuille" && bot == "Pierre") ||
        (joueur == "Ciseau" && bot == "Feuille"))
        return 1;
    else
        return -1;
}

// Joue une série complète de 10 manches, retourne le score de série
int jouerSerie()
{
    int scoreSerie = 0;
    for (int manche = 1; manche <= 10; ++manche)
    {
        std::string choixJoueur;
        while (true)
        {
            std::cout << "\n--- Manche " << manche << "/10 ---" << std::endl;
            std::cout << "Liste des Choix :\n- Pierre (ou p)\n- Feuille (ou f)\n- Ciseau (ou c)" << std::endl;
            std::cout << "Que voulez-vous jouer ? ";
            std::getline(std::cin, choixJoueur);

            choixJoueur = normaliserChoix(choixJoueur);
            if (!choixJoueur.empty()) break;
            std::cout << "Choix invalide. Veuillez reessayer." << std::endl;
        }

        std::string choixBot = choixBotAleatoire();
        std::cout << "\nVotre choix : " << choixJoueur << std::endl;
        std::cout << "Le bot a choisi : " << choixBot << std::endl;

        int resultat = resultatManche(choixJoueur, choixBot);
        if (resultat == 1)
        {
            std::cout << "Vous avez gagne !" << std::endl;
            scoreSerie += 2;
        }
        else if (resultat == -1)
        {
            std::cout << "Vous avez perdu." << std::endl;
            scoreSerie -= 1;
        }
        else
        {
            std::cout << "Egalite !" << std::endl;
        }

        std::cout << "Score actuel de la série : " << scoreSerie << std::endl;
    }
    return scoreSerie;
}

void afficherRegles()
{
    std::cout << "=== Pierre - Feuille - Ciseau ===" << std::endl;
    std::cout << "\nRegle du jeu :" << std::endl;
    std::cout << "Deux joueurs choisissent simultanement un des trois elements :" << std::endl;
    std::cout << "Pierre, Feuille ou Ciseau." << std::endl;
    std::cout << "Le but est de battre le choix de l'adversaire selon les regles ci-dessous." << std::endl;
    std::cout << "- La Pierre bat le Ciseau." << std::endl;
    std::cout << "- Le Ciseau bat la Feuille." << std::endl;
    std::cout << "- La Feuille bat la Pierre." << std::endl;
    std::cout << "\nRecompense :" << std::endl;
    std::cout << "+2 points par victoire" << std::endl;
    std::cout << "-1 point par defaite" << std::endl;
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    afficherRegles();

    int scoreTotal = 0;
    while (true)
    {
        std::cout << "\n=== Nouvelle série de 10 manches ===" << std::endl;
        int scoreSerie = jouerSerie();
        scoreTotal += scoreSerie;

        std::cout << "\n=== Fin de la série de 10 manches ===" << std::endl;
        std::cout << "Score de la série : " << scoreSerie << std::endl;
        std::cout << "Score total : " << scoreTotal << std::endl;

        std::string rejouerSerie;
        std::cout << "\nVoulez-vous rejouer une nouvelle série de 10 manches ? (o pour oui, autre pour quitter) : ";
        std::getline(std::cin, rejouerSerie);
        if (rejouerSerie != "o" && rejouerSerie != "O")
        {
            std::cout << "\nMerci d'avoir joue ! Score final : " << scoreTotal << std::endl;
            std::cout << "A bientot.\n";
            break;
        }
    }
    return 0;
}
