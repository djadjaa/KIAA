#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void buildSegmentTree(vector<pair<int,int>>&arr, vector<pair<int,int>>&tree, int k, int x, int y){
    if(x==y){
        tree[k] = arr[x];
        return;
    }
    int s = (x+y)/2;
    buildSegmentTree(arr,tree,2*k+1,x,s);
    buildSegmentTree(arr,tree,2*k+2,s+1,y);
    //f(x)=a*x+b
    auto a = tree[2*k+1].first;
    auto b = tree[2*k+1].second;
    //g(x)=c*x+d
    auto c = tree[2*k+2].first;
    auto d = tree[2*k+2].second;
    //f(g(x)) - ovo ocekujemo u korenu
    tree[k] = {c*a,c*b+d};
}
//e i f su novi koeficijenti
void update(vector<pair<int,int>>&tree, int k, int x, int y, int ind, int e, int f){
    if(x==y){
        tree[k] = {e,f};
        return;
    }
    int s=(x+y)/2;
    //koje trenutno podstablo
    if(ind<=s)
        update(tree,2*k+1,x,s,ind,e,f);
    else
        update(tree,2*k+2,s+1,y,ind,e,f);
    //dopuna ostalih cvorova
    auto a = tree[2*k+1].first;
    auto b = tree[2*k+1].second;
    auto c = tree[2*k+2].first;
    auto d = tree[2*k+2].second;
    tree[k] = {c*a,c*b+d};
}

pair<int,int> query(vector<pair<int,int>>&tree, int k, int x, int y, int l, int r){
    if(y<l || x>r)
        return {1,0}; //neutral
    if(x>=l && y<=r)
        return tree[k];
    int s = (x+y)/2;
    auto a = query(tree,2*k+1,x,s,l,r).first;
    auto b = query(tree,2*k+1,x,s,l,r).second;
    auto c = query(tree,2*k+2,s+1,y,l,r).first;
    auto d = query(tree,2*k+2,s+1,y,l,r).second;
    return {c*a,c*b+d};
}

int main(){

    int n,q;
    cin >> n >> q;
    vector<pair<int,int>> arr(n);
    for(int i=0; i<n; i++)
        cin >> arr[i].first >> arr[i].second;
    
    int height = ceil(log2(n));
    int size = 2*pow(2,height)-1;
    vector<pair<int,int>>tree(size);
    buildSegmentTree(arr,tree,0,0,n-1);

    while(q--){
        int op;
        cin >> op;
        if(op==0){
            int i,c,d;
            cin >> i >> c >> d;
            update(tree,0,0,n-1,i,c,d);
        }else if(op==1){
            int l,r,x;
            cin >> l >> r >> x;
            const auto a = query(tree,0,0,n-1,l,r).first;
            const auto b = query(tree,0,0,n-1,l,r).second;
            cout << a*x+b << endl;
        }
    }

    return 0;
}