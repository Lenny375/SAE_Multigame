#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

// --------- MORPION (DUO) ---------
struct Morpion {
    int lignes;
    int colonnes;
    std::vector<std::vector<char>> grille;
    char joueur_actuel;
    int symboles_a_aligner;
    std::string joueur1;
    std::string joueur2;
};

Morpion initialiserJeu(int n, int m, const std::string& j1, const std::string& j2) {
    Morpion jeu;
    jeu.lignes = n;
    jeu.colonnes = m;
	// Construction d'une matrice n x m initialisée avec des espaces ' '
    jeu.grille = std::vector<std::vector<char>>(n, std::vector<char>(m, ' '));
    jeu.joueur_actuel = 'X';
    jeu.joueur1 = j1;
    jeu.joueur2 = j2;
	// Ici on choisit d'aligner le minimum entre lignes et colonnes (ex: 3x3 => 3)
    jeu.symboles_a_aligner = std::min(n, m);
    return jeu;
}

void afficherGrille(const Morpion& jeu) {
    std::cout << "\n   ";
    for (int col = 0; col < jeu.colonnes; col++) {
        std::cout << " " << col + 1 << "  ";
    }
    std::cout << "\n";
    for (int i = 0; i < jeu.lignes; i++) {
        std::cout << "   ";
        for (int col = 0; col < jeu.colonnes; col++) {
            std::cout << "----";
        }
        std::cout << "-\n";
        std::cout << " " << i + 1 << " ";
        for (int j = 0; j < jeu.colonnes; j++) {
            std::cout << "| " << jeu.grille[i][j] << " ";
        }
        std::cout << "|\n";
    }
    std::cout << "   ";
    for (int col = 0; col < jeu.colonnes; col++) {
        std::cout << "----";
    }
    std::cout << "-\n\n";
}

bool verifierVictoire(const Morpion& jeu, char joueur) {
    int n = jeu.symboles_a_aligner;
    // Lignes
    for (int i = 0; i < jeu.lignes; i++)
        for (int j = 0; j <= jeu.colonnes - n; j++) {
            bool gagne = true;
            for (int k = 0; k < n; k++)
                if (jeu.grille[i][j + k] != joueur) gagne = false;
            if (gagne) return true;
        }
    // Colonnes
    for (int j = 0; j < jeu.colonnes; j++)
        for (int i = 0; i <= jeu.lignes - n; i++) {
            bool gagne = true;
            for (int k = 0; k < n; k++)
                if (jeu.grille[i + k][j] != joueur) gagne = false;
            if (gagne) return true;
        }
    // Diagonales descendantes
    for (int i = 0; i <= jeu.lignes - n; i++)
        for (int j = 0; j <= jeu.colonnes - n; j++) {
            bool gagne = true;
            for (int k = 0; k < n; k++)
                if (jeu.grille[i + k][j + k] != joueur) gagne = false;
            if (gagne) return true;
        }
    // Diagonales montantes
    for (int i = n - 1; i < jeu.lignes; i++)
        for (int j = 0; j <= jeu.colonnes - n; j++) {
            bool gagne = true;
            for (int k = 0; k < n; k++)
                if (jeu.grille[i - k][j + k] != joueur) gagne = false;
            if (gagne) return true;
        }
    return false;
}

bool grilleComplete(const Morpion& jeu) {
    for (auto& ligne : jeu.grille)
        for (auto c : ligne)
            if (c == ' ') return false;
    return true;
}

bool jouerCoup(Morpion& jeu, int ligne, int colonne) {
    if (ligne < 1 || ligne > jeu.lignes || colonne < 1 || colonne > jeu.colonnes) {
        std::cout << "Position invalide !\n";
        return false;
    }
    int i = ligne - 1, j = colonne - 1;
    if (jeu.grille[i][j] != ' ') {
        std::cout << "Case deja occupee !\n";
        return false;
    }
    jeu.grille[i][j] = jeu.joueur_actuel;
    return true;
}

void changerJoueur(Morpion& jeu) {
    jeu.joueur_actuel = (jeu.joueur_actuel == 'X') ? 'O' : 'X';
}

int jouerMorpion(const std::string& joueur1, const std::string& joueur2) {
    std::cout << "\n=== JEU DE MORPION ===\n";
    int lignes, colonnes;
    std::cout << "Saisir le nombre de lignes : ";
    std::cin >> lignes;
    std::cout << "Saisir le nombre de colonnes : ";
    std::cin >> colonnes;
    std::cin.ignore(); // consomme le '\n' laissé par l'entrée précédente
    Morpion jeu = initialiserJeu(lignes, colonnes, joueur1, joueur2);
    std::cout << joueur1 << " joue avec les X | " << joueur2 << " joue avec les O\n";
    while (true) {
        afficherGrille(jeu);
        std::string nomJoueur = (jeu.joueur_actuel == 'X') ? jeu.joueur1 : jeu.joueur2;
        std::cout << "Tour de " << nomJoueur << " (" << jeu.joueur_actuel << ")\n";
        int ligne, colonne;
        std::cout << "Ligne : ";
        std::cin >> ligne;
        std::cout << "Colonne : ";
        std::cin >> colonne;
        if (jouerCoup(jeu, ligne, colonne)) {
            if (verifierVictoire(jeu, jeu.joueur_actuel)) {
                afficherGrille(jeu);
                std::cout << "Bravo " << nomJoueur << " ! Vous avez gagne !\n";
                return 5;
            }
            if (grilleComplete(jeu)) {
                afficherGrille(jeu);
                std::cout << "Match nul !\n";
                return 0;
            }
            changerJoueur(jeu);
        }
    }
}

// --------- PIERRE-FEUILLE-CISEAU (SOLO/HARDCORE) ---------

std::string faireChoix(std::string input, bool hardcore = false) {
	// transforme toutes les lettres en minuscules
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	// supprime les espaces : remove_if retourne un itérateur, erase retire la partie non voulue
    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
    if (input == "p" || input == "pierre") return "Pierre";
    if (input == "f" || input == "feuille") return "Feuille";
    if (input == "c" || input == "ciseau" || input == "ciseaux") return "Ciseau";
    if (hardcore && (input == "pu" || input == "puit")) return "Puit";
    return ""; // entrée non reconnue
}

// Renvoie un choix random adapté au mode hardcore (ajout du Puit)
std::string choixBotPierreFeuilleCiseau(bool hardcore) {
    int bot = std::rand() % (hardcore ? 4 : 3);
    if (bot == 0) return "Pierre";
    if (bot == 1) return "Feuille";
    if (bot == 2) return "Ciseau";
    if (hardcore && bot == 3) return "Puit";
    return "Pierre";
}

// Renvoie le résultat du round selon hardcore
int resultatPierreFeuilleCiseau(const std::string& joueur, const std::string& bot, bool hardcore) {
    if (joueur == bot) return 0; // égalité
    // règles supplémentaires pour le mode hardcore
    if (hardcore) {
        if (joueur == "Puit") {
            if (bot == "Pierre" || bot == "Ciseau") return 2; // Puit bat Pierre et Ciseau
            if (bot == "Feuille") return -1; // Feuille bat Puit
        }
        if (bot == "Puit") {
            if (joueur == "Pierre" || joueur == "Ciseau") return -1;
            if (joueur == "Feuille") return 2;
        }
    }
    // classique
    if ((joueur == "Pierre" && bot == "Ciseau") ||
        (joueur == "Feuille" && bot == "Pierre") ||
        (joueur == "Ciseau" && bot == "Feuille")) return 2;
    // perdu
    return -1;
}

int jouerPierreFeuilleCiseau(bool hardcore = false) {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // mélange le générateur
    std::cout << "\n=== Pierre - Feuille - Ciseau";
    if (hardcore) std::cout << " + Puit [MODE HARDCORE]";
    std::cout << " ===\n";
    int scoreTotal = 0;
    for (int manche = 1; manche <= 10; ++manche) {
        std::string action;
        std::cout << "\nManche " << manche << "/10\nChoix ";
        std::cout << "(Pierre/P, Feuille/F, Ciseau/C";
        if (hardcore) std::cout << ", Puit/Pu";
        std::cout << ") : ";
        std::getline(std::cin, action);
        std::string choixJoueur = faireChoix(action, hardcore);
        if (choixJoueur.empty()) { std::cout << "Choix invalide.\n"; --manche; continue; }
        std::string choixBot = choixBotPierreFeuilleCiseau(hardcore);

        std::cout << "Vous : " << choixJoueur << " | Bot : " << choixBot << "\n";
        int res = resultatPierreFeuilleCiseau(choixJoueur, choixBot, hardcore);
        if (res == 0) std::cout << "Egalite !\n";
        else if (res > 0) { std::cout << "Victoire ! +" << res << " pts\n"; scoreTotal += res; }
        else { std::cout << "Defaite ! -1 pt\n"; scoreTotal -= 1; }
        std::cout << "Score : " << scoreTotal << "\n";
    }
    std::cout << "\nSerie terminee. Score : " << scoreTotal << "\n";
    return scoreTotal;
}

// --------- ROULETTE RUSSE ---------

// Mode hardcore: réduit le nombre de balles à blanc du mode duo
int jouerRouletteRusseSolo() {
    const int chambers = 6;
    int bulletPosition = rand() % chambers; // position de la balle (0..5)
    int currentChamber = 0;
    int score = 0;
    std::string input;
    std::cout << "\n=== Roulette Russe (Solo) ===\n";
    std::cout << "Chaque clic sauve rapporte +2 points.\n";
    std::cout << "Si tu meurs... tu perds tout.\n\n";
    while (true) {
        std::cout << "[Entree pour tirer, q pour arreter] ";
        std::getline(std::cin, input);
        if (input == "q" || input == "Q") {
            std::cout << "\nTu arretes ici. Score gagne : " << score << "\n";
            return score; // on quitte et garde le score
        }
        std::cout << "Tu appuies sur la gachette... ";
        if (currentChamber == bulletPosition) {
            std::cout << "BANG ! Tu es mort.\n";
            std::cout << "Tu perds tout ton score pour cette partie.\n";
            return 0; // tout perdu
        } else {
            std::cout << "clic. Sauve cette fois.\n";
            score += 2;
            std::cout << "Score actuel : " << score << "\n";
            currentChamber = (currentChamber + 1) % chambers;
        }
    }
}

// Mode duo adapté pour hardcore (plus de balles chargées, plus risqué)
int jouerRouletteRusseDuo(const std::string& joueur1, const std::string& joueur2, bool hardcore = false) {
    const int chambers = 6;
    int numBullets = hardcore ? 3 : 1; // HARDCORE: plus de balles
    std::vector<bool> barillet(chambers, false);
    // Place les balles
    int placed = 0;
    while (placed < numBullets) {
        int pos = rand() % chambers;
        if (!barillet[pos]) { barillet[pos] = true; placed++; }
    }
    int currentChamber = 0;
    int tour = 0;
    std::cout << "\n=== Roulette Russe (Duo";
    if (hardcore) std::cout << " [MODE HARDCORE]";
    std::cout << ") ===\n";
    std::cout << joueur1 << " vs " << joueur2 << "\n";
    while (true) {
        std::string currentPlayer = (tour % 2 == 0) ? joueur1 : joueur2;
        std::string opponent = (tour % 2 == 0) ? joueur2 : joueur1;
        std::cout << "\n--- Tour de " << currentPlayer << " ---\n";
        std::cout << "1. Se tirer dessus\n";
        std::cout << "2. Tirer sur " << opponent << "\n";
        std::cout << "Choix (1 ou 2) : ";
        std::string choix;
        std::getline(std::cin, choix);
		// lambda (fonction locale) pour tirer : renvoie true si mort
        auto tirer = [&]() -> bool {
            bool mort = barillet[currentChamber];
            currentChamber = (currentChamber + 1) % chambers;
            return mort;
        };
        if (choix == "1") {
            std::cout << currentPlayer << " se tire dessus...\n";
            if (tirer()) {
                std::cout << currentPlayer << " est mort ! " << opponent << " gagne !\n";
                return 5;
            } else {
                std::cout << "clic. Rien ne se passe. " << currentPlayer << " a survecu et rejoue immediatement !\n";
                continue; // même joueur rejoue
            }
        } else if (choix == "2") {
            std::cout << currentPlayer << " tire sur " << opponent << "...\n";
            if (tirer()) {
                std::cout << opponent << " est mort ! " << currentPlayer << " gagne !\n";
                return 5;
            } else {
                std::cout << "clic. Rate ! " << opponent << " prend le pistolet.\n";
                tour++; // passe au joueur suivant
            }
        } else {
            std::cout << "Choix invalide. Tour perdu.\n";
            tour++;
        }
    }
}

int jouerRouletteRusse(const std::string& joueur1, const std::string& joueur2, bool hardcore = false) {
    int mode;
    std::cout << "\nChoisissez le mode :\n1  Solo\n2  Duo\nVotre choix : ";
    std::cin >> mode;
    std::cin.ignore();
    if (mode == 2) return jouerRouletteRusseDuo(joueur1, joueur2, hardcore);
    return jouerRouletteRusseSolo();
}

// --------- WORD GUESS (SOLO/HARDCORE) ---------

// Codes ANSI pour colorer le texte dans le terminal (vert/jaune/rouge).
const std::string GREEN = "\033[1;32m";
const std::string YELLOW = "\033[1;33m";
const std::string RED = "\033[1;31m";
const std::string RESET = "\033[0m";

std::vector<std::string> mots = {
    "arbre", "avion", "biche", "buche", "crane", "drame", "flanc", "fraie", "glace",
    "gorge", "grave", "haine", "hibou", "jaune", "livre", "miel", "monte", "neige",
    "navet", "plage", "poire", "prune", "rouge", "rever", "table", "tombe", "usure", "verbe",
	"craft", "blanc", "rages", "arien", "cesar", "codes"
};

// Convertit une chaîne en minuscules.
std::string toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Vérifie que le mot a exactement 5 lettres
bool motValide(const std::string& mot) {
    return mot.length() == 5;
}

void afficherFeedback(const std::string& essai, const std::string& motSecret) {
    std::string motTemp = motSecret; // copie pour marquer les lettres déjà trouvées
    for (int i = 0; i < 5; ++i) {
        if (essai[i] == motSecret[i]) {
            std::cout << GREEN << essai[i] << RESET; // bonne lettre bonne place
            motTemp[i] = '*'; // on marque comme "utilisée"
        } else {
            std::cout << "_ ";
        }
    }
    std::cout << "   ";
    for (int i = 0; i < 5; ++i) {
        if (essai[i] == motSecret[i]) continue; // déjà affiché en vert
        size_t found = motTemp.find(essai[i]);
        if (found != std::string::npos) {
            std::cout << YELLOW << essai[i] << RESET; // présent mais mal placé
            motTemp[found] = '*'; // évite de compter plusieurs fois la même lettre
        } else {
            std::cout << RED << essai[i] << RESET;
        }
    }
    std::cout << std::endl;
}

int jouerWordGuessSolo(bool hardcore = false) {
    std::string motSecret = mots[std::rand() % mots.size()]; // mot choisi aléatoirement
    const int maxEssais = hardcore ? 3 : 5; // HARDCORE: 3 essais
    std::string essai;
    std::cout << "\n=== WORD GUESS (Solo";
    if (hardcore) std::cout << " [MODE HARDCORE]";
    std::cout << ") ===\n";
    std::cout << "Devine le mot en 5 lettres ! Tu as " << maxEssais << " essais.\n";
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
            return 10;
        }
        afficherFeedback(essai, motSecret);
    }
    std::cout << RED << "\nPerdu ! Le mot etait : " << motSecret << RESET << "\n";
    return 0;
}

// --------- INTERFACE PRINCIPALE ---------

int main() {
    srand(static_cast<unsigned int>(time(0)));
    std::string joueur1, joueur2;
    int scoreGlobal = 0;
    bool modeHardcore = false;
    std::cout << "=== Enregistrement des joueurs ===\n";
    std::cout << "Nom du joueur 1 : ";
    std::getline(std::cin, joueur1);
    std::cout << "Nom du joueur 2 : ";
    std::getline(std::cin, joueur2);
    std::cout << "\nBienvenue " << joueur1 << " et " << joueur2 << " !\n";
    std::cout << "Atteignez 50 points pour debloquer le MODE HARDCORE.\n";
    while (true) {
        if (scoreGlobal >= 50) modeHardcore = true;
        std::cout << "\n=====================================\n";
        std::cout << " SCORE GLOBAL : " << scoreGlobal << " points\n";
        if (modeHardcore) std::cout << "MODE HARDCORE DEBLOQUE\n";
        std::cout << "=====================================\n";
        std::cout << "\nChoisissez un jeu :\n";
        std::cout << "1  Morpion\n";
        std::cout << "2  Pierre - Feuille - Ciseau";
        if (modeHardcore) std::cout << " + Puit";
        std::cout << "\n";
        std::cout << "3  Roulette Russe";
        if (modeHardcore) std::cout << " (Duo plus risque !)";
        std::cout << "\n";
        std::cout << "4  Word Guess (Solo)";
        if (modeHardcore) std::cout << " [3 essais]";
        std::cout << "\n";
        std::cout << "0  Quitter\n";
        int choix;
        std::cout << "\nVotre choix : ";
        std::cin >> choix;
        std::cin.ignore();
        if (choix == 0) {
            std::cout << "\nMerci d'avoir joue ! A bientot.\n";
            break;
        }
        int scorePartie = 0;
        switch (choix) {
            case 1: scorePartie = jouerMorpion(joueur1, joueur2); break;
            case 2: scorePartie = jouerPierreFeuilleCiseau(modeHardcore); break;
            case 3: scorePartie = jouerRouletteRusse(joueur1, joueur2, modeHardcore); break;
            case 4: scorePartie = jouerWordGuessSolo(modeHardcore); break;
            default: std::cout << "Choix invalide.\n"; continue;
        }
        scoreGlobal += scorePartie;
        std::cout << "\nResultat de la partie : " << scorePartie << " points\n";
    }
    return 0;
}
