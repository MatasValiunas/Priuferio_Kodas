#include <array>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#define Random rand() % n + 1;

using namespace std;


struct Virsune {
    int sk;             // virsunes skaicius
    int br = 0;         // briaunu skaicius
};

void MedzioGeneravimas(vector<Virsune>&, vector<array<int, 2>>&, int);      // generuoja medi briaunu aibe
void PriuferioKodas(vector<array<int, 2>>&, vector<int>&);                  // briaunu aibe pavercia priuferio kodu
void IsvedimasBriaun(vector<array<int, 2>>&);                               // isveda briaunu aibe
void IsvedimasPriuf(vector<int>&);                                          // isveda Priuferio koda

int main(){
    vector<Virsune> Virs;                // virsuniu aibe
    vector<array<int, 2>> Briaun;        // briaunu aibe
    vector<int> Priuf;                   // Priuferio kodas
    int n;                               // medzio virsuniu skaicius

    cout << endl << "Medzio virsuniu skaicius (nuo 2): ";
    cin >> n;
    while (n < 2){
        cout << "Klaida! Skaicius turi buti nuo 2" << endl;
        cout << endl <<  "Medzio virsuniu skaicius (nuo 2): ";
        cin >> n;
    }


    MedzioGeneravimas(Virs, Briaun, n);
    IsvedimasBriaun(Briaun);
    PriuferioKodas(Briaun, Priuf);
    IsvedimasPriuf(Priuf);
}

void MedzioGeneravimas(vector<Virsune>& Virs, vector<array<int, 2>>& Briaun, int n){
    srand(time(NULL));

    Virs.resize(1);                           // sukuriama pirma virsune
    Virs[0].sk = Random;                      //

    for (int i=1; i<n; i++){
        int laik = Random;

        for (int j=0; j<Virs.size(); j++){          // jei naujai sugeneruotas 
            if (Virs[j].sk == laik){                // skaicius jau egzistuoja
                laik = Random;                      // virsuniu aibeje, tai
                j = -1;                             // generuojamas kitas skaicius
            }                                 
        }                                          

        Virs.resize(Virs.size()+1);                 // pridedama nauja virsune
        Virs[i].sk = laik;                          //

        do {                                                                                       // generuojamas naujas atsitiktinis sk., jei:
            laik = Random;                                                                         //  • virsune, prie kurios bandome prijungti, turi daugiau ne 2 vaikus
        } while (Virs[laik % Virs.size()].br > 2 || Virs[i].sk == Virs[laik % Virs.size()].sk);    //  • random virsune yra naujai sukurta virsune

        array<int, 2> A{Virs[i].sk, Virs[laik % Virs.size()].sk};
        Virs[i].br++;                                               
        Virs[laik % Virs.size()].br++;                              
        Briaun.push_back(A);                                        // prie briaunu aibes pridedama nauja briauna
    }
}

void PriuferioKodas(vector<array<int, 2>>& Briaun, vector<int>& Priuf){
    int virs;                        
    int brInd;
    int n = Briaun.size()+2;
    for (int i=1; i<n; i++){
        int brSk = 0;                           // virsunes briaunu skaicius

        if (Briaun.size() > 1){
            for (int j=0; j<Briaun.size(); j++){                    //
                if (Briaun[j][0] == i || Briaun[j][1] == i){        //
                    brSk++;                                         // randa kiek briaunu turi "i" 
                    brInd = j;                                      // virsune ir duoda jai gretima 
                    if (Briaun[j][0] == i)                          // virsune, kuria reikes ivesti
                        virs = Briaun[j][1];                        // i Priuferio koda
                    else if (Briaun[j][1] == i)                     // 
                        virs = Briaun[j][0];                        //
                }                                                 
            }         
        }                                           

        if (brSk == 1){                                         // jei virsune turi tik 1 briauna,
            Priuf.push_back(virs);                              // tai jai gretima virsune pridedama
            Briaun.erase(Briaun.begin()+brInd);                 // i priuferio koda, briauna istrinama
            i = 0;                                              // ir ciklas kartojamas is naujo
        }                                                      
    }
}

void IsvedimasBriaun(vector<array<int, 2>>& Briaun){
    cout << endl << "Briaunu aibe: ";
    for (int i=0; i<Briaun.size(); i++)
        cout << "{" << Briaun[i][0] << ", " << Briaun[i][1] << "} ";
}

void IsvedimasPriuf(vector<int>& Priuf){
    cout << endl << "Priuferio kodas: [";
    if (Priuf.size() != 0){
        for (int i=0; i<Priuf.size()-1; i++)
            cout << Priuf[i] << ", ";
        cout << Priuf.back();
    }
    cout << "]" << endl << endl;
}