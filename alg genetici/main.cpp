#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <vector>
#include <string>
using namespace std;
ifstream fin("evolutie.in");
ofstream fout("evolutie.out");
int SEED = time(NULL);

struct Interval{
    int lo, hi;
    Interval(){
        this->lo = 0;
        this->hi = 1;
    }
    Interval(int lo, int hi){
        this->lo = lo;
        this->hi = hi;
    }
};

struct Ecuatie{
    //a * x^2 + b * x + c
    int a, b, c;
    Ecuatie(){
        this->a = 0;
        this->b = 0;
        this->c = 0;
    }
    Ecuatie(int a, int b, int c){
        this->a = a;
        this->b = b;
        this->c = c;
    }

    long double solEc(long double x) const{
        return x * x * this->a + x * this->b + this->c;
    }
};

class Cromozom{
private:
    int l, p;
    vector<bool> gene;
    Interval inter;

    void set_l(){
        this->l = ceil(log2((inter.hi - inter.lo) * pow(10, this->p)));
    }

    void generateRandCrom(){
        this->gene.clear();
        for(int i = 0; i < this->l; ++i){
            this->gene.push_back(rand()%2);
        }
    }

public:
    Cromozom(){
        int p = 0;
        int l = 1;
    }

    Cromozom(Interval inter, int p){
        this->inter = inter;
        this->p = p;
        this->set_l();
        this->generateRandCrom();
    }

    int get_l() const{
        return this->l;
    }

    int b10() const{
        int sum = 0;
        int p = 1;
        for(int i = this->l - 1; i >= 0; --i){
            sum += gene[i]*p;
            p *= 2;
        }

        return sum;
    }

    long double getValue() const{
        int b10 = this->b10();
        long double res = ((inter.hi - inter.lo) / (pow(2, l) - 1)) * b10 + inter.lo;

        return res;
    }

    string getCromozomString() const{
        string res;
        for(bool gena : gene){
            if(gena){
                res += '1';
            }
            else{
                res += '0';
            }
        }

        return res;
    }

    void pairCross(Cromozom &b, bool afiseaza = false){
        if(this->gene.size() != b.gene.size())
            return;

        int poz = rand() % this->gene.size() + 1;
        if(afiseaza){
            string str1 = this->getCromozomString(), str2 = b.getCromozomString();
            fout<<str1<<" "<<str2<<" punct "<<poz<<"\n";
        }
        for(int i = 0; i < poz; ++i){
            swap(this->gene[i], b.gene[i]);
        }
        if(afiseaza){
            string str1 = this->getCromozomString(), str2 = b.getCromozomString();
            fout<<"Rezultat "<<str1<<" "<<str2<<"\n";
        }
    }

    void mutatie(){
        int poz = rand() % this->gene.size();
        this->gene[poz] = !this->gene[poz];
    }
};

class Generatie{
private:
    int dim, precizie, etape;
    double crProb, mutProb;
    Ecuatie ec;
    Interval inter;
    vector<Cromozom> populatie;
    vector<long double> maxim, medie;

    vector<long double> fitness(bool afiseaza = false) const{
        vector<long double> fit, funcValues;
        long double sum = 0;
        for(int i = 0; i < this->dim; ++i){
            long double value = this->populatie[i].getValue();
            long double fValue = this->ec.solEc(value);
            funcValues.push_back(fValue);
            sum += fValue;
        }
        if(afiseaza) fout<<"\nProbabilitati selectie:\n";
        for(int i = 0; i < this->dim; ++i){
            long double x = funcValues[i] / sum;
            fit.push_back(x);
            if(afiseaza) fout<<"cromozom "<<i+1<<" probabilitate "<<fit[i]<<"\n";
        }
        return fit;
    }

    vector<long double> intervaleProbabilitati(const vector<long double> &fit, bool afiseaza = false) const{
        vector<long double> interval;
        interval.push_back(fit[0]);
        if(afiseaza){
            fout<<"\nIntervale probabilitati selectie:\n"<<0<<" "<<interval[0]<<" ";
        }
        for(int i = 1; i < this->dim; ++i){
            interval.push_back(interval[i-1] + fit[i]);
            if(afiseaza){
                fout<<interval[i]<<" ";
            }
        }
        if(afiseaza) fout<<"\n";

        return interval;
    }

    vector<Cromozom> selecteaza(const vector<long double> &intervalProb, bool afiseaza = false) const{
        vector<Cromozom> sol;
        for(int i = 1; i < this->dim; ++i){
            long double u = rand01();
            int st = 0, dr = this->dim - 1, indice;
            while(st <= dr){
                int mi = (st + dr) / 2;
                if(u <= intervalProb[mi]){
                    indice = mi;
                    dr = mi - 1;
                }
                else{
                    st = mi + 1;
                }
            }
            sol.push_back(this->populatie[indice]);
            if(afiseaza){
                fout<<"u = "<<u<<" selectam cromozomul "<< indice + 1<<"\n";
            }
        }

        return sol;
    }

    void incrucisare(vector<Cromozom> &vec, bool afisare = false) const{
        if(afisare)
            fout<<"\nProbabilitate de incrucisare este "<<this->crProb<<"\n";
        vector<int> selected;
        for(int i = 0; i < vec.size(); ++i){
            long double u = this->rand01();
            if(u < this->crProb){
                selected.push_back(i);
            }
            if(afisare){
                fout<<i+1<<": "<<vec[i].getCromozomString()<<" u= "<<u;
                if(u < this->crProb) fout<<"<"<<this->crProb<<" participa\n";
                else fout<<"\n";
            }
        }

        if(afisare){
            fout<<"\n";
        }

        if(selected.size() % 2 == 0){
            for(int i = 0; i < selected.size(); i+=2){
                if(afisare){
                    fout<<"Recombinare dintre cromozomul "<<selected[i]+1<<" cu cromozomul "<<selected[i+1]+1<<"\n";
                }
                vec[selected[i]].pairCross(vec[selected[i+1]], afisare);
            }
        }
        else{
            for(int i = 0; i < selected.size() - 1; i+=2){
                if(afisare){
                    fout<<"Recombinare dintre cromozomul "<<selected[i]+1<<" cu cromozomul "<<selected[i+1]+1<<"\n";
                }
                vec[selected[i]].pairCross(vec[selected[i+1]], afisare);
            }
            int a = selected.size() - 1;
            if(afisare){
                fout<<"Cromozomul "<< selected[a]+1 <<" nu are partener =(\n";
            }
        }
    }

    void mutatie(vector<Cromozom> &vec, bool afisare = false){
        vector<int> selected;
        for(int i = 0; i < vec.size(); ++i){
            long double u = this->rand01();
            if(u < this->mutProb){
                selected.push_back(i);
                vec[i].mutatie();
            }
        }
        if(afisare){
            fout<<"\nProbabilitate de mutatie pentru fiecare cromozom "<<this->mutProb<<"\n";
            if(selected.size()){
                fout<<"Au fost modificati cromozomii:\n";
                for(int i : selected){
                    fout<<i+1<<"\n";
                }
            }
            else{
                fout<<"Nu au fost modificati cromozomi\n";
            }
        }
    }

    Cromozom getElita(bool afisare = false) const{
        int i = 0, elitaidx = 1;
        Cromozom elita = this->populatie[0];
        long double elitaFit =this->ec.solEc(elita.getValue());
        for(Cromozom x : this->populatie){
            ++i;
            long double fval = this->ec.solEc(x.getValue());
            if(fval > elitaFit){
                elitaFit = fval;
                elita = x;
                elitaidx = i;
            }
        }
        if(afisare){
            fout<<"\nElita:\n"<<elitaidx<<": cromozom "<<elita.getCromozomString()<<" x= "<<elita.getValue()<<" f= "<<elitaFit<<"\n";
        }
        return elita;
    }

    void addBest(){
        long double maxim = this->ec.solEc(this->populatie[0].getValue()), sum = 0;
        for(auto cr : this->populatie){
            auto x = this->ec.solEc(cr.getValue());
            sum += x;
            if(maxim < x){
                maxim = x;
            }
        }
        this->maxim.push_back(maxim);
        this->medie.push_back(sum / this->dim);
    }

    void showBest() const{
        fout<<"\nEvolutia maximului:\n";
        for(int i = 0; i < this->maxim.size(); ++i){
            fout<<"max: "<<maxim[i]<<" medie: "<<medie[i]<<"\n";
        }
    }


    void populatieInitiala(){
        fout<<"Populatia initiala:\n";
        for(int i = 0; i < this->dim; ++i){
            this->populatie[i] = Cromozom(this->inter, this->precizie);
            string cromozom = this->populatie[i].getCromozomString();
            long double value = this->populatie[i].getValue();
            long double fValue = this->ec.solEc(value);
            fout<<i+1<<": "<<cromozom<<" x= "<<value<<" f= "<<fValue<<"\n";
        }
        this->addBest();
        vector<long double> fit = this->fitness(true);
        vector<long double> interval = this->intervaleProbabilitati(fit, true);
        vector<Cromozom> selectie = this->selecteaza(interval, true);
        fout<<"\nDupa selectie:\n";
        this->afiseaza(selectie);
        this->incrucisare(selectie, true);
        fout<<"\nDupa recombinare:\n";
        this->afiseaza(selectie);
        this->mutatie(selectie, true);
        fout<<"\nDupa mutatie:\n";
        this->afiseaza(selectie);
        Cromozom elita = this->getElita(true);
        selectie.push_back(elita);
        fout<<"\nDupa introducerea elitei:\n";
        this->afiseaza(selectie);
        this->populatie = selectie;
        this->urmatoarelePopulati();
    }

    void urmatoarelePopulati(){
        for(int i = 1; i < this->etape; ++i){
            this->addBest();
            vector<long double> fit = this->fitness();
            vector<long double> interval = this->intervaleProbabilitati(fit);
            vector<Cromozom> selectie = this->selecteaza(interval);
            this->incrucisare(selectie);
            this->mutatie(selectie);
            Cromozom elita = this->getElita();
            selectie.push_back(elita);
            this->populatie = selectie;
        }
        this->showBest();
    }

public:
    Generatie(int dim, Interval inter, Ecuatie ec, int precizie, double crProb, double mutProb, int etape) : populatie(dim){
        this->dim = dim;
        this->inter = inter;
        this->ec = ec;
        this->precizie = precizie;
        this->crProb = crProb;
        this->mutProb = mutProb;
        this->etape = etape;
        this->populatieInitiala();
    }

    static long double rand01(){
        long double res = static_cast <long double> (rand()) / static_cast <long double> (RAND_MAX);

        return res;
    }

    void afiseaza(const vector<Cromozom> &vec) const{
        for(int i = 0; i < vec.size(); ++i){
            string str = vec[i].getCromozomString();
            long double x = vec[i].getValue();
            long double f = ec.solEc(x);

            fout<<i+1<<": "<<str<<" x= "<<x<<" f= "<<f<<"\n";
        }
    }
};


int main()
{
    srand(SEED);
    int dim, precizie, etape, a, b, c1, c2, c3;
    double crossP, mutatieP;
    fin>>dim;
    fin>>a>>b;
    fin>>c1>>c2>>c3;
    fin>>precizie;
    fin>>crossP;
    fin>>mutatieP;
    fin>>etape;

    Generatie x(dim, Interval(a, b), Ecuatie(c1, c2, c3), precizie, crossP, mutatieP, etape);

}
