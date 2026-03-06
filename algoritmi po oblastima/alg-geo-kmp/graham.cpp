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

vector<Point> graham(vector<Point> &tacke, int n){
    if(n<3)
        return tacke;
    auto max = max_element(begin(tacke),end(tacke),[](Point A, Point B){
        return A.x < B.x || (A.x == B.x && A.y > B.y);
    });

    //auto it0 = find(begin(tacke),end(tacke),max);
    swap(*begin(tacke),*max);
    Point &p0 = tacke[0];

    sort(next(begin(tacke)), end(tacke), [&p0](Point &A, Point &B){
        long long o = orijentacija(p0,A,B);
        if(o==0)
            return rastojanje(p0,A) < rastojanje(p0,B);
        return o>0;
    });

    auto it = prev(end(tacke));
    while(orijentacija(*prev(it),*it,p0)==0)
        it = prev(it);
    reverse(it,end(tacke));

    vector<Point> convex;
    convex.push_back(p0);
    for(int i=1; i<tacke.size(); i++){
        while(convex.size()>1 && orijentacija(tacke[convex.size()-2], tacke[convex.size()-1], tacke[i])<=0)
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
    vector<Point> konveksniOmotac = graham(tacke,n);

    cout << konveksniOmotac.size() << endl;
    for(auto &p : konveksniOmotac)
        cout << p.x << ' ' << p.y << endl;


    return 0;
}