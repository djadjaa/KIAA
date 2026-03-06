/*
dato je n gradova povezano sa m dvosmernih puteva i svaki grad ima osvetljenost (ceo broj) potrebno je u 
suštini naći zbir osvetljenosti svih artikulacionih tačaka.
*/

#include <bits/stdc++.h>

using namespace std;

int discoveryTime=0;
vector<bool> posecen;
vector<vector<int>> susedi;
vector<int> inDeg;
vector<int> lowlink;
vector<int> parent;
vector<bool> artikulacioneTacke;

vector<int> osvetljenje;

void Tarjan(int cvor){
    posecen[cvor]=true; 
    inDeg[cvor] = discoveryTime++;
    int numChild=0;
    lowlink[cvor]=inDeg[cvor];

    for(auto sused : susedi[cvor]){
        if(posecen[sused]){
            if(sused!=parent[cvor])
                lowlink[cvor] = min(lowlink[cvor],inDeg[sused]);
        }else{
            numChild++;
            parent[sused] = cvor;
            Tarjan(sused);
            lowlink[cvor] = min(lowlink[cvor],lowlink[sused]);
            if(parent[cvor]!=-1 && lowlink[sused]>=inDeg[cvor])
                artikulacioneTacke[cvor]=true;
        }
    }
    if(parent[cvor]==-1 && numChild>1)
        artikulacioneTacke[cvor] = true;
}

int main(){

    int n,m;
    cin >> n >> m;

    susedi.resize(n);
    posecen.resize(n,false);
    inDeg.resize(n);
    lowlink.resize(n);
    parent.resize(n,-1);
    artikulacioneTacke.resize(n,false);
    osvetljenje.resize(n);

    int u,v;
    for(int i=0; i<m; i++){
        cin >> u >> v;
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }

    for(int i=0; i<n; i++)
        cin >> osvetljenje[i];

    for(int i=0; i<n; i++){
        if(!posecen[i])
            Tarjan(i);
    }
    int sum=0;
    for(int i=0; i<n; i++){
        if(artikulacioneTacke[i])
            sum+=osvetljenje[i];
    }
    cout << sum << endl;
    return 0;
}