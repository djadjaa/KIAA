/*
na farmi postoje određeni stubovi, metalni i drveni. između dva metalna može stajati isključivo metalna ograda, između dva 
drvena može isključivo drvena ograda, a između dve različite je nebitno. izračunati minimalnu cenu ograđivanja maksimalne 
površine na farmi, ako su zadate koorde stubova, kao i cena drvene i metalne ograde
*/

#include <bits/stdc++.h>
using namespace std;

struct Point{
    int x,y;
    char type;
};

int orijentacija(Point A, Point B, Point C){
    return (B.y-A.y)*(C.x-B.x) - (B.x-A.x)*(C.y-B.y);
}

double rastojanje(Point A, Point B){
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

vector<Point> graham(vector<Point> &tacke, int n){
    if (n<3)
        return tacke;
    Point p0 = *min_element(tacke.begin(), tacke.end(), [](Point a, Point b){
        return make_pair(a.y,a.x)<make_pair(b.y,b.x);
    });
    sort(tacke.begin(), tacke.end(), [&p0](Point &a, Point &b){
        int val = orijentacija(p0,a,b);
        if(val==0)
            return rastojanje(p0,a) < rastojanje(p0,b);
        return val > 0;
    });
    vector<Point> konveksniOmotac;
    for(int i=0; i<n; i++){
        while(konveksniOmotac.size()>1 && orijentacija(konveksniOmotac[konveksniOmotac.size()-2],konveksniOmotac[konveksniOmotac.size()-1],tacke[i])<=0){
            konveksniOmotac.pop_back();
        }
        konveksniOmotac.push_back(tacke[i]);
    }
    return konveksniOmotac;
}

int main(){
    int n;
    cin >> n;
    vector<Point> tacke(n);
    for(int i=0; i<n; i++){
        cin >> tacke[i].x >> tacke[i].y >> tacke[i].type;
    }
    double drvocena, metalcena;
    cin >> drvocena >> metalcena;

    vector<Point> convex = graham(tacke,n);

    double res = 0;
    for(int i=0; i<convex.size(); i++){
        Point A = convex[i];
        Point B = convex[(i+1)%convex.size()];

        double len = rastojanje(A,B);
        if(A.type == 'M' && B.type == 'M')
            res += metalcena*len;
        else if(A.type == 'D' && B.type == 'D')
            res += drvocena*len;
        else
            res += min(drvocena,metalcena)*len;
    }


    cout << res << endl;
    return 0;
}