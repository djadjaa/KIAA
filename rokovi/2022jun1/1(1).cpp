/*
U bioskupu se nalazi n osoba neke visine. Dat je broj k koji oznacava sledece: ako si ti na mestu i, ne mozes da vidis platno ako je bar jedna od 
osoba na mestima i-k,i-k+1,i-k+2,...,i-1 strogo visa od tebe. Za svaku osobu treba odrediti koliko njih treba da zamoli da se spusti kako bi videla platno.
Ako je najvisa osoba visine m, slozenost treba da bude O(nlogm) a prostorna O(m+n)

Primer:
5 3
4 2 3 2 1

Ispis:
0 1 1 2 3

[0]150  [1]160  [2]155  [3]165  [4]150  [5]170
max = 170
i=0; trenutni elem 150 query(151,170) = 0;
[150] [0]
i=1; 160 q(161,170)=0
[150,160] [0,0]
i=2; 155 q(156,170)=1 
[150,160,155] [0,0,1]
i=3 165 q(166,170)=0;
izbacujemo 150
[160 155 165] [0,0,1,0]
i=4 150 q(151,170)=3
izbacujemo 160
[155 165 150] [0 0 1 0 3]
i=5 170 q(171,170) van opsega
izbacujemo 155 .... 


-> 0 0 1 0 3 0
*/

#include <bits/stdc++.h>

using namespace std;

int sum(vector<int>&tree, int k, int start, int end, int left, int right){
    if(right < start || left > end)
        return 0;
    if(start >= left && end <= right)
        return tree[k];
    int s = (start+end)/2;
    return sum(tree,2*k,start,s,left,right)+sum(tree,2*k+1,s+1,end,left,right);
}

void update(vector<int>&tree, int k, int start, int end, int i, int val){
    if(start==end){
        tree[k]+=val;
        return;
    }
    int s = (start+end)/2;
    if(i<=s)
        update(tree,2*k,start,s,i,val);
    else
        update(tree,2*k+1,s+1,end,i,val);
    tree[k] = tree[2*k]+tree[2*k+1];
}

int main(){

    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for(int i=0; i<n; i++)
        cin >> arr[i];
    int m = *max_element(arr.begin(),arr.end());
    int height = ceil(log2(m+1));
    int size = 2*pow(2,height);
    vector<int> tree(size,0);
    vector<int> res;
    for(int i=0; i<n; i++){
        int brVisokih = sum(tree,0,0,m,arr[i]+1,m);
        res.push_back(brVisokih);
        update(tree,0,0,m,arr[i],1);
        //pokretni prozor:
        if(i>=k)
            update(tree,0,0,m,arr[i-k],-1);
    }
    for(auto x : res)
        cout << x << ' ';
    cout << endl;
    return 0;
}