#include <bits/stdc++.h>

using namespace std;

struct Point{
    int x,y;
};

long long orijentacija(Point A, Point B, Point C){
    return (long long)(B.x-A.x)*(C.y-A.y) - (long long)(B.y-A.y)*(C.x-A.x);
}

long long rastojanje(Point A, Point B){
    return (long long)(A.x-B.x)*(A.x-B.x) + (long long)(A.y-B.y)*(A.y-B.y);
}

bool uTrouglu(Point &A, Point &B, Point &C, Point &X){
    long long o1 = orijentacija(A,B,X);
    long long o2 = orijentacija(B,C,X);
    long long o3 = orijentacija(C,A,X);
    return o1>=0 && o2>=0 && o3>=0;
}

//formiranje konveksnog mnogougla: vector<Point> graham(vector<Point> &tacke, int n)

bool pripada(vector<Point> &tacke, Point &t){
    int n = tacke.size();
    if(orijentacija(tacke[0],tacke[1],t)<0)
        return false;
    if(orijentacija(tacke[0],tacke[n-1],t)>0)
        return false;
    int l=1, r=n-1;
    while(r-l>1){
        int s = (l+r)/2;
        if(orijentacija(tacke[0],tacke[s],t)>=0)
            l = s;
        else
            r = s;
    }
    return uTrouglu(tacke[0],tacke[l], tacke[l+1==n ? 1 : l+1],t);
}

int main(){
    int n,m;
    cin >> n;
    vector<Point> tacke(n);
    for(int i=0; i<n; i++)
        cin >> tacke[i].x >> tacke[i].y;
    cin >> m;
        Point queryPoint;
        while(m--){
            cin >> queryPoint.x >> queryPoint.y;
            //if(pripada(konveksniOmotac,queryPoint))
            if(pripada(tacke,queryPoint))
                cout << "da\n";
            else
                cout << "ne\n";
        }

    return 0;
}