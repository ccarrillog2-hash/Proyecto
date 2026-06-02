#include "utilidades.h"
#include "estructuras.h"
#include "archivos.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

extern Producto productos[];
extern int totalProductos;
extern double ventasPorMes[12][31];

void exportarReporteTxt() {
    ofstream archivo("reporte.txt");
    if(!archivo.is_open()) {
        cout << "Error al crear archivo\n";
        return;
    }

    archivo << "=== REPORTE DE INVENTARIO ===\n\n";
    archivo << left << setw(10) << "Codigo" << setw(35) << "Nombre"
            << setw(10) << "Stock" << setw(12) << "Precio"
            << setw(10) << "Ventas" << endl;
    archivo << "------------------------------------------------------------\n";

    for(int i = 0; i < totalProductos; i++) {
        if(productos[i].activo) {
            archivo << left << setw(10) << productos[i].codigo
                    << setw(35) << productos[i].nombre
                    << setw(10) << productos[i].stock
                    << setw(12) << fixed << setprecision(2) << productos[i].precio
                    << setw(10) << productos[i].ventasAcumuladas << endl;
        }
    }

    archivo.close();
    cout << "Reporte exportado a reporte.txt\n";
}

void reiniciarInventario() {
    char confirmacion;
    cout << "¿Esta seguro de reiniciar el inventario? (s/n): ";
    cin >> confirmacion;

    if(confirmacion == 's' || confirmacion == 'S') {
        totalProductos = 0;
        guardarProductos();

        for(int i = 0; i < 12; i++) {
            for(int j = 0; j < 31; j++) {
                ventasPorMes[i][j] = 0;
            }
        }

        remove("ventas.dat");
        cout << "Inventario reiniciado exitosamente\n";
    }
}

void mostrarEstadisticas() {
    double valorTotalInventario = 0;
    int productosBajoStock = 0;
    int totalVentasRegistradas = 0;
    int totalUnidadesVendidas = 0;

    for(int i = 0; i < totalProductos; i++) {
        if(productos[i].activo) {
            valorTotalInventario += productos[i].precio * productos[i].stock;
            if(productos[i].stock < 5) productosBajoStock++;
            totalUnidadesVendidas += productos[i].ventasAcumuladas;
        }
    }

    ifstream archivo("ventas.dat", ios::binary);
    if(archivo.is_open()) {
        Venta v;
        while(archivo.read(reinterpret_cast<char*>(&v), sizeof(Venta))) {
            totalVentasRegistradas++;
        }
        archivo.close();
    }

    cout << "\n=== ESTADISTICAS GENERALES ===\n";
    cout << "Total productos activos: " << totalProductos << endl;
    cout << "Valor inventario: Q" << fixed << setprecision(2) << valorTotalInventario << endl;
    cout << "Productos con stock bajo (<5): " << productosBajoStock << endl;
    cout << "Unidades totales vendidas: " << totalUnidadesVendidas << endl;
    cout << "Total ventas registradas: " << totalVentasRegistradas << endl;
}

void utilidades() {
    int opcion;
    do {
        cout << "\n===========================\n";
        cout << "        UTILIDADES \n";
        cout << "===========================\n";
        cout << "1. Exportar reporte a TXT\n";
        cout << "2. Reiniciar inventario\n";
        cout << "3. Mostrar estadisticas\n";
        cout << "4. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: exportarReporteTxt(); break;
            case 2: reiniciarInventario(); break;
            case 3: mostrarEstadisticas(); break;
        }
    } while(opcion != 4);
}