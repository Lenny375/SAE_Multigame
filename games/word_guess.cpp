#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <string>

// Codes couleurs ANSI
const std::string GREEN = "\033[1;32m";   // bien placé
const std::string YELLOW = "\033[1;33m";  // mal placé
const std::string RED = "\033[1;31m";     // absent
const std::string RESET = "\033[0m";

// Liste de mots de 5 lettres (pour les mots secrets seulement)
std::vector<std::string> mots = {
    "arbre", "avion", "biche", "buche", "crane", "drame", "flanc", "fraie", "glace",
    "gorge", "grave", "haine", "hibou", "jaune", "livre", "miel", "monte", "neige",
    "navet", "plage", "poire", "prune", "rouge", "rever", "table", "tombe", "usure", "verbe"
};

// Convertit une string en minuscule
std::string toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Vérifie que le mot saisi fait bien 5 lettres
bool motValide(const std::string& mot) {
    return mot.length() == 5;
}

// Affiche le mot en couleurs selon les lettres
void afficherFeedback(const std::string& essai, const std::string& motSecret) {
    std::string motTemp = motSecret; // Copie pour marquer les lettres déjà trouvées

    // Première passe : lettres bien placées
    for (int i = 0; i < 5; ++i) {
        if (essai[i] == motSecret[i]) {
            std::cout << GREEN << essai[i] << RESET;
            motTemp[i] = '*'; // Marque la lettre comme utilisée
        } else {
            std::cout << "_ "; // Placeholder pour alignement
        }
    }
    std::cout << "   ";

    // Deuxième passe : lettres mal placées ou absentes
    for (int i = 0; i < 5; ++i) {
        if (essai[i] == motSecret[i]) continue; // déjà traité

        size_t found = motTemp.find(essai[i]);
        if (found != std::string::npos) {
            std::cout << YELLOW << essai[i] << RESET;
            motTemp[found] = '*'; // Marque cette lettre
        } else {
            std::cout << RED << essai[i] << RESET;
        }
    }
    std::cout << std::endl;
}

bool jouerPartie() {
    std::string motSecret = mots[std::rand() % mots.size()];
    const int maxEssais = 5;
    std::string essai;

    std::cout << "\nDevine le mot en 5 lettres ! Tu as " << maxEssais << " essais.\n";

    for (int essaiNum = 1; essaiNum <= maxEssais; ++essaiNum) {
        do {
            std::cout << "\nEssai " << essaiNum << "/" << maxEssais << " : ";
            std::getline(std::cin, essai);
            essai = toLower(essai);

            if (!motValide(essai)) {
                std::cout << "Mot invalide. Entre un mot de 5 lettres.\n";
            }
        } while (!motValide(essai));

        if (essai == motSecret) {
            std::cout << GREEN << "Bravo ! Tu as trouve le mot : " << motSecret << " \n" << RESET;
            return true;
        }

        afficherFeedback(essai, motSecret);
    }

    std::cout << RED << "\nPerdu ! Le mot etait : " << motSecret << RESET << "\n";
    return false;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));

    while (true) {
        jouerPartie();

        std::cout << "\nVoulez-vous rejouer ? (o pour oui, autre pour quitter) : ";
        std::string rep;
        std::getline(std::cin, rep);
        if (rep != "o" && rep != "O") {
            std::cout << "Merci d'avoir joue ! A bientot.\n";
            break;
        }
    }

    return 0;
}
