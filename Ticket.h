#pragma once
#include "Order.h"
#include "Shipping.h"
#include "VehicleType.h"
#include "RouteTime.h"
#include "Register.h"
#include <string>
using namespace std;

class Ticket {
private:
    Order* order;
    Register calendar;
    Shipping shipping;
    VehicleType vehicleType;
    RouteTime routeTime;
    string customerName;
    int orderID;
    string vehicle;


public:
    Ticket(Order* order, const string& customerName, int id)
        : order(order), customerName(customerName), orderID(id), calendar() {
    }

    int getOrderID() const { return orderID; }

    string getUsername() {
        return customerName;
    }
    void printTicket() {

        double totalWeight = order->getTotalWeight();
        double distance = order->getDistance();

        double shippingCost = shipping.calculateShippingPrice(totalWeight, distance);
        vehicle = vehicleType.determineVehicleType(totalWeight);
        double travelTime = routeTime.calculateTime(distance);

        cout << "============================ Detalles de la boleta ==========================" << endl;
        cout << "  -----------------------["; calendar.printDate(); cout << "]---------------------  " << endl;
        cout << "   "; calendar.printHour(); cout << endl;
        cout << "   ID de la boleta: " << orderID << endl;
        cout << "   Nombre del propietario: " << customerName << endl;
        order->showProducts();
        cout << "   Vehiculo asignado: " << vehicle << endl;
        cout << "   Precio total: " << shippingCost << endl;
        cout << "   Tiempo estimado de demora (minutos): " << travelTime << endl;
        cout << " -----------------------------------------------------------------------------" << endl;
    }

    void showOrderDetails() {
        double shippingCost = shipping.calculateShippingPrice(order->getTotalWeight(), order->getDistance());
        double travelTime = routeTime.calculateTime(order->getDistance());
        cout << "Pedido hecho por: " << customerName << " con el ID: " << orderID + 1;
        cout << "\nPrecio del pedido: " << shippingCost;
        cout << "\nTiempo aproximado de ruta: " << travelTime;
    }
    string getVehicleType() const {
        return vehicle;
    }
};
