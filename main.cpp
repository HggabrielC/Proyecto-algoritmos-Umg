#include <iostream>
using namespace std;

char menu() {
    char opcion = 0;
    cout << "Ingrese la opción\n";
    cout << "1). Crear cuentas monetarias\n";
    cout << "2). Operar depósitos\n";
    cout << "3). Operar retiros\n";
    cout << "4). Transferencias\n";
    cout << "5). Consulta saldo de cuenta\n";
    cout << "6). Salir\n";
    cin >> opcion;

    return opcion;
}

int main() {
    char opcion;
    opcion = menu();
    
    switch (opcion) {
        case '1':
            std::cout << "Has seleccionado: Crear cuentas monetarias" << std::endl;
            break;
        case '2':
            std::cout << "Has seleccionado: Operar depósitos" << std::endl;
            break;
        case '3':
            std::cout << "Has seleccionado: Operar retiros" << std::endl;
            break;
        case '4':
            std::cout << "Has seleccionado: Transferencias" << std::endl;
            break;
        case '5':
            std::cout << "Has seleccionado: Consulta saldo de cuenta" << std::endl;
            break;
        case '6':
            std::cout << "Saliendo del programa..." << std::endl;
            break;
        default:
            std::cout << "Opción no válida, por favor intente nuevamente." << std::endl;
    }

    return 0;
}
