#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct bitka{
    int nacija1, vladar1, nacija2,  vladar2;
};

void dodajOgranicenje(vector<vector<int>> &minrazlika, const vector<vector<int>>&times, const bitka &bitka){
    auto [n1,v1,n2,v2] = bitka;
    /*
    Početna godina nacije 2 mora biti najmanje min_x godina kasnija od nacije 1
    da bi njihovi vladari mogli imati preklapajući period vladavine

    sa stanovišta nacije 2, odnos je obrnuto: početna godina nacije 1 
    ne sme biti kasnija od početka nacije 2 više od neke vrednosti.
    */
    int min_x = times[n1][v1] - times[n2][v2+1]+1;
    int max_x = times[n1][v1+1] - times[n2][v2]-1;
    //definiše minimalnu potrebnu razliku godina da intervali vladavine imaju presek.
    minrazlika[n1][n2] = max(minrazlika[n1][n2],min_x);
    //ova razlika mora da omoguci preklapanje intervala
    /*
    Ako razlika xi,j padne izvan tog intervala [min_x, max_x], 
    onda njihovi intervali vladavine ne preklapaju se, 
    što znači da bitka ne može da se desi.
    */
   //definiše maksimalnu dopuštenu razliku u obrnutom smeru.
    minrazlika[n2][n1] = max(minrazlika[n2][n1],-max_x);
}

bool dolaziDoBitke(const vector<vector<int>> &times, const vector<bitka> &bitke, const bitka &upit){
    const int n = times.size();
    vector<vector<int>> minrazlika(n,vector<int>(n,numeric_limits<int>::min()));
    for(auto bitka : bitke){
        dodajOgranicenje(minrazlika,times,bitka);
    }
    //kako dodaje ogranicenja za sve bitke dodaje i za upite
    dodajOgranicenje(minrazlika,times,upit);

    //flojd varsal kako bismo nasli zeljenu minimalnu razliku
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                //xi,j​≥xi,k ​+ xk,j
                //svaka pojedinacna bitka izmedju dve nacije daje lokalno ogranicenje za razliku pocetnih godina
                //ovde posmatramo globalno izmedju svih bitki i tada ce minrazlika da cuva najstrozije minimalno ogranicenje
                minrazlika[i][j] = max(minrazlika[i][j], minrazlika[i][k]+minrazlika[k][j]);
                //cout << minrazlika[i][j] << endl;
            }
        }
    }
    for(int i=0; i<n; i++){
        //nacija ne moze da pocne sama od sebe
        if(minrazlika[i][i]>0)
            return false;
    }
    return true;
}

int main(){
    int n, m, k, q;

    cin >> n;
    vector<vector<int>> times(n);
    for (int i = 0; i < n; i++) {
        cin >> m;
        times[i] = vector<int>(m);
        for (int j = 0; j < m; j++) {
            cin >> times[i][j];
        }
    }

    cin >> k;
    vector<bitka> battles(k);
    for (int i = 0; i < k; i++) {
        cin >> battles[i].nacija1 >> battles[i].vladar1 
            >> battles[i].nacija2 >> battles[i].vladar2;
    }

    cin >> q;
    vector<bitka> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].nacija1 >> queries[i].vladar1
            >> queries[i].nacija2 >> queries[i].vladar2;
    }

    for (auto query : queries) {
        cout << (dolaziDoBitke(times, battles, query) ? "Da" : "Ne") << endl;
    }

    return 0;
}