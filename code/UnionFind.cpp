#include <iostream>
#include <vector>

using namespace std;

int find(vector<int> &C, int x) {
    return (C[x] == x) ? x : C[x] = find(C, C[x]);
}
void merge(vector<int> &C, int x, int y) {
    C[find(C, x)] = find(C, y);
}

int main() {
    return 0;
}