#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

// =========================
// == Roulette Solo ========
// =========================
bool jouerPartieSolo() {
    const int chambers = 6;
    int bulletPosition = rand() % chambers;
    int currentChamber = 0;

    std::cout << "\n=== Roulette Russe (Solo) ===\n";
    std::cout << "Une balle est placée dans le barillet...\n";
    std::cout << "Appuie sur Entrée pour tirer, ou tape 'q' puis Entrée pour arrêter.\n\n";

    std::string input;
    while (true) {
        std::cout << "[Tirer ? (Entrée pour tirer, q pour quitter)] ";
        getline(std::cin, input);

        if (input == "q" || input == "Q") {
            std::cout << "Tu as choisi de quitter. \n";
            return false; // quitter le jeu
        }

        std::cout << "Tu appuies sur la gâchette... ";

        if (currentChamber == bulletPosition) {
            std::cout << " Bang ! Tu es mort.\n";
            return true; // mort, proposer de rejouer
        } else {
            std::cout << "clic. Sauvé cette fois.\n";
            currentChamber = (currentChamber + 1) % chambers;
        }
    }
}

// =========================
// == Roulette Duo  ========
// =========================
bool jouerPartieDuo() {
    std::string joueur1, joueur2;
    std::cout << "\n=== Nouvelle Partie : Duel de Roulette Russe ===\n";
    std::cout << "Nom du Joueur 1 : ";
    std::getline(std::cin, joueur1);
    std::cout << "Nom du Joueur 2 : ";
    std::getline(std::cin, joueur2);

    const int chambers = 6;
    int bulletPosition = std::rand() % chambers;
    int currentChamber = 0;

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
                continue;
            }
        }
        else if (choix == "2") {
            std::cout << currentPlayer << " tire sur " << opponent << "...\n";
            if (tirer()) {
                std::cout << opponent << " est mort ! " << currentPlayer << " gagne !\n";
                return true;
            } else {
                std::cout << "clic. Rate ! " << opponent << " prend le pistolet.\n";
                tour++;
            }
        }
        else {
            std::cout << "Choix invalide. Tour perdu.\n";
            tour++;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    while (true) {
        std::cout << "\nChoisissez le mode :\n1  Solo\n2  Duo\nVotre choix : ";
        int mode;
        std::cin >> mode;
        std::cin.ignore();

        bool estMortOuFin;
        if (mode == 1) {
            estMortOuFin = jouerPartieSolo();
        } else if (mode == 2) {
            estMortOuFin = jouerPartieDuo();
        } else {
            std::cout << "Choix invalide.\n";
            continue;
        }

        std::string replay;
        std::cout << "\nVoulez-vous rejouer ? (o pour oui, autre pour quitter) : ";
        std::getline(std::cin, replay);

        if (replay != "o" && replay != "O") {
            std::cout << "Merci d'avoir joué. À bientôt !\n";
            break;
        }
    }
    return 0;
}
