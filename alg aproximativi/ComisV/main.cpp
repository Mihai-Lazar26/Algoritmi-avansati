#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define N 1005

ifstream fin("date.in");
ofstream fout("date.out");

struct Punct{
    float x = 0, y = 0;
};
int inf = 1000000000;
int n;
Punct puncte[N];
float dist[N][N];
int sol[N];
bool viz[N];
float mini = inf;
int savedSol[N];

int next(int x){
    for(int i = x+1; i <= n; i++){
        if(!viz[i]){
            return i;
        }
    }

    return -1;
}
//Pt debug:
//void checkSol(){
//    float d = 0;
//    fout<<sol[1]<<" ";
//    for(int i = 2; i <= n; i++){
//        fout<<sol[i]<<" ";
//        int d1 = sol[i-1], d2 = sol[i];
//        d += dist[d1][d2];
//    }
//    d += dist[sol[n]][sol[1]];
//    fout<<sol[1]<<" D: "<<d<<"\n";
//    return;
//}

void checksol2(){
    float d = 0;
    for(int i = 2; i <=n; i++){
        int d1 = sol[i-1], d2 = sol[i];
        d += dist[d1][d2];
    }
    d += dist[sol[n]][sol[1]];

    if(d < mini){
        mini = d;
        for(int i = 1; i<=n; i++){
            savedSol[i] = sol[i];
        }
    }
    return;
}

void afisSol(){
    for(int i = 1; i <= n; i++){
        fout<<savedSol[i]<<" ";
    }
    fout<<savedSol[1]<<" D: "<<mini;
    return;
}


void solve(int start){
    sol[1] = start;
    viz[start] = true;
    int mini = inf;
    int i = 2;
    while(i > 1){
        viz[sol[i]] = false;
        int a = next(sol[i]);
        if(a != -1){
            sol[i] = a;
            viz[a] = true;
            if(i == n){
                checksol2();
            }
            else{
                i++;
            }
        }
        else{
            sol[i--] = 0;
        }
    }
    afisSol();
}

int main()
{

    fin>>n;
    for(int i = 1; i <= n; i++){
        fin>>puncte[i].x>>puncte[i].y;
    }

    for(int i = 1; i < n; i++){
        for(int j = i+1; j<= n; j++){
            dist[i][j] = dist[j][i] = sqrt(pow((puncte[j].x - puncte[i].x), 2) + pow((puncte[j].y - puncte[i].y),2));
        }
    }

//    for(int i = 1; i <= n; i++){
//        for(int j = 1; j<= n; j++){
//            fout<<dist[i][j]<<" ";
//        }
//        fout<<"\n";
//    }

    solve(1);


}
