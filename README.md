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
* **Statistical Analysis:**
    * Calculation of average/max heights and circumferences.
    * Age estimation based on planting year.
* **Filtering & Searching:** Ability to query trees based on specific criteria (e.g., finding all trees of a certain genus).

## 💻 Technical Implementation

The core of the project relies on efficient memory structuring to handle dataset entries.

### Data Structure
The project maps the CSV columns to a strictly typed C structure:

```c
typedef struct {
    int id;
    char lieu[100];
    char genre[50];
    char espece[50];
    float hauteur;
    float circonference;
    int annee_plantation;
} Arbre;
