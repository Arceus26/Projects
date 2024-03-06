#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdlib>

using namespace std;

class produs {
    int pret;
    string nume;
    int stoc;
    string caracteristici;
    long int cod_bare;

public:
    produs(int cod_bare = 0, string nume = "", int stoc = 0, int pret = 0, string caracteristici = "") {
        this->pret = pret;
        this->nume = nume;
        this->stoc = stoc;
        this->caracteristici = caracteristici;
        this->cod_bare = cod_bare;
    }

    produs(const produs& p) {
        this->pret = p.pret;
        this->nume = p.nume;
        this->stoc = p.stoc;
        this->caracteristici = p.caracteristici;
        this->cod_bare = p.cod_bare;
    }

    produs(produs& p) {
        this->pret = std::move(p.pret);
        this->nume = std::move(p.nume);
        this->stoc = std::move(p.stoc);
        this->caracteristici = std::move(p.caracteristici);
        this->cod_bare = std::move(p.cod_bare);
    }

    produs& operator=(const produs& p) {
        if (this != &p) {
            this->pret = p.pret;
            this->nume = p.nume;
            this->stoc = p.stoc;
            this->caracteristici = p.caracteristici;
            this->cod_bare = p.cod_bare;
        }
        return *this;
    }

    produs& operator=(produs& p) {
        if (this != &p) {
            this->pret = std::move(p.pret);
            this->nume = std::move(p.nume);
            this->stoc = std::move(p.stoc);
            this->caracteristici = std::move(p.caracteristici);
            this->cod_bare = std::move(p.cod_bare);
        }
        return *this;
    }

    int getPret() const {
        return pret;
    }

    string getNume() const {
        return nume;
    }

    int getStoc() const {
        return stoc;
    }

    string getCaracteristici() const {
        return caracteristici;
    }

    long int getCodBare() const {
        return cod_bare;
    }

    void afisare() const {
        cout << "Cod de bare: " << cod_bare << ", Numele Produsului: " << nume << ", Pretul: " << pret << ", Cantitate: " << stoc << endl << "Caracteristici: " << caracteristici << endl;
    }
};



class Comanda {

vector<produs> Produse;

public:

Comanda () {}

Comanda(vector<produs>& produse) {
    this->Produse = produse;
    }

  vector<produs> getProduse(){
    return Produse;
    }

};



class categorii {
private:
    map<string, vector<produs> > categorii_produse;

public:

    void adaugaProdus(const produs& p, const string& categorie) {
        categorii_produse[categorie].push_back(p);
    }

    void afisProduseCategorie(const string& categorie) {
        if (categorii_produse.count(categorie) > 0) {
            cout << "Categoria: " << categorie << endl;
            for (const produs& p : categorii_produse[categorie]) {
            }
        }
    }

    void scrieStocInFisier() {
        ofstream fout("C:\\Program Files\\ppp\\App1\\Stoc_de_produse.txt");
        if (!fout) {
            cerr << "Nu s-a putut deschide fisierul pentru scriere!" << endl;
            return;
        }

        for (const auto& categorie : categorii_produse) {
            for (const produs& p : categorie.second) {
                fout << "Categoria: " << categorie.first << endl;
                fout << "Cod de bare: " << p.getCodBare() << ", Numele Produsului: " << p.getNume() << ", Pretul: " << p.getPret() << ", Cantitate: " << p.getStoc() << endl;
                fout << "Caracteristici: " << p.getCaracteristici() << endl;
                fout << endl;
            }
        }

        fout.close();
    }

};



void adaugaProdusInCos(const char* fisier, long int cod_bare1, int stoc1) {
    if (stoc1 == 0) {
        cout << "Nu puteti adauga 0 produse in cos!" << endl;
    } else {
        ofstream fout(fisier, ios::app);
        if (!fout) {
            cerr << "Nu s-a putut deschide fisierul pentru scriere!" << endl;
            return;
        }

        ifstream fin(fisier);
        bool isFileEmpty = fin.peek() == ifstream::traits_type::eof();
        fin.close();

        if (!isFileEmpty) {
            fout << endl;
        }

        categorii listaProduse;
        ifstream finProduse("C:\\Program Files\\ppp\\App1\\Stoc_de_produse.txt");
        if (!finProduse) {
            cerr << "Nu s-a putut deschide fisierul de produse!" << endl;
            return;
        }

        string cod_bare_str, nume_str, stoc_str, pret_str, caracteristici_str, categorie;
        long int cod_bare;
        string nume;
        int stoc;
        int pret;
        string caracteristici;

        bool produsGasit = false;

        while (getline(finProduse >> ws, categorie, ',')) {
            getline(finProduse >> ws, cod_bare_str, ',');
            getline(finProduse >> ws, nume_str, ',');
            getline(finProduse >> ws, stoc_str, ',');
            getline(finProduse >> ws, pret_str, ',');

            nume = nume_str;
            cod_bare = std::stol(cod_bare_str);
            stoc = std::stoi(stoc_str);
            pret = std::stoi(pret_str);

            if (cod_bare == cod_bare1) {
                stoc = stoc1;
                produsGasit = true;
            }

            getline(finProduse >> ws, caracteristici_str);

            caracteristici = caracteristici_str.substr(0, caracteristici_str.length());

            produs p(cod_bare1, nume, stoc, pret, caracteristici);
            listaProduse.adaugaProdus(p, categorie);

            if (produsGasit) {
                fout << categorie << ", " << cod_bare1 << ", " << nume << ", " << stoc1 << ", " << pret << ", " << caracteristici;
                break;
            }
        }

        finProduse.close();
        fout.close();

        if (produsGasit) {
            cout << "Produsul a fost adaugat in cos." << endl;
        } else {
            cout << "Produsul nu a fost gasit in stoc." << endl;
        }
    }
}



void modificareProdusInCos(const char* fisierr, long int cod_bare1, int stoc1) {
    const string nume_fisier = fisierr;
    ifstream fisier(nume_fisier);
    string linie;
    vector<string> linii_actualizate;

    bool produsGasit = false;

    while (getline(fisier, linie)) {
        istringstream iss(linie);
        string categorie, cod_bare_str, nume, stoc_str, pret_str, caracteristici;
        getline(iss, categorie, ',');
        getline(iss, cod_bare_str, ',');
        getline(iss, nume, ',');
        getline(iss, stoc_str, ',');
        getline(iss, pret_str, ',');
        getline(iss, caracteristici);

        long int cod_bare_actual = std::stol(cod_bare_str);
        int stoc_actual = stoi(stoc_str);

        if (cod_bare_actual == cod_bare1) {
            if (stoc1 == 0) {
                produsGasit = true;
                continue;
            } else {
                stoc_actual = stoc1;
            }
        }

        if (stoc_actual == 0) {
            continue;
        }

        stringstream ss;
        ss << categorie << "," << cod_bare_actual << "," << nume << "," << stoc_actual << "," << pret_str << "," << caracteristici;
        linii_actualizate.push_back(ss.str());
    }

    fisier.close();

    if (!produsGasit && stoc1 == 0) {
        cout << "Produsul nu a fost gasit in cos." << endl;
        return;
    }

    ofstream fisier_actualizat(nume_fisier);
    for (size_t i = 0; i < linii_actualizate.size(); i++) {
        fisier_actualizat << linii_actualizate[i];
        if (i != linii_actualizate.size() - 1) {
            fisier_actualizat << endl;
        }
    }
    fisier_actualizat.close();

    cout << "A fost actualizat cu succes." << endl;
}



void stergereProdusInCos(const char* fisierr, long int cod_bare1) {
    const string nume_fisier = fisierr;
    ifstream fisier(nume_fisier);
    string linie;
    vector<string> linii_actualizate;

    bool produsGasit = false;

    while (getline(fisier, linie)) {
        istringstream iss(linie);
        string categorie, cod_bare_str, nume, stoc_str, pret_str, caracteristici;
        getline(iss, categorie, ',');
        getline(iss, cod_bare_str, ',');
        getline(iss, nume, ',');
        getline(iss, stoc_str, ',');
        getline(iss, pret_str, ',');
        getline(iss, caracteristici);

        long int cod_bare_actual = std::stol(cod_bare_str);

        if (cod_bare_actual == cod_bare1) {
            produsGasit = true;
            continue;
        }

        stringstream ss;
        ss << categorie << "," << cod_bare_actual << "," << nume << "," << stoc_str << "," << pret_str << "," << caracteristici;
        linii_actualizate.push_back(ss.str());
    }

    fisier.close();

    if (!produsGasit) {
        cout << "Produsul nu a fost gasit in cos." << endl;
        return;
    }

    ofstream fisier_actualizat(nume_fisier);
    for (size_t i = 0; i < linii_actualizate.size(); i++) {
        fisier_actualizat << linii_actualizate[i];
        if (i != linii_actualizate.size() - 1) {
            fisier_actualizat << endl;
        }
    }
    fisier_actualizat.close();

    cout << "Produsul a fost eliminat cu succes din cos." << endl;
}



void transfer(const char* fisierSursa, const char* fisierDestinatie) {
    ifstream fin(fisierSursa);
    if (!fin) {
        cerr << "Nu s-a putut deschide fisierul sursa pentru citire!" << endl;
        return;
    }

    string linie;
    vector<string> continut;
    while (getline(fin, linie)) {
        if (!linie.empty() && linie.find_first_not_of(" \t") != string::npos) {
            continut.push_back(linie);
        }
    }

    fin.close();

    ofstream fout(fisierDestinatie, ofstream::app);
    if (!fout) {
        cerr << "Nu s-a putut deschide fisierul destinatie pentru scriere!" << endl;
        return;
    }

    for (const string& linie : continut) {
        fout << linie << endl;
    }

    fout.close();

    fout.open(fisierSursa, ofstream::out | ofstream::trunc);
    if (!fout) {
        cerr << "Nu s-a putut deschide fisierul sursa pentru stergere!" << endl;
        return;
    }

    fout.close();

    cout << "Transferul s-a realizat cu succes!" << endl;
}



void vizualizare() {

    categorii listaProduse;
    ifstream fin("C:\\Program Files\\ppp\\App2\\Cos_cumparaturi.txt");
    if(!fin) {
        cerr << "Nu s-a putut deschide fisierul!" << endl;
        return;
    }
    long int cod_bare;
    string nume;
    int stoc;
    int pret;
    string caracteristici;
    string categorie;


       while (getline(fin >> ws, categorie, ',')) {
        std::string cod_bare_str, nume, stoc_str, pret_str, caracteristici;

        getline(fin >> ws, cod_bare_str, ',');
        getline(fin >> ws, nume, ',');
        getline(fin >> ws, stoc_str, ',');
        getline(fin >> ws, pret_str, ',');

        long int cod_bare = std::stol(cod_bare_str);
        int stoc = std::stoi(stoc_str);
        int pret = std::stoi(pret_str);

        getline(fin >> ws, caracteristici);

        caracteristici = caracteristici.substr(1, caracteristici.length() - 2);

        produs p(cod_bare, nume, stoc, pret, caracteristici);
        listaProduse.adaugaProdus(p, categorie);

        listaProduse.afisProduseCategorie(categorie);
        p.afisare();
        cout<<endl;
    }
    fin.close();
}



int main(int argc, const char* argv[]) {

    categorii listaProduse;
    if(strcmp(argv[1],"vizualizare_cos")==0){
        vizualizare();
    } else if (strcmp(argv[1], "adaugare_produs") == 0) {
        if (argc != 4) {
            cerr << "Sintaxa invalida! Sintaxa corecta: ./app.exe adaugare_produs <cod_de_bare> <cantitate>" << endl;
            return 1;
        }

        const char* fisier = "C:\\Program Files\\ppp\\App2\\Cos_cumparaturi.txt";

        long int cod_bare1 = stol(argv[2]);
        int stoc1 = stoi(argv[3]);

        adaugaProdusInCos(fisier, cod_bare1, stoc1);
    } else if(strcmp(argv[1],"modificare_produs") == 0) {
        if(argc != 4) {
            cerr << "Sintaxa invalida! Sintaxa corecta: ./app.exe modificare_produs <cod_de_bare> <numar_corespunzator_cantitatii>" << endl;
            return 1;
        }

        const char* fisier = "C:\\Program Files\\ppp\\App2\\Cos_cumparaturi.txt";
        long int cod_bare1 = stol(argv[2]);
        int stoc1 = stoi(argv[3]);

        modificareProdusInCos(fisier, cod_bare1, stoc1);

    } else if(strcmp(argv[1],"stergere_produs") == 0) {
        if(argc != 3) {
            cerr << "Sintaxa invalida! Sintaxa corecta: ./app.exe stergere_produs <cod_de_bare>" << endl;
            return 1;
        }

        const char* fisier = "C:\\Program Files\\ppp\\App2\\Cos_cumparaturi.txt";
        long int cod_bare1 = stol(argv[2]);

        stergereProdusInCos(fisier, cod_bare1);
    } else if(strcmp(argv[1],"cumparare") == 0) {

        const char* fisier1 = "C:\\Program Files\\ppp\\App2\\Cos_cumparaturi.txt";
        const char* fisier2 = "C:\\Program Files\\ppp\\App2\\Cumparaturi.txt";

        transfer(fisier1, fisier2);
    } else {
        cerr<<"Comanda necunoscuta,comenzile disponibile sunt:"<<endl;
        cerr<<"./app.exe vizualizare_cos"<<endl;
        cerr<<"./app.exe adaugare_produs <cod_de_bare> <cantitate>"<<endl;
        cerr<<"./app.exe modificare_produs <cod_de_bare> <numar_corespunzator_cantitatii>"<<endl;
        cerr<<"./app.exe stergere_produs <cod_de_bare>"<<endl;
        cerr<<"./app.exe cumparare"<<endl;

        return 1;
    }

return 0;
}
