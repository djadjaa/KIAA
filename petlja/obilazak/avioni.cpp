#include <bits/stdc++.h>

using namespace std;

vector<vector<int>>susedi;

void bfs(int start, int end, int id){
    vector<int> rastojanje(id,-1);
    queue<int> q;

    rastojanje[start]=0;
    q.push(start);

    while(!q.empty()){
        int tmp = q.front();
        q.pop();

        for(int sused : susedi[tmp]){
            if(rastojanje[sused]==-1){
                rastojanje[sused]= rastojanje[tmp]+1;
                q.push(sused);
            }
        }
    }
    if(rastojanje[end]==-1)
        cout << "ne\n";
    else
        cout << rastojanje[end] << endl;
}

int main(){

    int n;
    cin >> n;
    string src,dest;
    susedi.resize(n); //nije neophodna klasa
    map<string,int> gradovi;

    int id=0;
    auto get_id = [&](const string &s){
        if(!gradovi.count(s)){
            gradovi[s] = id++;
            susedi.push_back({});
        }
        return gradovi[s];
    };

    for(int i=0; i<n; i++){
        cin >> src >> dest;
        int u = get_id(src);
        int v = get_id(dest);

        susedi[u].push_back(v);
        //susedi[v].push_back(u);
    }
    
    int q;
    cin >> q;
    while(q--){
        cin >> src >> dest;

        if(!gradovi.count(src) || !gradovi.count(dest)){
            cout << "ne\n";
            continue;
        }

        int start = gradovi[src];
        int end = gradovi[dest];

        bfs(start,end,id);
    }


    return 0;
}