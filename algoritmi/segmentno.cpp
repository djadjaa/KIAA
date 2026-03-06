#include <bits/stdc++.h>

using namespace std;

void buildsegtree(vector<double> &segtree,vector<double> &arr, int k, int start, int end){
    if(start==end){
        segtree[k] = arr[start];
        return;
    }
    int s = (start+end)/2;
    buildsegtree(segtree,arr,2*k,start,s);
    buildsegtree(segtree,arr,2*k+1,s+1,end);
    segtree[k] = segtree[2*k]+segtree[2*k+1];
}

void update(vector<double> &segtree, int k, int start, int end, int ind, double val){
    if(start==end){
        segtree[k] = val;
        return;
    }
    int s = (start+end)/2;
    if(ind <= s)
        update(segtree,2*k,start,s,ind,val);
    else
        update(segtree,2*k+1,s+1,end,ind,val);

    segtree[k] = segtree[2*k]+segtree[2*k+1];
}

double sum(vector<double> &segtree, int k, int start, int end, int l, int r){
    if(r<start || l>end)
        return 0;
    if(l<=start && r>=end)
        return segtree[k];
    int s = (start+end)/2;
    return sum(segtree,2*k,start,s,l,r)+sum(segtree,2*k+1,s+1,end,l,r);
}

int main(){

    int n;
    cin >> n;
    vector<double> temp(n);
    for(int i=0; i<n; i++){
        cin>>temp[i];
    }
    int height = ceil(log2(n));
    int size = 2*pow(2,height);

    vector<double> segtree(size);

    buildsegtree(segtree,temp,1,0,n-1);

    int q;
    cin >> q;
    while(q--){
        char c;
        cin >> c;
        if(c=='p'){
            int a,b;
            cin >> a >> b;
            a--; b--;
            cout << sum(segtree,1,0,n-1,a,b)/(b-a+1) << endl;
        }else if(c=='u'){
            int i;
            double val;
            cin >> i >> val;
            i--;
            update(segtree,1,0,n-1,i,val);
        }
    }

    return 0;
}