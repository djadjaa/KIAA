#include <bits/stdc++.h>

using namespace std;
int n;
void Tarjan(int cvor=0){
    vector<int> roditelj(n,-1);
    vector<int> lowlink(n,-1);
    vector<int> times(n,-1);
    int discoveryTime=0;
    vector<vector<int>> susedi(n);
    vector<int> posecen(n,false);
    vector<bool>artikulacione(n,false);

    times[cvor] = discoveryTime++;
    posecen[cvor] = true;
    lowlink[cvor] = times[cvor];
    int numChild=0;
    for(int sused : susedi[cvor]){
        if(posecen[sused]){
            if(sused!=roditelj[cvor])
                lowlink[cvor] = min(lowlink[cvor],times[sused]);
        }else{
            numChild++;
            roditelj[sused] = cvor;
            Tarjan(sused);
            lowlink[cvor] = min(lowlink[cvor],lowlink[sused]);

            if(roditelj[cvor]!=-1 && lowlink[sused]>=times[cvor])
                artikulacione[cvor] = true;
        }
    }
    if(roditelj[cvor]==-1 && numChild>1)
        artikulacione[cvor] =true;
}

int main(){



    return 0;
}