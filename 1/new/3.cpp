/*
disjunktni skup cemo implementirati preko povezane liste
head ce pokazati na prvi objekat u listi
tail -||- poslednji -||-
objekat cini element skupa, pokazivac na sledeci elem i pokazivac na
skup u kom se nalazi

make_set - formiracemo novu povezanu listu koju cini samo taj objekat x
find_set - trazimo pokazivac na skup kome x pripada i vratimo elem
na koji pokazuje head
union - nadovezacemo dve povezane liste i time azurirati pokazivac druge liste/skupa
*/

#include <iostream>
#include <vector>

using namespace std;

int idstart = 0;

//najpre cemo ga definisati da bismo ga upotrebili u novoj strukturi
struct set;

struct element{
    char sadrzaj; //sta nam se nalazi u tom elementu
    struct set *set = nullptr; //pokazivac na skup u kom je element
    struct element *next = nullptr; //pokazivac na sledeci element
};

struct set{
    int id; //pretpostavljamo redni br skupa kog ga definise
    struct element *head = nullptr; //pokazivac na prvi elem skupa
    struct element *tail = nullptr; // -||- poslednji elem skupa
    //oni svi na pocetku ne pokazuju ni na sta
};

void make_set(struct element *x){
    auto new_set = new set(); //konstruktor
    new_set->id = idstart++;
    new_set->head = x; //njegov pocetni elem

    //element x je zvanicno u nasem novoformiranom skupu
    x->set = new_set;
}

struct element *find_set(struct element *x){
    return x->set->head; //kako smo rekli, najpre trazimo skup u kom se nalazi elem pa onda vracamo njegov prvi elem
    //x->set jer nam je tip fje struct element
}

void union_set(struct element *x, struct element *y){
    //najpre trazimo skupove preko parametara fja odnosno elemenata x i y
    auto x_set = find_set(x)->set;
    auto y_set = find_set(y)->set;

    //menjanje pokazivaca:
    x_set->tail->next = y_set->head; //pokazivac poslednjeg elementa skupa x na sledeci element bice prvi element skupa y
    x_set->tail = y_set->tail; //pokazivac na poslednji elem skupa x bice poslednji elem skupa y

    //ažuriranje pokazivača na skup svih elemenata povezane liste kojoj y pripada.
    auto y_head = y_set->head;
    while(y_head!=nullptr){
        y_head->set = x_set; //pokazivace sada  na skup x jer smo objedinili ta dva skupa
        y_head = y_head->next; //i idemo na sledeci elem
    }
}

void print_element(struct element *x){
    cout << x->sadrzaj << " ";
}

void print_set(struct set *s){
    cout << s->id << "[ ";
    auto head = s->head;
    while(head!=nullptr){
        print_element(head);
        head=head->next; //i idemo na sledeci elem;
    }
    cout << "]" << endl;
}

int main(){
    auto a = new element(); a->sadrzaj = 'a';
    auto b = new element(); b->sadrzaj = 'b';
    auto c = new element(); c->sadrzaj = 'c';
    auto d = new element(); d->sadrzaj = 'd';
    auto e = new element(); e->sadrzaj = 'e';
    auto f = new element(); f->sadrzaj = 'f';
    auto g = new element(); g->sadrzaj = 'g';

    make_set(a);
    make_set(b);
    make_set(c);
    make_set(d);
    make_set(e);
    make_set(f);
    make_set(g);

    union_set(a, b);
    union_set(a, c);
    union_set(d, e);
    union_set(d, f);
    union_set(d, g);

    print_set(a->set);
    print_set(f->set);

    union_set(a, f);

    print_set(a->set);

    delete find_set(a);

    delete a;
    delete b;
    delete c;
    delete d;
    delete e;
    delete f;
    delete g;

    return 0;
}