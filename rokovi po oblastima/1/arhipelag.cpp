#include <bits/stdc++.h>

using namespace std;

int groups; //size of groups
vector<int> parent;
vector<int> velicina; //niz velicina svake od grupe

int find(int x){
    while(x!=parent[x]){
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void unionGroups(int x, int y){
    int fx = find(x);
    int fy = find(y);
    if(fx==fy)
        return;
    if(velicina[fx]<velicina[fy])
        swap(fx,fy);
    parent[fy] = fx;
    velicina[fx]+=velicina[fy];
    groups--;
}

int sizeOfGroup(int x){
    return velicina[find(x)];
}

bool pripada(int x, int y){
    return parent[find(x)] == parent[find(y)];
}

int main(){

    int n,m;
    cin >> n >> m;
    parent.resize(n+1);
    velicina.resize(n+1,1);

    groups = n;
    for(int i=0; i<n; i++)
        parent[i] = i;
    /*
    for(auto &p : parent)
        cout << p << ' ';
    cout << endl;
*/
    char c;
    int a,b,x;
    while(m--){
        cin >> c;
        if(c=='K'){
            cout << groups << endl;
        }else if(c=='U'){
            cin >> a >> b;
            unionGroups(a,b);
        }else if(c=='V'){
            cin >> x;
            cout << sizeOfGroup(x) << endl;
        }else if(c=='P'){
            cin >> a >> b;
            cout << (pripada(a,b) ? "da\n" : "ne\n");
        }
    }

    return 0;
}