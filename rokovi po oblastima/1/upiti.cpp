#include <bits/stdc++.h>
using namespace std;

void build(vector<pair<long long,int>>&tree, vector<int>&arr, int x, int k, int start, int end){
    if(start==end){
        tree[k].first = arr[start];
        tree[k].second = (arr[start] >= x);
        return;
    }
    int s = (start+end)/2;
    build(tree,arr,x,2*k,start,s);
    build(tree,arr,x,2*k+1,s+1,end);
    tree[k].first = tree[2*k].first+tree[2*k+1].first;
    tree[k].second = tree[2*k].second+tree[2*k+1].second;
}

void update(vector<pair<long long,int>>&tree, int k, int start, int end, int ind, int val, int x){
    if(start == end){
        tree[k].first = val;
        tree[k].second = (val>=x);
        return;
    }
    int s = (start+end)/2;
    if(ind<=s)
        update(tree,2*k,start,s,ind,val,x);
    else
        update(tree,2*k+1,s+1,end,ind,val,x);
    
    tree[k].first = tree[2*k].first+tree[2*k+1].first;
    tree[k].second = tree[2*k].second+tree[2*k+1].second;
}

pair<long long,int>query(vector<pair<long long,int>>&tree, int k, int start, int end, int left, int right){
    if(start>right || end<left)
        return {0,0};
    if(start>=left && end <=right)
        return tree[k];
    int s = (start+end)/2;
    auto lq = query(tree,2*k,start,s,left,right);
    auto rq = query(tree,2*k+1,s+1,end, left,right);
    return {lq.first+rq.first, lq.second+rq.second};
}

int main(){
    int n,q,x;
    cin >> n >> q >> x;
    vector<int> arr(n);
    for(int i=0; i<n; i++)
        cin >> arr[i];
    int height = ceil(log2(n));
    int size = 2*pow(2,height);//-1
    vector<pair<long long,int>> tree(size);
    build(tree,arr,x,1,0,n-1);

    while(q--){
        int k,v,a,b;
        cin >> k >> v >> a >> b;
        update(tree,1,0,n-1,k,v,x);
        pair<long long, int> res = query(tree,1,0,n-1,a,b);
        cout << res.first <<  ' ' << res.second << endl;
    }

    return 0;
}