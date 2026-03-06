/*
na farmi postoje određeni stubovi, metalni i drveni. između dva metalna može stajati isključivo metalna ograda, između dva 
drvena može isključivo drvena ograda, a između dve različite je nebitno. izračunati minimalnu cenu ograđivanja maksimalne 
površine na farmi, ako su zadate koorde stubova, kao i cena drvene i metalne ograde

jedan nacin - algoritam konveksnog omotača
drugi nacin - primov/kruskalov alg:

-svaki stub je cvor u grafu i postoji ograda izmedju stubova koja varira od vrste stuba3
-cena za istu vrstu stuba je cena odgovarajue ograde * duzina segmenta
inace je manja cena
->Minimalna cena je mininalno povezujuce drvo
*/

#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <climits> 
#include <cmath> 
using namespace std;

struct Point{
    int x,y;
    char tip;
};

//determinanta:
int orijentacija(Point P, Point Q, Point R){
    return(Q.y-P.y)*(R.x-Q.x)-(Q.x-P.x)*(R.y-Q.y);
}

double rastojanje(Point P, Point Q){
    return sqrt((P.x-Q.x)*(P.x-Q.x)+(P.y-Q.y)*(P.y-Q.y));
}

//algoritam konveksnog omotača
vector<Point> sorting(vector<Point> farm){
    int n = farm.size();
    if(n<=1)
        return farm;
    //donje levo tacka 
    Point p0 = *min_element(farm.begin(),farm.end(),
    [](Point a, Point b){
        return make_pair(a.y,a.x) < make_pair(b.y,b.x);
    });
    //sortiranje radi formiranja konveksnog omotaca
    sort(farm.begin(),farm.end(),
    [&p0](const Point &a, const Point &b){
        int o = orijentacija(p0,a,b);
        if(o==0)
            return rastojanje(p0,a)<rastojanje(p0,b);
        return o>0;
    });
    //tzv stek za cuvanje tacaka koje potencijalno formiraju konveksni omotac
    vector<Point> konveksniOmotac;
    for(int i=0; i<n; i++){
        //dokle god pretposlednja, poslednja tacka i nova tacka formiraju orijentaciju < 0, izbacujemo poslednju tacku
        while (konveksniOmotac.size() > 1 && orijentacija(konveksniOmotac[konveksniOmotac.size()-2], konveksniOmotac.back(), farm[i])<=0)
            konveksniOmotac.pop_back();
        konveksniOmotac.push_back(farm[i]);
        
    }
    return konveksniOmotac;
}

int main(){

    vector<Point> farm = {{0,0,'M'}, {0,5,'D'}, {5,5,'M'}, {5,0,'D'}, {2,2,'M'}};

    double priceWood = 3;
    double priceMetal = 5;

    vector<Point> sorted = sorting(farm);

    for(auto s : sorted){
        cout << s.x << " " << s.y << " " << s.tip << endl;
    }

    double sum = 0;
    int i = 0;
    for(int i = 0; i < sorted.size(); i++){
        Point A = sorted[i];
        Point B = sorted[(i+1) % sorted.size()];

        double len = rastojanje(A,B);
        if(A.tip=='M' && B.tip=='M') 
            sum += priceMetal*len;
        else if(A.tip=='D' && B.tip=='D') 
            sum += priceWood*len;
        else 
            sum += min(priceWood, priceMetal)*len;
    }

    cout << sum << endl;

    return 0;
}