#include "pch.h"
#include <iostream>
#include <conio.h>
#include <map>
#include <algorithm>
#include <vector>
#include <time.h>
#include <fstream>
#include <functional>
#include <Windows.h>
#include <stdio.h>
#include <sstream>

#include "string"
#include "List.h"
#include "Person.h"
#include "Company.h"
#include "Driver.h"
#include "Ticket.h"
#include "BST.h"
#include "HashTable.h"
#include "Grafos.h"
#include "Header.h"

using namespace dby;
using namespace std;
using namespace System;

//////////////////// ARBOL /////////////////////////
BST<pair<double, Ticket*>> ArbolDistancias;
List<Order*>* ordersList = new List<Order*>;
List<Ticket*>* ticketsList = new List<Ticket*>;
List<Product*>* productsList = new List<Product*>;


List<User*>* usersList = new List<User*>;
List<Person*>* personsList = new List<Person*>;
List<Driver*>* driversList = new List<Driver*>;
List<Customer*>* customersList = new List<Customer*>;
List<Company*>* companiesList = new List<Company*>;

//////////// Listas para cada tipo de vehiculo //////////////////
List<Driver*>* driversMoto = new List<Driver*>;
List<Driver*>* driversAuto = new List<Driver*>;
List<Driver*>* driversCamion = new List<Driver*>;

/////////////// Mapa que asociará los pedidos con conductores ////////////////
map<Order*, Driver*> orderDriverMap;

//////////////////HASH TABLE////////////////////////////////
HashTable hashTable(100);

Grafos grafoConductores;

void leerDrivers(string arc) {
    ifstream archivo(arc);
    if (!archivo.is_open()) {
        cout << "no se puede";
    }
    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string username, email, password, licence, model;
        if (getline(iss, username, ',') && getline(iss, email, ',') && getline(iss, password, ',') && getline(iss, licence, ',') && getline(iss, model, ',')) {
            driversList->push_back(new Driver(username, email, password, licence, model));
            usersList->push_back(new Driver(username, email, password, licence, model));
            grafoConductores.agregarConductor(username, model);
        }
    }

    archivo.close();
}



// --------------  generar datos aleatorios ----------------------------
string generateRandomString(size_t length) {
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string randomString;
    for (size_t i = 0; i < length; ++i) {
        randomString += characters[rand() % characters.size()];
    }
    return randomString;
}


string randomVehicle() {

    const vector<string> vehicleTypes = { "moto", "auto", "camion" };
    string vehicleType = vehicleTypes[rand() % vehicleTypes.size()];
    return vehicleType;
}

string randomEmail() {
    return generateRandomString(6) + "@email.com";
}

string randomPassword() {
    return generateRandomString(5);
}

string randomLicense() {
    return "L" + to_string(rand() % 10000);
}

string randomUserType() {
    return (rand() % 2 == 0) ? "Person" : "Company";
}

string randomDNI() {
    srand(time(0));
    int dni = rand() % 90000000 + 10000000;
    stringstream ss;
    ss << dni;
    return ss.str();

}

string randomRUC() {
    srand(time(0));
    int ruc = rand() % 90000000000 + 10000000000;
    stringstream ss;
    ss << ruc;
    return ss.str();
}

string randomProductName() {
    const vector<string> products = { "Camiseta", "Pantalon", "Zapatos", "Reloj", "Celular", "Laptop", "Libro", "Gafas" };
    return products[rand() % products.size()];
}

float randomValue(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}


///////////////////CREAR DRIVERS//////////////////////////

void generateDrivers(int n) {
  
    srand(static_cast<unsigned>(time(0))); 
    
    for (int i = 0; i < n; ++i) {
        const vector<string> names = { "Juan ", "Ana ", "Carlos ", "Luis ", "Maria ", "Isabel ", "Pedro ", "Omar ", "Pancha ", "Fernanda ", "Felipe ", "Mateo " };
        const vector<string> secondNames = { "Perez", "Gomez", " Diaz", "Ramirez", "Rodriguez", "Gonzales", "Contreras", "Ojeda" };

        string name = names[rand() % names.size()] + secondNames[rand() % secondNames.size()];
        string email = generateRandomString(6) + "@driver.com";
        string password = generateRandomString(5);
        string licenseNumber = "L" + to_string(rand() % 10000);
        string vehicleType = randomVehicle();

        Driver* driver = new Driver(name, email, password, licenseNumber, vehicleType);
        driversList->push_back(driver);
        usersList->push_back(driver);

        if (vehicleType == "moto") {
            driversMoto->push_back(driver);
        }
        else if (vehicleType == "auto") {
            driversAuto->push_back(driver);
        }
        else if (vehicleType == "camion") {
            driversCamion->push_back(driver);
        }
    }

    cout << n << " conductores generados aleatoriamente." << endl;
    cout << "Presione cualquier tecla para continuar..." << endl;
    _getch();
}
void generatePersonCompany(int n) {

    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < n; ++i) {
        const vector<string> namesU = { "Emilio ", "Juana ", "Carla ", "Federico ", "Emilia ", "Alejandra ", "Paul ", "Mauricio ", "Elena ", "Pablo ", "Sebastian ", "Martin " };
        const vector<string> secondNames = { "Herrera", "Loyola", "Chavez", "Medina", "Castro", "Alvarez", "Sauñe", "Garcia", "Aguilar", "Alves", "Sanchez", "Vasquez", "Mamani" };
        string name = namesU[rand() % namesU.size()] + secondNames[rand() % secondNames.size()];
        string email = generateRandomString(6) + "@user.com";
        string password = generateRandomString(5);
        string userType = randomUserType();
        User* user = nullptr;
       
        if (userType == "Person") {
            string dni = randomDNI();
            user = new Person(name, email, password, dni);
            personsList->push_back(static_cast<Person*>(user));
        }
        else if (userType == "Company") {
            string ruc = randomRUC();
            user = new Company(name, email, password, ruc);
            companiesList->push_back(static_cast<Company*>(user));
        }

        if (user != nullptr) {
            usersList->push_back(user);
        }
    }
    cout << n << " usuarios generados aleatoriamente." << endl;
    cout << "Presione cualquier tecla para continuar..." << endl;
    _getch();
}

void createOrders(int n, string& customerName) {
    system("cls");
    std::cout << "Creando ordenes..." << endl;
    Sleep(500);

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < n; ++i) {
        double distance = static_cast<double>(rand() % 100 + 10);
        int numProducts = rand() % 3 + 1;  // entre 1 y 3 productos por orden

        List<Product*>* productsList = new List<Product*>;
        for (int j = 0; j < numProducts; ++j) {
            string productName = randomProductName();
            float width = randomValue(5.0f, 50.0f);
            float height = randomValue(2.0f, 30.0f);
            float weight = randomValue(0.1f, 10.0f);
            float value = randomValue(50.0f, 500.0f);

            productsList->push_back(new Product(productName, width, height, weight, value, j + 1, i + 1, customerName));

    
        }

        Route* route = new Route("Origen", "Destino", distance);
        Order* order = new Order(productsList, route, i + 1, customerName);
        Ticket* ticket = new Ticket(order, customerName, i+1);
        ticketsList->push_back(ticket);
        hashTable.insert(ticket);
    }

    system("cls");
    std::cout << "Ordenes generadas exitosamente." << endl;
    Sleep(500);
}

// ----------------- MOSTRAR LISTA DE CONDUCTORES ---------------------
void showDriversList(List<Driver*>* driversList, Order* order) {
    Ticket* ticket = nullptr;
    std::cout << "Seleccione un conductor de la siguiente lista:" << endl;
    for (int i = 0; i < driversList->size(); i++) {
        std::cout << i + 1 << ". " << driversList->at(i)->getName() << endl;
    }
    int selectedDriverIndex;
    std::cin >> selectedDriverIndex;
    selectedDriverIndex--;  // ajustar a índice basado en 0

    Driver* selectedDriver = driversList->at(selectedDriverIndex);
    orderDriverMap[order] = selectedDriver;

    std::cout << "Conductor " << selectedDriver->getName() << " asignado al pedido." << endl;

}

// -------------- MOSTRAR MENÚ PARA CUSTOMER Y DRIVER -----------------

int showMenuForCustomers() {
    std::cout << "==================== MENU DE CLIENTES ==================" << endl << endl;
    std::cout << "|  [1] Hacer pedido                                    |" << endl;
    std::cout << "|  [2] Mostrar boletas                                 |" << endl;
    std::cout << "|  [3] Generar pedidos                                 |" << endl;
    std::cout << "|  [4] Buscar  Orden por ID (HashTable)                |" << endl;
    std::cout << "|  [5] Eliminar Orden por ID (HashTable)               |" << endl;
    std::cout << "|  [6] Cerrar sesion                                   |" << endl << endl;
    std::cout << "========================================================" << endl << endl;
    int option;
    do
    {
        std::cin >> option;
        if (option < 1 || option>6)
            std::cout << "Ingrese una opcion valida... ";
    } while (option < 1 || option>6);

    return option;
}

int showMenuForEmployees() {
    std::cout << "========================== MENU DE EMPLEADOS =======================" << endl << endl;
    std::cout << "|[1] Mostrar informacion del perfil                                |" << endl;
    std::cout << "|[2] Mostrar lista pedidos (seleccionar pedido a realizar)         |" << endl;
    std::cout << "|[3] Manejar distancias (km) usando arboles de busqueda binaria    |" << endl;
    std::cout << "|[4] Cerrar sesion                                                 |" << endl;
    std::cout << "====================================================================" << endl << endl;
    int option;
    do
    {
        std::cin >> option;
        if (option < 1 || option>4)
            std::cout << "Ingrese una opcion valida... ";
    } while (option < 1 || option>4);

    return option;
}

// --------------- EJECTUTAR MENU PARA CUSTOMER Y DRIVER ----------------
void executeMenuForCustomers(int option, int idCustomer, int& integer) {

    string origin, destination;
    string vehicleType;
    double distance;
    int n;
    string nameProduct;
    float width, height, weight, value;
    bool ticketF;

    Ticket* currentTicket;
    Ticket* foundTicket;
    Ticket* ticket = nullptr;
    Order* order = nullptr;
    Route* route = nullptr;
    Shipping shipping;


    double shippingCost = 0;

    switch (option) {
    case 1:
        integer++;
        system("cls");
        std::cout << " ............................ " << endl;
        std::cout << " Pedido " << integer + 1 << ": " << endl;

        std::cout << " Ingresa el lugar de recojo: ";
        std::cin >> origin;
        std::cout << " Ingresa el lugar de entrega: ";
        std::cin >> destination;
        std::cout << " Ingresa la distancia entre el punto de origen y el destino en km: ";
        std::cin >> distance;

        route = new Route(origin, destination, distance);

        std::cout << " Ingresa la cantidad de productos a transportar: ";
        std::cin >> n;

        for (int i = 0; i < n; i++) {

            std::cout << " Ingresa el nombre del producto " << i + 1 << ": ";
            std::cin >> nameProduct;
            std::cout << " Ingresa la altura del producto " << i + 1 << " en centimetros: ";
            std::cin >> height;
            std::cout << " Ingresa el ancho del producto " << i + 1 << " en centimetros: ";
            std::cin >> width;
            std::cout << " Ingresa el peso del producto " << i + 1 << " en kilogramos: ";
            std::cin >> weight;
            std::cout << " Ingresa el valor (S/.) del producto " << i + 1 << " en soles: S/.";
            std::cin >> value;
            std::cout << " Producto registrado exitosamente!" << endl;
            std::cout << " Presiona cualquier tecla para continuar..." << endl;

            productsList->push_back(new Product(nameProduct, width, height, weight, value, i + 1, integer,
                usersList->at(idCustomer)->getName()));

            _getch();

        }
        order = new Order(productsList, route, integer, usersList->at(idCustomer)->getName());
        ordersList->push_back(order);

        shippingCost = shipping.calculateShippingPrice(order->getTotalWeight(), distance);


        ticket = new Ticket(order, usersList->at(idCustomer)->getName(), integer);
        ticketsList->push_back(ticket);

        ArbolDistancias.insert({distance, ticket});

        system("cls");
        ticket->printTicket();
        std::cout << " Presione cualquier tecla para ver los conductores disponibles para su pedido..." << endl;

        _getch();



        vehicleType = VehicleType().determineVehicleType(order->getTotalWeight());

        if (vehicleType == "moto" && !driversMoto->empty()) {
            std::cout << " -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ " << endl;
            std::cout << " Lista de conductores de moto: " << endl;
            std::cout << " -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ " << endl;
            showDriversList(driversMoto, order);
        }
        else if (vehicleType == "auto" && !driversAuto->empty()) {
            std::cout << " -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ " << endl;
            std::cout << " Lista de conductores de auto: " << endl;
            std::cout << " -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ " << endl;
            showDriversList(driversAuto, order);
        }
        else if (vehicleType == "camion" && !driversCamion->empty()) {
            std::cout << " -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ " << endl;
            std::cout << "Lista de conductores de camión:" << endl;
            std::cout << " -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ " << endl;
            showDriversList(driversCamion, order);
        }

        if (driversMoto->empty() && driversAuto->empty() && driversCamion->empty()) {
            std::cout << " Actualmente no hay conductores disponibles " << endl;
        }

        std::cout << "Presione cualquier tecla para volver al menu..." << endl;
        _getch();

        system("cls");
        executeMenuForCustomers(showMenuForCustomers(), idCustomer, integer);
        break;
    case 2:
        system("cls");
        std::cout << " ------- [ MOSTRANDO BOLETAS ] ------- " << endl;

        if (!ticketsList->empty()) {
            for (int i = 0; i < ticketsList->size(); ++i) {
                if (ticketsList->at(i)->getUsername() == usersList->at(idCustomer)->getName()) {
                    std::cout << " Boleta " << ticketsList->at(i)->getOrderID() << ":" << endl;
                    ticketsList->at(i)->printTicket();
                    std::cout << endl;
                }
            }
        }
        else {
            std::cout << "No hay boletas para mostrar " << endl;
        }

        std::cout << "Presione cualquier tecla para volver al menu..." << endl;
        _getch();
        system("cls");
        executeMenuForCustomers(showMenuForCustomers(), idCustomer, integer);
        break;
    case 3:
        int numPedidos;
        std::cout << "Ingrese el numero de pedidos aleatorios a generar: ";
        std::cin >> numPedidos;
        createOrders(numPedidos, usersList->at(idCustomer)->getName());

        std::cout << "Presione cualquier tecla para volver al menu..." << endl;
        _getch();

        system("cls");
        executeMenuForCustomers(showMenuForCustomers(), idCustomer, integer);
        break;
    case 4:
        int ticketID;
        std::cout << "Ingrese el ID del ticket a buscar: ";
        std::cin >> ticketID;

        // Realizar la búsqueda en la HashTable
        foundTicket = hashTable.search(ticketID);

        if (foundTicket != nullptr) {
            std::cout << "Ticket encontrado:" << endl;
            foundTicket->printTicket();
        }
        else {
            std::cout << "No se encontro ningún ticket con el ID ingresado." << endl;
        }

        std::cout << "Presione cualquier tecla para volver al menu..." << endl;
        _getch();
        system("cls");
        executeMenuForCustomers(showMenuForCustomers(), idCustomer, integer);
        break;
    case 5:
        int ticketIDToDelete;
        std::cout << "Ingrese el ID del ticket a eliminar: ";
        std::cin >> ticketIDToDelete;

        // Realizar la búsqueda en la HashTable
        foundTicket = hashTable.search(ticketIDToDelete);

        if (foundTicket != nullptr) {
            std::cout << " ¡Ticket encontrado! " << endl;
            foundTicket->printTicket();
            std::cout << " ¿Esta seguro que desea eliminar este ticket? (S/N): ";
            char confirmation;
            std::cin >> confirmation;
            if (confirmation == 'S' || confirmation == 's') {
                // Eliminar ticket de la HashTable y de la lista de tickets
                hashTable.erase(foundTicket->getOrderID(), foundTicket->getUsername());
                std::cout << "Ticket eliminado exitosamente." << endl;
            }
        }
        else {
            std::cout << "No se encontro ningún ticket con el ID ingresado." << endl;
        }

        std::cout << "Presione cualquier tecla para volver al menú..." << endl;
        _getch();
        system("cls");
        executeMenuForCustomers(showMenuForCustomers(), idCustomer, integer);
        break;
    case 6:
        std::cout << "Cerrando sesion..." << endl;
        return;

    }

}

//ORDENAMIENTO POR PRECIO, DISTANCIA Y PESO

void showOrdersMenu() {
    std::cout << " +=======================================+ " << endl;
    std::cout << "  Seleccione el criterio de ordenamiento  " << endl;
    std::cout << " +=======================================+ " << endl;
    std::cout << "  [1] Ordenar por monto                    " << endl;
    std::cout << "  [2] Ordenar por kilometros               " << endl;
    std::cout << "  [3] Ordenar por peso                     " << endl;
    std::cout << "  [4] Sin ordenamiento                     " << endl;
    std::cout << " ----------------------------------------- " << endl;
}

bool compareByAmount(Order* a, Order* b) {
    return a->getTotalAmount() < b->getTotalAmount(); //Forma ascendente
}
bool compareByDistance(Order* a, Order* b) {
    return a->getRoute()->getDistance() > b->getRoute()->getDistance(); //Forma descendente
}
bool compareByWeight(Order* a, Order* b) {
    return a->getTotalWeight() > b->getTotalWeight(); //Forma descendente
}

void sortOrdersByAmount(List<Order*>* ordersList) {
    // Bubble Sort
    int n = ordersList->size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            // Comparar y hacer el intercambio si es necesario
            if (!compareByAmount(ordersList->at(j), ordersList->at(j + 1))) {
                swap(ordersList->at(j), ordersList->at(j + 1));
            }
        }
    }
}

void sortOrdersByDistance(List<Order*>* ordersList) {
    vector<Order*> orderVector;
    for (int i = 0; i < ordersList->size(); ++i) {
        orderVector.push_back(ordersList->at(i));
    }
    sort(orderVector.begin(), orderVector.end(), compareByDistance);
    for (int i = 0; i < orderVector.size(); ++i) {
        ordersList->at(i) = orderVector[i];
    }
}

void sortOrderByWeight(List<Order*>* ordersList) {
    vector<Order*> orderVector;
    for (int i = 0; i < ordersList->size(); ++i) {
        orderVector.push_back(ordersList->at(i));
    }
    // Ordenamiento por inserción
    for (int i = 1; i < orderVector.size(); ++i) {
        Order* key = orderVector[i];
        int j = i - 1;
        // Mover elementos de orderVector[0..i-1], que son mayores que key,
        // a una posición adelante de su posición actual
        while (j >= 0 && key->getTotalWeight() > orderVector[j]->getTotalWeight()) {
            orderVector[j + 1] = orderVector[j];
            j = j - 1;
        }
        orderVector[j + 1] = key;
    }

    for (int i = 0; i < orderVector.size(); ++i) {
        ordersList->at(i) = orderVector[i];
    }
}

int menuForBST() {
    int option;
    system("cls");
    std::cout << " ========= [ ARBOL-BST MENU ] ========= " << endl << endl;
    std::cout << "  [1] Ver distancias mayores            " << endl;
    std::cout << "  [2] Buscar pedido por distancia especifica (km)   " << endl;
    std::cout << "  [3] Buscar pedidos en rango de distancias (km)    " << endl;
    std::cout << "  [4] Salir                             " << endl;
    std::cout << " -------------------------------------- " << endl;

    do {
        std::cin >> option;
        if (option < 1 || option>4) {
            std::cout << "Ingrese una opcion valida...";
        }
    } while (option < 1 || option>4);

    return option;
}

void executeMenuForEmployees(int option, int idEmployee)
{

    int optionForBST = 0;
    switch (option) {
    case 1:
        system("cls");
        std::cout << " ========= [ PERFIL - EMPLEADO ] ========= " << endl << endl;
        std::cout << "  Usuario: " << driversList->at(idEmployee)->getName() << endl;
        std::cout << "  Email: " << driversList->at(idEmployee)->getEmail() << endl;
        std::cout << "  Licencia de Conducir: " << driversList->at(idEmployee)->getDriverLicense() << endl;
        std::cout << "  Tipo de Vehiculo: " << driversList->at(idEmployee)->getModel() << endl;
        std::cout << "  Contrasenia: ";
        for (int i = 0; i < driversList->at(idEmployee)->getPassword().size(); i++) {
            std::cout << "*";
        }
        std::cout << endl;
        _getch();
        system("cls");
        executeMenuForEmployees(showMenuForEmployees(), idEmployee);
        break;
    case 2:
        // Mostrar lista de pedidos pendientes y permitir al empleado seleccionar un pedido
        if (ordersList->empty()) {
            system("cls");
            std::cout << "No hay pedidos pendientes." << endl;
            _getch();
        }
        else {
            // Mostrar lista de opciones de ordenamiento
            system("cls");
            showOrdersMenu();
            int orderBy;
            std::cin >> orderBy;
            List<Order*>* assignedOrdersList = new List<Order*>;
            for (int i = 0; i < ordersList->size(); ++i) {
                if (orderDriverMap[ordersList->at(i)]->getEmail() == usersList->at(idEmployee)->getEmail()) {
                    assignedOrdersList->push_back(ordersList->at(i));
                }
            }
            // Aplicar el ordenamiento según la opción seleccionada
            switch (orderBy) {
            case 1:
                sortOrdersByAmount(assignedOrdersList);
                break;
            case 2:
                sortOrdersByDistance(assignedOrdersList);
                break;
            case 3:
                sortOrderByWeight(assignedOrdersList);
                break;
            case 4:
                break;
            default:
                std::cout << "Opción no válida." << endl;
                return;
            }

            // Mostrar los datos de los pedidos ordenados
            std::cout << "Lista de pedidos pendientes:" << endl;
            for (int i = 0; i < assignedOrdersList->size(); ++i) {
                Order* order = assignedOrdersList->at(i);
                std::cout << i + 1 << ". Pedido desde " << assignedOrdersList->at(i)->getRoute()->getOrigin()
                    << " hasta " << assignedOrdersList->at(i)->getRoute()->getDestination() << endl;
                std::cout << "   Monto total: S/." << order->getTotalAmount() << endl;
                std::cout << "   Distancia: " << order->getDistance() << " km" << endl;
                std::cout << "   Peso: " << order->getTotalWeight() << endl;
            }

            // Permitir al conductor seleccionar un pedido
            std::cout << "Seleccione el número de pedido que desea realizar: ";
            int selectedOrderIndex;
            std::cin >> selectedOrderIndex;
            selectedOrderIndex--;

            // Validar la entrada del usuario
            system("cls");
            if (selectedOrderIndex >= 0 && selectedOrderIndex < assignedOrdersList->size()) {
                Order* selectedOrder = assignedOrdersList->at(selectedOrderIndex);
                List<Product*>* productsOfOrder = selectedOrder->getProductsList();
                std::cout << "Productos del pedido seleccionado:" << endl;
                for (int i = 0; i < productsOfOrder->size(); ++i) {
                    Product* product = productsOfOrder->at(i);
                    // Verificar si el pedido del producto coincide con el pedido seleccionado
                    if (product->getOrderID() == selectedOrder->getOrderID()) {
                        product->showProductInfo();
                    }
                }
                std::cout << "Orden en curso...";
            }
            else {
                std::cout << "Numero de pedido no válido." << endl;
            }
            _getch();
        }
        system("cls");
        executeMenuForEmployees(showMenuForEmployees(), idEmployee);
        break;
    case 3:
        while (true) {
            optionForBST = menuForBST();

            if (optionForBST == 1) {
                system("cls");
                std::cout << "Mostrando distancias de forma descendente con usuario asignado...\n";
                ArbolDistancias.traverse_descending([](pair<double, Ticket*> value) {
                    std::cout << value.first << " - " << value.second->getUsername() << endl;
                    });

                _getch();


            }
            else if (optionForBST == 2) {
                system("cls");
                double distanceBST;
                std::cout << "Ingrese distancia especifica a buscar: "; std::cin >> distanceBST;
                pair<double, Ticket*>* found = ArbolDistancias.find(distanceBST);
                if (found) {
                    std::cout << "Detalles del pedido con distancia: " << distanceBST << ": \n";
                    found->second->showOrderDetails();

                }
                else {
                    std::cout << "No se encontro ningun pedido con esa distancia...\n";
                }
                _getch();


            }

            else if (optionForBST == 3) {
                system("cls");
                int x, y;
                int existen = 0;
                std::cout << endl << "Ingrese rango busqueda desde: ";
                std::cin >> x;
                std::cout << endl << "Hasta: "; std::cin >> y; std::cout << endl;

                for (int i = x; i <= y; i++) {
                    pair<double, Ticket*>* foundi = ArbolDistancias.find(i);
                    if (foundi) {
                        existen++;
                    }
                }
                if (existen) {
                    for (int i = x; i <= y; i++) {
                        pair<double, Ticket*>* foundj = ArbolDistancias.find(i);
                        if (foundj) {
                            std::cout << "Detalles de los pedidos en el rango de distancias de " << x << " km hasta " << y << " km" << endl;
                            foundj->second->showOrderDetails();
                            std::cout << endl;
                        }
                    }
                }
                else {
                    std::cout << "No se han encontrado pedidos en ese rango de distancias...\n";
                }
                _getch();


            }
            else {
                system("cls");
                executeMenuForEmployees(showMenuForEmployees(), idEmployee);
                break;
            }
        }
    case 4:
        std::cout << "Cerrando sesión..." << endl;
        return;
    }
}

//REGISTRAR USUARIO

void registerUser() {

    string username, email, password;
    string dni;
    string ruc;
    string licenseNumber, vehicleType;


    //USUARIO (USER):
    system("cls");
    std::cout << "Ingrese:" << endl;
    std::cout << "1. Customer -> Si desea usar nuestro servicio" << endl;
    std::cout << "2. Employee -> Si desea trabajar para nosotros" << endl;
    std::cout << " --- --- --- --- --- --- --- --- --- --- --- ---" << endl;
    int userType;
    do {
        std::cin >> userType;
        if (userType < 1 || userType>2) std::cout << "Ingrese opcion valida... ";
    } while (userType < 1 || userType > 2);
    std::cout << endl;

    //CLIENTE (CUSTOMER):
    if (userType == 1) {



        std::cout << "Ingrese: " << endl;
        std::cout << "1. Person -> Si es persona" << endl;
        std::cout << "2. Company -> Si es compania/empresa" << endl;
        std::cout << " --- --- --- --- --- --- --- --- --- ---" << endl;

        int customerType;

        do {
            std::cin >> customerType;
            if (customerType < 1 || customerType>2) std::cout << "Ingrese opcion valida... ";
        } while (customerType < 1 || customerType > 2);
        switch (customerType) {

            //PERSONA (PERSON):
        case 1:


            system("cls");
            std::cout << "REGISTRANDO CLIENTE PERSONA..." << endl;
            std::cout << "Ingresa tu nombre y apellido: ";
            std::cin.ignore();
            getline(std::cin, username);
            std::cout << "Ingresa tu correo electronico: ";
            std::cin >> email;
            std::cout << "Crea tu contrasenia: ";
            std::cin >> password;
            std::cout << "Ingrese tu numero de DNI: ";
            std::cin >> dni;

            usersList->push_back(new Person(username, email, password, dni));
            customersList->push_back(new Person(username, email, password, dni));
            break;

            //COMPAÑIA/EMPRESA (COMPANY):
        case 2:


            system("cls");
            std::cout << "REGISTRANDO CLIENTE EMPRESA..." << endl;
            std::cout << "Ingresa el nombre de tu empresa: ";
            std::cin.ignore();
            getline(std::cin, username);
            std::cout << "Ingresa tu correo electronico: ";
            std::cin >> email;
            std::cout << "Crea tu contrasenia: ";
            std::cin >> password;
            std::cout << "Ingrese tu numero de RUC: ";
            std::cin >> ruc;

            usersList->push_back(new Company(username, email, password, ruc));
            customersList->push_back(new Company(username, email, password, ruc));
            break;

        }

    }
    //EMPLEADO (EMPLOYEE):

                    //CONDUCTOR (DRIVER):
    else if (userType == 2) {
        system("cls");
        std::cout << "REGISTRANDO EMPLEADO CONDUCTOR..." << endl;
        std::cout << "Ingresa tu nombre y apellido: ";
        std::cin.ignore();
        getline(std::cin, username);
        std::cout << "Ingresa tu correo electronico: ";
        std::cin >> email;
        std::cout << "Crea tu contrasenia: ";
        std::cin >> password;
        std::cout << "Ingrese tu numero de licencia de conducir: ";
        std::cin >> licenseNumber;
        std::cout << "Ingrese el tipo de tu vehiculo: ";
        std::cin >> vehicleType;
        //VALIDANDO TIPO DE VEHÍCULO
        while (vehicleType != "moto" && vehicleType != "auto" && vehicleType != "camion") {
            std::cout << "Tipo de vehiculo no valido. Ingrese 'moto', 'auto' o 'camion': ";
            std::cin >> vehicleType;
        }
        Driver* driver = new Driver(username, email, password, licenseNumber, vehicleType);
        driversList->push_back(driver);
        usersList->push_back(driver);

        if (vehicleType == "moto") {
            driversMoto->push_back(driver);
        }
        else if (vehicleType == "auto") {
            driversAuto->push_back(driver);
        }
        else if (vehicleType == "camion") {
            driversCamion->push_back(driver);
        }

    }
    std::cout << "\nUsuario registrado exitosamente..." << endl;
    std::cout << "Presione cualquier tecla para volver al menu..." << endl;
    _getch();
}

//MOSTRAR ORDENES PENDIENTES PARA DRIVER
void showPendingOrders(Driver* driver) {
    User* user = nullptr;
    std::cout << "\nPedidos pendientes para el conductor " << driver->getName() << ":" << endl;
    bool hasPendingOrders = false;

    // Iterar sobre el mapa de pedidos y conductores
    for (const auto& pair : orderDriverMap) {
        // Verificar si el conductor coincide
        if (pair.second == driver) {
            Order* order = pair.first;
            Route* route = order->getRoute();
            std::cout << "Pedido desde " << route->getOrigin() << " hasta " << route->getDestination() << endl;
            std::cout << "Distancia: " << route->getDistance() << " km" << endl;
            std::cout << "Productos: " << endl;

            // Iterar sobre la lista de productos del pedido
            for (int i = 0; i < order->getProductsList()->size(); i++) {
                Product* product = order->getProductsList()->at(i);
                std::cout << "   - " << product->getNameProduct() << " (" << product->getWeight() << " kg)" << endl;
            }
            hasPendingOrders = true;
        }
    }

    // Verificar si no hay pedidos pendientes
    if (!hasPendingOrders) {
        std::cout << "No hay pedidos pendientes." << endl;
    }
    std::cout << "Presione cualquier tecla para volver al menu..." << endl;
    _getch();
}

void showUsersListForLogin() {
    cout << "Lista de usuarios registrados:" << endl;
    cout << "Personas: " << endl;
    for (int i = 0; i < personsList->size(); ++i) {
        Person* person = personsList->at(i);
        cout << i + 1 << ". " << person->getName() << endl;
    }
    cout << "Companias: " << endl;
    for (int i = 0; i < companiesList->size(); ++i) {
        Company* company = companiesList->at(i);
        std::cout << i + 1 << ". " << company->getName() << endl;
    }
}

// Función para mostrar la información de inicio de sesión de un conductor
void showUsersLoginInfo(int usersIndex) {
    if (usersIndex >= 0 && usersIndex < personsList->size()) {
        Person* person = personsList->at(usersIndex);
        std::cout << "Correo electronico: " << person->getEmail() << endl;
        std::cout << "Contraseña: " << person->getPassword() << endl;
        std::cout << endl;
    }
    else if (usersIndex >= personsList->size() && usersIndex < personsList->size() + companiesList->size()) {
        Company* company = companiesList->at(usersIndex - personsList->size());
        std::cout << "Correo electronico: " << company->getEmail() << endl;
        std::cout << "Contraseña: " << company->getPassword() << endl;
        std::cout << endl;
    }
    else {
        std::cout << "Indice de usuario no válido." << endl;
    }
}
void showDriversListForLogin() {
    std::cout << "Lista de conductores disponibles:" << endl;
    for (int i = 0; i < driversList->size(); ++i) {
        Driver* driver = driversList->at(i);
        std::cout << i + 1 << ". " << driver->getName() << endl;
    }
}

// Función para mostrar la información de inicio de sesión de un conductor
void showDriverLoginInfo(int driverIndex) {
    if (driverIndex >= 0 && driverIndex < driversList->size()) {
        Driver* driver = driversList->at(driverIndex);
        std::cout << "Correo electronico: " << driver->getEmail() << endl;
        std::cout << "Contrasenia: " << driver->getPassword() << endl;
        std::cout << endl;
    }
    else {
        std::cout << "Indice de conductor no válido." << endl;
    }
}


//INICIAR SESIÓN
void LogIn() {

    int option;
    string email, password;
    bool correctPassword = false;
    bool accountFound = false;
    int optionForCustomers = 0, optionForEmployees = 0;
    int integer = -1; //ID: TICKET, ORDER, PRODUCT


    system("cls");
    std::cout << " +****************************************+ " << endl;
    std::cout << " [1] Mostrar datos de conductores generados" << endl;
    std::cout << " [2] Mostrar datos de customers generados" << endl;
    std::cout << " [3] Iniciar sesion con tu cuenta" << endl;
    std::cout << " +****************************************+ " << endl;
    std::cin >> option;

    switch (option) {
    case 1:
        showDriversListForLogin();
        std::cout << "Seleccione el numero de conductor del cual desea ver la informacion de inicio de sesion: ";
        int driverIndex;
        std::cin >> driverIndex;
        driverIndex--;  // Ajustar al índice base 0
        system("cls");
        showDriverLoginInfo(driverIndex);
        cout << "Presione cualquier tecla para continuar a iniciar sesion..." << endl;
        _getch(); 
        option = 3;
        break;
    case 2:
        showUsersListForLogin();
        cout << "Seleccione el numero de customer del cual desea ver la informacion de inicio de sesion: ";
        int userIndex;
        cin >> userIndex;
        userIndex--;  // Ajustar al índice base 0
        system("cls");
        showUsersLoginInfo(userIndex);
        _getch();
        option = 3;
        break;
    case 3:
        std::cout << endl;
    }
    std::cout << "Ingresa tu correo electronico: ";
    std::cin >> email;

    for (int i = 0; i < usersList->size(); i++) {
        if (email == usersList->at(i)->getEmail()) {
            accountFound = true;
            std::cout << "Cuenta encontrada!\n";
            std::cout << "Ingresa tu contrasenia: ";
            std::cin >> password;
            if (password == usersList->at(i)->getPassword()) {
                correctPassword = true;
                system("cls");
                std::cout << "Bienvenido de vuelta " << usersList->at(i)->getName() << endl << endl;
                if (usersList->at(i)->getUserType() == "Customer") {
                    optionForCustomers = showMenuForCustomers();
                    executeMenuForCustomers(optionForCustomers, i, integer);
                }
                if (usersList->at(i)->getUserType() == "Employee") {
                    for (int j = 0; j < driversList->size(); j++) {
                        if ((usersList->at(i)->getEmail() == driversList->at(j)->getEmail()) && (usersList->at(i)->getPassword() == driversList->at(j)->getPassword())) {
                            Employee* employee = dynamic_cast<Employee*>(usersList->at(i));
                            Driver* driver = dynamic_cast<Driver*>(employee);
                            optionForEmployees = showMenuForEmployees();
                            executeMenuForEmployees(optionForEmployees, j);
                        }
                    }
                }
                break;
            }
        }

    }

    if (!accountFound) std::cout << "No hay ninguna cuenta registrada con este correo electronico..." << endl;
}

int main() {
    leerDrivers("conductoresInicio.txt");
    Console::CursorVisible = false;
    int option = 1;
    string tipoConductor;
    vector<string>conductoresBuscados;
    
    applicationLogo();
    Console::SetCursorPosition(35, 0);
    barCharge();
    backGroundMenu();
    while (option != 8) {
        system("cls");
        option = showMenu();

        switch (option) {
        case 1:
            system("cls");
            registerUser();
            break;
        case 2:
            system("cls");
            LogIn();
            break;
        case 3:
            system("cls");
            if (usersList->size() == 0) { 
                std::cout << "Aun no se ha registro ningun usuario..." << endl; 
            }
            else {
                for (int i = 0; i < usersList->size(); i++) {
                    std::cout << " Usuario " << i + 1 << ": " << usersList->at(i)->getUserType() << endl;
                    std::cout << " Nombre: " << usersList->at(i)->getName() << endl << endl;

                }
            }
            _getch();
            break;

        case 4:
            int numDrivers;
            cout << "Ingrese el numero de conductores aleatorios a generar: ";
            cin >> numDrivers;
            generateDrivers(numDrivers);
            break;
        case 5:
            int numUser;
            cout << "Ingrese el numero de usuarios aleatorios a generar: ";
            cin >> numUser;
            generatePersonCompany(numUser);
            
            break;
        case 6:
            system("cls");
            if (driversList->empty()) {
                std::cout << "No ha registrado aun ningun conductor...\n";
                _getch();
            }
            else {
                std::cout << "Mostrar grafo de conductores de tipo: ";
                do {

                    std::cin >> tipoConductor;
                    if (tipoConductor != "moto" && tipoConductor != "auto" && tipoConductor != "camion") {
                        std::cout << "Ingres solo: auto, moto o camion\n";
                    }
                } while (tipoConductor != "moto" && tipoConductor != "auto" && tipoConductor != "camion");
                conductoresBuscados = grafoConductores.obtenerConductores(tipoConductor);
                std::cout << "Conductores asignados al tipo de vehiculo " << tipoConductor << ": \n";
                for (string conductor : conductoresBuscados) {
                    std::cout << " -  " << conductor << endl;
                }
                std::cout << endl;
                _getch();

            }
            break;
        case 7:
            settings();
            _getch();
            break;
        case 8:
            applicationExit();
            break;
        }
    }
    return 0;
}