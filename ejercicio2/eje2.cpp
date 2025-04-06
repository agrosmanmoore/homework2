#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Estudiante {

private:

    string nombre;
    int n_legajo;
    vector<int> notas;

public:
    // Constructor
    Estudiante(string n, int legajo, vector<int> notas) : nombre(n), n_legajo(legajo), notas(notas) {}

    // Getters
    string getName() const { return nombre; }

    int getLegajo() const { return n_legajo; }

    int getPromedio() const {

        if (notas.empty()) return 0;
        int suma = 0;
        for (int nota : notas) suma += nota;
        return suma / notas.size();

    }

    // Sobrecarga de "<" para ordenar por nombre
    bool operator<(const Estudiante& otro) const { return nombre < otro.nombre; }

    // Sobrecarga de "<<" para imprimir estudiante
    friend ostream& operator<<(ostream& os, const Estudiante& e) {
        os << "Nombre: " << e.nombre << ", Legajo: " << e.n_legajo << ", Promedio: " << e.getPromedio();
        return os;
    }
};

class Curso {

private:

    vector<Estudiante*> estudiantes;

public:
    // Constructor por defecto
    Curso() {}

    // Constructor de copia profunda
    Curso(const Curso& otro) {

        for (Estudiante* e : otro.estudiantes) {
            estudiantes.push_back(new Estudiante(*e));  // Deep copy (Si se usara una shallow copy, ambos cursos compartirían los mismos punteros, lo que causaría problemas como modificaciones no deseadas entre cursos, errores de doble liberación de memoria al destruirlos, etc.)
        }
    }

    // Destructor para liberar la memoria
    ~Curso() {

        for (Estudiante* e : estudiantes) {
            delete e;

        }
    }

    void agregarEstudiante(Estudiante* e) {

        if (findStudent(e->getLegajo())) {
            cout << "El estudiante ya está inscrito" << endl;
            return;
        }
        if (estudiantes.size() >= 20) {
            cout << "El curso está lleno" << endl;
            return;
        }
        estudiantes.push_back(e);
    }

    bool findStudent(int legajo) const {

        for (Estudiante* e : estudiantes) {
            if (e->getLegajo() == legajo) return true;

        }
        return false;
    }

    void desinscribir(int legajo) {

        for (auto it = estudiantes.begin(); it != estudiantes.end(); ++it) {

            if ((*it)->getLegajo() == legajo) {

                delete *it;  // Liberar memoria
                estudiantes.erase(it);  // Eliminar del vector
                cout << "Estudiante con legajo " << legajo << " eliminado." << endl;
                return;
            }
        }
        cout << "Estudiante con legajo " << legajo << " no encontrado." << endl;
    }

    void imprimirOrdenado() const {

        vector<Estudiante*> copia = estudiantes;
        sort(copia.begin(), copia.end(), [](Estudiante* a, Estudiante* b) { return *a < *b; });

        for (Estudiante* e : copia) {
            cout << *e << endl;
        }
    }
};

void menu() {
    Curso curso1;

    vector<Estudiante*> estudiantes = {
        new Estudiante("Carlos", 101, {8, 9, 7}),
        new Estudiante("Ana", 102, {10, 9, 8}),
        new Estudiante("Bruno", 103, {6, 7, 5})
    };

    for (Estudiante* e : estudiantes) {
        curso1.agregarEstudiante(e);
    }

    int opcion;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Mostrar estudiantes ordenados\n";
        cout << "2. Copiar curso y mostrar copia\n";
        cout << "3. Desinscribir estudiante\n";
        cout << "4. Inscribir estudiante\n";
        cout << "5. Salir\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                curso1.imprimirOrdenado();
                break;
            case 2: {
                Curso curso2 = curso1; // Copia profunda
                cout << "Estudiantes en el curso copiado:\n";
                curso2.imprimirOrdenado();
                break;
            }
            case 3: {
                int legajo;
                cout << "Ingrese el legajo del estudiante a eliminar: ";
                cin >> legajo;
                curso1.desinscribir(legajo);
                break;
            }

            case 4: {
                string nombre;
                int legajo;
                vector<int> notas;

                cout << "Ingrese el nombre del estudiante: ";
                cin >> nombre;
                cout << "Ingrese el legajo del estudiante: ";
                cin >> legajo;

                cout << "Ingrese las notas (separadas por espacio, termine con -1): ";
                int nota;
                while (true) {
                    cin >> nota;
                    if (nota == -1) break;
                    notas.push_back(nota);
                }

                Estudiante* nuevoEstudiante = new Estudiante(nombre, legajo, notas);
                curso1.agregarEstudiante(nuevoEstudiante);
                break;
            }

            case 5:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida, intente de nuevo.\n";
        }
    } while (opcion != 5);

}

int main() {
    menu();
    return 0;
}
