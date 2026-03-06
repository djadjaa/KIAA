#include <bits/stdc++.h>

using namespace std;

struct Point{
    double x,y;
    int cena;
};
//da li postoji presecna tacka na pravoj AB
bool rayIntersect(Point &A, Point &B, Point P){
    if(P.y == A.y || P.y == B.y)
        P.y += 1.0E-9; //ako su jednake y koord, pomeri dovoljno koordinatu tacke P
    //van opsega u x i y osi
    if(P.y < A.y || P.y > B.y)
        return false;
    if(P.x > max(A.x,B.x))
        return false;
    //x∈[min(x1​,x2​),max(x1​,x2​)] i y∈[min(y1​,y2​),max(y1​,y2​)] !!!
    if(P.x < min(A.x, B.x))
        return true;
    //provera koeficijenta preseka
    auto kAB = (B.y-A.y)/(B.x-A.x);
    auto kAP = (P.y-A.y)/(P.x-A.x);
    return kAP>=kAB;
}

//ako je broj presecnih tacaka paran, tacka pripada unutrasnjosti mnogougla

bool rayCasting(vector<Point> &tacke, Point &P){
    int num=0;
    for(int i=0; i<tacke.size()-1; i++){
        //redosled tacaka u zavisnosti od y koordinate
        if(tacke[i].y < tacke[i+1].y){
            if(rayIntersect(tacke[i],tacke[i+1],P))
                num++;
        }else{
            if(rayIntersect(tacke[i+1],tacke[i],P))
                num++;
        }
    }
    return num%2;
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<Point> tacke(n+1);
    for(int i=0; i<n; i++)
        cin >> tacke[i].x >> tacke[i].y;
    tacke[n]=tacke[0];

    vector<Point> upiti(m);
    for(int i=0; i<m; i++)
        cin >> upiti[i].x >> upiti[i].y >> upiti[i].cena;
    int res = 0;
    for(int i=0; i<m; i++){
        if(rayCasting(tacke,upiti[i]))
            res += upiti[i].cena;
    }
    cout << res << endl;
}