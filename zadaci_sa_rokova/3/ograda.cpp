#include <bits/stdc++.h>

using namespace std;

struct Point{
    int x,y;
};

Point izvornaTacka, najboljaTacka;
/*
int orijentacija(Point A,Point B, Point C){
    int val = (B.y - A.y)*(C.x - B.x) - (B.x - A.x)*(C.y-B.y);
    if(val==0)
        return 0;
    return(val > 0 ) ? 1 : -1;
}*/

int orijentacija(Point A, Point B, Point C) {
    return (B.y - A.y)*(C.x - B.x) - (B.x - A.x)*(C.y-B.y);
}

double dist(Point A, Point B){
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

/*
void graham(vector<Point> &tacke, int n){
    if(n<3)
        return;
    //sortiranje
    int l = 0;
    for(int i=1; i<n; i++){
        if(tacke[i].x < tacke[l].x)
            l = i;
    }
    int p=l,q;
    double najboljerastojanje = dist(izvornaTacka, tacke[p]);
    najboljaTacka = tacke[p];

    do{
        q = (p+1)%n;
        for(int i=0;i<n;i++)
            if(orijentacija(tacke[p], tacke[i], tacke[q])==-1){

            }
    }
}
    */
vector<Point> graham(vector<Point> &tacke, int n){
    if (n<3)
        return tacke;
    Point p0 = *min_element(tacke.begin(), tacke.end(), [](Point a, Point b){
        return make_pair(a.y,a.x)<make_pair(b.y,b.x);
    });
    sort(tacke.begin(), tacke.end(), [&p0](const Point &a, const Point &b){
        int val = orijentacija(p0,a,b);
        if(val==0)
            return dist(p0,a) < dist(p0,b);
        return val > 0;
    });
    vector<Point> konveksniOmotac;
    for(int i=0; i<n; i++){
        while(konveksniOmotac.size() > 1 && orijentacija(konveksniOmotac[konveksniOmotac.size()-2], konveksniOmotac[konveksniOmotac.size()-1], tacke[i])<=0)
            konveksniOmotac.pop_back();
        konveksniOmotac.push_back(tacke[i]);
    }
    return konveksniOmotac;
}


int main(){

    int N;
   cin >> N;

   vector<Point> points(N);

   for(int i = 0; i < N; i++)
      cin >> points[i].x >> points[i].y;
   
   cin >> izvornaTacka.x >> izvornaTacka.y;

    vector<Point> convex = graham(points, N);

    double najboljeRast = dist(izvornaTacka, convex[0]);
    najboljaTacka = convex[0];

    for(int i=1; i<convex.size(); i++){
        if(dist(convex[i],izvornaTacka)<najboljeRast){
            najboljeRast = dist(convex[i],izvornaTacka);
            najboljaTacka = convex[i];
        }
    }


   cout << najboljaTacka.x << " " << najboljaTacka.y << endl;

    return 0;
}