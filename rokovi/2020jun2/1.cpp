#include <bits/stdc++.h>
//pogresni test primeri ig

using namespace std;

void build(const vector<int> &arr, vector<pair<long long,int>>&tree, int k, int start, int end,int x){
    if(start==end){
        tree[k].first = arr[start]; //suma
        tree[k].second = (arr[start] > x); //broj vecih od x
        return;
    }
    int s = (start+end)/2;
    build(arr,tree,2*k+1,start,s,x);
    build(arr,tree,2*k+2,s+1,end,x);
    tree[k].first=tree[2*k+1].first+tree[2*k+2].first;
    tree[k].second=tree[2*k+1].second+tree[2*k+2].second;
}

void update(vector<pair<long long,int>>&tree, int k, int start, int end, int ind, int val,int x){
    if(start == end){
        tree[k].first = val;
        tree[k].second = (val > x); //broj vecih od x
        return;
    }
    int s = (start+end)/2;
    if(ind <= s)
        update(tree,2*k+1,start,s,ind,val,x);
    else
        update(tree,2*k+2,s+1,end,ind,val,x);
    tree[k].first=tree[2*k+1].first+tree[2*k+2].first;
    tree[k].second=tree[2*k+1].second+tree[2*k+2].second;
}

pair <long long,int> query(vector<pair<long long,int>>&tree, int k, int start, int end, int left, int right){
    if(right<start || left>end)
        return {0,0};
    if(left<=start && end <= right){
        return tree[k];
    }
    int mid = (start + end) / 2;
    auto L = query(tree, 2*k+1, start, mid, left, right);
    auto R = query(tree, 2*k+2, mid+1, end, left, right);
    return {L.first + R.first, L.second + R.second};
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q,x;
    cin >> n >> q >> x;
    vector<int> arr(n);
    for(int i=0; i<n; i++)
        cin >> arr[i];
    int height = ceil(log2(n));
    int size = 2*pow(2,height)-1;
    vector<pair<long long,int>> segtree(size);
    build(arr,segtree,0,0,n-1,x);
    while(q--){
        int k,v,a,b;
        cin >> k >> v >> a >> b;
        update(segtree,0,0,n-1,k,v,x);
        for(auto x : segtree)
            cout << x.first << ' ';
        cout << endl;
        pair<long long,int> p = query(segtree,0,0,n-1,a,b);
        cout << p.first << ' ' << p.second << endl;
    }

    return 0;
}