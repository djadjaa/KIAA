#include <bits/stdc++.h>
using namespace std;

struct Grana {
    int to;
    int kuce;   // broj kuća na ulici
    bool korišcena;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<Grana>> graf(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t; // t = broj kuća između u i v
        graf[u].push_back({v, t, false});
        graf[v].push_back({u, t, false});
    }

    int start;
    cin >> start;

    long long zarada = 0;
    stack<int> st;
    vector<int> put;

    st.push(start);

    while (!st.empty()) {
        int cvor = st.top();
        bool found = false;

        // tražimo neiskorišćenu granu
        for (auto &g : graf[cvor]) {
            if (!g.korišcena) {
                g.korišcena = true;
                // obeležavamo i suprotnu granu
                for (auto &h : graf[g.to]) {
                    if (h.to == cvor && !h.korišcena) {
                        h.korišcena = true;
                        break;
                    }
                }
                zarada += 1LL * g.kuce * k;
                st.push(g.to);
                found = true;
                break;
            }
        }

        if (!found) {
            st.pop();
            put.push_back(cvor);
        }
    }

    // Ispis puta
    for (size_t i = 0; i < put.size(); i++) {
        cout << put[i] << (i + 1 < put.size() ? " " : "\n");
    }

    cout << zarada << "\n";

    return 0;
}
