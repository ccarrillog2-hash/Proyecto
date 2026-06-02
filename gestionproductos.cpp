#include "gestionProductos.h"
#include "estructuras.h"
#include "archivos.h"
#include "validaciones.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <stdexcept>

using namespace std;

extern Producto productos[];
extern int totalProductos;

void gestionProductos() {
    int opcion;
    do {
        cout << "\n=====================\n";
        cout << "GESTION DE PRODUCTOS \n";
        cout << "=====================\n";
        cout << "1. Registrar producto\n";
        cout << "2. Listar productos\n";
        cout << "3. Buscar por codigo\n";
        cout << "4. Buscar por nombre\n";
        cout << "5. Actualizar stock\n";
        cout << "6. Modificar precio\n";
        cout << "7. Eliminar/Desactivar producto\n";
        cout << "8. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: registrarProducto(); break;
            case 2: listarProductos(); break;
            case 3: buscarPorCodigo(); break;
            case 4: buscarPorNombre(); break;
            case 5: actualizarStock(); break;
            case 6: modificarPrecio(); break;
            case 7: eliminarProducto(); break;
        }
    } while(opcion != 8);
}

void registrarProducto() {
    try {
        Producto p;
        string entrada;

        cout << "\n=== Registro de Producto ===\n";

        do {
            cout << "Ingrese codigo: ";
            cin >> entrada;
            if(!esNumeroPositivo(entrada)) {
                cout << "Error: Solo numeros positivos sin letras ni signos.\n";
            }
        } while(!esNumeroPositivo(entrada));
        p.codigo = stoi(entrada);

        for(int i = 0; i < totalProductos; i++) {
            if(productos[i].codigo == p.codigo && productos[i].activo) {
                throw runtime_error("El codigo ya existe");
            }
        }

        cout << "Ingrese nombre: ";
        cin.ignore();
        cin.getline(p.nombre, 50);

        do {
            cout << "Ingrese stock: ";
            cin >> entrada;
            if(!esNumeroPositivo(entrada)) {
                cout << "Error: Solo numeros positivos.\n";
            } else if(stoi(entrada) <= 0) {
                cout << "Error: Stock debe ser mayor a 0.\n";
            } else {
                p.stock = stoi(entrada);
                break;
            }
        } while(true);

        do {
            cout << "Ingrese precio: Q";
            cin >> entrada;
            if(!esPrecioValido(entrada)) {
                cout << "Error: no se permite letras, ni numeros con signos.\n";
            } else if(stod(entrada) <= 0) {
                cout << "Error: Precio debe ser mayor a 0.\n";
            } else {
                p.precio = stod(entrada);
                break;
            }
        } while(true);

        p.ventasAcumuladas = 0;
        p.activo = true;
        productos[totalProductos++] = p;
        guardarProductos();
        cout << "Producto registrado exitosamente\n\n";

    } catch(const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void listarProductos() {
    cout << "\n=============================LISTA DE PRODUCTOS =========================== \n";
    cout << left << setw(10) << "Codigo" << setw(30) << "Nombre"
         << setw(10) << "Stock" << setw(12) << "Precio"
         << setw(10) << "Ventas" << "Estado\n";
    cout << "-------------------------------------------------------------------------------\n";
    for(int i = 0; i < totalProductos; i++) {
        if(productos[i].activo) {
            cout << left << setw(10) << productos[i].codigo
                 << setw(30) << productos[i].nombre
                 << setw(10) << productos[i].stock
                 << setw(12) << fixed << setprecision(2) << productos[i].precio
                 << setw(10) << productos[i].ventasAcumuladas << "Activo\n";
        }
    }
}

void buscarPorCodigo() {
    string entrada;
    int codigo;

    cout << "\n=== Busqueda por Codigo ===\n";
    do {
        cout << "Ingrese codigo que registro: ";
        cin >> entrada;
        if(!esNumeroPositivo(entrada)) {
            cout << "Error: Solo numeros positivos.\n";
        }
    } while(!esNumeroPositivo(entrada));
    codigo = stoi(entrada);

    for(int i = 0; i < totalProductos; i++) {
        if(productos[i].codigo == codigo && productos[i].activo) {
            cout << "Encontrado: " << productos[i].nombre
                 << " - Stock: " << productos[i].stock
                 << " - Precio: Q " << productos[i].precio << endl;
            return;
        }
    }
    cout << "Producto no encontrado\n\n";
}

void buscarPorNombre() {
    char nombre[50];
    cout << "\n=== Busqueda por Nombre ===\n";
    cin.ignore();
    cout << "Ingrese nombre: ";
    cin.getline(nombre, 50);

    bool encontrado = false;
    for(int i = 0; i < totalProductos; i++) {
        if(strstr(productos[i].nombre, nombre) != nullptr && productos[i].activo) {
            cout << "Codigo: " << productos[i].codigo
                 << " - Nombre: " << productos[i].nombre
                 << " - Stock: " << productos[i].stock << endl;
            encontrado = true;
        }
    }
    if(!encontrado) cout << "No se encontraron productos\n\n";
}

void actualizarStock() {
    string entrada;
    int codigo, nuevoStock;

    cout << "\n=== Actualizar Stock ===\n";

    do {
        cout << "Ingrese codigo que registro: ";
        cin >> entrada;
        if(!esNumeroPositivo(entrada)) {
            cout << "Error: Solo numeros positivos.\n";
        }
    } while(!esNumeroPositivo(entrada));
    codigo = stoi(entrada);

    for(int i = 0; i < totalProductos; i++) {
        if(productos[i].codigo == codigo && productos[i].activo) {
            cout << "Stock actual: " << productos[i].stock << endl;
            do {
                cout << "Nuevo stock: ";
                cin >> entrada;
                if(!esNumeroPositivo(entrada)) {
                    cout << "Error: Solo numeros positivos.\n";
                } else {
                    nuevoStock = stoi(entrada);
                    break;
                }
            } while(true);
            productos[i].stock = nuevoStock;
            guardarProductos();
            cout << "Stock actualizado\n\n";
            return;
        }
    }
    cout << "Producto no encontrado\n\n";
}

void modificarPrecio() {
    string entrada;
    int codigo;
    double nuevoPrecio;

    cout << "\n=== Modificar Precio ===\n";

    do {
        cout << "Ingrese codigo que registro: ";
        cin >> entrada;
        if(!esNumeroPositivo(entrada)) {
            cout << "Error: Solo numeros positivos.\n";
        }
    } while(!esNumeroPositivo(entrada));
    codigo = stoi(entrada);

    for(int i = 0; i < totalProductos; i++) {
        if(productos[i].codigo == codigo && productos[i].activo) {
            cout << "Precio actual: Q" << productos[i].precio << endl;
            do {
                cout << "Nuevo precio: Q";
                cin >> entrada;
                if(!esPrecioValido(entrada) || stod(entrada) <= 0) {
                    cout << "Error: Precio debe ser mayor a 0.\n";
                } else {
                    nuevoPrecio = stod(entrada);
                    break;
                }
            } while(true);
            productos[i].precio = nuevoPrecio;
            guardarProductos();
            cout << "Precio actualizado\n\n";
            return;
        }
    }
    cout << "Producto no encontrado\n\n";
}

void eliminarProducto() {
    int codigo;
    cout << "\n=== Eliminar Producto ===\n";
    cout << "Codigo que deseas eliminar: ";
    cin >> codigo;

    for(int i = 0; i < totalProductos; i++) {
        if(productos[i].codigo == codigo && productos[i].activo) {
            productos[i].activo = false;
            guardarProductos();
            cout << "Producto desactivado\n";
            return;
        }
    }
    cout << "Producto no encontrado\n";
}