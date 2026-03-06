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

void prostMnogougao(vector<Point> &tacke, int n){
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
}

bool uMnogouglu(vector<Point> &tacke, Point &t){
    int n = tacke.size();
    bool pripada = false;
    for(int i=0; i<n; i++){
        int j = (i+1)%n;
        if(tacke[i].x < t.x && t.x > tacke[j].x &&
        orijentacija(tacke[i],tacke[j],t)<=0)
            pripada = !pripada;
    }
    return pripada;
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<Point> tacke(n);
    for(int i=0; i<n; i++)
        cin >> tacke[i].x >> tacke[i].y;
    prostMnogougao(tacke,n);
    Point queryPoint;
    while(m--){
        cin >> queryPoint.x >> queryPoint.y;
        if(uMnogouglu(tacke,queryPoint))
            cout << "da\n";
        else
            cout << "ne\n";
    }
    
    return 0;
}