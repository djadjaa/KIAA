#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<int> inDeg;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        inDeg.resize(V,0);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        inDeg[v]++;
    }

    int topolosko(){
        int res=0;
        queue<int> s;
        for(int i=0; i<V; i++){
            if(inDeg[i]==0){
                s.push(i);
            }
        }
        if(s.empty())
            return -1;
        s.push(-1); //indikator da smo obradili zadatke za 'taj dan'
        while(!s.empty()){
            int tmp = s.front();
            s.pop();

            if(tmp==-1){
                res++;
                if(s.empty())
                    break;
                s.push(-1);
                continue;
            }

            for(auto sused : susedi[tmp]){   
                inDeg[sused]--;
                if(inDeg[sused]==0)
                    s.push(sused);
            }
            
        }
        //da li su svi obradjeni cvorovi
            for(int i=0; i<V; i++){
                if(inDeg[i]>0)
                    return -1;
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
        G->dodajGranu(u-1,v-1);
    }
    cout << G->topolosko() << endl;

    return 0;
}