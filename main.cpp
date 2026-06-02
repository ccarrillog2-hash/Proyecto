#include "estructuras.h"
#include "archivos.h"
#include "gestionProductos.h"
#include "ventas.h"
#include "reportes.h"
#include "utilidades.h"
#include <iostream>

using namespace std;

void menuPrincipal();

int main() {
    cout << "Nombre del estudiante: Cindy Julissa Carrillo Guarcas\n\n";
    cargarProductos();
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    int opcion;
    do {
        cout << "==============================================\n";
        cout << "   SISTEMA DE GESTION DE VENTAS E INVENTARIO\n";
        cout << "==============================================\n";
        cout << "1. Gestion de Productos\n";
        cout << "2. Proceso de Venta\n";
        cout << "3. Reportes\n";
        cout << "4. Utilidades\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: gestionProductos(); break;
            case 2: procesoVenta(); break;
            case 3: reportes(); break;
            case 4: utilidades(); break;
            case 5: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion no valida\n";
        }
    } while(opcion != 5);
}