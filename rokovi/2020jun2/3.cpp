#include <bits/stdc++.h>

using namespace std;

int result=0;
/*
struct Node {
    int id; //trenutni cvor
    int parent; //njegov roditelj
    int child_index; //njegov potomak
};*/

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void dodajGrane(int u,int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }
    //node trenutni cvor, parent roditelj trenutnog cvora
    int dfs(int node, int parent){
        int size=1; //broj cvorova u podstablu, svaki cvor za sebe ima barem jedan cvor
        //idemo kroz svu decu trenutnog cvora
        for(int child:susedi[node]){
            if(child!=parent){
                int childsize = dfs(child, node); //broj cvorova u podstablu
                if(childsize%2==0) //ako imamo paran broj grana tj velicina podstabla je parna;
                    result++;
                else
                    size+=childsize; //inace sabiramo dalje
            }
        }
        return size;
    }

};

int main(){
    int n;
    cin >> n;
    Graph *G = new Graph(n+1);
    for(int i=0; i<n-1; i++){
        int u,v;
        cin >> u >> v;
        G->dodajGrane(u,v);
    }
    G->dfs(1,0); //povratnu vrednost koristimo samo kroz rekurzivne pozive ali ne i kroz rez
    cout << result << endl;
    return 0;
}