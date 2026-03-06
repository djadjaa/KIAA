//kosaraju
#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<vector<int>> susediRev;
    //vector<int> discT;
    //vector<int> low;
    vector<bool> posecen;
    int discoveryTime=0;
    stack<int> inDeg;
    vector<int> komponente;
    int komponenteId=0;

    void dfsInDeg(int v){
        posecen[v] = true;
        stack<int>s;
        s.push(v);
        while(!s.empty()){
            int tmp = s.top();
            s.pop();
            inDeg.push(tmp);

            for(int sused : susedi[tmp]){
                if(!posecen[sused]){
                    posecen[sused] = true;
                    s.push(sused);
                }
            }
        }
    }

    void dfsKomponente(int v, vector<bool>&posecen){
        posecen[v] = true;
        komponente[v] = komponenteId;
        for(int sused : susediRev[v]){
            if(!posecen[sused])
                dfsKomponente(sused,posecen);
        }
    }

    void nadjiKomponente(){
        fill(posecen.begin(), posecen.end(), false);
        for(int i=0; i<V; i++){
            if(!posecen[i])
                dfsInDeg(i);
        }
        fill(posecen.begin(), posecen.end(), false);

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
        //discT.resize(V,-1);
        //low.resize(V,-1);
        posecen.resize(V,false);
        komponente.resize(V,-1);
        susediRev.resize(V);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susediRev[v].push_back(u);
    }

    int query(){
        nadjiKomponente();
        //broj ulaznih grana:
        vector<int> komponenteVec(komponenteId,0);
        for(int i=0; i<V; i++){
            for(auto sused : susedi[i]){
                //Ako grana ide iz jedne SCC u drugu SCC
                if(komponente[i]!=komponente[sused])
                    komponenteVec[komponente[sused]]++;
            }
        }
        int res=0;
        for(int i=0; i<komponenteId;i++){
            if(komponenteVec[i]==0)
                res++;
        }
        return res;
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
    cout << G->query() << endl;
    return 0;
}