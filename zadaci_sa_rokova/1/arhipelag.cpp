#include <bits/stdc++.h>

using namespace std;

vector<int> parent;
vector<int> vel;
int grupe;

//funkcija koja pronalazi roditelja za dati elem
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
    grupe--;
}

bool pripada(int x, int y){
    return parent[find(x)] == parent[find(y)];
}

int velicina(int x){
    return vel[find(x)];
}

int main(){

    int n,m;
    cin >> n >> m;
    parent.resize(n+1);
    vel.resize(n+1,1);
    grupe = n;
    for(int i=0; i<n; i++)
        parent[i] = i;
    
    char c;
    int x,y;
    while(m--){
        cin >> c;
        if(c=='U'){
            cin >> x >> y;
            unionSets(x,y);
        }else if(c=='P'){
            cin >> x >> y;
            cout << (pripada(x,y) ? "da\n" : "ne\n");
        }else if(c=='V'){
            cin >> x;
            cout << velicina(x) << endl;
        }else if(c=='K'){
            cout << grupe << endl;
        }
    }

    return 0;
}