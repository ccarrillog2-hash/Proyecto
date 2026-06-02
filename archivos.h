#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "estructuras.h"

extern const int MAX_PRODUCTOS;
extern const int MAX_DETALLES;
extern Producto productos[];
extern int totalProductos;
extern double ventasPorMes[12][31];

bool cargarProductos();
bool guardarProductos();
bool guardarVenta(Venta venta);
int generarIdVenta();

#endif