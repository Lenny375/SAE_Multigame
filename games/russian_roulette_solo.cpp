#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool jouerPartie() {
    const int chambers = 6;
    int bulletPosition = rand() % chambers;
    int currentChamber = 0;

    cout << "\n=== Nouvelle Partie ===\n";
    cout << "Une balle est placee dans le barillet...\n";
    cout << "Appuie sur Entree pour tirer, ou tape 'q' puis Entree pour arreter.\n\n";

    string input;

    while (true) {
        cout << "[Tirer ? (Entree pour tirer, q pour quitter)] ";
        getline(cin, input);

        if (input == "q" || input == "Q") {
            cout << "Tu as choisi de quitter. \n";
            return false; // quitter le jeu
        }

        cout << "Tu appuies sur la gachette... ";

        if (currentChamber == bulletPosition) {
            cout << " Bang ! Tu es mort.\n";
            return true; // mort, proposer de rejouer
        } else {
            cout << "clic. Sauve cette fois.\n";
            currentChamber = (currentChamber + 1) % chambers;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    bool rejouer = true;

    while (rejouer) {
        bool estMort = jouerPartie();

        if (estMort) {
            string choix;
            cout << "\nVeux-tu rejouer ? (o/n) : ";
            getline(cin, choix);

            if (choix != "o" && choix != "O") {
                rejouer = false;
                cout << "Fin du jeu. Repose en paix. \n";
            }
        } else {
            // Le joueur a quitté volontairement
            rejouer = false;
            cout << "Merci d'avoir joue. A bientot ! \n";
        }
    }

    return 0;
}
