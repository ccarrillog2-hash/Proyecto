#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

struct Producto {
    int codigo;
    char nombre[50];
    int stock;
    double precio;
    bool activo;
    int ventasAcumuladas;
};

struct DetalleVenta {
    int codigoProducto;
    int cantidad;
    double precioUnitario;
    double subtotal;
};

struct Venta {
    int id;
    int dia, mes, anio;
    int numProductos;
    DetalleVenta detalles[20];
    double subtotal;
    double iva;
    double descuento;
    double total;
};
#endif