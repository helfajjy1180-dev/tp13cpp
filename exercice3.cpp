
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// Exception : pile pleine
class StackOverflow : public std::exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la pile est pleine !";
    }
};

// Exception : pile vide
class StackUnderflow : public std::exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la pile est vide !";
    }
};

template <typename T>
class Stack {
private:
    std::unique_ptr<T[]> data;
    std::size_t capacity;
    std::size_t top;

public:
    // Constructeur avec capacite par defaut
    Stack(std::size_t c = 10) {
        capacity = c;
        top = 0;
        data = std::make_unique<T[]>(capacity);
    }

    // Constructeur avec iterateurs
    template <typename Iterator>
    Stack(Iterator begin, Iterator end) {
        std::vector<T> elements(begin, end);

        capacity = elements.size();
        top = 0;

        data = std::make_unique<T[]>(capacity);

        for (const auto& e : elements) {
            push(e);
        }
    }

    // Ajouter un element
    void push(const T& valeur) {
        if (top >= capacity) {
            throw StackOverflow();
        }

        data[top] = valeur;
        top++;
    }

    // Supprimer le dernier element
    void pop() {
        if (empty()) {
            throw StackUnderflow();
        }

        top--;
    }

    // Consulter le dernier element
    const T& peek() const {
        if (empty()) {
            throw StackUnderflow();
        }

        return data[top - 1];
    }

    // Verifier si la pile est vide
    bool empty() const {
        return top == 0;
    }

    // Afficher la pile
    void afficher() const {
        for (std::size_t i = 0; i < top; i++) {
            std::cout << data[i] << " ";
        }

        std::cout << std::endl;
    }
};

int main() {

    try {
        // Pile d'entiers
        Stack<int> s(5);

        s.push(10);
        s.push(20);
        s.push(30);

        std::cout << "Pile : ";
        s.afficher();

        std::cout << "Sommet : " << s.peek() << std::endl;

        s.pop();

        std::cout << "Apres pop : ";
        s.afficher();

        // Tester le debordement
        s.push(40);
        s.push(50);
        s.push(60);
        s.push(70);

    }
    catch (const StackOverflow& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const StackUnderflow& e) {
        std::cout << e.what() << std::endl;
    }

    // Pile de chaines
    Stack<std::string> mots(3);

    mots.push("Bonjour");
    mots.push("C++");
    mots.push("Templates");

    std::cout << "Sommet des mots : " << mots.peek() << std::endl;

    // Initialisation avec des iterateurs
    std::vector<int> valeurs = {1, 2, 3, 4};

    Stack<int> s2(valeurs.begin(), valeurs.end());

    std::cout << "Pile initialisee : ";
    s2.afficher();

    return 0;
}
