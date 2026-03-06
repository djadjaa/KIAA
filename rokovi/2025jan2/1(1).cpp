/*
Unosi se broj n i temperature za narednih n dana. Zatim m upita koji su ili oblika *u i v* gde se 
temperatura na dan *i* menja na vrednost v ili *p a b* gde se prikazuje prosečna temperatura u intervalu [a, b]
*/

#include <bits/stdc++.h>

using namespace std;

void build(vector<int>& tree, vector<int>& array, const int k, const int start, const int end){
    if(start==end){
        tree[k] = array[start];
        return;
    }
    int s = (start+end)/2;
    build(tree,array,2*k,start,s);
    build(tree,array,2*k+1,s+1,end);
    tree[k]=tree[2*k]+tree[2*k+1];
}

void update(vector<int>&tree, const int k, const int start, const int end, const int ind, const int val){
    if(start==end){
        tree[k]=val;
        return;
    }
    int s = (start+end)/2;
    if(ind <= s)
        update(tree,2*k,start,s,ind,val);
    else
        update(tree,2*k+1,s+1,end,ind,val);
    tree[k] = tree[2*k]+tree[2*k+1];
}

int sumOfSegment(vector<int>&tree,int k,int start,int end,int left, int right){
    if(right<start || left>end)
        return 0;
    if(start<=left && end>=right)
        return tree[k];
    int s = (start+end)/2;
    int calcleft = sumOfSegment(tree,2*k,start,s,left,right);
    int calcright = sumOfSegment(tree,2*k+1,s+1,end,left,right);
    return calcleft+calcright;
}

int main(){

    int n;
    cin >> n;
    vector<int> temp(n);
    for(int i=0; i<n; i++)
        cin>>temp[i];
    int height = ceil(log2(n));
    int size = 2*pow(2,height);
    vector<int> tree(size);
    build(tree,temp,0,0,n-1);
    int m;
    cin >> m;
    while(m--){
        char c;
        cin >> c;
        if(c=='u'){
            int i,v;
            cin >> i >> v;
            update(tree,1,0,n-1,i,v);
        }else if(c=='p'){
            int a,b;
            cin >> a >> b;
            cout << sumOfSegment(tree,1,0,n-1,a,b)/(b-a+1) << endl;
        }
    }
    return 0;
}