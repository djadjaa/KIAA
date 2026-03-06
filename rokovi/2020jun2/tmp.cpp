#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id;
    int parent;
    int child_index;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n % 2 != 0) {
        // ako je broj čvorova neparan, nije moguće ukloniti grane da svi delovi budu parni
        cout << 0 << "\n";
        return 0;
    }

    vector<vector<int>> tree(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    vector<int> subtree_size(n + 1, 1); // svaki čvor najmanje 1
    int result = 0;

    stack<Node> st;
    st.push({1, 0, 0}); // koren 1

    while (!st.empty()) {
        Node &top = st.top();
        if (top.child_index < (int)tree[top.id].size()) {
            int child = tree[top.id][top.child_index++];
            if (child == top.parent) continue;
            st.push({child, top.id, 0});
        } else {
            // svi child obrađeni, vraćamo se roditelju
            int parent = top.parent;
            int sz = subtree_size[top.id];
            if (parent != 0) {
                if (sz % 2 == 0) {
                    result++; // možemo ukloniti granu do roditelja
                } else {
                    subtree_size[parent] += sz; // dodajemo veličinu podstabla roditelju
                }
            }
            st.pop();
        }
    }

    cout << result << "\n";

    return 0;
}
