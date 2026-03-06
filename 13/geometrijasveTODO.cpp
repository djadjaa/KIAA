#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using point = pair<int, int>; 

struct Point {
    double x;
    double y;
};

//vektor:
point vec(point a, point b) {
	return {b.first - a.first, b.second - a.second};
}

//skalarni proizvod
int dot(point u, point v) {
	return u.first * v.first + u.second * v.second;
}

//vektorski proizvod (determinanta)
int cross(point u, point v) {
	return u.first * v.second - u.second * v.first;
}

//orijentacija vektora (isto preko determinante)
int orient(point a, point b, point c) {
	return cross(vec(a, b), vec(a, c));
}

//kolinearnost vektora
bool colinear(point a, point b, point c) {
	return orient(a, b, c) == 0;
}

// proverava da li je tacka u trouglu ili na stranici trougla
bool inTriangle(point a, point b, point c, point x) {
	if(orient(a, b, x) >= 0 && orient(b, c, x) >= 0 && orient(c, a, x) >= 0)
		return true;
	if(orient(a, b, x) <= 0 && orient(b, c, x) <= 0 && orient(c, a, x) <= 0)
		return true;
	return false;
}

// proverava konveksnost mnogougla
bool checkConvex(vector<point>& p) {
	bool pos = false, neg = false; //pozitivna i negativna orijentacija
	for(int i = 0; i < p.size(); i++) {
        //ciklicno se petlja vrti oko mnogougla (zadnja tačka se spaja sa prvom)
		int j = (i + 1) % p.size();
		int k = (i + 2) % p.size();
		if(orient(p[i], p[j], p[k]) > 0)
			pos = true;
		if(orient(p[i], p[j], p[k]) < 0)
			neg = true;
	}
    /*
    Ako postoji i levi i desni zavoj → mnogougao je nekonveksan (ima rupu)
    inace je konveksan
    */
	return !(pos && neg);
}

// pretpostavka je da nema trojki kolinearnih tacaka
/*
priprema za Grahamov algoritam:
nalazi tacku sa najmanjom y koordinatom i postavlja je na pocetak
primenom orijentacije sortira sve ostale tacke po uglu u odnosu na pocetnu
*/
vector<point> makeSimple(vector<point> pts) {
	vector<point> p = pts;
	swap(p[0], *min_element(begin(p), end(p)));
	sort(begin(p) + 1, end(p),
			[&](point a, point b) {
				return orient(p[0], a, b) > 0;
			});
	return p;
}

// pretpostavka je da nema trojki kolinearnih tacaka
/*
gradi konveksni omotac omotavajuci tacke
ide redom iterativno od najlevo dole tacke i bira sledecu
tacku koja formira levi zavoj sve dok ne stignemo do pocetne tacke ponovo

vector<int> jarvisHull(vector<point>& p) {
	vector<int> hull;

	int t = min_element(begin(p), end(p)) - begin(p);
	do {
		hull.push_back(t);
		int nt = (t + 1) % p.size(); // treba uzeti bilo koju tacku razlicitu od t
		for(int i = 0; i < p.size(); i++)
			if(orient(p[t], p[i], p[nt]) > 0)
				nt = i;
		t = nt;
	} while(t != hull[0]);

	return hull;
}
*/

// pretpostavka je da nema trojki kolinearnih tacaka
/*efikasnija od jarvisovog algoritma
sortira na osnovu pocetne tacke i izbacuje poslednju tacku ukoliko 
je orijentacija trougla ove tri tacke negativna
*/
vector<int> grahamHull(vector<point>& p) {
	swap(p[0], *min_element(begin(p), end(p)));
	sort(begin(p) + 1, end(p),
			[&](point a, point b) {
				return orient(p[0], a, b) > 0;
			});

	vector<int> hull = {0};
	for(int i = 1; i < p.size(); i++) {
		while(hull.size() > 1 &&
					orient(p[hull[hull.size() - 2]],
					       p[hull[hull.size() - 1]],
								 p[i]) < 0)
			hull.pop_back();

		hull.push_back(i);
	}

	return hull;
}

// pretpostavka je da su tacke konveksnog mnogougla p
// orijentisane u pozitivnom matematickom smeru

/*
primena binarne pretrage da bi se pronaslo
u kom trouglu se tacka nalazi(pocetna tacka i dva suseda trenutne tacke)
*/
bool inConvex(point t, vector<point>& p) {
	auto it = lower_bound(begin(p) + 1, end(p), t,
	                      [&](point a, point b) {
													return orient(p[0], a, b) > 0;
												});
	if(it == end(p))
		return false;
	int i = it - begin(p); //indeks
	return inTriangle(p[0], p[i - 1], p[i], t);
}

//povrsina trougla
float orientedArea(point a, point b, point c) {
	return orient(a, b, c) * 0.5f;
}

// radi za bilo koji prost mnogougao; povrsina mnogougla
float orientedArea(vector<point>& p) {
	float a = 0;
	for(int i = 2; i < p.size(); i++)
		a += orientedArea(p[0], p[i - 1], p[i]);
	return a;
}



/*
if orijentacija(p1,q1,p2)!=orijentacija(p1,q1,q2) && orijentacija(p2,q2,p1)!=orijentacija(p2,q2,q1) return true

if orijentacija(p1,p2,q1)==0 && pripadaduzi(p1,q1,p2) return true
                p1,q2,q1 -||-
                p2,p1,q2 -||-
                p2,q1,q2 -||-
*/





//funkcije za proveru da li se tacka nalazi u prostom mnogouglu

//da li horizontalni znak iz tacke P udesno sece iviu AB
bool ray_intersect(const Point& A, const Point &B, Point P)
{
    if (P.y == A.y || P.y == B.y) {
        P.y += 1.0E-9; //pomera tacku ako je na istom y niv
    }
    
    if (P.y < A.y || P.y > B.y) {
        return false;
    }

    if (P.x > max(A.x, B.x)) {
        return false;
    }

    if (P.x < min(A.x, B.x)) {
        return true;
    }
//y = kx+n (ako je ispod tacka, nagib ce sig biti manji!!)
//AB -> k
//AP -> k 
    const auto k_AB = (B.y - A.y) / (B.x - A.x);
    const auto k_AP = (P.y - A.y) / (P.x - A.x);

    return k_AP >= k_AB;
}

bool ray_casting(const vector<Point> &poly, const Point &P)
{
    int count = 0;

    for (int i = 0; i < poly.size() - 1; i++) {
        const auto &A = poly[i];
        const auto &B = poly[i + 1];

        if (A.y < B.y) {
            if (ray_intersect(A, B, P)) {
                count++;
            }
        } else {
            if (ray_intersect(B, A, P)) {
                count++;
            }
        }
    }

    return count % 2;
}


double ugao(double x0,double y0, double x, double y){
    return atan2(y-y0,x-x0);
}

bool kolinearne(t1,t2,t3){
    return abs(ugao(t1.x,t1.y,t2.x,t2.y)-ugao(t1.x,t1.y,t3.x,t3.y))<eps;
}

/*
void prostMnogougao(vector tacke){
    int i=2;
    while(kolinearne(tacke0,tacke1,tacke_i))
        i++;
    int teziste(tacke1.x+tacke2.x+tacke_i.x/3)//analogno za y

    sort(begin.tacke, end.tacke, [teziste](t1,t2){
    
        ugao1 = ugao(teziste.x, teziste.y, t1.x, t1.y)
            2 =                             t2.x,t2.y
        
        if(ugao1<ugao2-eps)
            return true;
        if(ugao2<ugao1-eps)
            return false;
        return(rastojanje(teziste.x,teziste.y,t1.x,t1.y)<rast(teziste.x,teziste.y,t2.x,t2.y));
    })
}

void prostMnogougao(vector tacke){
    auto max = max_elem(begin.tacke, end.tacke, [](t1,t2){
           return t1.x < t2.x || (t1.x == t2.x && t1.y == t2.y)

});
   swap(*begin(tacke), *max);
   t0 = tacke[0];
    sort(next(begin(tacke)),end(tacke), [t0](t1,t2){
        o=orijentacija(t0,t1,t2)
        if(o==0)
            return rast(t0,t1) <= rast(t0,t2)
          return o>0

})

//obrni niz
auto it = prev(end(tacke));
while(orijentacija(*prev(it),*it,t0)==0)
    it = prev(it);
reverse(it,end.tacke);
}

*/




































