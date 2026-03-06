/*

*/
#include <bits/stdc++.h> 
using namespace std;

struct Point{
    double x,y;
    double ugao;
    double rastojanje;
};

int main(){

    int n;
    cin >> n;
    vector<Point>points(n);
    for(int i=0; i<n; i++){
        cin >> points[i].x >> points[i].y;
        //od koordinatnog pocetka odredjujemo i ugao i rastojanje, s tim da nam je rastojanje vektor pocetnog pravca
        points[i].ugao = atan2(points[i].y, points[i].x);
        points[i].rastojanje = sqrt(points[i].x*points[i].x +points[i].y*points[i].y);
    }

    //sortiranje tacaka:
    sort(points.begin(),points.end(), [](const Point &a, const Point &b){
        if(a.ugao!=b.ugao)
            return a.ugao < b.ugao;
        return a.rastojanje < b.rastojanje;
    });

    for(auto &p:points){
        cout << fixed << setprecision(1) << p.x << ' ' << p.y << endl;
    }
    return 0;
}