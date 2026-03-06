/*Drustvene mreze    (disjunktni skupovi)
Ljudi koriste drustvene mreze i povezuju se jedni sa drugima.
napisi program koji ce da ima dve radnje:
    M - spajamo osobu a i b
    Q - ispisujemo koliko osoba ima u mrezi u kojoj je  

ulaz: h, broj ljudi i q, broj upita, pa onda q upita koji imaju M ili Q radnju 
    ako je M onda unosimo jos a i b 
    ako je Q onda unosimo jos a 

izlaz: za svaki Q upit da ispise koliko ima ljudi ima u toj a mrezi

test primer:
3 6
Q 1
M 1 2 
Q 2
M 2 3
Q 3
Q 2

izlaz:
1
2
3
3*/

#include <iostream>
#include <vector>

using namespace std;

vector<int>parent;
vector<int>rang;
vector<int>velicina;

void init(int n){
    parent.resize(n);
    rang.resize(n);
    velicina.resize(n+1,1);
    for(int i=0; i<n; i++){
        parent[i] = i;
        rang[i] = 0;
    }
}

int find(int x){
    if(parent[x]!=x)
        parent[x] = parent[parent[x]];
    return parent[x];
}

void unionSet(int a, int b){
    int r_a = find(a);
    int r_b = find(b);
    if(r_a == r_b)
        return;
    if(rang[r_a]<rang[r_b]){
        parent[r_a] = r_b;
        //dodavanje broj elemenata skupa
        velicina[r_b]+=velicina[r_a];
    }
    else if(rang[r_b]<rang[r_a]){
        parent[r_b] = r_a;
        velicina[r_a]+=velicina[r_b];
    }
    else{
        parent[r_b] = r_a;
        velicina[r_a]+=velicina[r_b];
        rang[r_a]++;
    }
}

int main(){

    int n;
    cin >> n;
    init(n);
    int q;
    cin >> q;
    while(q--){
        char query;
        cin >> query;
        if(query == 'M'){
            int a,b;
            cin >> a >> b;
            //spajanje:
            unionSet(a,b);
        }else if(query =='Q'){
            int a;
            cin >> a;
            int a_set = find(a);
            cout << velicina[a_set] << endl;
        }
    }
    return 0;
}