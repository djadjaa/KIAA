#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Funkcija za proveru da li je broj složen
bool jeSlozen(int x) {
    if (x <= 1) return false;
    for (int i = 2; i <= sqrt(x); ++i)
        if (x % i == 0)
            return true;
    return false;
}

// Segmentno stablo
class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(const vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 1, 0, n - 1);
    }

    void build(const vector<int>& data, int node, int l, int r) {
        if (l == r) {
            tree[node] = data[l];
        } else {
            int mid = (l + r) / 2;
            build(data, 2 * node, l, mid);
            build(data, 2 * node + 1, mid + 1, r);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    int query(int a, int b) {
        return query(1, 0, n - 1, a, b);
    }

private:
    int query(int node, int l, int r, int a, int b) {
        if (b < l || a > r) return 0;
        if (a <= l && r <= b) return tree[node];
        int mid = (l + r) / 2;
        return query(2 * node, l, mid, a, b) +
               query(2 * node + 1, mid + 1, r, a, b);
    }
};

int main() {
    // Primer niza A
    vector<int> A = {2, 4, 6, 7, 9, 11, 12, 13};

    // Preprocesiramo niz u binarni niz: 1 ako je broj složen, 0 inače
    vector<int> slozenost;
    for (int x : A) {
        slozenost.push_back(jeSlozen(x) ? 1 : 0);
    }

    // Pravimo segmentno stablo
    SegmentTree st(slozenost);

    // Primer upita: broj složenih brojeva u intervalu [2, 6]
    int a = 2, b = 6;
    cout << "Broj složenih brojeva u intervalu [" << a << ", " << b << "] je: ";
    cout << st.query(a, b) << endl;

    return 0;
}
