#pragma once
#include "List.h"
#include "Product.h"
#include "Route.h"
#include "Shipping.h"
using namespace dby;
using namespace std;


class Order
{
private:
	List<Product*>* productsList = new List<Product*>;
	Route* route;
	int orderID;
	string customerName;


public:
	Order(List<Product*>* productsList, Route* route, int orderID, string customerName) : productsList(productsList),
		route(route), orderID(orderID), customerName(customerName) {}

	double getDistance() {
		return route->getDistance();
	}

	double getTotalAmount() {
		Shipping shipping;
		return shipping.calculateShippingPrice(getTotalWeight(), getDistance());
	}

	double getTotalWeight() {
		double totalWeight = 0.0;
		for (int i = 0; i < productsList->size(); i++) {
			if (productsList->at(i)->getOrderID() == orderID) {
				totalWeight += productsList->at(i)->getWeight();
			}
		}
		return totalWeight;
	}
	int getOrderID() {
		return orderID;
	}

	string getCustomerName() { return customerName; }

	void showProducts() {


		cout << "   Producto/s en 'ORDEN " << orderID + 1 << "': " << endl;
		for (int i = 0; i < productsList->size(); i++) {
			if (productsList->at(i)->getOrderID() == orderID && productsList->at(i)->getCustomerName() == customerName) {
				cout << "   " << "[]" << " " << productsList->at(i)->getNameProduct() << endl;
			}
		}
		cout << endl;

	}

	List<Product*>* getProductsList() {
		return productsList;
	}

	Route* getRoute() {
		return route;
	}

	~Order() {}
};