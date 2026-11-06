
#include <iostream>
#include <initializer_list>
#include <stdexcept>

template <typename T, int N, int M>
class Matrice {
private:
    T data[N][M];

public:
    // Constructeur par defaut
    Matrice() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = 0;
            }
        }
    }

    // Constructeur avec liste d'initialisation
    Matrice(std::initializer_list<std::initializer_list<T>> valeurs) {
        if (valeurs.size() != N) {
            throw std::invalid_argument("Nombre de lignes invalide");
        }

        int i = 0;

        for (const auto& ligne : valeurs) {
            if (ligne.size() != M) {
                throw std::invalid_argument("Nombre de colonnes invalide");
            }

            int j = 0;

            for (const auto& valeur : ligne) {
                data[i][j] = valeur;
                j++;
            }

            i++;
        }
    }

    // Addition de deux matrices
    Matrice operator+(const Matrice& autre) const {
        Matrice resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                resultat.data[i][j] = data[i][j] + autre.data[i][j];
            }
        }

        return resultat;
    }

    // Multiplication de matrices
    template <int P>
    Matrice<T, N, P> operator*(const Matrice<T, M, P>& autre) const {
        Matrice<T, N, P> resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {
                for (int k = 0; k < M; k++) {
                    resultat.data[i][j] += data[i][k] * autre.data[k][j];
                }
            }
        }

        return resultat;
    }

    // Operateur d'affichage
    friend std::ostream& operator<<(std::ostream& os, const Matrice& mat) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                os << mat.data[i][j] << "\t";
            }

            os << std::endl;
        }

        return os;
    }
};

int main() {

    // Matrices d'entiers
    Matrice<int, 2, 2> A{
        {1, 2},
        {3, 4}
    };

    Matrice<int, 2, 2> B{
        {5, 6},
        {7, 8}
    };

    std::cout << "Matrice A :" << std::endl;
    std::cout << A;

    std::cout << "Matrice B :" << std::endl;
    std::cout << B;

    Matrice<int, 2, 2> C = A + B;

    std::cout << "A + B :" << std::endl;
    std::cout << C;

    Matrice<int, 2, 2> D = A * B;

    std::cout << "A * B :" << std::endl;
    std::cout << D;

    // Matrices de double
    Matrice<double, 2, 2> X{
        {1.5, 2.5},
        {3.5, 4.5}
    };

    Matrice<double, 2, 2> Y{
        {2.0, 1.0},
        {1.0, 2.0}
    };

    std::cout << "Multiplication des matrices double :" << std::endl;
    std::cout << X * Y;

    return 0;
}
