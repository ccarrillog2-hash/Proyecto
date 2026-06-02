#include "ventas.h"
#include "estructuras.h"
#include "archivos.h"
#include "validaciones.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>      // <--- ESTA LÍNEA FALTA
#include <stdexcept>

using namespace std;

extern Producto productos[];
extern int totalProductos;
extern double ventasPorMes[12][31];
extern const int MAX_DETALLES;

double aplicarDescuento(double subtotal, int totalArticulos) {
    double descuento = 0;
    if(subtotal > 500) {
        descuento = subtotal * 0.05;
        cout << "Descuento por monto > Q500: Q" << descuento << endl;
    }
    if(totalArticulos % 5 == 0 && totalArticulos > 0) {
        double bono = subtotal * 0.02;
        descuento += bono;
        cout << "Bono por multiplo de 5 articulos: Q" << bono << endl;
    }
    return descuento;
}

double redondear(double valor) {
    return round(valor * 100) / 100;
}

void crearVenta() {
    try {
        Venta venta;
        string entrada;
        venta.id = generarIdVenta();

        time_t t = time(0);
        tm* now = localtime(&t);
        venta.dia = now->tm_mday;
        venta.mes = now->tm_mon + 1;
        venta.anio = now->tm_year + 1900;

        venta.numProductos = 0;
        venta.subtotal = 0;
        int totalArticulos = 0;

        char continuar;
        do {
            if(venta.numProductos >= MAX_DETALLES) {
                throw runtime_error("Limite de productos por venta alcanzado");
            }

            int codigo, cantidad;

            do {
                cout << "\n===================================\n";
                cout << "        Proceso de venta \n";
                cout << "===================================\n";
                cout << "Codigo de producto registrado: ";
                cin >> entrada;
                if(!esNumeroPositivo(entrada)) {
                    cout << "Error: Solo numeros positivos.\n";
                }
            } while(!esNumeroPositivo(entrada));
            codigo = stoi(entrada);

            Producto* prod = nullptr;
            for(int i = 0; i < totalProductos; i++) {
                if(productos[i].codigo == codigo && productos[i].activo) {
                    prod = &productos[i];
                    break;
                }
            }

            if(prod == nullptr) {
                cout << "Producto no encontrado\n";
                continue;
            }

            cout << "Producto: " << prod->nombre << " - Stock: " << prod->stock << " - Precio: Q" << prod->precio << endl;

            do {
                cout << "Ingrese cantidad: ";
                cin >> entrada;
                if(!esNumeroPositivo(entrada) || stoi(entrada) <= 0) {
                    cout << "Error: Cantidad debe ser mayor a 0.\n";
                } else {
                    cantidad = stoi(entrada);
                    break;
                }
            } while(true);

            if(cantidad > prod->stock) {
                throw runtime_error("Stock insuficiente");
            }

            DetalleVenta detalle;
            detalle.codigoProducto = codigo;
            detalle.cantidad = cantidad;
            detalle.precioUnitario = prod->precio;
            detalle.subtotal = prod->precio * cantidad;

            venta.detalles[venta.numProductos++] = detalle;
            venta.subtotal += detalle.subtotal;
            totalArticulos += cantidad;

            ventasPorMes[venta.mes - 1][venta.dia - 1] += detalle.subtotal;

            prod->stock -= cantidad;
            prod->ventasAcumuladas += cantidad;

            cout << "Agregar otro producto (s/n): ";
            cin >> continuar;
        } while(continuar == 's' || continuar == 'S');

        venta.iva = venta.subtotal * 0.12;
        venta.descuento = aplicarDescuento(venta.subtotal, totalArticulos);
        venta.total = redondear(venta.subtotal + venta.iva - venta.descuento);

        cout << "\n====RESUMEN DE VENTA ====\n";
        cout << "Subtotal: Q" << fixed << setprecision(2) << venta.subtotal << endl;
        cout << "IVA (12%): Q" << venta.iva << endl;
        cout << "Descuento: Q" << venta.descuento << endl;
        cout << "TOTAL: Q" << venta.total << endl;

        guardarVenta(venta);
        guardarProductos();
        cout << "Venta registrada exitosamente\n";

    } catch(const exception& e) {
        cout << "Error en la venta: " << e.what() << endl;
    }
}

void procesoVenta() {
    crearVenta();
}