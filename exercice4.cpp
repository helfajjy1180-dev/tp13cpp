
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <concepts>
#include <utility>

// Concept Sortable
template <typename T>
concept Sortable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
};

// Foncteur : tri croissant
struct Asc {
    template <typename T>
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

// Foncteur : tri decroissant
struct Desc {
    template <typename T>
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

// Fonction de partition
template <Sortable T, typename Comp>
std::size_t partition(std::vector<T>& v, std::size_t low,
                      std::size_t high, Comp comp) {
    T pivot = v[high];
    std::size_t i = low;

    for (std::size_t j = low; j < high; j++) {
        if (comp(v[j], pivot)) {
            std::swap(v[i], v[j]);
            i++;
        }
    }

    std::swap(v[i], v[high]);

    return i;
}

// QuickSort
template <Sortable T, typename Comp = std::less<T>>
void quickSortRange(std::vector<T>& v, std::size_t low,
                    std::size_t high, Comp comp = Comp{}) {
    if (low < high) {
        std::size_t p = partition(v, low, high, comp);

        if (p > low) {
            quickSortRange(v, low, p - 1, comp);
        }

        if (p < high) {
            quickSortRange(v, p + 1, high, comp);
        }
    }
}

// Fonction principale de tri
template <Sortable T, typename Comp = std::less<T>>
void quickSort(std::vector<T>& v, Comp comp = Comp{}) {
    if (!v.empty()) {
        quickSortRange(v, 0, v.size() - 1, comp);
    }
}

// Classe Etudiant
class Etudiant {
public:
    std::string nom;
    int note;

    Etudiant(std::string n, int no) {
        nom = n;
        note = no;
    }

    bool operator<(const Etudiant& e) const {
        return note < e.note;
    }

    bool operator>(const Etudiant& e) const {
        return note > e.note;
    }
};

// Affichage des etudiants
void afficherEtudiants(const std::vector<Etudiant>& v) {
    for (const auto& e : v) {
        std::cout << e.nom << " : " << e.note << std::endl;
    }
}

int main() {

    // Test avec int
    std::vector<int> nombres = {8, 3, 6, 1, 9, 2};

    quickSort(nombres, Asc{});

    std::cout << "Tri croissant des entiers : ";

    for (int n : nombres) {
        std::cout << n << " ";
    }

    std::cout << std::endl;

    std::cout << "Test : "
              << (std::is_sorted(nombres.begin(), nombres.end())
                  ? "Reussi" : "Echoue") << std::endl;

    // Test avec string
    std::vector<std::string> mots = {
        "Java", "Python", "C++", "HTML"
    };

    quickSort(mots, Desc{});

    std::cout << "\nTri decroissant des chaines : ";

    for (const auto& mot : mots) {
        std::cout << mot << " ";
    }

    std::cout << std::endl;

    std::cout << "Test : "
              << (std::is_sorted(mots.begin(), mots.end(), Desc{})
                  ? "Reussi" : "Echoue") << std::endl;

    // Test avec une classe personnelle
    std::vector<Etudiant> etudiants = {
        {"Ali", 12},
        {"Sara", 18},
        {"Youssef", 10},
        {"Amine", 15}
    };

    quickSort(etudiants, Asc{});

    std::cout << "\nTri des etudiants par note : " << std::endl;

    afficherEtudiants(etudiants);

    std::cout << "Test : "
              << (std::is_sorted(etudiants.begin(), etudiants.end())
                  ? "Reussi" : "Echoue") << std::endl;

    return 0;
}
