#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
class Grafos {
private:
    unordered_map<string, vector<string>> adyacencia; // Lista de adyacencia usando un unordered_map

public:
    // Constructor
    Grafos() {}

    // A�adir un conductor con un tipo de veh�culo
    void agregarConductor(string conductor, string tipoVehiculo) {
        adyacencia[tipoVehiculo].push_back(conductor);
    }

    // Mostrar el grafo
    void mostrarGrafo() {
        for (auto& pair : adyacencia) {
            cout << "Veh�culo " << pair.first << " tiene conductores: ";
            for (string conductor : pair.second) {
                cout << conductor << " ";
            }
            cout << endl;
        }
    }

    // Obtener conductores de un tipo de veh�culo espec�fico
    vector<string> obtenerConductores(string tipoVehiculo) {
        if (adyacencia.find(tipoVehiculo) != adyacencia.end()) {
            return adyacencia[tipoVehiculo];
        }
        else {
            return {};
        }
    }
};
