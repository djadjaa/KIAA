/*
imamo neusmeren graf
server je kritican ako njegovim uklanjanjem prekida komunikaciju izmedju glavnog i barem jednog od servera
-> serveri su artikulacione tacke, jer ako ih uklonimo gubimo jednu celu
komponentu povezanosti i imamo ih vise
ukupna cena popravke bice suma artikulacionih tacaka

->primena Tarjanovog algoritma
*/
#include <bits/stdc++.h> 
using namespace std;

int discoveryTime =0;
vector<bool> posecen;
vector<int> timeIn;
vector<int> lowlink;
vector<int> roditelj;
vector<bool> artikulacioneTacke;
int numChilds;
vector<vector<int>> susedi;

void Tarjan(int cvor){
    posecen[cvor] = true;
    timeIn[cvor] = discoveryTime++;
    lowlink[cvor] = timeIn[cvor];
    numChilds=0;

    for(auto sused : susedi[cvor]){
        if(posecen[sused]){
            if(sused!=roditelj[cvor])
                lowlink[cvor] = min(lowlink[cvor],timeIn[sused]);
        }else{
            numChilds++;
            roditelj[sused] = cvor;
            Tarjan(sused);
            lowlink[cvor] = min(lowlink[cvor],lowlink[sused]);

            if(roditelj[cvor]!=-1 && lowlink[sused]>=timeIn[cvor])
                artikulacioneTacke[cvor] = true;
        }
    }
    if(roditelj[cvor]==-1 && numChilds>1)
        artikulacioneTacke[cvor] = true;
}
int main(){
    int n,m;
    cin >> n >> m;
    susedi.resize(n);
    posecen.resize(n,false);
    timeIn.resize(n);
    lowlink.resize(n);
    roditelj.resize(n,-1);
    artikulacioneTacke.resize(n,false);

    int u,v;
    for(int i=0; i<m; i++){
        cin >> u >> v;
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }
    vector<int> cene(n);
    for(int i=0; i<n; i++)
        cin >> cene[i];
    int glavniServer;
    cin >> glavniServer;
    Tarjan(glavniServer);
    int sum=0;
    for(int i=0; i<n; i++){
        if(artikulacioneTacke[i])
            sum+=cene[i];
    }
    cout << sum << endl;

    return 0;
}