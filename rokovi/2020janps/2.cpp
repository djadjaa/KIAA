#include <bits/stdc++.h>

using namespace std;

struct Tacka{
    int x,y;
};

int main(){

    int n;
    cin >> n;
    vector<Tacka> tacke(n);
    //postojanje tacke:
    set<pair<int,int>> S;

    for(int i=0; i<n; i++){
        double x,y;
        cin >> x >> y;
        tacke[i] = {(int)round(x*100),(int)round(y*100)};
        S.insert({(int)round(x*100),(int)round(y*100)});
    }

    int numtriang=0;

    //visine formirane sa x osom:
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n;j++){
            if(tacke[i].y == tacke[j].y){
                int x1 = tacke[i].x;
                int x2 = tacke[j].x;

                int y = tacke[i].y; //svejedno je koju koordinatu uzimamo

                double h = sqrt(3.0)/2.0 * abs(x2-x1);
                int h_i = round(h);

                //srediste
                int xm = (x1+x2)/2;

                //ako se novodobijene tacke nalaze u nizu
                if(S.count({xm,y+h_i}))
                    numtriang++;
                if(S.count({xm,y-h_i}))
                    numtriang++;
            }
        }
    }

    //isto i sa y osom
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(tacke[j].x == tacke[i].x){
                int y1 = tacke[i].y;
                int y2 = tacke[j].y;

                int x = tacke[j].x;

                double h = sqrt(3.0)/2.0 * abs(y2-y1);
                int h_i = round(h);

                //srediste
                int ym = (y1+y2)/2;

                if(S.count({x+h_i,ym}))
                    numtriang++;
                if(S.count({x-h_i,ym}))
                    numtriang++;
            }
        }
    }
    cout << numtriang << endl;
    return 0;
}