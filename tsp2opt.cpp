#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

map<int, pair<double, double>> vertices;
vector<vector<int>> distances;

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
    return distances[v1][v2];
}

/**
* Calculates the distance of a given route.
*/
int calculate_tour_distance(const vector<int>& route) {
    int distance = 0;
    for(int i = 0; i < route.size()-1; ++i) {
        distance += calculate_distance(route[i], route[i+1]);
    }
    distance += calculate_distance(route[route.size()-1], route[0]);
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

vector<int> greedy_route(int n) {
    vector<int> route(n);
    bool used[n];
    for(int i = 0; i < n; ++i) {
        used[i] = false;
    }
    used[0] = true;
    route[0] = 0;
    for(int i = 1; i < n; ++i) {
        int best = -1;
        for(int j = 1; j < n; ++j) {
            if(!used[j] && (best == -1 || (calculate_distance(route[i-1], j) < calculate_distance(route[i-1], best)))) {
                best = j;
            }
        }
        route[i] = best;
        used[best] = true;
    }
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
    for(int i = 0; i < n-2; ++i) {
        for(int k = i+2; k < n; ++k) {
            int prev_first_dist = calculate_distance(route[(i-1) % n], route[i]);
            int prev_second_dist = calculate_distance(route[k], route[(k+1) % n]);
            int new_first_dist = calculate_distance(route[(i-1) % n], route[k]);
            int new_second_dist = calculate_distance(route[i], route[(k+1) % n]);
            if(new_first_dist + new_second_dist < prev_first_dist + prev_second_dist) {
                reverse(route.begin() + i, route.begin() + k + 1);
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
        distances.push_back(vector<int>(n, -1));
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            distances[i][j] = calculate_distance(vertices[i], vertices[j]);
        }
    }

    vector<int> route = greedy_route(n);
    for(int i = 0; i < 1000; ++i) {
        two_opt(n, route);
    }

    for (int i = 0; i < n; ++i) {
        cout << route[i] << endl;
    }
}
