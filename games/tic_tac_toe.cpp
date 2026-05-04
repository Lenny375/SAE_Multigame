#include <iostream>
#include <vector>
#include <algorithm> // Pour min()


struct Morpion {
	int taille;
    std::vector<std::vector<char>> grille;  // Déclaration de la grille du jeu : tableau dynamique à deux dimensions où chaque case contient un symbole ('X', 'O' ou vide)
    char joueur_actuel;
    int symboles_a_aligner;
};

Morpion initialiserJeu(int n, int k) {
    Morpion jeu; // Déclaration d'une variable 'jeu' de type Morpion, qui va représenter une partie de morpion (avec sa grille, joueur actuel, etc.)
	jeu.taille=n;
    jeu.grille = std::vector<std::vector<char>>(n, std::vector<char>(n, ' ')); // Initialise la grille du jeu : crée un tableau de n lignes et m colonnes, où chaque case est remplie par un espace vide (' ')
    jeu.joueur_actuel = 'X';
    jeu.symboles_a_aligner = k;
    return jeu;
}

void afficherGrille(const Morpion& jeu){ 
// prend en argument une référence constante à un objet Morpion, 
// ce qui permet d'afficher la grille sans modifier l'objet original
    std::cout << "\n   ";
    // Affichage des indices de colonnes
    for(int col = 0; col < jeu.taille; col++){
        std::cout << " " << col+1 << "  ";
    }
    std::cout << "\n";

    // Affichage de la grille avec séparateurs
    for(int i = 0; i < jeu.taille; i++){
        std::cout << "   ";
        for(int col = 0; col < jeu.taille; col++){
            std::cout << "----";
        }
        std::cout << "-\n";

        // Affichage de la ligne de jeu
        std::cout << " " << i+1 << " ";
        for(int j = 0; j < jeu.taille; j++){
            std::cout << "| " << jeu.grille[i][j] << " ";
        }
        std::cout << "|\n";
    }
    // Dernière ligne de séparateur
    std::cout << "   ";
    for(int col = 0; col < jeu.taille; col++){
        std::cout << "----";
    }
    std::cout << "-\n\n";
}
	

bool verifierVictoire(const Morpion& jeu, char joueur){
	int n=jeu.symboles_a_aligner;
	
	//Verifier toutes les lignes
	for (int i=0; i<jeu.taille; i++){
		for (int j=0; j<=jeu.taille-n; j++){
			bool gagne=true;
			for (int k=0; k<n; k++){
				if (jeu.grille[i][j+k]!=joueur){
					gagne=false;
					break;
				}
			}
			if (gagne){
				return true;
			}
		}
	}
	
	//Verifier toutes les colonnes 
	for (int j=0; j<jeu.taille; j++){
		for (int i=0; i<=jeu.taille-n; i++){
			bool gagne=true;
			for (int k=0; k<n; k++){
				if (jeu.grille[i+k][j]!=joueur){
					gagne=false;
					break;
				}
			}
			if (gagne){
				return true;
			}
		}
	}
	
	//Verifier les diagonales descendantes
	for (int i=0; i<=jeu.taille-n; i++){
		for (int j=0; j<=jeu.taille-n; j++){
			bool gagne=true;
			for (int k=0; k<n; k++){
				if (jeu.grille[i+k][j+k]!=joueur){
					gagne=false;
					break;
				}
			}
			if (gagne){
				return true;
			}
		}
	}
	
	//Verifier les diagonales montantes
	for (int i=n-1; i<jeu.taille; i++){
		for (int j=0; j<=jeu.taille-n; j++){
			bool gagne=true;
			for (int k=0; k<n; k++){
				if (jeu.grille[i-k][j+k]!=joueur){
					gagne=false;
					break;
				}
			}
			if (gagne){
				return true;
			}
		}
	}
	return false;
}

bool grilleComplete(const Morpion& jeu){
	for (int i=0; i<jeu.taille; i++){
		for (int j=0; j<jeu.taille; j++){
			if (jeu.grille[i][j]==' ') {
				return false;
			}
		}
	}
	return true;
}

bool jouerCoup(Morpion& jeu, int ligne, int colonne){
	//Verifie si les coordonnees sont valides
	if (ligne<1 || ligne>jeu.taille || colonne<1 || colonne>jeu.taille){
		std::cout<< "Position invalide ! Choisissez entre 1 et " << jeu.taille<< " pour la ligne et entre 1 et " << jeu.taille<< " pour la colonne.\n"<<std::endl;
		return false;
	}
	int i=ligne-1;
	int j=colonne-1;
	if (jeu.grille[i][j]!=' '){
		std::cout<< "Cette case est deja occupee !\n"<<std::endl;
		return false;
	}
	jeu.grille[i][j]=jeu.joueur_actuel;
	return true;
}

void changerJoueur(Morpion& jeu){
	if (jeu.joueur_actuel=='X'){
		jeu.joueur_actuel='O';
	}
	else{
		jeu.joueur_actuel='X';
	}
}	

int main() {
	std::cout<<"=== JEU DE MORPION ==="<<std::endl;
	int taille;
	int k;
    while (true) {
        std::cout << "Saisir la taille de la grille (N pour une grille NxN) : " << std::endl;
        std::cin >> taille;
        if (taille < 2) {
            std::cout << "Erreur: la taille de la grille doit être au moins 2." << std::endl;
        } 
		else {
			break;
        }
    }
	int borneMin = 2;
	int borneMax = taille;
    while (true) {
        std::cout<<"Saisir le nombre de symboles a aligner pour gagner (K) :"<<std::endl;
        std::cin>>k;
        if (k < borneMin || k > borneMax) {
            std::cout << "Erreur: K doit etre entre " << borneMin << " et " << borneMax << "." << std::endl;
        } 
		else {
			break;
        }
    }
    Morpion jeu = initialiserJeu(taille, k);
	std::cout<<"\nPour gagner, alignez "<< jeu.symboles_a_aligner<< " symboles horizontalement, verticalement ou en diagonale !\n";
	
	//boucle principale du jeu
	bool JeuEnCours=true;
	while (JeuEnCours){
		afficherGrille(jeu);
		std::cout<< "Joueur" << jeu.joueur_actuel<< ", a vous de jouer ! !\n";
		int ligne;
		int colonne;
		std::cout<<"Entrez le numero de ligne : "<<std::endl;
		std::cin>>ligne;
		std::cout<<"Entrez le numero de colonne : "<<std::endl;
		std::cin>>colonne;
		if (jouerCoup(jeu, ligne, colonne)){
			if(verifierVictoire(jeu,jeu.joueur_actuel)){
				afficherGrille(jeu);
				std::cout<<"Felicitations ! Le joueur " <<jeu.joueur_actuel << " a gagne !\n";
				JeuEnCours=false;
			}
			else if(grilleComplete(jeu)){
				afficherGrille(jeu);
				std::cout<<"Match nul ! La grille est pleine.\n"<<std::endl;
				JeuEnCours=false;
			}
			else{
				changerJoueur(jeu);
			}
		}
	}
	return 0;
}
