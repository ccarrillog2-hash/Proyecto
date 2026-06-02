#include "archivos.h"
#include "estructuras.h"
#include <fstream>
#include <iostream>

using namespace std;

const int MAX_PRODUCTOS = 100;
const int MAX_DETALLES = 20;
Producto productos[MAX_PRODUCTOS];
int totalProductos = 0;
double ventasPorMes[12][31] = {0};

bool cargarProductos() {
    ifstream archivo("productos.dat", ios::binary);
    if(archivo.is_open()) {
        archivo.read(reinterpret_cast<char*>(&totalProductos), sizeof(totalProductos));
        archivo.read(reinterpret_cast<char*>(productos), sizeof(Producto) * totalProductos);
        archivo.close();

        ifstream archivoVentas("ventas.dat", ios::binary);
        if(archivoVentas.is_open()) {
            Venta v;
            while(archivoVentas.read(reinterpret_cast<char*>(&v), sizeof(Venta))) {
                for(int i = 0; i < v.numProductos; i++) {
                    ventasPorMes[v.mes - 1][v.dia - 1] += v.detalles[i].subtotal;
                }
            }
            archivoVentas.close();
        }
        return true;
    }
    return false;
}

bool guardarProductos() {
    ofstream archivo("productos.dat", ios::binary);
    if(archivo.is_open()) {
        archivo.write(reinterpret_cast<char*>(&totalProductos), sizeof(totalProductos));
        archivo.write(reinterpret_cast<char*>(productos), sizeof(Producto) * totalProductos);
        archivo.close();
        return true;
    }
    return false;
}

bool guardarVenta(Venta venta) {
    ofstream archivo("ventas.dat", ios::binary | ios::app);
    if(archivo.is_open()) {
        archivo.write(reinterpret_cast<char*>(&venta), sizeof(Venta));
        archivo.close();
        return true;
    }
    return false;
}

int generarIdVenta() {
    static int ultimoId = 0;
    ifstream archivo("ventas.dat", ios::binary);
    if(archivo.is_open()) {
        Venta v;
        while(archivo.read(reinterpret_cast<char*>(&v), sizeof(Venta))) {
            if(v.id > ultimoId) ultimoId = v.id;
        }
        archivo.close();
    }
    return ultimoId + 1;
}