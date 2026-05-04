#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

bool jouerPartie() {
    std::string joueur1, joueur2;
    std::cout << "\n=== Nouvelle Partie : Duel de Roulette Russe ===\n";
    std::cout << "Nom du Joueur 1 : ";
    std::getline(std::cin, joueur1);
    std::cout << "Nom du Joueur 2 : ";
    std::getline(std::cin, joueur2);

    // Variables pour le barillet
    const int chambers = 6;                    // 6 chambres
    int bulletPosition = std::rand() % chambers; // position de la balle
    int currentChamber = 0;                     // chambre actuelle

    int tour = 0;
    std::string currentPlayer, opponent;

    while (true) {
        currentPlayer = (tour % 2 == 0) ? joueur1 : joueur2;
        opponent = (tour % 2 == 0) ? joueur2 : joueur1;

        std::cout << "\n--- Tour de " << currentPlayer << " ---\n";
        std::cout << "1. Se tirer dessus\n";
        std::cout << "2. Tirer sur " << opponent << "\n";
        std::cout << "Choix (1 ou 2) : ";

        std::string choix;
        std::getline(std::cin, choix);

        auto tirer = [&]() -> bool {
            bool mort = (currentChamber == bulletPosition);
            currentChamber = (currentChamber + 1) % chambers;
            return mort;
        };

        if (choix == "1") {
            std::cout << currentPlayer << " se tire dessus...\n";
            if (tirer()) {
                std::cout << currentPlayer << " est mort ! " << opponent << " gagne !\n";
                return true;
            } else {
                std::cout << "clic. Rien ne se passe. " << currentPlayer << " a survecu et rejoue immediatement !\n";
                continue; // le joueur rejoue automatiquement
            }
        }
        else if (choix == "2") {
            std::cout << currentPlayer << " tire sur " << opponent << "...\n";
            if (tirer()) {
                std::cout << opponent << " est mort ! " << currentPlayer << " gagne !\n";
                return true;
            } else {
                std::cout << "clic. Rate ! " << opponent << " prend le pistolet.\n";
                tour++; // passe au joueur suivant
            }
        }
        else {
            std::cout << "Choix invalide. Tour perdu.\n";
            tour++; // mauvaise saisie = passe le tour
        }
    }
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(0))); // initialisation aléatoire

    while (true) {
        bool partieFinie = jouerPartie();

        std::cout << "\nVoulez-vous rejouer ? (o pour oui, autre pour quitter) : ";
        std::string replay;
        std::getline(std::cin, replay);

        if (replay != "o" && replay != "O") {
            std::cout << "Merci d'avoir joue. A bientot !\n";
            break;
        }
    }

    return 0;
}
