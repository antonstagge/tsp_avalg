#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

map<int, pair<double, double>> vertices;

int random_int(int n) {
    return rand() % n;
}

int calc_dist(pair<double, double> v1, pair<double, double> v2) {
    return round(sqrt(pow(v1.first - v2.first, 2) + pow(v1.second - v2.second, 2)));
}

vector<int> random_route(int n) {
    vector<int> route(n);
    for (int i = 0; i < n; ++i) {
        route[i] = i;
    }
    random_shuffle(route.begin(), route.end(), random_int);
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
    }
    vector<int> route = random_route(n);
    for (int i = 0; i < n; ++i) {
        cout << route[i] << endl;
    }
}
