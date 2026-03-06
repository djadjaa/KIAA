#include <bits/stdc++.h>

using namespace std;

void buildSegmentTree(vector<int> &a, vector<int> &tree, int k, int start, int end){
    if(start == end){
        tree[k] = a[start];
        return;
    }
    int s = (start+end)/2;
    buildSegmentTree(a,tree,2*k+1,start,s);
    buildSegmentTree(a,tree,2*k+1,s+1,end);
    tree[k] = tree[2*k+1]+tree[2*k+2];
}

int query(vector<int> &tree, int k, int start, int end, int l, int r){
    if(r<start || l>end)
        return 0;
    if(l<=start && r>=end)
        return tree[k];
    int s = (start+end)/2;
    //ovde moze stajati proizvod, minimum/maksimum...
    return query(tree,2*k+1,start,s,l,r)+query(tree,2*k+2,s+1,end,l,r);
}

void update(vector<int> &tree, int k, int start, int end, int val, int i){
    if(start == end){
        tree[k] = val;
        return;
    }
    int s = (start+end)/2;
    if(i<=s)
        update(tree,2*k+1,start,s,val,i);
    else
        update(tree,2*k+2,s+1,end,val,i);
    tree[k] = tree[2*k+1]+tree[2*k+2];
}

int main(){

    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0; i<n; i++)
        cin >> a[i];

    int height = ceil(log2(n));
    int size = 2*pow(2,height)-1;

    vector<int> tree(size);

    buildSegmentTree(a,tree,0,0,n-1);

    //query operacije
    return 0;
}