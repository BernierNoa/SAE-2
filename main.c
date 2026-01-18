#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE_SIZE 1024
#define DELIMITEUR ";"

typedef struct
{                    // Ceci est la création du type arbre pour permettre d'utiliser les données des arbres plus tard
    char id[20];     // ID de l'arbre
    char espece[30]; // Son espèce
    int age;         // Son âge
    float hauteur;   // Sa hauteur
    float diametre;  // Son diamètre
    float volume;    // Son volume
    int sante;       // Son état de santé
} Arbre;

void choix(int *choix_utilisateur)
{ // Procédure pour demander le choix de l'utilisateur avec une variable par adresse
    while (*choix_utilisateur > 5 || *choix_utilisateur < 1)
    {
        printf("---------------MENU---------------\n");
        printf("Veuillez entrez le chiffre lié à l'action que vous souhaitez effectuer:\n");
        printf("1. Afficher tous les arbres\n");
        printf("2. Rechercher une espèce d'arbre\n");
        printf("3. Trier par âge\n");
        printf("4. Trier par santé\n");
        printf("5. Quitter\n");
        printf("----------------------------------\n");
        printf("Que souhaitez vous faire ? ");
        scanf("%d", choix_utilisateur);
    }
}

// Fonction pour remplacer la virgule par un point
void remplacer_virgule(char *str)
{
    char *ptr = strchr(str, ','); // Cherche la virgule
    if (ptr != NULL)
    {
        *ptr = '.'; // Remplace par un point
    }
}

void charger(Arbre foret[])
{
    FILE *fichier = fopen("foret_arbres_50_V1.csv", "r");
    // fopen permet d'ouvrir le fichier de mettre son addresse dans la variable fichier pour le reste du code

    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
    }
    else
    {
        char ligne[MAX_LINE_SIZE];

        // 1. On saute la première ligne (les en-têtes)
        fgets(ligne, MAX_LINE_SIZE, fichier);
        // fgets permet de lire les lignes du fichier une par une

        int i = 0;

        // 2. Lecture ligne par ligne
        while (fgets(ligne, MAX_LINE_SIZE, fichier) != NULL)
        {
            Arbre arbre;
            char *token;

            // -- Colonne 1 : Identifiant --
            token = strtok(ligne, DELIMITEUR);
            // strtok permet de découper la ligne en plusieurs parties selon le délimiteur
            if (token != NULL)
                strcpy(arbre.id, token);
            // strcpy permet de copier une chaîne de caractères dans une autre donc la le token dans arbre.id

            // -- Colonne 2 : Espèce --
            token = strtok(NULL, DELIMITEUR);
            if (token != NULL)
                strcpy(arbre.espece, token);

            // -- Colonne 3 : Age (int) --
            token = strtok(NULL, DELIMITEUR);
            if (token != NULL)
                arbre.age = atoi(token);
            // atoi permet de convertir une chaîne de caractères en entier

            // -- Colonne 4 : Hauteur (float avec virgule) --
            token = strtok(NULL, DELIMITEUR);
            if (token != NULL)
            {
                remplacer_virgule(token); // On remplace la virgule par un point
                arbre.hauteur = atof(token);
                // atof permet de convertir une chaîne de caractères en float
            }

            // -- Colonne 5 : Diamètre --
            token = strtok(NULL, DELIMITEUR);
            if (token != NULL)
            {
                remplacer_virgule(token);
                arbre.diametre = atof(token);
            }

            // -- Colonne 6 : Volume --
            token = strtok(NULL, DELIMITEUR);
            if (token != NULL)
            {
                remplacer_virgule(token);
                arbre.volume = atof(token);
            }

            // -- Colonne 7 : Santé --
            token = strtok(NULL, DELIMITEUR);
            if (token != NULL)
                arbre.sante = atoi(token);
            foret[i] = arbre; // Stockage de l'arbre dans le tableau
            i++;
        }

        fclose(fichier);
    }
}

// Fonction "Nettoyeur" : Elle enlève les majuscules et les accents bizarres
// Utile pour comparer "Chêne" et "chene" sans que l'ordi ne panique.
void normaliser_chaine(const char *entree, char *sortie)
{
    int i = 0, j = 0;
    while (entree[i] != '\0')
    {
        unsigned char c = (unsigned char)entree[i];

        // 1. Gestion des Majuscules simples (A-Z -> a-z)
        if (c >= 'A' && c <= 'Z')
        {
            sortie[j++] = c + 32; // On transforme en minuscule
        }
        // 2. Gestion des minuscules simples (a-z) et chiffres
        else if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
        {
            sortie[j++] = c;
        }
        // 3. Gestion UTF-8 (Cas où l'accent est sur 2 octets, ex: Linux/Modern Editor)
        else if (c == 0xC3)
        {
            i++; // On regarde l'octet suivant
            unsigned char c2 = (unsigned char)entree[i];
            // é, è, ê, ë
            if (c2 >= 0xA8 && c2 <= 0xEB)
                sortie[j++] = 'e';
            // à, â
            else if (c2 >= 0x80 && c2 <= 0x86)
                sortie[j++] = 'a';
            // î, ï
            else if (c2 >= 0xAC && c2 <= 0xAF)
                sortie[j++] = 'i';
            // ô
            else if (c2 >= 0xB2 && c2 <= 0xB8)
                sortie[j++] = 'o';
            // ù, û
            else if (c2 >= 0xB9 && c2 <= 0xBC)
                sortie[j++] = 'u';
            // ç
            else if (c2 == 0xA7)
                sortie[j++] = 'c';
        }
        // 4. Gestion WINDOWS / ANSI (Cas où l'accent est sur 1 seul octet)
        else if (c > 127) // Si c'est un caractère spécial étendu
        {
            // É, È, Ê, Ë, é, è, ê, ë (Codes ANSI courants et CP850)
            if (c == 0xE9 || c == 0xE8 || c == 0xEA || c == 0xEB || c == 130 || c == 138 || c == 136 || c == 137)
                sortie[j++] = 'e';
            // À, Â, à, â
            else if (c == 0xE0 || c == 0xE2 || c == 133 || c == 131)
                sortie[j++] = 'a';
            // Î, Ï, î, ï
            else if (c == 0xEE || c == 0xEF || c == 140 || c == 139)
                sortie[j++] = 'i';
            // Ô, Ö, ô, ö
            else if (c == 0xF4 || c == 0xF6 || c == 147 || c == 148)
                sortie[j++] = 'o';
            // Ù, Û, Ü, ù, û, ü
            else if (c == 0xF9 || c == 0xFB || c == 0xFC || c == 150 || c == 151 || c == 129)
                sortie[j++] = 'u';
            // Ç, ç
            else if (c == 0xE7 || c == 135)
                sortie[j++] = 'c';
            else
                sortie[j++] = '_'; // On remplace les caractères inconnus par _ pour pas casser la chaine
        }
        i++;
    }
    sortie[j] = '\0';
}

void afficher(Arbre foret[], int taille) // J'ajoute 'taille' car c'est plus sûr que de mettre 60 en dur
{
    int i;
    char tampon_nom[30];

    // 1. On définit la ligne de séparation une seule fois pour la réutiliser
    // La longueur totale correspond à la somme des largeurs des colonnes + les séparateurs
    const char *ligne = "+-------+----------------------+-----+---------+----------+--------+-------+\n";

    // 2. Affichage de l'en-tête
    printf("%s", ligne);
    printf("| %-5s | %-20s | %-3s | %-7s | %-8s | %-6s | %-5s |\n",
           "ID", "Espece", "Age", "Hauteur", "Diametre", "Volume", "Sante");
    printf("%s", ligne);

    // 3. Boucle d'affichage des données
    for (i = 0; i < taille; i++)
    {
        // Explications des codes de formatage :
        // %-4s   : Texte aligné à GAUCHE sur 4 espaces (pour l'ID)
        // %-20s  : Texte aligné à GAUCHE sur 20 espaces (pour l'Espèce, car les noms varient)
        // %3d    : Entier aligné à DROITE sur 3 espaces (pour l'Age)
        // %7.2f  : Float aligné à DROITE sur 7 espaces totaux, avec 2 chiffres après la virgule
        normaliser_chaine(foret[i].espece, tampon_nom);

        printf("| %-4s | %-20s | %3d | %7.2f | %8.2f | %6.2f | %5d |\n",
               foret[i].id,
               tampon_nom,
               foret[i].age,
               foret[i].hauteur,
               foret[i].diametre,
               foret[i].volume,
               foret[i].sante);
    }

    // 4. Ligne de fin
    printf("%s", ligne);
}

void rechercher_espece(Arbre foret[], int taille)
{
    char saisie[30];        // Ce que l'utilisateur tape
    char saisie_propre[30]; // Ce que l'utilisateur tape (nettoyé)
    char espece_propre[30]; // L'espèce de l'arbre dans le tableau (nettoyé)

    // On crée un petit tableau temporaire juste pour stocker les résultats de la recherche
    Arbre resultats[taille];
    int compteur = 0; // Pour compter combien d'arbres on a trouvés

    printf("Quelle espece recherchez-vous ? (ex: Chene) : ");
    // Attention : scanf coupe au premier espace. Pour "Pin Sylvestre", il ne verra que "Pin".
    scanf("%s", saisie);

    // 1. On nettoie la saisie (ex: Si la personne tape "CHÊNE", ça devient "chene")
    normaliser_chaine(saisie, saisie_propre);

    // 2. On parcourt toute la forêt pour voir qui correspond
    for (int i = 0; i < taille; i++)
    {
        // On nettoie aussi le nom de l'arbre qu'on est en train de regarder
        normaliser_chaine(foret[i].espece, espece_propre);
        // strcmp renvoie 0 si les deux chaînes sont identiques
        if (strcmp(espece_propre, saisie_propre) == 0)
        {
            resultats[compteur] = foret[i]; // On le copie dans les résultats
            compteur++;
        }
    }

    // 3. Verdict
    if (compteur > 0)
    {
        printf("\n--- %d arbre(s) trouve(s) pour la recherche '%s' ---\n", compteur, saisie);
        // On réutilise la fonction afficher existante
        afficher(resultats, compteur);
        
    }
    else
    {
        printf("Desole, aucune espece correspondant a '%s' n'a ete trouvee.\n", saisie);
    }
}

void trier_age(Arbre foret[])
{
    // On définit la taille maximal du tableau
    int taille = 60;

    // On crée un tableau temporaire pour pouvoir faire une copie du tableau principal et pour faire un trie plus tard
    Arbre foret_age[60];

    // Création d'une variable x pour le choix de l'utilisateur
    int x;

    // Grâce au tableau qu'on a créé avant, on copie chaque terme du tableau princpal (foret[i]) pour les coller dans le tableau (foret_age[]) qu'on a créé
    for (int i = 0; i < taille; i++)
    {
        foret_age[i] = foret[i];
    }

    // On demande à l'utilisateur de quelle manière il veut que l'âge soit trier.
    // On utilise un do while pour mettre un message d'erreur.
    do
    {
        printf("\n1. Trie par ordre croissant\n2. Trie par ordre décroissant\nVotre choix : "); // Soit de façon croisant (en tapant sur 1) ou décroissant (en tapant sur 2)
        scanf("%d", &x);

        if (x != 1 && x != 2)
        {
            printf("\nErreur : choix invalide. Veuillez entrer 1 ou 2.\n");
        }

    } while (x != 1 && x != 2);

    for (int i = 0; i < taille - 1; i++)
    {
        for (int j = 0; j < taille - i - 1; j++)
        {
            int choix = 0;

            if (x == 1) // Si l'utilisateur choisit le tri par mode croissant x vaut 1
            {
                if (foret_age[j].age > foret_age[j + 1].age)
                    choix = 1;
            }
            else // Si l'utilisateur choisit le tri par mode croissant x vaut 1
            {
                if (foret_age[j].age < foret_age[j + 1].age)
                    choix = 1;
            }

            // Si cela se passe bien, on fait l'échange ici
            if (choix == 1)
            {
                Arbre tmp = foret_age[j];
                foret_age[j] = foret_age[j + 1];
                foret_age[j + 1] = tmp;
            }
        }
    }

    // L'affichage du nouveau tableau avec le tri de fait
    afficher(foret_age, taille);
}

void trier_sante(Arbre foret[60])
{
    int i, j, min_i, max_i, taille = 60, choixtri;
    Arbre temp;
    Arbre foret_triee[60];
    // affichage pour demandé à lutilisateur comment i lveut triee
    printf("Dans quel ordre voulez-vous trier? Veuillez saisir le chiffre correspondant: \n");
    printf("1: tri par ordre croissant, de la pire à la meilleur santée\n");
    printf("0: tri par ordre déccroissant, de la meilleur à la pire santée\n");
    scanf("%d", &choixtri);

    switch (choixtri)
    {

    case 1:
        for (i = 0; i < taille; i++)
        {
            foret_triee[i] = foret[i]; // creatio nd'une copie de la liste foret pour ne pas modifier la liste principale (pour povuoir faire la comapraison a la fin)
        }

        // on cherche l'arbre avec la pire santee (0) pour le mettre en debut de liste, pour commencer donc on prend la premiere valeur de la liste
        for (i = 0; i < taille - 1; i++)
        {
            min_i = i;
            for (j = i + 1; j < taille; j++)
            { // on reparcours la liste a aprtir de l'element suivant pour verifier s'il n'y a pas une santee plus petite
                if (foret_triee[j].sante < foret_triee[min_i].sante)
                {              // si la sante de l'element arbre a la position j est pluspetit que la sante de l'elemnt arbre a laa position min_i
                    min_i = j; // alors lindice de santee minimal devient cellede lindice j
                }
            }
            // on permute les deux arbres entre eux pour les ranges dans lordre de sante croissant grace a une variable temporaire 'temp'
            temp = foret_triee[i];
            foret_triee[i] = foret_triee[min_i];
            foret_triee[min_i] = temp;
        }
        break;

    case 0:
        for (i = 0; i < taille; i++)
        {
            foret_triee[i] = foret[i]; // creatio nd'une copie de la liste foret pour ne pas modifier la liste principale (pour povuoir faire la comapraison a la fin)
        }

        // on cherche l'arbre avec la meilleur santee (10) pour le mettre en debut de liste, pour commencer donc on prend la premiere valeur de la liste
        for (i = 0; i < taille - 1; i++)
        {
            max_i = i;
            for (j = i + 1; j < taille; j++)
            { // on reparcours la liste a aprtir de l'element suivant pour verifier s'il n'y a pas une santee plus grande
                if (foret_triee[j].sante > foret_triee[max_i].sante)
                {              // si la sante de l'element arbre a la position j est plus grand que la sante de l'elemnt arbre a laa position max_i
                    max_i = j; // alors lindice de santee maximale devient celle de lindice j
                }
            }
            // on permute les deux arbres entre eux pour les ranges dans lordre de sante decroissantt grace a une variable temporaire 'temp'
            temp = foret_triee[i];
            foret_triee[i] = foret_triee[max_i];
            foret_triee[max_i] = temp;
        }
        break;
    }
    afficher(foret_triee, 60); // Affichage de la forêt triée
}

int main()
{
    Arbre foret[60];
    charger(foret); // On charge les données des arbres dans la mémoire ram
    int choix_utilisateur;
    do
    {
        choix_utilisateur = 0;     // Réinitialisation du choix de l'utilisateur
        choix(&choix_utilisateur); // on récupére le choix de l'utilisateur
        switch (choix_utilisateur) // On effectue l'action choisie par l'utilisateur
        {
        case 1:
            afficher(foret, 60); // Procédure pour afficher tous les arbres
            break;
        case 2:
            rechercher_espece(foret, 60); // Procédure pour rechercher une espèce d'arbre
            break;
        case 3:
            trier_age(foret); // Procédure pour trier les arbres par âge
            break;
        case 4:
            trier_sante(foret); // Procédure pour trier les arbres par santé
            break;
        default:
            break;
        }
    } while (choix_utilisateur != 5); // On continue tant que l'utilisateur ne souhaite pas quitter

    return 0;
}