#include <bits/stdc++.h>

using namespace std;

vector<int> parent;
vector<int> vel;

int find(int x){
    while(x!=parent[x]){
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void unionSets(int x, int y){
    int fx = find(x);
    int fy = find(y);
    if(fx==fy)
        return;
    if(vel[fx]<vel[fy])
        swap(fx,fy);
    parent[fy] = fx;
    vel[fx]+=vel[fy];
}

int main(){

    int n,q;
    cin >> n >> q;
    parent.resize(n);
    vel.resize(n,1);
    for(int i=0; i<n; i++)
        parent[i] = i;
    
    char c;
    while(q--){
        cin >> c;
        if(c=='M'){
            int a,b;
            cin >> a >> b;
            unionSets(a,b);
        }else if(c=='Q'){
            int x;
            cin >> x;
            cout << vel[find(x)] << endl;
        }
    }

    return 0;
}