#include <fstream>
#include <vector>
#include <algorithm>

#define INPUT "U2.txt"
#define OUTPUT "U2rez.txt"

using namespace std;

class Katinas {
public:
    Katinas(string, int, int);
    string get_vardas();
    int get_minutes();
    int get_sekundes();
    int get_visas_laikas();
private:
    string vardas;
    int minutes;
    int sekundes;
};

int takeliu;
int* takelyje;
vector<Katinas> nugaletojai;
vector<Katinas>* takelyjeB;

void skaitymas();
void rusiavimas();
void rasymas();
bool greitesnis(Katinas a, Katinas b);

Katinas::Katinas(string v, int m, int s) {
    vardas = v;
    minutes = m;
    sekundes = s;
}

string Katinas::get_vardas() {
    return vardas;
}

int Katinas::get_minutes() {
    return minutes;
}

int Katinas::get_sekundes() {
    return sekundes;
}

int Katinas::get_visas_laikas() {
    return (minutes*60 + sekundes);
}

bool greitesnis(Katinas a, Katinas b) {
    return a.get_visas_laikas() < b.get_visas_laikas();
}

void skaitymas() {
    ifstream df;
    int i, j;
    char v[20];
    int m, s;

    df.open(INPUT);
    df >> takeliu;
    df.ignore();
    takelyje = new int[takeliu];
    takelyjeB = new vector<Katinas>[takeliu];
    for (i=0; i<takeliu; i++) {
        df >> takelyje[i];
        df.ignore();
        for (j=0; j<takelyje[i]; j++) {
            df.get(v, sizeof(v));
            df >> m >> s;
            df.ignore();
            takelyjeB[i].push_back(Katinas(v, m, s));
        }
    }
    df.close();
}

void rusiavimas() {
    int i, j;
    for (i=0; i<takeliu; i++) {
        sort(takelyjeB[i].begin(), takelyjeB[i].end(), greitesnis);
        for (j=0; j<takelyje[i]/2; j++) {
            nugaletojai.push_back(takelyjeB[i][j]);
        }
    }
    delete[] takelyjeB;
    sort(nugaletojai.begin(), nugaletojai.end(), greitesnis);
}

void rasymas() {
    ofstream rf;
    rf.open(OUTPUT);
    int i;
    Katinas* p;
    for (i=0; i<nugaletojai.size(); i++) {
        p = &nugaletojai[i];
        rf << p->get_vardas() << p->get_minutes() << ' ' << p->get_sekundes() << endl;
    }
    nugaletojai.clear();
    delete[] takelyje;
    rf.close();
}

int main() {
    skaitymas();
    rusiavimas();
    rasymas();

    return 0;
}
