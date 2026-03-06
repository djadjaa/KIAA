#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<vector<int>> susediRev;
    vector<bool> posecen;
    vector<int> komponente;
    int komponenteId;
    stack<int> inDeg;
    /*
    void dfsInDeg(int u){
        stack<int> s;
        s.push(u);
        posecen[u] = true;
        while(!s.empty()){
            int tmp = s.top();
            s.pop();

            inDeg.push(tmp);

            for(int sused : susedi[tmp]){
                if(posecen[sused])
                    continue;
                posecen[sused] = true;
                s.push(sused);
            }
        }
    }*/

    void dfsInDeg(int u) {
        posecen[u] = true;
        for (int v : susedi[u]) {
            if (!posecen[v])
                dfsInDeg(v);
        }
        inDeg.push(u); // završno vreme
    }

    void dfsKomponente(int u, vector<bool>&posecen){
        posecen[u] = true;
        komponente[u] = komponenteId;
        for(int v : susediRev[u]){
            if(!posecen[v])
                dfsKomponente(v,posecen);
        }
    }

    void scc(){
        fill(begin(posecen),end(posecen),false);
        for(int i=0; i<V; i++){
            if(!posecen[i])
                dfsInDeg(i);
        }
        fill(begin(posecen),end(posecen),false);
        while(!inDeg.empty()){
            int tmp = inDeg.top();
            inDeg.pop();
            if(!posecen[tmp]){
                dfsKomponente(tmp,posecen);
                komponenteId++;
            }
        }
    }

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        susediRev.resize(V);
        posecen.resize(V,false);
        komponente.resize(V,-1);
        komponenteId=0;
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susediRev[v].push_back(u);
    }

    void query(){
        scc();
        vector<int>komponenteVec(komponenteId,0);
        for(int u=0; u<V; u++){
            for(int v : susedi[u]){
                if(komponente[u]!=komponente[v])
                    komponenteVec[komponente[v]]++;
            }
        }
        for(int i=0; i<komponenteVec.size(); i++){
            cout << "komponenta br: " << i << " br ulaznih grana: " << komponenteVec[i] << endl;
        }
    }
    
};

int main(){

    int n,m;
    cin >> n >> m;
    Graph *G = new Graph(n);
    for(int i=0; i<m; i++){
        int u,v;
        cin >> u >> v;
        G->dodajGranu(u,v);
    }
    G->query();
    return 0;
}