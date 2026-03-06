#include <bits/stdc++.h>

using namespace std;

struct Point{
    double x,y;
};

int orijentacija(Point A, Point B, Point C){
    return (B.x-A.x)*(C.y-A.y) - (B.y-A.y)*(C.x-A.x);
}
double rastojanje(Point A, Point B){
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

vector<Point> graham(vector<Point>&tacke, int n){
    if(n<3)
        return tacke;
    Point p0 = *min_element(tacke.begin(), tacke.end(), [](Point a, Point b){
        return make_pair(a.y,b.y) < make_pair(a.y,b.x);
    });
    sort(tacke.begin(), tacke.end(), [&p0](Point &a, Point &b){
        int val = orijentacija(p0,a,b);
        if(val==0)
            return rastojanje(p0,a) < rastojanje(p0,b);
        return val > 0;
    });
    vector<Point> convex;
    for(int i=0; i<n; i++){
        while(convex.size() > 1 && orijentacija(convex[convex.size()-2], convex[convex.size()-1], tacke[i])<=0)
            convex.pop_back();
        convex.push_back(tacke[i]);
    }
    return convex;
}

int main(){
    int n;
    cin >> n;
    vector<Point> tacke(n);
    for(int i=0; i<n; i++)
        cin >> tacke[i].x >> tacke[i].y;
    vector<Point> convex = graham(tacke, n);
    double res = 0.0;
    for(int i=0; i<convex.size(); i++){
        Point A = convex[i];
        Point B = convex[(i+1)%convex.size()];
        res += rastojanje(A,B);
    }
    cout << res << endl;
    return 0;
}