#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

void build(vector<pair<int,int>> &tree, const vector<int>&a, int k, int x, int y){
    if(x==y){
        tree[k] = {a[x],1}; //na pocetku jedan elem i jedno pojavljivanje
        return;
    }
    int s = (x+y)/2;
    build(tree,a,2*k+1,x,s);
    build(tree,a,2*k+2,s+1,y);
    //za levog i desnog potomka
    int max_left = tree[2*k+1].first;
    int count_left = tree[2*k+1].second;
    int max_right = tree[2*k+2].first;
    int count_right = tree[2*k+2].second;
    
    if(max_left > max_right)
        tree[k] = {max_left, count_left};
    else if(max_right > max_left)
        tree[k] = {max_right, count_right};
    else
    /*Ukoliko je ml=mr, onda u korenu stabla maksimalni element mora biti ml koji se javlja cl+cr puta. 
    Za operaciju max neutral je −∞, dok je neutral za operaciju + nula. Zbog toga je par koji predstavlja neutral (−∞,0).*/
        tree[k] = {max_left, count_left+count_right};
}

void update(vector<pair<int,int>>&tree, int k, int x, int y, int i, int val){
    if(x==y){
        tree[k] = {val,1};
        return;
    }
    int s = (x+y)/2;
    if(i<=s) //levo podstablo
        update(tree,2*k+1,x,s,i,val);
    else //desno podstablo
        update(tree,2*k+2,s+1,y,i,val);
    
    int max_left = tree[2*k+1].first;
    int count_left = tree[2*k+1].second;
    int max_right = tree[2*k+2].first;
    int count_right = tree[2*k+2].second;
    
    if(max_left > max_right)
        tree[k] = {max_left, count_left};
    else if(max_right > max_left)
        tree[k] = {max_right, count_right};
    else
        tree[k] = {max_left, count_left+count_right};
}

pair<int,int> query(vector<pair<int,int>> &tree, int k, int x, int y, int a, int b){
    if(x>b || y<a)
        return {INT_MIN, 0};//inicijalne vrednosti ako smo izvan segmenta
    if(x<=a && y>=b)
        return tree[k]; //sadrzanost u segmentu
        
    //inace se segmenti seku
    int s = (x+y)/2;
    auto max_left = query(tree,2*k+1,x,s,a,b).first;
    auto count_left = query(tree,2*k+1,x,s,a,b).second;
    auto max_right = query(tree,2*k+2,s+1,y,a,b).first;
    auto count_right = query(tree,2*k+2, s+1,y,a,b).second;

    if(max_left > max_right)
        return {max_left, count_left};
    else if(max_right > max_left)
        return {max_right, count_right};
    else
        return{max_left, count_left+count_right};
}

int main(void) 
{
    int n, q; cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    const int height = ceil(log2(n));
    const int size = 2 * pow(2, height) - 1;

    //prvi par je maksimum segmenta koji cvor pokriva
    //drugi par je broj pojavljivanja tog maksimuma
    vector<pair<int, int>> tree(size); 

    build(tree, arr, 0, 0, n - 1);

    while (q--) {
        char op; cin >> op;
        if (op == 'u') {
            int ind, val; cin >> ind >> val;
            update(tree, 0, 0, n - 1, ind, val);
        } else if (op == 'm') {
            int l, r; cin >> l >> r;
            auto max = query(tree, 0, 0, n - 1, l, r).first;
            auto count = query(tree, 0, 0, n - 1, l, r).second;
            cout << max << " " << count << endl;
        } 
    }

    return 0;
}