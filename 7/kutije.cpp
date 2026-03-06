#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//typedef vector<int> Box;

bool mozeLiStati(const vector<int> &b1, const vector<int> &b2){
    const int d = b1.size();//broj dimenzija kutije
    for(int i=0; i<d; i++){
        /*
        ako je u bilo kojoj dimenziji kutija b1 veća ili jednaka od b2, 
        onda se ne može staviti unutra.
        */
        if(b1[i]>=b2[i])
            return false;
    }
    return true;
}

int lanac(vector<vector<int>> &boxes){
    const int n = boxes.size(); //broj kutija
    const int d = boxes[0].size(); //broj dimenzija svake kutije

    //sortiranje dimenzija unutar te kutije u rastucem poretku
    /*
    A(3,2,5) -> A(2,3,5)
    B(4,6,3) -> B(3,4,6)
    */
    for(int i=0;i<n; i++)
        sort(boxes[i].begin(),boxes[i].end());
    
    //sortiranje prema dimenzijama globalno -> prema visini, pa sirini pa duzini respektivno
    /*
    boxes = {
    {2, 3, 5},
    {3, 4, 6},
    {2, 2, 8}
    }
    prva it: {2,3,5}, {3,4,6}, {2,2,8}
    druga it: {2,2,8}, {2,3,5}, {3,4,6}
    treca it: {2,2,8}, {2,3,5}, {3,4,6}
    */
    for(int i=d-1; i>=0; i--){
        //lambda funkcija za svaku od dimenzija
        sort(boxes.begin(), boxes.end(), [i](auto b1, auto b2){
            return b1[i] < b2[i];
        });
    }

    /*kreiramo graf takav da su cvorovi kutije a usmerene grane 
    relacija da li moze jedna kutija da stane u drugu
    
    ovo su sve kutije u koje moze da stane kutija i ili j
    */
    vector<vector<int>> susedi(n);

    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            //ako i<j kutija i ce vrv moci da stane u kutiju j
            if(mozeLiStati(boxes[i],boxes[j]))
                susedi[i].push_back(j);
                /*
                A(2,3,5), B(3,4,6) → 2<3, 3<4, 5<6 → ✅
                Dodajemo granu: A → B
                */
        }
    }

    //vektor dinamickog programiranja, cuva najduzi lanac ugnjezdenih kutija koji zavrsava u kutiji i
    vector<int> rastojanje(n,1);
    for(int i=0; i<n; i++){
        for(int j:susedi[i]){ //prolazimo kroz sve kutije u koje mogu da stanu u kutiju i
            //Ako je lanac do j manji od lanca do i + 1, ažuriramo j.
            if(rastojanje[j]<rastojanje[i]+1)
                rastojanje[j]=rastojanje[i]+1;
                //rastojanje[sused] = max(rastojanje[sused], rastojanje[roditelj]+1)
        }
    }

    return *max_element(rastojanje.begin(),rastojanje.end());
}

int main(){

    int d, n; cin >> d >> n;

    vector<vector<int>> boxes(n, vector<int>(d));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            cin >> boxes[i][j];
        }
    }

    cout << lanac(boxes) << endl;

    return 0;
}