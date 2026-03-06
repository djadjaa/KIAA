#include <bits/stdc++.h>
using namespace std;

void build(vector<int>&arr, vector<int>&tree, int k, int start, int end){
    if(start == end){
        tree[k]=arr[start];
        return;
    }
    int s = (start+end)/2;
    build(arr,tree,2*k+1,start,s);
    build(arr,tree,2*k+2,s+1,end);
    tree[k] = max(tree[2*k+1],tree[2*k+2]);
}

int query(vector<int>&tree, int k, int start,int end, int left, int right){
    if(right < start || left>end)
        return 0;
    if(start>=left && end<=right)
        return tree[k];
    int s = (start+end)/2;
    return max(query(tree,2*k+1,start,s,left,right), query(tree,2*k+2,s+1,end,left,right));
}

int main(){

    int n;
    cin >> n;
    vector<int> r(n);
    int height = ceil(log2(n));
    int size = 2*pow(2,height)-1;
    vector<int> segtree(size);
    for(int i=0; i<n; i++)
        cin >> r[i];
    build(r,segtree,0,0,n-1);
    vector<int> res(n);
    for(int i=0; i<n; i++){
        int L = max(0, i - r[i]);
        int R = min(n - 1, i + r[i]);
        int maxdomet = query(segtree, 0, 0, n - 1, L, R);
        res[i] = maxdomet;
    }
    for(int x : res)
        cout << x << ' ';
    cout << endl;
    return 0;
}