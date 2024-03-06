#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

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



void vizualizare()
{
    categorii listaProduse;
    ifstream fin("C:\\Program Files\\ppp\\App1\\Stoc_de_produse.txt");
    if (!fin) {
        cerr << "Nu s-a putut deschide fisierul!" << endl;
        return ;
    }

    string nume;
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


        produs p(cod_bare, nume, stoc, pret, caracteristici);
        listaProduse.adaugaProdus(p, categorie);

        listaProduse.afisProduseCategorie(categorie);
        p.afisare();
        cout<<endl;
    }

    fin.close();
}

void vizualizare_comenzi()
{
    categorii listaProduse;
    ifstream fin("C:\\Program Files\\ppp\\App2\\Cumparaturi.txt");
    if (!fin) {
        cerr << "Nu s-a putut deschide fisierul!" << endl;
        return ;
    }

    string nume;
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



void adaugaProdusInStoc(const char* fisier, const char* categorie, long int cod_bare, const char* nume, int stoc, int pret, const char* caracteristici) {
    ofstream fout(fisier, ios::app);
    if (!fout) {
        cerr << "Nu s-a putut deschide fisierul pentru scriere!" << endl;
        return;
    }

    fout << categorie << "," << cod_bare << "," << "\"" << nume << "\"" << "," << stoc << "," << pret << ","<< "\"" << caracteristici << "\"" << endl;


    fout.close();

    cout << "Produsul a fost adaugat in stoc." << endl;

}


void modificarePret(int cod_bare, int pret_nou) {
    const string nume_fisier = "C:\\Program Files\\ppp\\App1\\Stoc_de_produse.txt";
    ifstream fisier(nume_fisier);
    string linie;
    vector<string> linii_actualizate;

    while (getline(fisier, linie)) {
        istringstream iss(linie);
        string categorie, cod_bare_str, nume, stoc_str, pret_str, caracteristici;
        getline(iss, categorie, ',');
        getline(iss, cod_bare_str, ',');
        getline(iss, nume, ',');
        getline(iss, stoc_str, ',');
        getline(iss, pret_str, ',');
        getline(iss, caracteristici);

        int cod_bare_actual = stoi(cod_bare_str);
        int pret_actual = stoi(pret_str);

        if (cod_bare_actual == cod_bare) {
            pret_actual = pret_nou;
        }

        stringstream ss;
        ss << categorie << "," << cod_bare_actual << "," << nume << "," << stoc_str << "," << pret_actual << "," << caracteristici;
        linii_actualizate.push_back(ss.str());
    }

    fisier.close();

    ofstream fisier_actualizat(nume_fisier);
    for (const auto& linie_actualizata : linii_actualizate) {
        fisier_actualizat << linie_actualizata << endl;
    }
    fisier_actualizat.close();

    cout << "Pretul pentru codul de bare " << cod_bare << " a fost actualizat cu succes." << endl;
}



void stergeProdusDinStoc(long int cod_bare, int cantitate) {
    ifstream fin("C:\\Program Files\\ppp\\App1\\Stoc_de_produse.txt");
    if (!fin) {
        cerr << "Nu s-a putut deschide fisierul pentru citire!" << endl;
        return;
    }

    vector<string> lines;
    string line ;

    while (getline(fin, line)) {
        string codBareStr = line.substr(line.find(",") + 1);
        long int codBareLinie;
        try {
            codBareLinie = stol(codBareStr);
        } catch (const std::invalid_argument& e) {
            cerr << "Invalid argument: " << e.what() << endl;
            fin.close();
            return;
        } catch (const std::out_of_range& e) {
            cerr << "Out of range: " << e.what() << endl;
            fin.close();
            return;
        }
        if (codBareLinie == cod_bare) {
            std::istringstream iss(line);
            std::string token;
            std::getline(iss, token, ',');
            std::getline(iss, token, ',');
            std::getline(iss, token, ',');
            std::getline(iss, token, ',');

            int stoc = std::stoi(token);
            if (stoc == cantitate) {
                continue;
            } else if (stoc > cantitate) {
                int diferenta = stoc - cantitate;

                if (diferenta == 0) {
                    lines.erase(lines.begin() + lines.size() - 1);
                    continue;
                } else {
                    size_t firstCommaPos = line.find(',');

                        size_t fourthCommaPos = line.find(',', line.find(',', line.find(',') + 1) + 1);

                        if (fourthCommaPos != std::string::npos) {
                            line = line.substr(0, fourthCommaPos + 1) + std::to_string(diferenta) +
                                   line.substr(fourthCommaPos + 2);

                        } else {
                            std::cout << "Linia nu are suficiente argumente separate prin virgule." << std::endl;
                        }
                }
            } else {
                cerr << "Cantitatea introdusÄƒ este mai mare decÃ¢t stocul disponibil pentru produsul selectat." << endl;
                fin.close();
                return;
            }
        }
        lines.push_back(line);
    }

    fin.close();

    ofstream fout("C:\\Program Files\\ppp\\App1\\Stoc_de_produse.txt");
    if (!fout) {
        cerr << "Nu s-a putut deschide fisierul pentru scriere!" << endl;
        return;
    }

    for (const string& line : lines) {
        fout << line << endl;
    }

    fout.close();

    cout << "Produsul a fost sters din stoc." << endl;
}



int main(int argc, const char* argv[]) {

    categorii listaProduse;
    if(strcmp(argv[1],"vizualizare_stoc")==0){
        vizualizare();
    }

    else if (strcmp(argv[1], "adaugare_stoc") == 0) {
        if (argc != 8) {
            cerr << "Numarul incorect de argumente pentru comanda 'adaugare_stoc'." << endl;
            return 1;
        }
        const char* fisier = "C:\\Program Files\\ppp\\App1\\Stoc_de_produse.txt";
        const char* categorie = argv[2];
        long int cod_bare = stol(argv[3]);
        const char* nume = argv[4];
        int stoc = stoi(argv[5]);
        int pret = stoi(argv[6]);
        const char* caracteristici = argv[7];

        adaugaProdusInStoc(fisier, categorie, cod_bare, nume, stoc, pret, caracteristici);
    }

    else   if (strcmp(argv[1], "sterge_produs") == 0) {

    long int cod_bare =stol(argv[2]);
    int cantitate = stoi(argv[3]);

        if (cod_bare == 0 || cantitate == 0) {
            cerr << "Argumente invalide pentru codul de bare sau cantitate." << endl;
            return 1;
        }

        stergeProdusDinStoc(cod_bare, cantitate);
    }

    else if(strcmp(argv[1], "modifica_pret")==0) {
        int cod_bare, pret_nou;
        cod_bare = stoi(argv[2]);
        pret_nou = stoi(argv[3]);
        if(cod_bare == 0 || pret_nou == 0)
            return 1;
        modificarePret(cod_bare, pret_nou);
        }

    else if(strcmp(argv[1], "vizualizare_comenzi")==0) {
        vizualizare_comenzi();
    }

   else {
       cerr << "Comanda necunoscuta,comenzile disponibile sunt:"<<endl;
       cerr<<"<vizualizare_stoc>"<<endl;
       cerr<<"<adaugare_stoc> categorie cod_bare nume stoc pret caracteristici "<<endl;
       cerr<<"<sterge_produs> cod_bare cantitate "<<endl;
       cerr<<"<modifica_pret> cod_bare pret"<<endl;
       cerr<<"<vizualizare_comenzi>"<<endl;


        return 1;
    }

    return 0;
}
