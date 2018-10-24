#include <iostream>
#include <map>
using namespace std;

map<int, pair<double, double>> vertices;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        vertices[i] = make_pair(x, y);
    }

}
