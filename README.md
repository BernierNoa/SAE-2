# 🌳 Urban Forest Data Analyzer

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Data](https://img.shields.io/badge/Data-CSV_Parsing-4285F4?style=for-the-badge&logo=csv&logoColor=white)
![School](https://img.shields.io/badge/School-IUT_Amiens-EC1C24?style=for-the-badge)

## 📄 Overview

This project is a **C-based data analysis tool** developed during the first semester of the BUT Informatique at IUT Amiens.

Its purpose is to load, process, and analyze real urban data regarding trees planted in the city (specifically dealing with `foret_arbres_50_V1.csv`). It demonstrates how to handle structured data, file I/O operations, and perform statistical analysis in a low-level language.

## 📊 Key Features

* **CSV Data Import:** Robust parsing of semicolon-separated (`.csv`) files containing tree data.
* **Data Modeling:** Uses C `structs` to map complex real-world data (Species, Genus, Height, Circumference, Location).
* **Browsing:** Displays the imported tree records.
* **Sorting:** Sorts by age or health, in either direction.
* **Searching:** Searches by species using the normalization routine in `main.c`.

The current program does not calculate average/max measurements or estimate age from planting year. Its arrays and display loops assume 60 records.

## 💻 Technical Implementation

The core of the project relies on efficient memory structuring to handle dataset entries.

### Data Structure
The project maps the CSV columns to a strictly typed C structure:

```c
typedef struct {
    char id[20];
    char espece[30];
    int age;
    float hauteur;
    float diametre;
    float volume;
    int sante;
} Arbre;
```

Each row of the CSV is parsed into an `Arbre` structure, then stored in an array so the program can iterate over the full dataset to display records, search by species, and sort by age or health.

## 🚀 Comment lancer

### Prérequis
Un compilateur C (`gcc`) installé sur votre machine.

### Compilation
```bash
gcc main.c -o forest_analyzer
```

### Exécution
* **Windows:**
    ```bash
    .\forest_analyzer.exe
    ```
* **Mac/Linux:**
    ```bash
    ./forest_analyzer
    ```

Le programme lit le fichier `foret_arbres_50_V1.csv` (présent à la racine du dépôt) et propose un menu de consultation, recherche par espèce et tri par âge ou santé. Lancer depuis la racine pour que le chemin relatif du CSV soit résolu.

## 👤 Auteur

**Noa** - Étudiant @ IUT Amiens
* [Mon profil GitHub](https://github.com/BernierNoa)

---
*Projet réalisé dans le cadre du Bachelor Universitaire de Technologie (BUT) Informatique - Semestre 1.*
