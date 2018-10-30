#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

#ifndef ITERATIONS
#define ITERATIONS 1000
#endif

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
int get_distance(int v1, int v2) {
    return distances[v1][v2];
}

/**
* Returns a greedy route given the number of vertices
*/
vector<pair<int, int>> greedy_route(int n) {
    vector<int> node_route(n);
    bool used[n];
    for(int i = 0; i < n; ++i) {
        used[i] = false;
    }
    used[0] = true;
    node_route[0] = 0;
    for(int i = 1; i < n; ++i) {
        int best = -1;
        for(int j = 1; j < n; ++j) {
            if(!used[j] && (best == -1 || (get_distance(node_route[i-1], j) < get_distance(node_route[i-1], best)))) {
                best = j;
            }
        }
        node_route[i] = best;
        used[best] = true;
    }
    vector<pair<int, int>> route(n);
    for(int i = 0; i < n-1; ++i) {
        route[i] = make_pair(node_route[i], node_route[i+1]);
    }
    route[n-1] = make_pair(node_route[n-1], node_route[0]);
    return route;
}

void two_opt(int n, vector<pair<int, int>>& route) {
    for(int i = 0; i < n-2; ++i) {
        for(int k = i+2; k < n; ++k) {
            int prev_first_dist = get_distance(route[i].first, route[i].second);
            int prev_second_dist = get_distance(route[k].first, route[k].second);
            int new_first_dist = get_distance(route[i].first, route[k].first);
            int new_second_dist = get_distance(route[i].second, route[k].second);
            if(new_first_dist + new_second_dist < prev_first_dist + prev_second_dist) {
                int temp = route[i].second;
                route[i].second = route[k].first;
                route[k].first = temp;
                reverse(route.begin() + i+1, route.begin() + k);
                for(int j = i+1; j < k; ++j) {
                    int t = route[j].first;
                    route[j].first = route[j].second;
                    route[j].second = t;
                }
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

    vector<pair<int, int>> route = greedy_route(n);
    for(int i = 0; i < ITERATIONS; ++i) {
        two_opt(n, route);
    }

    for (int i = 0; i < n; ++i) {
        cout << route[i].first << endl;
    }
}
