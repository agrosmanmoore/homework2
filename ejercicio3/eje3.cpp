#include <iostream>
#include <iomanip> 
#include <sstream>

using namespace std;

// Plantilla de la interfaz Numero
template<typename temp>
class Numero {
public:
    virtual temp operator+(const temp& otro) const = 0;
    virtual temp operator-(const temp& otro) const = 0;
    virtual temp operator*(const temp& otro) const = 0;
    virtual temp operator/(const temp& otro) const = 0;
    virtual string toString() const = 0;
    virtual ~Numero() = default;
};

// Clase Entero
class Entero : public Numero<Entero> {
    
private:
    int valor;
    
public:
    Entero(int v) : valor(v) {}

    Entero operator+(const Entero& otro) const override {
        return Entero(valor + otro.valor);
    }

    Entero operator-(const Entero& otro) const override {
        return Entero(valor - otro.valor);
    }

    Entero operator*(const Entero& otro) const override {
        return Entero(valor * otro.valor);
    }

    Entero operator/(const Entero& otro) const override {
        if (otro.valor == 0) throw invalid_argument("División por cero");
        return Entero(valor / otro.valor);
    }

    string toString() const override {
        return to_string(valor);
    }
};

// Clase Real
class Real : public Numero<Real> {
private:
    double valor;

public:
    Real(double v) : valor(v) {}

    Real operator+(const Real& otro) const override {
        return Real(valor + otro.valor);
    }

    Real operator-(const Real& otro) const override {
        return Real(valor - otro.valor);
    }

    Real operator*(const Real& otro) const override {
        return Real(valor * otro.valor);
    }

    Real operator/(const Real& otro) const override {
        if (otro.valor == 0.0) throw invalid_argument("División por cero");
        return Real(valor / otro.valor);
    }

    string toString() const override {
        ostringstream stream;
        stream << fixed << setprecision(2) << valor;
        return stream.str();
    }
};

// Clase Complejo
class Complejo : public Numero<Complejo> {
private:
    double real;
    double imaginario;

public:
    Complejo(double r, double i) : real(r), imaginario(i) {}

    Complejo operator+(const Complejo& otro) const override {
        return Complejo(real + otro.real, imaginario + otro.imaginario);
    }

    Complejo operator-(const Complejo& otro) const override {
        return Complejo(real - otro.real, imaginario - otro.imaginario);
    }

    Complejo operator*(const Complejo& otro) const override {
        return Complejo(real * otro.real - imaginario * otro.imaginario,
                        real * otro.imaginario + imaginario * otro.real);
    }

    Complejo operator/(const Complejo& otro) const override {
        if (otro.real == 0.0 && otro.imaginario == 0.0) throw invalid_argument("División por cero");
        double denominador = otro.real * otro.real + otro.imaginario * otro.imaginario;
        return Complejo((real * otro.real + imaginario * otro.imaginario) / denominador,
                        (imaginario * otro.real - real * otro.imaginario) / denominador);
    }

    string toString() const override {
        ostringstream stream;
        stream << fixed << setprecision(2) << real;
        if (imaginario >= 0) stream << " + ";
        stream << fixed << setprecision(2) << imaginario << "i";
        return stream.str();
    }
};

// Prueba de las clases
int main() {
    Entero e1(10), e2(5);
    Real r1(10.5), r2(2.3);
    Complejo c1(3, 4), c2(1, -2);

    cout << "=== Entero ===" << endl;
    cout << "Suma: " << (e1 + e2).toString() << endl;
    cout << "Resta: " << (e1 - e2).toString() << endl;
    cout << "Multiplicacion: " << (e1 * e2).toString() << endl;
    cout << "Division: " << (e1 / e2).toString() << endl;

    cout << "\n=== Real ===" << endl;
    cout << "Suma: " << (r1 + r2).toString() << endl;
    cout << "Resta: " << (r1 - r2).toString() << endl;
    cout << "Multiplicacion: " << (r1 * r2).toString() << endl;
    cout << "Division: " << (r1 / r2).toString() << endl;

    cout << "\n=== Complejo ===" << endl;
    cout << "Suma: " << (c1 + c2).toString() << endl;
    cout << "Resta: " << (c1 - c2).toString() << endl;
    cout << "Multiplicacion: " << (c1 * c2).toString() << endl;
    cout << "Division: " << (c1 / c2).toString() << endl;

    return 0;
}
