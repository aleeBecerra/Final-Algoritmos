#pragma once

#include <vector>
#include <list>
#include <iostream>
#include "Ticket.h"  

using namespace std;

class HashTable {
private:
    vector<list<Ticket*>> _hashTable;
    size_t _size;
    size_t _capacity;

public:
    HashTable(size_t capacity) : _capacity(capacity), _size(0) {
        _hashTable.resize(capacity);
    }

    void insert(Ticket* ticket) {
        resize();

        int index = _hashFunction(ticket->getOrderID(), ticket->getUsername());
        _hashTable[index].push_back(ticket);

        _size++;
    }

    void display() {
        for (size_t i = 0; i < _hashTable.size(); ++i) {
            cout << "Key: " << i << " | ";
            for (auto& order : _hashTable[i]) {
                cout << "OrderID: " << order->getOrderID() << " ";
            }
            cout << endl;
        }
    }

    Ticket* search(int ticketID) {
        for (size_t i = 0; i < _hashTable.size(); ++i) {
            for (auto& ticket : _hashTable[i]) {
                if (ticket->getOrderID() == ticketID) {
                    return ticket;
                }
            }
        }
        return nullptr;
    }

    void erase(int orderID, const string& customerName) {
        int index = _hashFunction(orderID, customerName);
        for (auto it = _hashTable[index].begin(); it != _hashTable[index].end(); ++it) {
            if ((*it)->getOrderID() == orderID && (*it)->getUsername() == customerName) {
                delete* it;
                _hashTable[index].erase(it);
                _size--;
                break;
            }
        }
    }

private:
    int _hashFunction(int orderID, const string& customerName) {
        return (orderID % _capacity);
    }

    void resize() {

    }
};