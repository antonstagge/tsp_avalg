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
map<pair<int, int>, bool> checked_edges_x;
map<pair<int, int>, bool> checked_edges_y;
vector<int> vertex_list;
vector<pair<int, int>> edge_list_x;
vector<pair<int, int>> edge_list_y;

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
bool get_checked_edge_x(int v1, int v2) {
    if(checked_edges_x.find(make_pair(v1, v2)) == checked_edges_x.end()) {
        return false;
    }
    return checked_edges_x[make_pair(v1, v2)];
}

/**
* Sets whether a given edge has been checked or not.
*/
void set_checked_edge_y(int v1, int v2, bool value) {
    checked_edges_y[make_pair(v1, v2)] = value;
    checked_edges_y[make_pair(v2, v1)] = value;
}

/**
* Gets whether a given edge has been checked or not.
*/
bool get_checked_edge_y(int v1, int v2) {
    if(checked_edges_y.find(make_pair(v1, v2)) == checked_edges_y.end()) {
        return false;
    }
    return checked_edges_y[make_pair(v1, v2)];
}

/**
* Sets whether a given edge has been checked or not.
*/
void set_checked_edge_x(int v1, int v2, bool value) {
    checked_edges_x[make_pair(v1, v2)] = value;
    checked_edges_x[make_pair(v2, v1)] = value;
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

void stepTwo();
void stepThree();
void stepFour();
void stepFive();
void stepSix();
void stepSeven();
void stepEight();
void stepNine();
void stepTen();
void stepEleven();
void stepTwelve();
void stepThirteen();

void stepTwo(int n, vector<int>& route) {
    int i = 1;

    bool tried_all = true;
    for(int j = 0; j < n; j++) {
        if(!checked_vertices[j]) {
            tried_all = false;
            break;
        }
    }
    if(tried_all) {
        return;
    }

    do {
        vertex_list[i] = random_int(n); //t1
    } while(checked_vertices[vertex_list[i]]);
    checked_vertices[vertex_list[i]] = true;

    stepThree(n, route, i);
}

void stepThree(int n, vector<int>& route, int i) {
    for(int j = 0; j < n; ++j) {
        if(route[j] == vertex_list[i]) {
            if(get_checked_edge_x(make_pair(vertex_list[i], route[(j-1) % n])) &&
                get_checked_edge_x(make_pair(vertex_list[i], route[(j+1) % n]))) {
                return;
            }
        }
    }

    do {
        for(int j = 0; j < n; ++j) {
            if(route[j] == vertex_list[i]) {
                int flip = random_int(2);
                vertex_list[i+1] = flip == 0 ? route[(j-1) % n] : route[(j+1) % n]; //t2
                break;
            }
        }
        edge_list_x[i] = make_pair(vertex_list[i], vertex_list[i+1]); //x1
    } while(checked_edges_x[edge_list_x[i]]);
    set_checked_edge_x(vertex_list[i], vertex_list[i+1], true);

    stepFour(n, route, i);
}

void stepFour(int n, vector<int>& route, int i) {
    int edge_node1;
    int edge_node2;
    for(int j = 0; j < n; ++j) {
        if(route[j] == vertex_list[i+1]) {
            edge_node1 = route[(j-1) % n];
            edge_node2 = route[(j+1) % n];
            break;
        }
    }

    do {
        do {
            vertex_list[i+2] = random_int(n);
        } while(vertex_list[i+2] == edge_node1 || vertex_list[i+2] == edge_node2);

        edge_list_y[i] = make_pair(vertex_list[i+1], vertex_list[i+2]);
    } while(checked_edges_y[edge_list_y[i]]);
    set_checked_edge_y(vertex_list[i+1], vertex_list[i+2], true);

    stepFive(n, route, i);
}

void stepFive(int n, vector<int>& route, int i) {
    stepSix(n, route, i+1);
}

void stepSix(int n, vector<int>& route, int i) {
    for(int j = 0; j < n; ++j) {
        if(route[j] == vertex_list[2*i-1]) {
            if(get_checked_edge_x(make_pair(vertex_list[2*i-1], route[(j-1) % n])) &&
                get_checked_edge_x(make_pair(vertex_list[2*i-1], route[(j+1) % n]))) {
                return;
            }
        }
    }

    while(true) {
        do {
            for(int j = 0; j < n; ++j) {
                if(route[j] == vertex_list[2*i-1]) {
                    int flip = random_int(2);
                    vertex_list[2*i] = flip == 0 ? route[(j-1) % n] : route[(j+1) % n]; //t2i
                    break;
                }
            }
            edge_list_x[i] = make_pair(vertex_list[2*i-1], vertex_list[2*i]); //x1
        } while(checked_edges_x[edge_list_x[i]]);



    }

    stepFour(n, route, i);
}

/**
* Uses Lin-Kernighan local optimization to find a good TSP route.
*/
vector<int> lin_kernighan(int n) {
    //Step 1
    vector<int> route = random_route(n);

    //Make sure all collections used for storing info are cleared
    checked_edges_x.clear();
    checked_edges_y.clear();
    for(int i = 0; i < n; ++i) {
        checked_vertices[i] = false;
    }

    //Algorithm is one indexed
    checked_edges_x.push_back(-1);
    checked_edges_y.push_back(-1);
    vertex_list.push_back(-1);
    edge_list_x.push_back(make_pair(-1, -1));
    edge_list_y.push_back(make_pair(-1, -1));

    //Step 2
    stepTwo(n, route);
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
    vector<int> route = lin_kernighan(n);

    for (int i = 0; i < n; ++i) {
        cout << route[i] << endl;
    }
}
