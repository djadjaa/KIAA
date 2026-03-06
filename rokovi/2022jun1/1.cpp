/*
U bioskupu se nalazi n osoba neke visine. Dat je broj k koji oznacava sledece: ako si ti na mestu i, 
ne mozes da vidis platno ako je bar jedna od osoba na mestima i-k,i-k+1,i-k+2,...,i-1 strogo visa od tebe. 
Za svaku osobu treba odrediti koliko njih treba da zamoli da se spusti kako bi videla platno.
Ako je najvisa osoba visine m, slozenost treba da bude O(nlogm) a prostorna O(m+n)
*/

#include <bits/stdc++.h>

using namespace std;
/*
void build(vector<int>&tree, vector<int> &a, const int k, const int start, const int end){
    if(start==end){
        tree[k] = a[start];
        return;
    }
    int s = (start+end)/2;
    build(tree,a,2*k+1,start,s);
    build(tree,a,2*k+2,s+1,end);
    tree[k] = tree[2*k+1]+tree[2*k+2];
}*/

int sum(vector<int> &tree, int k, int start, int end, int l, int r){
    if(l>end || r< start)
        return 0;
    if(l<=start && end<=r)
        return tree[k];
    int s = (start+end)/2;
    int leftquery = sum(tree,2*k+1,start,s,l,r);
    int rightquery = sum(tree,2*k+2,s+1,end,l,r);
    return leftquery+rightquery;
}

void update(vector<int> &tree, int k, int start, int end, const int index, const int val){
    if(start == end){
        tree[k]+=val;
        return;
    }
    int s = (start+end)/2;
    if(index <=s)
        update(tree,2*k+1,start,s,index,val);
    else
        update(tree,2*k+2,s+1,end,index,val);
    tree[k] = tree[2*k+1]+tree[2*k+2];
}

int main(){

    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i=0; i<n; i++)
        cin >> a[i];
    //trazimo najvisu osobu
    int m = *max_element(begin(a),end(a));
    int height = ceil(log2(m+1));
    int size = 2*pow(2,height)-1;
    vector<int> segtree(size,0);
    vector<int> res;
    //build(segtree,a,0,0,n-1); nije neophodno
    //odredujemo koliko ljudi treba da se spuste, potom ih sklanjamo sa mesta
    for(int i=0; i<n; i++){
        //i-k,i-k+1,i-k+2,...,i-1 ljudi
        /*
        Leva granica: a[i]+1 → strogo veće od trenutne visine
        Desna granica: m → maksimalna visina u segmentnom drvetu
        */
        int brVisokih = sum(segtree,0,0,m,a[i]+1,m);
        res.push_back(brVisokih);
        //dodajemo osobu na mesto
        update(segtree,0,0,m,a[i],1);
        //ako zaklanja:
        if(i>=k)
            update(segtree,0,0,m,a[i-k],-1);
    }
    for(int x : res){
        cout << x << ' ';
    }

    return 0;
}