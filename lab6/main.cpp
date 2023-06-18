#include <iostream>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

typedef long long ll;
#define INF 1000000001
int SEED = time(NULL);

struct Point{
    ll x, y;
    Point(ll x = 0, ll y = 0){
        this->x = x;
        this->y = y;
    }
};

string orientare(Point a, Point b, Point c){
    ll res = a.x * b.y + b.x * c.y + c.x * a.y - a.x * c.y - b.x * a.y - c.x * b.y;
    if(res == 0) return "TOUCH";
    else if (res < 0) return "RIGHT";
    else return "LEFT";
}

bool isBetween(Point a, Point b, Point c){
    ll crossproduct = (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y);
    if (crossproduct != 0)
        return false;

    ll dotproduct = (c.x - a.x) * (b.x - a.x) + (c.y - a.y)*(b.y - a.y);
    if (dotproduct < 0)
        return false;

    ll squaredlengthba = (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y);
    if (dotproduct > squaredlengthba)
        return false;

    return true;
}


string whereInPolygon(vector<Point> &poligon, Point &p){
    int xrand = rand(), yrand = rand();
    Point a, b, ext(INF + xrand, INF + yrand);
    int n = poligon.size(), count = 0;
    for(int i = 0; i < n; ++i){
        a = poligon[i];
        b = poligon[(i+1)%n];
        string o1, o2, o3, o4;
        o1 = orientare(a, b, p);
        o2 = orientare(a, b, ext);
        o3 = orientare(ext, p, a);
        o4 = orientare(ext, p, b);
        bool ok = 0;
        if(o1 != o2 && o3 != o4){
            ok = 1;
        }
        if(o1 == "TOUCH" && isBetween(a, b, p)) return "BOUNDARY";
        if(o2 == "TOUCH" && isBetween(a, b, ext)) ok = 1;
        if(o3 == "TOUCH" && isBetween(ext, p, a)) ok = 1;
        if(o4 == "TOUCH" && isBetween(ext, p, b)) ok = 1;

        if(ok) ++count;

    }

    if(count % 2){
        return "INSIDE";
    }
    else{
        return "OUTSIDE";
    }
}

void problema1(){
    int n, m;
    vector<Point> poligon;
    cin>>n;
    for(int i = 0; i < n; ++i){
        ll x, y;
        cin>>x>>y;
        poligon.push_back(Point(x, y));
    }
    cin>>m;
    vector<string> sol;
    for(int i = 0; i < m; ++i){
        ll x, y;
        cin>>x>>y;
        Point a(x, y);
        sol.push_back(whereInPolygon(poligon, a));
    }

    for(string res : sol){
        cout<<res<<"\n";
    }
}

int findPointPoz(vector<Point> vec, Point pt){
    for(size_t i = 0; i < vec.size(); ++i){
        if(vec[i].x == pt.x && vec[i].y == pt.y){
            return i;
        }
    }
    return -1;
}

int nextPoz(int val, int n, int pas){
    int a = (val + pas) % n;
    if(a < 0) return n + a;
    return a;
}

void problema2(){
    int n;
    vector<Point> poligon;
    cin>>n;
    Point minX(INF, 0), maxX(-INF, 0), minY(0, INF), maxY(0, -INF);
    for(int i = 0; i < n; ++i){
        ll x, y;
        cin>>x>>y;
        Point pt(x, y);
        poligon.push_back(Point(x, y));
        if(minX.x > pt.x){
            minX.x = pt.x;
            minX.y = pt.y;
        }

        if(maxX.x < pt.x){
            maxX.x = pt.x;
            maxX.y = pt.y;
        }

        if(minY.y > pt.y){
            minY.x = pt.x;
            minY.y = pt.y;
        }

        if(maxY.y < pt.y){
            maxY.x = pt.x;
            maxY.y = pt.y;
        }
    }

    int primul, ultimul, a, b;

    primul = findPointPoz(poligon, minX);
    ultimul = findPointPoz(poligon, maxX);

    a = primul;
    b = ultimul;
    bool okX = true;
    while(a != b && okX){

        int curent = poligon[a].x, urmatorul = poligon[nextPoz(a, poligon.size(), 1)].x;

        if(urmatorul < curent) okX = false;

        a = nextPoz(a, poligon.size(), 1);
    }

    a = primul;
    b = ultimul;
    while(a != b && okX){

        int curent = poligon[a].x, urmatorul = poligon[nextPoz(a, poligon.size(), -1)].x;

        if(urmatorul < curent) okX = false;

        a = nextPoz(a, poligon.size(), -1);
    }

    primul = findPointPoz(poligon, minY);
    ultimul = findPointPoz(poligon, maxY);

    a = primul;
    b = ultimul;
    bool okY = true;
    while(a != b && okY){

        int curent = poligon[a].y, urmatorul = poligon[nextPoz(a, poligon.size(), -1)].y;

        if(urmatorul < curent) okY = false;

        a = nextPoz(a, poligon.size(), -1);
    }

    a = primul;
    b = ultimul;
    while(a != b && okY){

        int curent = poligon[a].y, urmatorul = poligon[nextPoz(a, poligon.size(), -1)].y;

        if(urmatorul < curent) okY = false;

        a = nextPoz(a, poligon.size(), -1);
    }


    if(okX){
        cout<<"YES\n";
    }
    else cout<<"NO\n";

    if(okY) cout<<"YES\n";
    else cout<<"NO\n";



}

int main()
{
    //srand(SEED);
    problema2();
    return 0;
}
