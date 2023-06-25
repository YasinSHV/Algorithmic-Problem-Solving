#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <ctime>

using namespace std;

void dfs(int city, vector<vector<int>>& graph, vector<bool>& visited, stack<int>& order) {
    visited[city] = true;

    for (int neighbor : graph[city]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, order);
        }
    }

    order.push(city);
}

vector<int> findCityOrder(int n, vector<vector<int>>& matrix) {
    vector<vector<int>> graph(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1 && matrix[j][i] == 0) {
                graph[i].push_back(j);
            }
        }
    }

    vector<bool> visited(n, false);
    stack<int> order;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, graph, visited, order);
        }
    }

    vector<int> cityOrder;

    while (!order.empty()) {
        cityOrder.push_back(order.top() + 1); 
        order.pop();
    }

    return cityOrder;
}

vector<vector<int>> generateMatrixTestCase(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 1);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int val = dis(gen);
            matrix[i][j] = val;
            matrix[j][i] = 1 - val; 
        }
    }

    return matrix;
}

void printMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the size of the matrix: ";
    cin >> n;

    char choice;
    cout << "Do you want to generate a random matrix? (y/n): ";
    cin >> choice;

    vector<vector<int>> matrix;

    if (choice == 'y' || choice == 'Y') {
        matrix = generateMatrixTestCase(n);
        cout << "Generated matrix:" << endl;
        printMatrix(matrix);
    }
    else {
        cout << "Enter the matrix values (0 or 1):" << endl;
        matrix.resize(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> matrix[i][j];
            }
        }
    }

    vector<int> order = findCityOrder(n, matrix);

    if (order.size() == n) {
        cout << "The order of cities is:" << endl;
        for (int city : order) {
            cout << city << endl;
        }
    }
    else {
        cout << "There is no valid path of length " << n << "." << endl;
    }

    cout << "Do you want to end the program? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        return 0;
    }
    else {
        matrix.clear();
        main();
    }
}
