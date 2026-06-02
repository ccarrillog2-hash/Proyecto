#include "reportes.h"
#include "estructuras.h"
#include "archivos.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

extern Producto productos[];
extern int totalProductos;
extern double ventasPorMes[12][31];
extern const int MAX_PRODUCTOS;

void productosMenorStock() {
    cout << "\n=== PRODUCTOS CON MENOR STOCK ===\n";
    Producto temp[MAX_PRODUCTOS];
    int count = 0;
    for(int i = 0; i < totalProductos; i++) {
        if(productos[i].activo) temp[count++] = productos[i];
    }

    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            if(temp[j].stock > temp[j+1].stock) {
                swap(temp[j], temp[j+1]);
            }
        }
    }

    for(int i = 0; i < min(5, count); i++) {
        cout << temp[i].codigo << " - " << temp[i].nombre << " - Stock: " << temp[i].stock << endl;
    }
}

void productosMasVendidos() {
    cout << "\n=== PRODUCTOS MAS VENDIDOS ===\n";

    Producto temp[MAX_PRODUCTOS];
    int count = 0;

    for(int i = 0; i < totalProductos; i++) {
        if(productos[i].activo && productos[i].ventasAcumuladas > 0) {
            temp[count++] = productos[i];
        }
    }

    if(count == 0) {
        cout << "No hay ventas registradas aun.\n";
        return;
    }

    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            if(temp[j].ventasAcumuladas < temp[j+1].ventasAcumuladas) {
                swap(temp[j], temp[j+1]);
            }
        }
    }

    cout << "TOP 5 PRODUCTOS MAS VENDIDOS:\n";
    for(int i = 0; i < min(5, count); i++) {
        cout << i+1 << ". " << temp[i].nombre << " - Ventas: " << temp[i].ventasAcumuladas << endl;
    }
}

void ventasTotalesDelDia() {
    time_t t = time(0);
    tm* now = localtime(&t);
    int dia = now->tm_mday, mes = now->tm_mon + 1, anio = now->tm_year + 1900;

    double totalDia = 0;
    ifstream archivo("ventas.dat", ios::binary);
    if(archivo.is_open()) {
        Venta v;
        while(archivo.read(reinterpret_cast<char*>(&v), sizeof(Venta))) {
            if(v.dia == dia && v.mes == mes && v.anio == anio) {
                totalDia += v.total;
            }
        }
        archivo.close();
    }
    cout << "Ventas totales del dia: Q" << fixed << setprecision(2) << totalDia << endl;
}

void ventasPorMesMatriz() {
    cout << "\n=== VENTAS POR MES (MATRIZ) ===\n";
    for(int m = 0; m < 12; m++) {
        double totalMes = 0;
        for(int d = 0; d < 31; d++) {
            totalMes += ventasPorMes[m][d];
        }
        if(totalMes > 0) {
            cout << "Mes " << (m+1) << ": Q" << fixed << setprecision(2) << totalMes << endl;
        }
    }
}

void ordenarPorPrecioAsc() {
    Producto temp[MAX_PRODUCTOS];
    int count = 0;
    for(int i = 0; i < totalProductos; i++) {
        if(productos[i].activo) temp[count++] = productos[i];
    }

    for(int i = 0; i < count - 1; i++) {
        int minIdx = i;
        for(int j = i+1; j < count; j++) {
            if(temp[j].precio < temp[minIdx].precio) minIdx = j;
        }
        swap(temp[i], temp[minIdx]);
    }

    cout << "\n=== PRECIO ASCENDENTE ===\n";
    for(int i = 0; i < count; i++) {
        cout << temp[i].codigo << " - " << temp[i].nombre << " - Q" << temp[i].precio << endl;
    }
}

void ordenarPorPrecioDesc() {
    Producto temp[MAX_PRODUCTOS];
    int count = 0;
    for(int i = 0; i < totalProductos; i++) {
        if(productos[i].activo) temp[count++] = productos[i];
    }

    for(int i = 0; i < count - 1; i++) {
        int maxIdx = i;
        for(int j = i+1; j < count; j++) {
            if(temp[j].precio > temp[maxIdx].precio) maxIdx = j;
        }
        swap(temp[i], temp[maxIdx]);
    }

    cout << "\n=== PRECIO DESCENDENTE ===\n";
    for(int i = 0; i < count; i++) {
        cout << temp[i].codigo << " - " << temp[i].nombre << " - Q" << temp[i].precio << endl;
    }
}

void ordenarPorStockAsc() {
    Producto temp[MAX_PRODUCTOS];
    int count = 0;
    for(int i = 0; i < totalProductos; i++) {
        if(productos[i].activo) temp[count++] = productos[i];
    }

    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            if(temp[j].stock > temp[j+1].stock) {
                swap(temp[j], temp[j+1]);
            }
        }
    }

    cout << "\n=== STOCK ASCENDENTE ===\n";
    for(int i = 0; i < count; i++) {
        cout << temp[i].codigo << " - " << temp[i].nombre << " - Stock: " << temp[i].stock << endl;
    }
}

void ordenarPorStockDesc() {
    Producto temp[MAX_PRODUCTOS];
    int count = 0;
    for(int i = 0; i < totalProductos; i++) {
        if(productos[i].activo) temp[count++] = productos[i];
    }

    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            if(temp[j].stock < temp[j+1].stock) {
                swap(temp[j], temp[j+1]);
            }
        }
    }

    cout << "\n=== STOCK DESCENDENTE ===\n";
    for(int i = 0; i < count; i++) {
        cout << temp[i].codigo << " - " << temp[i].nombre << " - Stock: " << temp[i].stock << endl;
    }
}

void ordenarPorVentasAcumuladas() {
    Producto temp[MAX_PRODUCTOS];
    int count = 0;
    for(int i = 0; i < totalProductos; i++) {
        if(productos[i].activo) temp[count++] = productos[i];
    }

    for(int i = 1; i < count; i++) {
        Producto clave = temp[i];
        int j = i - 1;
        while(j >= 0 && temp[j].ventasAcumuladas < clave.ventasAcumuladas) {
            temp[j + 1] = temp[j];
            j--;
        }
        temp[j + 1] = clave;
    }

    cout << "\n=== VENTAS ACUMULADAS (MAYOR A MENOR) ===\n";
    for(int i = 0; i < count; i++) {
        cout << temp[i].codigo << " - " << temp[i].nombre << " - Ventas: " << temp[i].ventasAcumuladas << endl;
    }
}

void ordenarProductos() {
    int opcion;
    do {
        cout << "\n=== ORDENAR PRODUCTOS ===\n";
        cout << "1. Precio ascendente\n";
        cout << "2. Precio descendente\n";
        cout << "3. Stock ascendente \n";
        cout << "4. Stock descendente \n";
        cout << "5. Ventas acumuladas \n";
        cout << "6. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: ordenarPorPrecioAsc(); break;
            case 2: ordenarPorPrecioDesc(); break;
            case 3: ordenarPorStockAsc(); break;
            case 4: ordenarPorStockDesc(); break;
            case 5: ordenarPorVentasAcumuladas(); break;
        }
    } while(opcion != 6);
}

void reportes() {
    int opcion;
    do {
        cout << "\n==============================\n";
        cout << "           REPORTES\n";
        cout << "==============================\n";
        cout << "1. Productos con menor stock\n";
        cout << "2. Productos mas vendidos\n";
        cout << "3. Ventas totales del dia\n";
        cout << "4. Ventas por mes (Matriz)\n";
        cout << "5. Ordenar productos\n";
        cout << "6. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: productosMenorStock(); break;
            case 2: productosMasVendidos(); break;
            case 3: ventasTotalesDelDia(); break;
            case 4: ventasPorMesMatriz(); break;
            case 5: ordenarProductos(); break;
        }
    } while(opcion != 6);
}