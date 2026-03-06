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

bool uTrouglu(Point A, Point B, Point C, Point X){
    if(orijentacija(A,B,X)>=0 && orijentacija(B,C,X)>=0 && orijentacija(C,A,X)>=0)
        return true;
    if(orijentacija(A,B,X)<=0 && orijentacija(B,C,X)<=0 && orijentacija(C,A,X)<=0)
        return true;
    return false;
}

bool pripadaPravoj(Point A, Point B, Point C){
    return orijentacija(A,B,C)==0 &&
    min(A.x,B.x) <= C.x && C.x <= max(A.x,B.x) 
    && min(A.y,B.y) <= C.y && C.y <= max(A.y,B.y);
}

vector<Point> graham(vector<Point> &tacke, int n){
    if(n<3)
        return tacke;
        /*
    auto max = max_element(begin(tacke),end(tacke),[](Point A, Point B){
        return A.x < B.x || (A.x == B.x && A.y > B.y);
    });

    //auto it0 = find(begin(tacke),end(tacke),max);
    swap(*begin(tacke),*max);
    Point &p0 = tacke[0];*/

    auto it0 = min_element(tacke.begin(), tacke.end(),
    [](const Point &A, const Point &B){
        return A.y < B.y || (A.y == B.y && A.x < B.x);
    });
    swap(tacke[0], *it0);
    Point &p0 = tacke[0];

    sort(next(begin(tacke)), end(tacke), [&p0](Point &A, Point &B){
        long long o = orijentacija(p0,A,B);
        if(o==0)
            return rastojanje(p0,A) < rastojanje(p0,B);
        return o>0;
    });

    auto it = prev(end(tacke));
    while(it != begin(tacke) && orijentacija(*prev(it),*it,p0)==0)
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

bool pripada(vector<Point> &mnogougao, Point &t, int l, int d){
    if(d-l==1)
        return uTrouglu(mnogougao[0],mnogougao[l],mnogougao[d],t);
    int s = (l+d)/2;
    if(orijentacija(mnogougao[0],mnogougao[s],t)==0)
        return pripada(mnogougao,t,s,d);
    else
        return pripada(mnogougao,t,l,s);
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<Point> tacke(n);
    for(int i=0; i<n; i++)
        cin >> tacke[i].x >> tacke[i].y;
    vector<Point> konveksniOmotac = graham(tacke,n);
    
    cout << endl << konveksniOmotac.size() << endl;
    for(auto &p : konveksniOmotac)
        cout << p.x << ' ' << p.y << endl;
    cout << endl;
        Point queryPoint;
        while(m--){
            cin >> queryPoint.x >> queryPoint.y;
            //if(pripada(konveksniOmotac,queryPoint))
            if(pripada(konveksniOmotac,queryPoint,1,konveksniOmotac.size()-1))
                cout << "da\n";
            else
                cout << "ne\n";
        }

    return 0;
}