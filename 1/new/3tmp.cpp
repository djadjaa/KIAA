#include <iostream>
#include <vector>

using namespace std;

int ID = 0;

struct set;

struct element {
    char id;
    struct set *set = nullptr;
    struct element *next = nullptr;
};

struct set {
    int id;
    struct element *head = nullptr;
    struct element *tail = nullptr;
};

void make_set(struct element *x) 
{
    auto new_set = new set();

    new_set->id = ID++;
    new_set->head = x;

    x->set = new_set;
}

struct element *find_set(struct element *x) 
{
    return x->set->head;
}

void union_set(struct element *x, struct element *y)
{
    auto x_set = find_set(x)->set;
    auto y_set = find_set(y)->set;

    x_set->tail->next = y_set->head;
    x_set->tail = y_set->tail;

    auto y_head = y_set->head;
    while (y_head != nullptr) {
        y_head->set = x_set;
        y_head = y_head->next;
    }
}

void print_element(struct element *x)
{
    cout << x->id << " ";
}

void print_set(struct set *s)
{
    cout << s->id << " [ ";
    auto head = s->head;
    while (head != nullptr) {
        print_element(head);
        head = head->next;
    }
    cout << "]" << endl;
}

int main(void)
{
    auto a = new element(); a->id = 'a';
    auto b = new element(); b->id = 'b';
    auto c = new element(); c->id = 'c';
    auto d = new element(); d->id = 'd';
    auto e = new element(); e->id = 'e';
    auto f = new element(); f->id = 'f';
    auto g = new element(); g->id = 'g';

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