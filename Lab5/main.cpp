#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
#define INF 1000000001

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

void problema1(){
    vector<string> vec;
    int t;
    Point p, q, r;
    cin>>t;
    for(int i = 1; i <= t; ++i){
        cin>>p.x>>p.y>>q.x>>q.y>>r.x>>r.y;
        vec.push_back(orientare(p, q, r));
    }
    for(string val : vec){
        cout<<val<<"\n";
    }
}

void problema2(){
    int n, l, r, t;
    l = r = t = 0;
    Point first, a, b, c;
    cin>>n;
    cin>>a.x>>a.y>>b.x>>b.y;
    first.x = a.x;
    first.y = a.y;
    for(int i = 3; i <= n; ++i){
        cin>>c.x>>c.y;

        string viraj = orientare(a, b, c);

        if(viraj == "RIGHT") ++r;
        else if (viraj == "LEFT") ++l;
        else ++t;

        a.x = b.x;
        a.y = b.y;
        b.x = c.x;
        b.y = c.y;
    }

    string viraj = orientare(a, b, first);
    if(viraj == "RIGHT") ++r;
    else if (viraj == "LEFT") ++l;
    else ++t;

    cout<<l<<' '<<r<<' '<<t;
}

void problema3(){
    int n;
    vector<Point> puncte;
    cin>>n;
    for(int i = 0; i < n; ++i){
        ll x, y;
        cin>>x>>y;
        puncte.push_back(Point(x, y));
        while(puncte.size() > 2 &&
              orientare(puncte[puncte.size()-3], puncte[puncte.size()-2], puncte[puncte.size()-1]) == "RIGHT"){
            puncte.erase(puncte.end()-2);
        }
    }
    if(puncte.size() > 2 &&
       orientare(puncte[puncte.size()-1], puncte[0], puncte[1]) == "RIGHT"){
        puncte.erase(puncte.begin());
       }
    cout<<'\n';
    for(Point p : puncte){
        cout<<p.x<<" "<<p.y<<"\n";
    }
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
    Point a, b, ext(INF, p.y);
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

void problema4(){
    int n, m;
    vector<Point> poligon;
    vector<string> sol;
    cin>>n;
    for(int i = 0; i < n; ++i){
        ll x, y;
        cin>>x>>y;
        poligon.push_back(Point(x, y));
    }
    cin>>m;
    for(int i = 0; i < m; ++i){
        Point p;
        cin>>p.x>>p.y;
        sol.push_back(whereInPolygon(poligon, p));
    }

    for(string val : sol){
        cout<<val<<"\n";
    }
}

int main()
{
//    problema1();
//    problema2();
//    problema3();
//    problema4();
    return 0;
}
