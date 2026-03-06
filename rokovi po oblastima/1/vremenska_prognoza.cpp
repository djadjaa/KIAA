#include <bits/stdc++.h>
using namespace std;

void build(vector<double>&tree, vector<double>&arr, int k, int start, int end){
    if(start == end){
        tree[k] = arr[start];
        return;
    }
    int s = (start+end)/2;
    build(tree,arr,2*k+1,start,s);
    build(tree,arr,2*k+2,s+1,end);
    tree[k] = tree[2*k+1]+tree[2*k+2];
}

double query(vector<double>&tree, int k, int start, int end, int left, int right){
    if(right<start || left>end)
        return 0;
    if(start>=left && end<=right)
        return tree[k];
    int s = (start+end)/2;
    return query(tree,2*k+1,start,s,left,right)+query(tree,2*k+2,s+1,end,left,right);
}

void update(vector<double>&tree, int k, int start, int end, int ind, double val){
    if(start==end){
        tree[k] = val;
        return;
    }
    int s = (start+end)/2;
    if(ind<=s)
        update(tree,2*k+1,start,s,ind,val);
    else
        update(tree,2*k+2,s+1,end,ind,val);
    tree[k]=tree[2*k+1]+tree[2*k+2];
}

int main(){
    int n;
    cin >> n;
    vector<double> arr(n);
    for(int i=0; i<n; i++)
        cin >> arr[i];
    int height = ceil(log2(n));
    int size = 2*pow(2,height)-1;
    vector<double> tree(size);
    build(tree,arr,0,0,n-1);
    int q;
    cin >> q;
    char c;
    while (q--){
        cin >> c;
        if(c=='p'){
            int a,b;
            cin >> a >> b;
            cout << fixed << setprecision(1) << query(tree,0,0,n-1,a-1,b-1)/(b-a+1) << endl;
        }else if(c=='u') {
            int i;
            double x;
            cin >> i >> x;
            update(tree,0,0,n-1,i-1,x);
        }
    }
    
    return 0;
}