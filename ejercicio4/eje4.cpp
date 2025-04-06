#include <iostream>
#include <string>

using namespace std;

// Clase abstracta CuentaBancaria

class Cuenta {

protected:

    double balance;

    string titularCuenta;

public:
    // Constructor
    Cuenta(string titular, double saldoInicial) : balance(saldoInicial), titularCuenta(titular) {}

    // Método para depositar dinero
    void depositar(double cantidad) {
        if (cantidad > 0) {
            balance += cantidad;
            cout << "Depósito exitoso de $" << cantidad << ". Nuevo balance: $" << balance << endl;
        } else {
            cout << "La cantidad a depositar debe ser positiva." << endl;
        }
    }

    // Método virtual puro para retirar dinero
    virtual void retirar(double cantidad) = 0;

    // Método virtual puro para mostrar información
    virtual void mostrarInfo() const = 0;

    // Destructor virtual
    virtual ~Cuenta() = default;
};

// Clase CuentaAhorros (derivada de CuentaBancaria)
class CuentaAhorros : public Cuenta {

private:

    double tasaInteres; // Porcentaje de interés anual

public:

    CuentaAhorros(string titular, double saldoInicial, double interes) : Cuenta(titular, saldoInicial), tasaInteres(interes) {}

    void retirar(double cantidad) override {
        if (cantidad > 0 && cantidad <= balance) {
            balance -= cantidad;
            cout << "Retiro exitoso de $" << cantidad << ". Nuevo balance: $" << balance << endl;
        } else {
            cout << "Fondos insuficientes o cantidad inválida." << endl;
        }
    }

    void mostrarInfo() const override {
        cout << "Cuenta de Ahorros - Titular: " << titularCuenta 
             << ", Balance: $" << balance 
             << ", Tasa de interés: " << tasaInteres << "%" << endl;
    }
};

// Clase CuentaCorriente (derivada de CuentaBancaria)

class CuentaCorriente : public Cuenta {
    
private:

    double limiteSobregiro;

public:

    CuentaCorriente(string titular, double saldoInicial, double sobregiro) : Cuenta(titular, saldoInicial), limiteSobregiro(sobregiro) {}

    void retirar(double cantidad) override {

        if (cantidad > 0 && (balance - cantidad) >= -limiteSobregiro) {
            balance -= cantidad;
            cout << "Retiro exitoso de $" << cantidad << ". Nuevo balance: $" << balance << endl;
        } else {
            cout << "No se puede retirar $" << cantidad << ". Excede el límite de sobregiro." << endl;
        }
    }

    void mostrarInfo() const override {
        cout << "Cuenta Corriente - Titular: " << titularCuenta 
             << ", Balance: $" << balance 
             << ", Límite de sobregiro: $" << limiteSobregiro << endl;
    }
};

// Prueba de las clases
int main() {
    CuentaAhorros ahorro("Carlos", 500.0, 2.5);
    CuentaCorriente corriente("Ana", 300.0, 200.0);

    ahorro.mostrarInfo();
    ahorro.depositar(200);
    ahorro.retirar(100);
    ahorro.mostrarInfo();

    cout << endl;

    corriente.mostrarInfo();
    corriente.depositar(150);
    corriente.retirar(600);
    corriente.mostrarInfo();

    return 0;
}
