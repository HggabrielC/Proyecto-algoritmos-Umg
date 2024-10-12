#include <iostream>
#include <string>
#include <fstream>
#include <cstdio> 
#include <sstream>
#include <iomanip>
#include <ctime>
#include <stdexcept>

using namespace std;

// Variables para las rutas de los archivos
string CTASMONETARIAS="E:/Mariano/Segundo Semestre/Algoritmos/Proyecto final/Proyecto-algoritmos-Umg/CTASMONETARIAS.txt";
string TRANSACCIONES="E:/Mariano/Segundo Semestre/Algoritmos/Proyecto final/Proyecto-algoritmos-Umg/TRANSACCIONES.txt";
string TEMP="E:/Mariano/Segundo Semestre/Algoritmos/Proyecto final/Proyecto-algoritmos-Umg/TEMP.txt";

// Función para mostrar el menú
char menu() {
    char opcion = 0;
    cout << "--------------------------------------" << endl;
    cout << "Ingrese la opcion\n";
    cout << "1). Crear cuentas monetarias\n";
    cout << "2). Operar depositos\n";
    cout << "3). Operar retiros\n";
    cout << "4). Transferencias\n";
    cout << "5). Consulta saldo de cuenta\n";
    cout << "6). Salir\n";
    cout << "--------------------------------------" << endl;
    cin >> opcion;
    return opcion;
}

// Función para obtener la fecha y hora actuales
string obtenerFechaHoraActual() {
    time_t ahora = time(0);
    tm *tiempoLocal = localtime(&ahora);
    stringstream fechaHora;
    fechaHora << setfill('0') << setw(2) << tiempoLocal->tm_mday << "/"
              << setw(2) << tiempoLocal->tm_mon + 1 << "/"  
              << tiempoLocal->tm_year + 1900 << " "  
              << setw(2) << tiempoLocal->tm_hour << ":"
              << setw(2) << tiempoLocal->tm_min << ":"
              << setw(2) << tiempoLocal->tm_sec;
    return fechaHora.str();
}

// Función para operar retiros
string retiros() {
    string numeroCuenta, linea, monto, nuevoSaldo, fecha;
    bool cuentaEncontrada = false;

    ifstream cuentas(CTASMONETARIAS);
    if (!cuentas.is_open()) {
        return "Error: No se pudo abrir el archivo de cuentas.";
    }

    ofstream temp(TEMP);
    if (!temp.is_open()) {
        cuentas.close();
        return "Error: No se pudo crear el archivo temporal.";
    }

    cout << "Ingrese el numero de cuenta: ";
    cin >> numeroCuenta;

    while (getline(cuentas, linea)) {
        stringstream ss(linea);
        string cuenta, nombre, telefono, correo, saldo;

        getline(ss, cuenta, ';');
        getline(ss, nombre, ';');
        getline(ss, telefono, ';');
        getline(ss, correo, ';');
        getline(ss, saldo, ';');

        if (cuenta == numeroCuenta) {
            cuentaEncontrada = true;
            cout << "Cuenta encontrada: " << nombre << endl;
            cout << "Saldo actual: " << saldo << endl;

            cout << "Ingrese la cantidad del retiro: ";
            cin >> monto;

            try {
                if (stoi(saldo) >= stoi(monto)) {
                    nuevoSaldo = to_string(stoi(saldo) - stoi(monto));
                    cout << "Retiro exitoso. Nuevo saldo: " << nuevoSaldo << endl;
                    temp << cuenta << ";" << nombre << ";" << telefono << ";" << correo << ";" << nuevoSaldo << endl;
                } else {
                    cout << "Fondos insuficientes." << endl;
                    temp << linea << endl;
                }
            } catch (invalid_argument &e) {
                cout << "Error: Datos no válidos en el archivo de cuentas." << endl;
                temp << linea << endl;
            }
        } else {
            temp << linea << endl;
        }
    }

    cuentas.close();
    temp.close();

    if (cuentaEncontrada) {
        if (remove(CTASMONETARIAS.c_str()) != 0) {
            return "Error al eliminar el archivo original.";
        }

        if (rename(TEMP.c_str(), CTASMONETARIAS.c_str()) != 0) {
            return "Error al renombrar archivo temporal.";
        }

        ofstream transacciones(TRANSACCIONES, ios::app);
        if (!transacciones.is_open()) {
            return "Error al registrar transaccion.";
        }

        fecha = obtenerFechaHoraActual();
        transacciones << numeroCuenta << ";" << fecha << ";" << monto << ";R" << endl;
        transacciones.close();

        return "Retiro registrado correctamente.";
    } else {
        remove(TEMP.c_str());
        return "Cuenta no encontrada.";
    }
}
// Función para consultar el saldo de una cuenta
string consultaSaldo() {
    string numeroCuenta, linea;
    bool cuentaEncontrada = false;

    ifstream cuentas(CTASMONETARIAS);
    if (!cuentas.is_open()) {
        return "Error: No se pudo abrir el archivo de cuentas.";
    }

    cout << "Ingrese el numero de cuenta: ";
    cin >> numeroCuenta;

    while (getline(cuentas, linea)) {
        stringstream ss(linea);
        string cuenta, nombre, telefono, correo, saldo;

        getline(ss, cuenta, ';');
        getline(ss, nombre, ';');
        getline(ss, telefono, ';');
        getline(ss, correo, ';');
        getline(ss, saldo, ';');

        if (cuenta == numeroCuenta) {
            cuentaEncontrada = true;
            cout << "Cuenta encontrada: " << nombre << endl;
            cout << "Saldo actual: " << saldo << endl;
            break;
        }
    }

    cuentas.close();

    if (!cuentaEncontrada) {
        return "Error: Cuenta no encontrada.";
    }
    return "Consulta de saldo realizada exitosamente.";
}


// Función principal con ciclo para mostrar el menú
int main() {
    char opcion;
    do {
        opcion = menu();
        switch (opcion) {
            case '1':
                cout << "Has seleccionado: Crear cuentas monetarias" << endl;
                cout << "--------------------------------------" << endl;
                break;
            case '2':
                cout << "Has seleccionado: Operar depositos" << endl;
                cout << "--------------------------------------" << endl;
                break;
            case '3':
                cout << "Has seleccionado: Operar retiros" << endl;
                cout << retiros() << endl;
                cout << "--------------------------------------" << endl;
                break;
            case '4':
                cout << "Has seleccionado: Transferencias" << endl;
                cout << "--------------------------------------" << endl;
                break;
            case '5':
                cout << "Has seleccionado: Consulta saldo de cuenta" << endl;
                cout << consultaSaldo() << endl;
                cout << "--------------------------------------" << endl;
                break;
            case '6':
                cout << "Saliendo del programa..." << endl;
                cout << "--------------------------------------" << endl;
                break;
            default:
                cout << "Opcion no valida, por favor intente nuevamente." << endl;
                cout << "--------------------------------------" << endl;
        }
    } while (opcion != '6');
    return 0;
}
//Funcion para la Creación de Cuentas Monetarias
    //Verifica que el número de cuenta sea exactamente de 10 dígitos y solo contenga números
    return numeroCuenta.length() == 10 && all_of(numeroCuenta.begin(), numeroCuenta.end(), ::isdigit);
}

bool validarTelefono(const string &telefono) {
    // Verifica que el teléfono tenga 8 dígitos y solo contenga números
    return telefono.length() == 8 && all_of(telefono.begin(), telefono.end(), ::isdigit);
}

bool validarCorreo(const string &correo) {
    // Verifica que el correo contenga un "@" y un "."
    size_t arroba = correo.find('@');
    size_t punto = correo.find('.', arroba);
    return arroba != string::npos && punto != string::npos && punto > arroba;
}

string crearCuenta() {
    string numeroCuenta, nombre, telefono, correo, saldoInicial;

    // Pedir número de cuenta y validarlo
    cout << "Ingrese el numero de cuenta (10 digitos): ";
    cin >> numeroCuenta;
    if (!validarNumeroCuenta(numeroCuenta)) {
        return "Error: Numero de cuenta invalido. Debe ser de 10 digitos.";
    }

    // Pedir el nombre
    cout << "Ingrese el nombre del titular: ";
    cin.ignore(); // Limpiar buffer
    getline(cin, nombre);
    if (nombre.empty()) {
        return "Error: El nombre no puede estar vacio.";
    }

    // Pedir el teléfono y validarlo
    cout << "Ingrese el telefono (8 digitos): ";
    cin >> telefono;
    if (!validarTelefono(telefono)) {
        return "Error: Telefono invalido. Debe ser de 8 digitos.";
    }

    // Pedir el correo y validarlo
    cout << "Ingrese el correo electronico: ";
    cin >> correo;
    if (!validarCorreo(correo)) {
        return "Error: Correo electronico invalido.";
    }

    // Pedir saldo inicial y validarlo
    cout << "Ingrese el saldo inicial: ";
    cin >> saldoInicial;
    try {
        if (stoi(saldoInicial) < 0) {
            return "Error: El saldo inicial no puede ser negativo.";
        }
    } catch (invalid_argument &e) {
        return "Error: Saldo invalido.";
    }

    // Almacenar la cuenta en el archivo
    ofstream cuentas(CTASMONETARIAS, ios::app);
    if (!cuentas.is_open()) {
        return "Error: No se pudo abrir el archivo de cuentas.";
    }

    cuentas << numeroCuenta << ";" << nombre << ";" << telefono << ";" << correo << ";" << saldoInicial << endl;
    cuentas.close();

    return "Cuenta creada exitosamente.";
}
