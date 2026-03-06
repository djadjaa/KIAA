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

int sizeGroup(int x){
    return vel[find(x)];
}

void unionSet(int x, int y){
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

    int a,q;
    cin >> a >> q;
    parent.resize(a);
    vel.resize(a,1);

    for(int i=0; i<a; i++){
        parent[i] = i;
    }

    while(q--){
        char c;
        cin >> c;
        if(c=='q'){
            int x;
            cin >> x;
            cout << sizeGroup(x) << endl;
        }else if(c=='m'){
            int x,y;
            cin >> x >>y;
            unionSet(x,y);
        }
    }

    return 0;
}