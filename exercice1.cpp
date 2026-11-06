
#include <iostream>
#include <string>
#include <stdexcept>

template <typename T>
class ArrayDyn {
private:
    T* data;
    std::size_t taille;
    std::size_t capacite;

    void agrandir() {
        std::size_t nouvelleCapacite = (capacite == 0) ? 1 : capacite * 2;

        T* nouveauData = new T[nouvelleCapacite];

        for (std::size_t i = 0; i < taille; i++) {
            nouveauData[i] = data[i];
        }

        delete[] data;

        data = nouveauData;
        capacite = nouvelleCapacite;
    }

public:
    // Constructeur par defaut
    ArrayDyn() {
        data = nullptr;
        taille = 0;
        capacite = 0;
    }

    // Constructeur avec capacite initiale
    ArrayDyn(std::size_t c) {
        taille = 0;
        capacite = c;

        if (capacite == 0) {
            data = nullptr;
        } else {
            data = new T[capacite];
        }
    }

    // Constructeur de copie
    ArrayDyn(const ArrayDyn& autre) {
        taille = autre.taille;
        capacite = autre.capacite;

        if (capacite == 0) {
            data = nullptr;
        } else {
            data = new T[capacite];

            for (std::size_t i = 0; i < taille; i++) {
                data[i] = autre.data[i];
            }
        }
    }

    // Operateur d'affectation
    ArrayDyn& operator=(const ArrayDyn& autre) {
        if (this != &autre) {
            T* nouveauData = nullptr;

            if (autre.capacite > 0) {
                nouveauData = new T[autre.capacite];

                for (std::size_t i = 0; i < autre.taille; i++) {
                    nouveauData[i] = autre.data[i];
                }
            }

            delete[] data;

            data = nouveauData;
            taille = autre.taille;
            capacite = autre.capacite;
        }

        return *this;
    }

    // Ajouter un element
    void push_back(const T& valeur) {
        if (taille == capacite) {
            agrandir();
        }

        data[taille] = valeur;
        taille++;
    }

    // Supprimer le dernier element
    void pop_back() {
        if (taille == 0) {
            throw std::out_of_range("Tableau vide");
        }

        taille--;
    }

    // Acces avec controle des bornes
    T& operator[](std::size_t index) {
        if (index >= taille) {
            throw std::out_of_range("Indice invalide");
        }

        return data[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= taille) {
            throw std::out_of_range("Indice invalide");
        }

        return data[index];
    }

    // Iterateur interne
    class Iterator {
    private:
        T* ptr;

    public:
        Iterator(T* p) {
            ptr = p;
        }

        T& operator*() const {
            return *ptr;
        }

        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        Iterator& operator--() {
            --ptr;
            return *this;
        }

        bool operator!=(const Iterator& autre) const {
            return ptr != autre.ptr;
        }

        bool operator==(const Iterator& autre) const {
            return ptr == autre.ptr;
        }
    };

    // Debut du tableau
    Iterator begin() {
        return Iterator(data);
    }

    // Fin du tableau
    Iterator end() {
        return Iterator(data == nullptr ? nullptr : data + taille);
    }

    // Destructeur
    ~ArrayDyn() {
        delete[] data;
    }
};

// Classe maison
class Etudiant {
private:
    std::string nom;
    int age;

public:
    Etudiant() {
        nom = "";
        age = 0;
    }

    Etudiant(std::string n, int a) {
        nom = n;
        age = a;
    }

    void afficher() const {
        std::cout << nom << " - " << age << " ans" << std::endl;
    }
};

int main() {
    // Tableau d'entiers
    ArrayDyn<int> nombres;

    nombres.push_back(10);
    nombres.push_back(20);
    nombres.push_back(30);

    std::cout << "Tableau d'entiers : ";

    for (auto& e : nombres) {
        std::cout << e << " ";
    }

    std::cout << std::endl;

    // Tableau de chaines
    ArrayDyn<std::string> mots;

    mots.push_back("Bonjour");
    mots.push_back("C++");
    mots.push_back("Templates");

    std::cout << "Tableau de chaines : ";

    for (auto& e : mots) {
        std::cout << e << " ";
    }

    std::cout << std::endl;

    // Tableau d'objets
    ArrayDyn<Etudiant> etudiants;

    etudiants.push_back(Etudiant("Ali", 20));
    etudiants.push_back(Etudiant("Sara", 21));

    std::cout << "Tableau d'etudiants :" << std::endl;

    for (auto& e : etudiants) {
        e.afficher();
    }

    return 0;
}
