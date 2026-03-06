#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<pair<int,int>>> susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void dodajGranu(int u,int v,int visina){
        susedi[u].push_back({v,visina});
        susedi[v].push_back({u,-visina});
    }

    void dfs(int visinatla){
        vector<int> visine(V, INT_MAX);
        vector<int> posecen(V,false);
        stack<int> s;
        s.push(0);
        visine[0] = visinatla;
        posecen[0]=true;

        while(!s.empty()){
            int tmp = s.top();
            s.pop();

            for(auto &[sused,susedivisina] : susedi[tmp]){
                if(!posecen[sused]){
                    /*
                    Ako znamo visinu jedne dvorane i razliku do suseda, možemo izračunati visinu suseda:
                    visina[sused]=visina[trenutna]+razlika

                    0 → 278
                    1 → 278 - 20 = 258
                    2 → 278 - 10 = 268
                    3 → 258 - 5 = 253
                    4 → 258 + 10 = 268
                    5 → 268 - 33 = 235
                    6 → 268 + 7 = 275
                    */
                    visine[sused]=visine[tmp]+susedivisina;
                    posecen[sused]=true;
                    s.push(sused);
                }
            }
        }

        cout << *min_element(visine.begin(), visine.end()) << endl;
    }
};

int main(){

    int visinatla,n;
    cin >> visinatla >> n;
    Graph *G = new Graph(n);
    for(int i=0; i<n-1; i++){
        int u,v,visina;
        cin >> u >> v >> visina;
        G->dodajGranu(u,v,visina);
    }
    G->dfs(visinatla);
    return 0;
}