#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

// Acest mini-proiect in C ofera o metoda pentru calcularea rangului permutarilor atat ale literelor, cat si ale cifrelor. De asemenea, ilustreaza permutarea 
// anterioara, precum si urmatoarea din punct de vedere lexicografic ale unei multimi total ordonate S, verificand mai intai daca astfel de permutari exista.

// Exemplu:
// Introduceti elementele multimii S: a b c
// Introduceti o permutarea lui S: b c a
// Rang-ul permutarii: 3
// Permutarea precedenta este: b a c
// Permutarea urmatoare este: c a b


// Funtie pentru a transforma literele in numere (a=1,b=2...).
int LTN(char letter) {
    if (!islower(letter)) {
        letter = tolower(letter);
    }
    return letter - 'a' + 1;
}

// Functie pentru a transforma numerele in litere (1=a,2=b...).
char NTL(int number) {
    return number + 'a' - 1;
}

// Functie pentru a vedea daca numerele dintr-un vector sunt consecutive.
bool Consecutiv(vector<int> P) {
    for(int i=0; i< P.size() - 1; i++) {
        if(P[i]+1 != P[i+1]) {
            return 0;
        }
    }
    return 1;
}

// Calculeaza formula matematica factorial.
int Fact(int n) {
    int fc=1;
    for(int i=1; i<=n; i++){
        fc*=i;
    }
    return fc;
}

// Calculeaza formula matematica permutare.
int Perm(int a,int b) {
    return Fact(a)/Fact(a-b);
    }

// Calculeaza rang-ul unei anumite permutari.
int Rang(vector<int> S , vector<int> P) {
    int rk=0,i;
    if(Consecutiv(P) == 1) {return 0;}
    else {
        while(P.size() > 0) {


    for (int j = 0; j < S.size(); j++) {
        if (S[j] == P[0]) {
            i = j;
            break;
        }
    }

    rk += i * Perm(S.size()-1,P.size()-1);

    for (auto it = S.begin(); it != S.end(); ++it) {
        if (*it == P[0]) {
            S.erase(it);
            break;
            }
        }
    P.erase(P.begin());
    }
    }
    return rk;
}

// Calculeaza noua permutarea cu rangul nr care va fi stocata in Nw.
void Prece(int nr,vector<int> S, vector<int>& Nw) {
    int n = nr;
    int nS = S.size();

    while (nS > 0) {
        int i = (n / Perm(nS - 1, nS - 1));
        Nw.push_back(S[i]);
        n = n - (i * Perm(nS - 1, nS - 1));

        S.erase(S.begin() + i);
        nS--;
    }
}

// Verifica daca elementele din permutare exista in multimea de caractere.
int confirm(vector<auto> S,vector<auto> P) {
for(auto elem : S) {
    if(find(P.begin(),P.end(), elem) == P.end()) {
        return 0;
    }
}
return 1;
}

// Functia principala.
int main() {

// Definirea de variabile.
string input1, input2;
vector<char> S;
vector<char> P;
vector<int> S1;
vector<int> S2;
int Litera = 1;

cout << "Introduceti elementele multimii S: ";


getline(cin, input1);

for (char c : input1) {
    if (isalpha(c)) {
        S.push_back(c);
    } else if (isdigit(c)) {
        S1.push_back(c - '0');
    }
}

cout << "Introduceti o permutarea lui S: ";

getline(cin,input2);

for (char c : input2) {
    if (isalpha(c)) {
        P.push_back(c);
    } else if (isdigit(c)) {
        S2.push_back(c - '0');
    }
}

// Verificam daca au fost introduse permutari de litere sau cifre.
if (S.empty()) {
    Litera = 0;
}
else {Litera = 1;}


// Daca au fot introduse litere.
if (Litera == 1) {
    if (confirm(S,P) == 0) {
    cout << "Ati introdus elemente ce nu sunt in multime!" << endl;
    }

else {
    for(auto& c :S) {
        S1.push_back(LTN(c));
        }
    for(auto& c :P) {
        S2.push_back(LTN(c));
        }

// Afisam rang-ul permutarii date.
cout << "Rang-ul permutarii: " << Rang(S1,S2) << endl;

vector<int> Nw;
vector<char> Nwc;

vector<int> Nw1;
vector<char> Nwc1;

if(Rang(S1,S2) == 0) {
    cout << "Nu exista permutare precedenta!";
}

// Daca exista permutare precedenta o afisam.
else if (Rang(S1,S2) != 0) {
Prece(Rang(S1, S2)-1,S1,Nw);

for(auto& c :Nw) {
    Nwc.push_back(NTL(c));
    }

cout << "Permutarea precedenta este: ";

for(auto& nr : Nwc) {
    cout << nr << " ";
    }
}

if(Rang(S1,S2) == Perm(S.size(),S.size())-1) {
    cout << endl;
    cout << "Nu exista permutare urmatoare!";
}

// Daca exista permutare urmatoare o afisam.
else if (Rang(S1,S2) != Perm(S.size(),S.size())) {
Prece(Rang(S1, S2)+1,S1,Nw1);

for(auto& c :Nw1) {
    Nwc1.push_back(NTL(c));
    }

cout << endl;
cout << "Permutarea urmatoare este: ";

for(auto& nr : Nwc1) {
    cout << nr << " ";
    }
}
cout << endl;
    }
}


// Daca au fost introduse cifre.
if (Litera == 0) {
    if (confirm(S1,S2) == 0) {
    cout << "Ati introdus elemente ce nu sunt in multime!" << endl;
    }

// Afisam rang-ul permutarii date.
else {
    cout << "Rang-ul permutarii: " << Rang(S1,S2) << endl;

vector<int> Nw;
vector<int> Nw1;

if(Rang(S1,S2) == 0) {
    cout << "Nu exista permutare precedenta!";
}

// Daca exista permutare precedenta o afisam.
else if (Rang(S1,S2) != 0) {
Prece(Rang(S1, S2)-1,S1,Nw);

cout << "Permutarea precedenta este: ";

for(auto& nr : Nw) {
    cout << nr << " ";
    }
}

if(Rang(S1,S2) == Perm(S1.size(),S1.size())-1) {
    cout << endl;
    cout << "Nu exista permutare urmatoare!";
}

// Daca exista permutare urmatoare o afisam.
else if (Rang(S1,S2) != Perm(S1.size(),S1.size())) {
Prece(Rang(S1, S2)+1,S1,Nw1);

cout << endl;
cout << "Permutarea urmatoare este: ";

for(auto& nr : Nw1) {
    cout << nr << " ";
    }
}
cout << endl;
    }
    
}
return 0;
}
