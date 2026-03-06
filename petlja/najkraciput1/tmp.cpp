#include <bits/stdc++.h>
using namespace std;

struct comparator {
    bool operator()(const pair<double, int> &p1, const pair<double, int> &p2) {
        return p1.first > p2.first;
    }
};

class Graph {
private:
    int V;
    vector<vector<pair<int, double>>> susedi;
    vector<bool> pronadjen;
    vector<double> rastojanje;
    vector<int> parent; // 🔹 za rekonstrukciju puta

public:
    Graph(int V) {
        this->V = V;
        rastojanje.assign(V, numeric_limits<double>::infinity());
        pronadjen.assign(V, false);
        parent.assign(V, -1);
        susedi.resize(V);
    }

    void dodajGranu(int u, int v, double w) {
        susedi[u].push_back({v, w});
        susedi[v].push_back({u, w});
    }

    double Dajkstra(int start, int end) {
        priority_queue<pair<double, int>, vector<pair<double, int>>, comparator> pq;

        rastojanje[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (pronadjen[u]) continue;
            pronadjen[u] = true;

            if (u == end) return d; // najkraci put pronadjen

            for (auto &[v, w] : susedi[u]) {
                double nd = d + w;
                if (nd < rastojanje[v]) {
                    rastojanje[v] = nd;
                    parent[v] = u; // 🔹 pamtimo prethodnika
                    pq.push({nd, v});
                }
            }
        }
        return -1;
    }

    void ispisi(int start, int end) {
        double res = Dajkstra(start, end);
        if (res == -1) {
            cout << "ne\n";
        } else {
            cout << fixed << setprecision(5) << res << "\n";
            
            /* 🔹 Rekonstrukcija puta
            vector<int> path;
            for (int v = end; v != -1; v = parent[v])
                path.push_back(v);
            reverse(path.begin(), path.end());

            for (int v : path)
                cout << v << " ";
            cout << "\n";*/
            stack<int> st;
            int v = end;
            while (v != -1) {
                st.push(v);
                v = parent[v];
            }

            while (!st.empty()) {
                cout << st.top() << " ";
                st.pop();
            }
            cout << "\n";
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Graph G(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        G.dodajGranu(u, v, w);
    }

    int start, end;
    cin >> start >> end;
    G.ispisi(start, end);

    return 0;
}
