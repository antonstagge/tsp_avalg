#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

map<int, pair<double, double>> vertices;
map<int, bool> checked_vertices;
map<pair<int, int>, bool> checked_edges;

/**
* Returns a random int.
*/
int random_int(int n) {
    return rand() % n;
}

/**
* Calculates the distance between two coordinate points.
*/
int calculate_distance(pair<double, double> v1, pair<double, double> v2) {
    return round(sqrt(pow(v1.first - v2.first, 2) + pow(v1.second - v2.second, 2)));
}

/**
* Calculates the distance between two vertices.
*/
int calculate_distance(int v1, int v2) {
    return calculate_distance(vertices[v1], vertices[v2]);
}

/**
* Calculates the distance of a given route.
*/
int calculate_tour_distance(vector<int> route) {
    int distance = 0;
    for(int i = 0; i < route.size()-1; ++i) {
        distance += calculate_distance(i, i+1);
    }
    return distance;
}

/**
* Gets whether a given edge has been checked or not.
*/
bool get_checked_edge(int v1, int v2) {
    if(checked_edges.find(make_pair(v1, v2)) == checked_edges.end()) {
        return false;
    }
    return checked_edges[make_pair(v1, v2)];
}

/**
* Sets whether a given edge has been checked or not.
*/
void set_checked_edge(int v1, int v2, bool value) {
    checked_edges[make_pair(v1, v2)] = value;
    checked_edges[make_pair(v2, v1)] = value;
}

/**
* Returns a random route given the number of vertices
*/
vector<int> random_route(int n) {
    vector<int> route(n);
    for (int i = 0; i < n; ++i) {
        route[i] = i;
    }
    random_shuffle(route.begin(), route.end(), random_int);
    return route;
}

/**
* Uses Lin-Kernighan local optimization to find a good TSP route.
*/
vector<int> lin_kernighan(vector<int> route) {
    return route;
}

int main() {
    srand(time(NULL));
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        vertices[i] = make_pair(x, y);
        checked_vertices[i] = false;
    }
    vector<int> route = random_route(n);

    for(int i = 0; i < n; ++i) {
        route = lin_kernighan(route);
    }

    for (int i = 0; i < n; ++i) {
        cout << route[i] << endl;
    }
}
