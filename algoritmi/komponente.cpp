#include <bits/stdc++.h>

using namespace std;
int n;

void dfs(vector<vector<int>>&susedi, vector<int>&komponente, int cvor, int k){
    komponente[cvor] = k;
    for(int sused : susedi[cvor])
        if(komponente[sused]==0)
            dfs(susedi, komponente, sused, k);
}

void komponente(vector<vector<int>>&susedi){
    vector<int> komponente(n,0);
    int id = 0;
    for(int i=0; i<n; i++)
        if(komponente[i]==0)
            dfs(susedi,komponente,i,++id);

    //nesto
}

int main(){



    return 0;
}