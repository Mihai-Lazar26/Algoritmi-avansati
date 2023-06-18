#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

#define INF 100000000000

class semiPlan{
public:
    double a, b, c;
    semiPlan(double a = 0, double b = 0, double c = 0){
        this->a = a;
        this->b = b;
        this->c = c;
    }
    string getAxa(){
        if(this->a == 0)
            return "y";
        if(this->b == 0)
            return "x";
        return "";
    }

    string getSemn(){
        string axa = this->getAxa();
        if(axa == "x"){
            //ax + c <= 0
            if(this->a < 0) return ">=";
            return "<=";
        }

        else{
            //by + c <= 0
            if(this->b < 0) return ">=";
            return "<=";
        }
    }

    double getVal(){
        string axa = this->getAxa();
        string semn = this->getSemn();
        double val = 0;

        if(axa == "x"){
            //ax + c <= 0
            if(semn == "<="){
                //ax <= -c
                //x <= -c/a
                val = (-this->c)/this->a;
            }
            else{
                //-ax >= c
                //x >= c/(-a)

                val = this->c/(-this->a);
            }
        }
        else{
            //by + c <= 0
            if(semn == "<="){
                //by <= -c
                //y <= -c/b
                val = (-this->c)/this->b;
            }
            else{
                //-by >= c
                //y >= c/(-b)
                val = this->c/(-this->b);
            }
        }
        return val;
    }
};

bool egale(double a, double b){
    return abs(a - b) <= 0.00000001;
}

string checkSemiplane(const vector<semiPlan> &semiplane){
    double minX = -INF, minY = -INF, maxX = INF, maxY = INF;
    for(semiPlan semiplan : semiplane){
        string axa = semiplan.getAxa();
        string semn = semiplan.getSemn();
        double val = semiplan.getVal();

//        cout<<axa<<" "<<semn<<" "<<val<<"\n";

        if(axa == "x"){
            if(semn == "<="){
                maxX = min(maxX, val);
            }
            else{
                minX = max(minX, val);
            }
        }
        else{
            if(semn == "<="){
                maxY = min(maxY, val);
            }
            else{
                minY = max(minY, val);
            }
        }
    }
//    cout<<"minX: "<<minX<<" maxX: "<<maxX<<" minY: "<<minY<<" maxY: "<<maxY<<"\n";
    if((minX <= maxX ) && (minY <= maxY)){

        if(minX == -INF || minY == -INF || maxX == INF || maxY == INF){
            return "UNBOUNDED";
        }
        else{
            return "BOUNDED";
        }
    }
    else{
        return "VOID";
    }
}

void problema1(){
    int n;
    cin>>n;
    vector<semiPlan> semiplane;
    for(int i = 0; i < n; ++i){
        int a, b, c;
        cin>>a>>b>>c;
        semiplane.push_back(semiPlan(a, b, c));
    }
    string sol = checkSemiplane(semiplane);
    cout<<sol;
}

//pentru problema 2 setprecision(6)

vector<semiPlan> getSemiplaneValide(const vector<semiPlan> &semiplane, double x, double y){
    vector<semiPlan> sol;
    for(semiPlan semiplan : semiplane){
        string axa = semiplan.getAxa();
        string semn = semiplan.getSemn();
        double val = semiplan.getVal();
        if(axa == "x"){
            if(semn == "<=" && x < val){
                sol.push_back(semiplan);
            }
            else if (semn == ">=" && x > val){
                sol.push_back(semiplan);
            }
        }
        else{
            if(semn == "<=" && y < val){
                sol.push_back(semiplan);
            }
            else if (semn == ">=" && y > val){
                sol.push_back(semiplan);
            }
        }
    }
    return sol;
}

double distEuclida(double x1, double y1, double x2, double y2){
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2) * (y1 - y2));
}

double ariaDreptunghi(double x1, double y1, double x2, double y2){
    //(x1, y2)----------------------(x2, y2)//
    //                                      //
    //                                      //
    //                                      //
    //(x1, y1)----------------------(x2, y1)//
    return distEuclida(x1, y2, x2, y2) * distEuclida(x1, y2, x1, y1);
}

pair<string, double> checkSemiplane2(const vector<semiPlan> &semiplane){
    double minX = -INF, minY = -INF, maxX = INF, maxY = INF;
    for(semiPlan semiplan : semiplane){
        string axa = semiplan.getAxa();
        string semn = semiplan.getSemn();
        double val = semiplan.getVal();

//        cout<<axa<<" "<<semn<<" "<<val<<"\n";


        if(axa == "x"){
            if(semn == "<="){
                maxX = min(maxX, val);
            }
            else{
                minX = max(minX, val);
            }
        }
        else{
            if(semn == "<="){
                maxY = min(maxY, val);
            }
            else{
                minY = max(minY, val);
            }
        }
    }
//    cout<<"minX: "<<minX<<" maxX: "<<maxX<<" minY: "<<minY<<" maxY: "<<maxY<<"\n";
    if((minX <= maxX ) && (minY <= maxY)){

        if(minX == -INF || minY == -INF || maxX == INF || maxY == INF){
            return make_pair("NO", -1);
        }
        else{
            double arie = ariaDreptunghi(minX, minY, maxX, maxY);
            return make_pair("YES", arie);
//            cout<<"YES\n";
//            double arie = ariaDreptunghi(minX, minY, maxX, maxY);
//            std::cout << std::fixed << std::showpoint;
//            std::cout << std::setprecision(6);
//            cout<<arie<<"\n";
        }
    }
    else{
        return make_pair("NO", -1);
    }
}


void problema2(){
    int n;
    cin>>n;
    vector<semiPlan> semiplane;
    for(int i = 0; i < n; ++i){
        int a, b, c;
        cin>>a>>b>>c;
        semiplane.push_back(semiPlan(a, b, c));
    }
    int m;
    cin>>m;
    vector<pair<string, double>> soluti;
    for(int i = 0; i < m; ++i){
        double x, y;
        cin>>x>>y;
        vector<semiPlan> spValide = getSemiplaneValide(semiplane, x, y);
        soluti.push_back(checkSemiplane2(spValide));
    }
    for(pair<string, double> val : soluti){
        if(val.first == "YES"){
            std::cout << std::fixed << std::showpoint;
            std::cout << std::setprecision(6);
            cout<<"YES\n"<<val.second<<"\n";
        }
        else{
            cout<<"NO\n";
        }
    }
}

int main()
{
    problema2();
    return 0;
}
