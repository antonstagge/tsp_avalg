#include <iostream>
#include <map>
#include <cmath>
#include <climits>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <random>
using namespace std;

#ifndef ITERATIONS
#define ITERATIONS 205000
#endif

map<int, pair<double, double>> vertices;
vector<vector<int>> constant_distances;
vector<vector<pair<int, int>>> distances;

/**
* Returns a random int.
*/
int random_int(int n) {
    return rand() % n;
}

double random_double() {
    return (double)random_int(999998) / 999999;
}

/**
* Calculates the distance between two coordinate points.
*/
int calculate_distance(pair<double, double> v1, pair<double, double> v2) {
    return round(sqrt(pow(v1.first - v2.first, 2) + pow(v1.second - v2.second, 2)));
}

/**
* Calculates the distance of a given route.
*/
int calculate_tour_distance(const vector<pair<int,int>>& route) {
    int distance = 0;
    for(int i = 0; i < route.size(); ++i) {
        distance += constant_distances[route[i].first][route[i].second];
    }
    return distance;
}

/**
 * Get the nearest neighbour to each node to build up a route.
 */
vector<pair<int,int>> greedy_route(int n) {
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
            if(!used[j] && (best == -1 || (constant_distances[node_route[i-1]][j] < constant_distances[node_route[i-1]][best]))) {
                best = j;
            }
        }
        node_route[i] = best;
        used[best] = true;
    }

    vector<pair<int,int>> route(n);
    for (int i = 0; i < n-1; ++i) {
        route[i] = make_pair(node_route[i], node_route[i+1]);
    }
    route[n-1] = make_pair(node_route[n-1], node_route[0]);
    return route;
}

void reverse(vector<pair<int,int>>& route, int i, int k) {
    // make 1-4 and 2-3
    int temp = route[i].second;
    route[i].second = route[k].first;
    route[k].first = temp;
    // flip order
    reverse(route.begin() + i + 1, route.begin() + k);
    // flip internally
    for (int j = i+1; j < k; ++j) {
        temp = route[j].first;
        route[j].first = route[j].second;
        route[j].second = temp;
    }
}

void calc_rev_route(vector<pair<int,int>>& route, vector<pair<int,int>>& rev_route) {
    for (int i = 0; i < route.size(); ++i) {
        int from = route[i].first;
        int to = route[i].second;

        rev_route[from].first = i;
        rev_route[to].second = i;
    }
}

int two_opt(int n, vector<pair<int,int>>& route, vector<pair<int,int>>& rev_route) {
    for(int i = 0; i < n; ++i) {
        int t1 = route[i].first;
        int t2 = route[i].second;
        int d_12 = constant_distances[t1][t2];
        for(auto& t3_pair : distances[t2]) {
            int t3 = t3_pair.first;
            int d_23 = t3_pair.second;

            if (d_23 >= d_12) break;
            if (t3 == route[(i+1) % n].second || t3 == t1) continue;
            
            int k = rev_route[t3].second;
            int t4 = route[k].first;
            int d_34 = constant_distances[t3][t4];
            int d_14 = constant_distances[t1][t4];
            if (d_14 + d_23 >= d_34 + d_12) {
                continue;
            }
            reverse(route, min(i,k), max(i,k));
            calc_rev_route(route, rev_route);
            return 0;
        }
    }
    return 1;
}

bool sortFunction (pair<int,int> x,pair<int,int> y) { 
    return (x.second < y.second);
}

void random_change(vector<pair<int,int>>& route, int n) {
    int done = 0;
    while (done != 2 && n >= 3) {
        int edge_1 = random_int(n);
        int edge_2 = random_int(n);
        if (edge_1 == edge_2) continue;
        int t1 = route[edge_1].first;
        int t2 = route[edge_1].second;
        int t4 = route[edge_2].first;
        int t3 = route[edge_2].second;
        if (t3 == route[(edge_1+1) % n].second || t3 == t1) continue;
        reverse(route, min(edge_1, edge_2), max(edge_1, edge_2));
        done += 1;
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
        constant_distances.push_back(vector<int>(n, -1));
        distances.push_back(vector<pair<int,int>>());
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if (i != j) {
                int dist = calculate_distance(vertices[i], vertices[j]);
                constant_distances[i][j] = dist;
                distances[i].push_back(make_pair(j, dist));
            } else {
                constant_distances[i][j] = 0;
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        sort(distances[i].begin(), distances[i].end(), sortFunction);
    }

    vector<pair<int,int>> route = greedy_route(n);
    vector<pair<int,int>> rev_route = vector<pair<int,int>>(n, make_pair(-1, -1));
    calc_rev_route(route, rev_route);

    int unchanged = 0;
    int minima = INT_MAX;
    vector<pair<int,int>> mini_route = route;

    for(int i = 0; i < ITERATIONS; ++i) {
        unchanged += two_opt(n, route, rev_route);

        if (unchanged == 1) {
            unchanged = 0;
            int total_cost = calculate_tour_distance(route);
            if (total_cost < minima) {
                minima = total_cost;
                mini_route = route;
            } else {
                route = mini_route;
            }
            random_change(route, n);
            calc_rev_route(route, rev_route);
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << mini_route[i].first << endl;
    }
}
