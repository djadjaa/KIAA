/*
dato segmentno stablo, 
optimizovati ga za problem ispitivanja da li je neki podniz datog niza strogo rastući 
i obezbediti da može da se efikasno promeni vrednost niza
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include <limits>
#include <climits>

using namespace std;

//segmentno stablo

void buildSegmentTree(const vector<int> &a,vector<int>&tree, int k, int start, int end){
    if(start == end){
        tree[k] = a[start];
        return;
    }
    int s = (start+end)/2;
    buildSegmentTree(a,tree,2*k+1,start,s);
    buildSegmentTree(a,tree,2*k+2,s+1,end);
    tree[k] = min(tree[2*k+1],tree[2*k+2]);
}

void updateTree(vector<int>&tree, const int k, const int start, const int end,
                const int index, const int value){
    if(start==end){
        tree[k] = value;
        return;
    }
    int s = (start+end)/2;
    if(index<=s)
        updateTree(tree,2*k+1,start,s,index,value);
    else
        updateTree(tree,2*k+2,s+1,end,index,value);
    tree[k] = min(tree[2*k+1],tree[2*k+2]);
    
}

int rastuci(vector<int>&tree, const int k, const int start, const int end, const int left, const int right){
    //van opsega:
    if(right<start || left>end)
        return INT_MAX;
    if(right>=end && left <=start){
        return tree[k];
    }
    int s = (start+end)/2;
    int leftquery = rastuci(tree,2*k+1, start,s,left,right);
    int rightquery = rastuci(tree,2*k+2,s+1,end,left,right);
    return min(leftquery,rightquery); //trazi minimalnu razliku izmedju elemenata u podnizu
    //ako je taj minimum > 0 na kraju, dobijamo strogo rastuci podniz, inace opadajuci
    //dakle nama je poenta da su sve razlike pozitivne medjusobno
}

int main(){

    int n;
    cin >> n;
    vector<int> niz(n);
    for(int i=0; i<n; i++)
        cin >> niz[i];
    vector<int> diff(n-1); //posmatraćemo razlike, ako je ona pozitivna potencijalno je podniz rastuć inače opadajuć
    for(int i=0; i<n-1; i++)
        diff[i] = niz[i+1]-niz[i];
    int height = ceil(log2(n));
    int size = 2*pow(2,height)-1;
    vector<int> segmentTree(size);
    buildSegmentTree(diff,segmentTree,0,0,n-2);
    int m;
    cin >> m;
    while(m--){
        char c;
        int br1,br2;
        cin >> c >> br1 >> br2;
        if(c=='u'){
            //br1 - indeks, br2 - value
            
            niz[br1] = br2;
            if(br1>0) //levi podniz
            //ubacujemo diff u segmentno drvo
            /*
            Samo ove dve pozicije u segmentnom stablu treba ažurirati,
            jer samo one mogu promeniti strogo rastuću osobinu za podniz koji uključuj
            */
                updateTree(segmentTree,0,0,n-2,br1-1,niz[br1]-niz[br1-1]);
            if(br1<n-1) //desni podniz
                updateTree(segmentTree,0,0,n-2,br1,niz[br1+1]-niz[br1]);
            for(auto x : segmentTree)
                cout << x << ' ';
            cout << endl;
        }else if(c=='r'){
            int left = br1, right = br2;
            int rastuciRes = rastuci(segmentTree,0,0,n-2,left,right-1);
            if(rastuciRes>0)
                cout << "strogo rastuci\n";
            else
                cout << "nije\n";
        }
    }

    return 0;
}