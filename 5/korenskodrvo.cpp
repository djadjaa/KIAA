/*drugi nacin su matrice povezanosti preko klasa, 
treci nacin vektori parova gde je prvi clan 
cvor odakle se vrsi dfs,a drugi je cvor ka kom ide prvi cvor
ugl grana povezanosti
*/
#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <algorithm>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> listaSuseda;
    vector<bool> visited;

    public:
    Graph(int V){ //konstruktor <=> inicijalizacija
        this->V = V;
        visited.resize(V,false);
        listaSuseda.resize(V);
    }

    void addEdge(int u,int v){
        //neusmereni graf
        listaSuseda[u].push_back(v);
        listaSuseda[v].push_back(u);
    }

    //DFS
    //root je cvor od kog pocinje dfs
    vector<pair<int,int>> createTree(int root){
        vector<pair<int,int>> edges; //grane
        edges.reserve(V-1); //alokacija
        //iterativna implementacija DFS-a je preko steka
        stack<int> s;
        s.push(root);
        visited[root] = true;

        int tmp;
        while(!s.empty()){
            tmp = s.top();
            s.pop();

            for(int sused : listaSuseda[tmp]){
                if(!visited[sused]){
                    s.push(sused);
                    visited[sused] = true;
                    //direktno ubacivanje para u vektor, kod push back je kompleksniji postupak
                    edges.emplace_back(tmp,sused);
                }
            }
        }

        sort(begin(edges),end(edges));
        return edges;
    }
};

int main(){

    int V;
    cin >> V;
    Graph *G = new Graph(V);
    int u, v;

    for(int i=0; i<V-1; i++){
        cin >> u >> v;
        G->addEdge(u,v);
    }

    int root;
    cin >> root;
    vector<pair<int, int>> edges = G->createTree(root);
    for(const auto &p : edges)
        cout << p.first << " " << p.second << '\n';

    delete G;
    return 0;
}