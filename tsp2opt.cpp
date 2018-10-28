#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

map<int, pair<double, double>> vertices;

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
int calculate_tour_distance(const vector<int>& route) {
    int distance = 0;
    for(int i = 0; i < route.size()-1; ++i) {
        distance += calculate_distance(route[i], route[i+1]);
    }
    return distance;
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

vector<int> two_opt_swap(const vector<int>& route, int i, int k) {
    vector<int> start(route.begin(), route.begin() + i);
    vector<int> flip(route.begin() + i, route.begin() + k + 1);
    vector<int> end(route.begin() + k + 1, route.end());
    reverse(flip.begin(), flip.end());
    start.insert(start.end(), flip.begin(), flip.end());
    start.insert(start.end(), end.begin(), end.end());
    return start;
}

void two_opt(int n, vector<int>& route) {
    int best_distance = calculate_tour_distance(route);
    for(int i = 0; i < n-1; ++i) {
        for(int k = i+2; k < n; ++k) {
            vector<int> new_route = two_opt_swap(route, i, k);
            int new_distance = calculate_tour_distance(new_route);
            if(new_distance < best_distance) {
                route = move(new_route);
                return;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        vertices[i] = make_pair(x, y);
    }
    vector<int> route = random_route(n);
    for(int i = 0; i < 1000; i++) {
        two_opt(n, route);
    }

    for (int i = 0; i < n; ++i) {
        cout << route[i] << endl;
    }
}
