#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

//segmentno stablo

void buildSegmentTree(const vector<int> &a,vector<int>&tree, int k, int start, int end){
    if(start == end){
        tree[k] = a[start];
        return;
    }
    int s = (start+end)/2;
    buildSegmentTree(a,tree,2*k,start,s);
    buildSegmentTree(a,tree,2*k+1,s+1,end);
    tree[k] = tree[2*k]+tree[2*k+1];
}

void updateTree(vector<int>&tree, const int k, const int start, const int end,
                const int index, const int value){
    if(start==end){
        tree[k] = value;
        return;
    }
    int s = (start+end)/2;
    if(index<=s)
        updateTree(tree,2*k,start,s,index,value);
    else
        updateTree(tree,2*k+1,s+1,end,index,value);
    tree[k] = tree[2*k]+tree[2*k+1];
    
}

int prosecnaTemp(vector<int>&tree, int k, int start, int end, int a, int b){
    /*iterativna!!
    int n = tree.size()/2;
    a+=n;
    b+=n;
    int sum = 0;
    while(a<=b){
        if(a%2==1)
            sum+=tree[a++];
        if(b%2==0)
            sum+=tree[b--];
        a/=2;
        b/=2;
    }
    return sum;*/

    if(b<start || a>end)
        return 0;
    if(start>=a && end<=b)
        return tree[k];
    int s=(start+end)/2;
    return prosecnaTemp(tree,2*k,start,s,a,b)+prosecnaTemp(tree,2*k+1,s+1,end,a,b);
}

int main(){

    int n;
    cin >> n;
    vector<int> temperature(n);
    for(int i=0; i<n; i++)
        cin >> temperature[i];
    int height = ceil(log2(n));
    int size = 2*pow(2,height);
    vector<int> segmentTree(size);
    buildSegmentTree(temperature,segmentTree,1,0,n-1);
    int m;
    cin >> m;
    while(m--){
        char c;
        int br1,br2;
        cin >> c >> br1 >> br2;
        if(c=='u'){
            //br1 - dan, br2 - value
            updateTree(segmentTree,1,0,n-1,br1,br2);
            for(auto x : segmentTree)
                cout << x << ' ';
            cout << endl;
        }else if(c=='p'){
            int a,b;
            a=br1;
            b=br2;
            a--; b--; // prebacivanje na 0-based
            cout << prosecnaTemp(segmentTree,1,0,n-1,a,b)/(b-a+1) << endl;
        }
    }

    return 0;
}