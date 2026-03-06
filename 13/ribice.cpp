#include <bits/stdc++.h>

using namespace std;

struct Point{
    double x,y;
};

bool rayIntersect(Point &A, Point &B, Point P){
    if(P.y == A.y || P.y == B.y)
        P.y += 1.0E-9;
    if(P.y < A.y || P.y > B.y)
        return false;
    if(P.x > max(A.x,B.x))
        return false;
    if(P.x < min(A.x,B.x))
        return true;

    auto kAB = (B.y-A.y)/(B.x-A.x);
    auto kAP = (P.y-A.y)/(P.x-A.x);

    return kAP >= kAB;
}

bool rayCasting(vector<Point> &tacke, Point &P){
    int count =0;
    for(int i=0; i<tacke.size()-1; i++){
        if(tacke[i].y < tacke[i+1].y){
            if(rayIntersect(tacke[i],tacke[i+1],P))
                count++;
        }else{
            if(rayIntersect(tacke[i+1],tacke[i],P))
                count++;
        }
    }
    return count%2;
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
        cin >> upiti[i].x >> upiti[i].y;
    int res=0;
    for(int i=0; i<m; i++){
        if(!rayCasting(tacke,upiti[i]))
            res++;
    }
    cout << res << endl;
    return 0;
}