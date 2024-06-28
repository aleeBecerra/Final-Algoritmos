#pragma once
#include <iostream>
using namespace std;

class Product {
private:
	string nameProduct;
	float width, height, weight, value;
	int id;
	int orderID;
	string customerName;

public:
	Product(string nameP, float width, float height, float weight, float value, int id, int orderID, string customerName) : nameProduct(nameP), width(width), height(height), weight(weight),
		value(value), id(id), orderID(orderID), customerName(customerName) {}
	~Product() {}

	// Setters and Getters
	void setNameProduct(string _nameProduct) { this->nameProduct = _nameProduct; }
	string getNameProduct() { return nameProduct; }

	void setID(int _id) { this->id = _id; }
	int getId() { return id; }

	void setWidth(float _width) { this->width = _width; }
	float getWidth() { return width; }

	void setHeight(float _height) { this->height = _height; }
	float getHeight() { return height; }

	void setWeight(float _weight) { this->weight = _weight; }
	float getWeight() { return weight; }

	void setValue(float _value) { this->value = _value; }
	float getValue() { return value; }

	void setorderID(int _orderID) { this->orderID = _orderID; }
	int getOrderID() { return orderID; }

	string getCustomerName() { return customerName; }

	// Service Metods
	void showProductInfo() {
		cout << "== Detalle del producto ==" << endl;
		cout << "ID del producto: " << id << endl;
		cout << "Propietario del producto: " << customerName << endl;
		cout << "Nombre del producto: " << nameProduct << endl;
		cout << "Ancho del producto: " << width << endl;
		cout << "Altura del producto: " << height << endl;
		cout << "Peso del producto: " << weight << endl;
		cout << "Valor del producto: " << value << endl;
		cout << endl;
	}
};
