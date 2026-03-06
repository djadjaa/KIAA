#include <bits/stdc++.h>
using namespace std;

vector<int> parent;
vector<int> vel;

int find(int x){
    while (x!=parent[x])
    {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
    
}

void unionF(int x, int y){
    int fx = find(x);
    int fy = find(y);

    if(fx==fy)
        return;
    if(vel[fx]<vel[fy])
        swap(fx,fy);
    parent[fy] = fx;
    vel[fx]+=vel[fy];
}

int velicina(int x){
    return vel[find(x)];
}

bool pripada(int x, int y){
    return parent[find(x)] ==  parent[find(y)];
}

int main(){

    int n;
    cin >> n;
    parent.resize(n+1);
    vel.resize(n+1,1);
    //init
    for(int i=0; i<n; i++)
        parent[i] = i;
    //query operacije

    return 0;
}