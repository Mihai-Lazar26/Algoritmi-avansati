#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

ifstream fin("date.in");

int maxSum(int k, vector<int> &s){
    vector<int> v(k+1, 0);
    for(auto e : s){
        for(int g = k; g >= e; --g){
            v[g] = max(v[g], v[g-e] + e);
        }
    }
    return v[k];
}

int maxSum2(ifstream &fin){
    int k, e, res = 0;
    fin>>k;
    while(fin>>e){
        if(e + res <= k){
            res += e;
        }
        else if(res < e){
            res = e;
        }
    }
    return res;
}

int main()
{
    int k, x;
    vector<int> s;
    fin>>k;
    while(fin>>x){
        s.push_back(x);
    }
    for(auto e : s){
        cout<<e<<" ";
    }
    cout<<"\n";
    cout<<maxSum(k, s);

    return 0;
}
