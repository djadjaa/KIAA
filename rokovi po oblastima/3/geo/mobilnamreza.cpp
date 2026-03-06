//
#include <bits/stdc++.h>

using namespace std;

struct Point{
    double x,y;
    int cena;
};

long long orijentacija(Point A, Point B, Point C) {
    return 1LL * (B.x - A.x) * (C.y - A.y) - 1LL * (B.y - A.y) * (C.x - A.x);
}

long long rastojanje(Point A, Point B) {
    long long dx = A.x - B.x;
    long long dy = A.y - B.y;
    return dx*dx + dy*dy;
}


//konstrukcija prostog mnogougla:
void prostMnogougao(vector<Point>& tacke){
    auto max = max_element(begin(tacke),end(tacke),[](const Point &a, const Point &b){
        return a.x < b.x || (a.x==b.x && a.y > b.y);
    });

    //zamena prve tacke
    swap(*begin(tacke),*max);
    const Point& p0 = tacke[0];

    //sortiranje ostatka
    sort(next(begin(tacke)),end(tacke),[&p0](const Point &a, const Point &b){
        long long o = orijentacija(p0,a,b);
        if(o==0)
            return rastojanje(p0,a) <= rastojanje(p0,b);
        return o>0;
    });

    //obrtanje kolinearnih tacaka
    auto it = prev(end(tacke));
    while(orijentacija(*prev(it),*it,p0)==0)
        it = prev(it);
    reverse(it,end(tacke));
}

//pripadnost tacaka u prostom mnogouglu
bool tackaUMnogouglu(vector<Point>& tacke, Point &P){
    int n = tacke.size();
    bool pripada=false;
    for(int i=0; i<n; i++){
        int j = (i+1)%n;
        if(tacke[i].x > tacke[j].x)
            swap(tacke[i],tacke[j]);
        if(tacke[i].x < P.x && P.x < tacke[j].x && 
            (tacke[i].y-P.y)*(tacke[j].x-tacke[i].x)<=(tacke[j].y-tacke[i].y)*(tacke[i].x-P.x))
            pripada = !pripada;
    }
    return pripada;
}

int main(){
    int n,q;
    cin >> n >> q;
    vector<Point> tacke(n);
    for(int i=0; i<n; i++)
        cin >> tacke[i].x >> tacke[i].y;
    prostMnogougao(tacke);
    vector<Point> query(q);
    for(int i=0; i<q; i++)
        cin >> query[i].x >> query[i].y >> query[i].cena;
    int uk=0;
    for(int i=0; i<q; i++){
        if(tackaUMnogouglu(tacke,query[i]))
            uk += query[i].cena;
    }
    cout << uk << endl;

    return 0;
}