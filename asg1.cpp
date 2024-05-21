#include <iostream>
#include <vector>
#include <functional>
#include <math.h>
#include <algorithm>
using namespace std;

const double EPS = 1e-10;

struct Point {
    double x, y;
    bool operator==(const Point& other) const {
        return abs(x - other.x) < EPS && abs(y - other.y) < EPS;
    }
};

struct Triangle {
    int i, j, k;
};

double cross_product(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

double area(const Point& a, const Point& b, const Point& c) {
	Point p, q;
	p.x = b.x - a.x;
	p.y = b.y - a.y;
	q.x = c.x - a.x;
	q.y = c.y - a.y;
    return cross_product(p,q) / 2.0;
}

vector<Triangle> triangulate_brute_force(const vector<Point>& vertices) {
    int n = vertices.size();
    vector<vector<vector<double>>> memo(n, vector<vector<double>>(n, vector<double>(n, -1.0)));
    function<double(int, int, int)> dp = [&](int i, int j, int k) -> double {
        if (memo[i][j][k] != -1.0) return memo[i][j][k];
        double res = numeric_limits<double>::max();
        for (int l = 0; l < n; l++) {
            if (l != i && l != j && l != k && area(vertices[i], vertices[j], vertices[l]) > 0 &&
                    area(vertices[j], vertices[k], vertices[l]) > 0 && area(vertices[k], vertices[i], vertices[l]) > 0) {
                double curr = dp(i, j, l) + dp(j, k, l) + dp(k, i, l);
                if (curr < res) res = curr;
            }
        }
        if (res == numeric_limits<double>::max()) return memo[i][j][k] = 0.0;
        return memo[i][j][k] = res;
    };
    dp(0, n - 2, n - 1);
    vector<Triangle> triangles;
    for (int i = 1; i < n - 1; i++) {
        if (area(vertices[0], vertices[i], vertices[i + 1]) > 0) {
            triangles.push_back({0, i, i + 1});
        } else {
            triangles.push_back({0, i + 1, i});
        }
    }
    return triangles;
}

vector<Triangle> triangulate_dynamic_programming(const vector<Point>& vertices) {
    int n = vertices.size();
    vector<vector<double>> memo(n, vector<double>(n, -1.0));
    for (int i = 0; i < n; i++) memo[i][(i + 1) % n] = 0.0;
    for (int len = 2; len < n; len++) {
        for (int i = 0; i < n - len; i++) {
            int j = i + len;
            for (int k = i + 1; k < j; k++) {
                double curr = memo[i][k] + memo[k][j] + area(vertices[i], vertices[j], vertices[k]);
                if (memo[i][j] == -1.0 || curr < memo[i][j]) {
                    memo[i][j] = curr;
                }
            }
        }
    }
    vector<Triangle> triangles;
    for (int i = 1; i < n - 1; i++){
		if (area(vertices[0], vertices[i], vertices[i + 1]) > 0) {
        triangles.push_back({0, i, i + 1});
		}
		else {
        triangles.push_back({0, i + 1, i});
		}
    }
    return triangles;
}

vector<Triangle> triangulate_greedy(const vector<Point>& vertices) {
    int n = vertices.size();
    vector<pair<double, pair<int, int>>> edges;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (i == 0 && j == n - 1) continue;
            double curr = 0;
            bool intersect = false;
            for (int k = 0; k < n; k++) {
                if (k == i || k == j || k == i + 1 || k == j - 1) continue;
                double curr_area = area(vertices[i], vertices[j], vertices[k]);
                if (curr_area < 0) {
                    curr -= curr_area;
                } else if (curr_area > 0) {
                    intersect = true;
                    break;
                }
            }
            if (!intersect) edges.push_back({curr, {i, j}});
        }
    }
    sort(edges.begin(), edges.end());
    vector<Triangle> triangles;
    vector<bool> used(n, false);
    used[0] = used[n - 1] = true;
    for (auto edge : edges) {
        int i = edge.second.first, j = edge.second.second;
        if (used[i] || used[j]) continue;
        triangles.push_back({0, i, j});
        used[i] = used[j] = true;}
    for (int i = 1; i < n - 1; i++) {
        if (!used[i]) {
            if (area(vertices[0], vertices[i], vertices[i + 1]) > 0) {
                triangles.push_back({0, i, i + 1});
            } else {
                triangles.push_back({0, i + 1, i});
            }
        }
    }
    return triangles;
}

int main() {
    // Generate dataset of convex polygons with increasing number of arbitrary vertices
    vector<vector<Point>> datasets;
    for (int n = 3; n <= 20; n++) {
        vector<Point> vertices;
        for (int i = 0; i < n; i++) {
            double angle = i * 2.0 * M_PI / n;
            vertices.push_back({cos(angle), sin(angle)});
        }
        datasets.push_back(vertices);
    }
    // Brute force method
    cout << "Brute force method:" << endl;
    for (int i = 0; i < datasets.size(); i++) {
        auto vertices = datasets[i];
        auto triangles = triangulate_brute_force(vertices);
        double sum = 0.0;
        for (auto triangle : triangles) {
            sum += area(vertices[triangle.i], vertices[triangle.j], vertices[triangle.k]);
        }
        cout << "n = " << vertices.size() << ", total area = " << sum << endl;
    }
    // Dynamic programming
    cout << "Dynamic programming:" << endl;
    for (int i = 0; i < datasets.size(); i++) {
        auto vertices = datasets[i];
        auto triangles = triangulate_dynamic_programming(vertices);
        double sum = 0.0;
        for (auto triangle : triangles) {
		        sum += area(vertices[triangle.i], vertices[triangle.j], vertices[triangle.k]);
        }
        cout << "n = " << vertices.size() << ", total area = " << sum << endl;
    }
    // Greedy method
    cout << "Greedy method:" << endl;
    for (int i = 0; i < datasets.size(); i++) {
        auto vertices = datasets[i];
        auto triangles = triangulate_greedy(vertices);
        double sum = 0.0;
        for (auto triangle : triangles) {
            sum += area(vertices[triangle.i], vertices[triangle.j], vertices[triangle.k]);
        }
        cout << "n = " << vertices.size() << ", total area = " << sum << endl;
    }
    return 0;
}

