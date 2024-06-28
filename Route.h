#pragma once
#include <iostream>
using namespace std;

class Route {
private:
	string origin, destination;
	double distance;

public:
	Route(string origin, string destination, double distance) : origin(origin), destination(destination),
		distance(distance) {}

	// Setter and Getter
	void setOrigin(string _origin) { origin = _origin; }
	string getOrigin() { return origin; }

	void setDestination(string _destination) { destination = _destination; }
	string getDestination() { return destination; }

	void setDistance(double _distance) { distance = _distance; }
	double getDistance() { return distance; }

	~Route() {}
};