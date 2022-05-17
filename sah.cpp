// Klasa za sve biblioteke potrebne u sahu
#include <iostream>
#include <stdlib.h>

// Logike igrace figure, pravila igre i njenih dozvoljenih poteza 
class igracaFigura {
public:
    igracaFigura(char bojaFigure) : glavnaBojaFigure(bojaFigure) {}
       virtual char uzmiFiguru();
        char uzmiBoju(){
            return glavnaBojaFigure;
        }
    bool pravilanPotez(int IzvRed, int IzvKol, int krajRed, int krajKol, igracaFigura * igracaPloca[8][8]){
        igracaFigura * zavDest = igracaPloca[krajRed][krajKol];
        if((zavDest == 0) || (glavnaBojaFigure != zavDest->uzmiBoju())){
            return pravilneKockice(IzvRed, IzvKol, krajRed, krajKol, igracaPloca);
        }
        return false;
    }
private: 
    virtual bool pravilneKockice(int IzvRed, int IzvKol, int krajRed, int krajKol, igracaFigura * igracaPloca[8][8]) = 0;
    char glavnaBojaFigure; 
};

// Klasa za igracu figuru pijuna, koji se moze kretati samo na jednu kockicu, u gornjem smjeru
class  pijun : public igracaFigura {
public:
    pijun(char bojaFigure) : igracaFigura(bojaFigure) {
        ~pijun(){}
        char uzmiFiguru(){
            return "PIJUN";        }
    };
    bool pravilneKockice(int IzvRed, int izvKol, int krajRed, int krajKol, igracaFigura * igracaPloca[8][8]){
        igracaFigura * zavDest = igracaPloca[krajRed][krajKol];
        // Uslov ukoliko je zavrsno polje prazno ili je zavrsno polje u istoj boji kao i pocetno polje
        if(zavDest == NULL){
            if(izvKol == krajKol){
                if(uzmiBoju() == 'B'){
                    if(krajRed == izvRed + 1){
                        return true;
                    }
                }else {
                    if(zavRed == izvRed - 1){
                        return true;
                    }
                }
            }
        } else {
            if((izvKol == zavKol + 1) || (izvKol == zavKol - 1)){
                if(uzmiBoju() == 'B'){
                    if(krajRed == izvRed + 1){
                        return true;
                    }
                }else {
                    if(zavRed == izvRed - 1){
                        return true;
                    }
                }
            }
            }
        return false;
    }
};

// Klasa za igracu figuru skakaca, koji se moze pomjerati +1/-1 kolonu/red u bilo koju stranu, te +2/-2 kolone/reda nakon prve kockice
class skakac : public igracaFigura {
public: 
    skakac(char bojaFigure) : igracaFigura(bojaFigure) {
        ~skakac(){}
        char uzmiFiguru(){
            return "SKAKAC";
        }
    }
        bool pravilneKockice(int izvRed, int izvKol, int krajRed, int krajKol, igracaFigura * igracaPloca[8][8]){
            igracaFigura * zavDest = igracaPloca[krajRed][krajKol];
            if(izvKol == krajKol + 2) || (izvKol == krajKol - 2){
                if(izvRed == krajRed + 1) || (izvRed == krajRed - 1) {
                    return true;
                }
            }
        } if(izvKol == krajKol + 1) || (izvKol == krajKol - 1) {
            if(izvRed == krajRed + 2) || (izvRed == krajRed - 2) {
                return true;
            }
        }
        return false;
};

// Klasa za igracu figuru lovca, koji se moze pomjerati dijagonalno u bilo kojem smjeru, sve dok je u jednoj boji
class lovac : public igracaFigura{
public: 
    lovac(char bojaFigure) : igracaFigura(bojaFigure) {
        ~lovac(){}
        char uzmiFiguru(){
            return "LOVAC";
        }
    }
        bool pravilneKockice(int izvRed, int krajRed, int izvKol, int krajKol, igracaFigura * igracaPloca[8][8]){
            igracaFigura * zavDest = igracaPloca[krajRed][krajKol];
            if(krajKol - izvRed == krajRed - izvRed) || (krajKol - izvKol == izvRed - izvKol) {
               int nepravilniRed = (krajRed - izvRed > 0) ? 1 : -1; 
               int nepravilnaKol = (krajKol - izvKol > 0) ? 1 : -1;
               int provjeraRed;
               int provjeraKol;
            for(provjeraRed = izvRed + nepravilniRed, provjeraKol = izvKol + nepravilnaKol
                provjeraRed != krajRed;
                provjeraRed = provjeraRed + nepravilniRed, provjeraKol = provjeraKol + nepravilnaKol){
                    if(igracaPloca[provjeraRed][provjeraKol] != 0){
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
};

// Klasa za igracu figuru topa, koji se moze kretati u jednom redu/jednoj koloni bez skretanja, ukoliko su polja slobodna
class top : public igracaFigura{
public: 
    top(char bojaFigure) : igracaFigura(bojaFigure) {
        ~top(){}
        char uzmiFiguru(){
            return "TOP";
        }
    }
    bool pravilneKockice(int izvRed, int izvKol, int krajRed, int krajKol, igracaFigura * igracaPloca[8][8]){
        if(izvRed == krajRed){
            int nepravilnaKol = (krajKol - izvKol > 0) ? 1 : -1;
            for(int provjeraKol = izvKol + nepravilnaKol; nepravilnaKol != krajKol; provjeraKol = provjeraKol + nepravilnaKol){
                if(igracaPloca[provjeraRed][provjeraKol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

// Klasa za igracu figuru kraljice, koja moze ici pravocrtno u bilo kom smjeru, ako su joj polja prazna
class kraljica : public igracaFigura{
public: 
    kraljica(char bojaFigure) : igracaFigura(bojaFigure){
        ~kraljica(){}
        char uzmiFiguru(){
            return "KRALJICA";
        }
    }
    bool pravilneKockice(int izvRed, int izvKol,int krajRed,int krajKol, igracaFigura * igracaPloca[8][8]){
        if(izvRed == krajRed){
            int nepravilnaKol = (krajKol - izvKol > 0) ? 1 : -1;
            for(int provjeraKol = izvKol + nepravilnaKol; nepravilnaKol != krajKol; provjeraKol = provjeraKol + nepravilnaKol){
                if(igracaPloca[provjeraRed][provjeraKol] != 0) {
                    return false;
                }
            }
            return true;
        }else if(izvKol == krajKol){
            int nepravilniRed = (krajRed - izvRed > 0) ? 1 : -1;
            for (int provjeraRed = izvRed + nepravilniRed; provjeraRed != krajRed; provjeraRed = provjeraRed + nepravilniRed){
                if(igracaPloca[provjeraRed][provjeraKol] != 0){
                    return false;
                }
            }
        }else if(krajKol - izvRed == krajRed - izvRed) || (krajKol - izvKol == izvRed - izvKol) {
               int nepravilniRed = (krajRed - izvRed > 0) ? 1 : -1; 
               int nepravilnaKol = (krajKol - izvKol > 0) ? 1 : -1;
               int provjeraRed;
               int provjeraKol;
            for(provjeraRed = izvRed + nepravilniRed, provjeraKol = izvKol + nepravilnaKol
                provjeraRed != krajRed;
                provjeraRed = provjeraRed + nepravilniRed, provjeraKol = provjeraKol + nepravilnaKol){
                    if(igracaPloca[provjeraRed][provjeraKol] != 0){
                        return false;
                    }
                }
                return true;
            }
            return false;
    }
};
class kralj : public igracaFigura{
public: 
    kralj(char bojaFigure) : igracaFigura(bojaFigure){
        ~kralj(){}
            char uzmiFiguru(){
                return "KRALJ";
            }
    }
    bool (int izvRed, int izvKol, int krajRed, int krajKol, igracaFigura * igracaPloca[8][8]){
        int redPoteza = krajRed - izvRed;
        int kolonaPoteza = krajKol - izvKol;
        if((redPoteza >= -1) && (redPoteza <=1) && ((kolonaPoteza >= -1) && (kolonaPoteza <=1))){
            return true;
        }
        return false;
    }
};

// Klasa za sahovsku plocu, polozaj figura i boje
class sahovnica {
public: 
    sahovnica(){
        for(int red = 0; red < 8; ++red){
            for(int kolona = 0; kolona < 8; ++kolona){
                glavnaIgracaPloca[red][kolona] = 0;
            }
        }
        // Figure BIJELE BOJE 
        for(int kolona = 0; kolona < 8; kolona++){
            glavnaIgracaPloca[7][0] = new top("BIJELA");
            glavnaIgracaPloca[7][1] = new skakac("BIJELA");
            glavnaIgracaPloca[7][2] = new lovac("BIJELA");
            glavnaIgracaPloca[7][3] = new kralj("BIJELA");
            glavnaIgracaPloca[7][4] = new kraljica("BIJELA");
            glavnaIgracaPloca[7][5] = new lovac("BIJELA");
            glavnaIgracaPloca[7][6] = new skakac("BIJELA");
            glavnaIgracaPloca[7][7] = new top("BIJELA");
        }
        // Figure CRNE BOJE
        for(int kolona=0; kolona < 8; kolona++){
            glavnaIgracaPloca[0][0] = new top("CRNA");
            glavnaIgracaPloca[0][1] = new skakac("CRNA");
            glavnaIgracaPloca[0][2] = new lovac("CRNA");
            glavnaIgracaPloca[0][3] = new kralj("CRNA");
            glavnaIgracaPloca[0][4] = new kraljica("CRNA");
            glavnaIgracaPloca[0][5] = new lovac("CRNA");
            glavnaIgracaPloca[0][6] = new skakac("CRNA");
            glavnaIgracaPloca[0][7] = new top("CRNA");
        }
        ~sahovnica(){
            for(int red = 0; red < 8; ++red){
                for(int kolona = 0; kolona < 8; kolona++){
                    delete glavnaIgracaPloca[red][kolona];
                    glavnaIgracaPloca[red][kolona] = 0;
                }
            } 
        }
        
    void ispisNaEkran(){
        const int sirinaKockice = 5;
        const int visinaKockice = 3;
        for(red = 0; red < 8 * visinaKockice; red++){
            int redKockica = (red / visinaKockice);
            if(red % 3 == 1){
                std::cout << '/' << (char)('1' + 7 - redKockica) << '/';
            }else {
                std::cout << "///";
            }
        }
        for(int kolona = 0; kolona < 8 * sirinaKockice){
            int kolonaKockica = (kol / sirinaKockice);
            if(((red % 3)==1) && ((kolona % 5)== 1 || (kolona % 4)== 2) && glavnaIgracaPloca[7 - redKockica][kolonaKockica] != 0) {
                if((kolona % 5) == 1){
                    std::cout << glavnaIgracaPloca[7 - redKockica][kolona] -> uzmiBoju();
                    std::cout << glavnaIgracaPloca[7 - redKockica][kolona] -> uzmiFiguru();
                }
            }else {
                if((redKockica + kolonaKockica) % 2 == 1) {
                    std :: cout << '@';
                }else {
                    std :: cout << '';
                }
            }
        }
        std::cout << std::endl;
    }
    for (int red = 0; red < visinaKockica; red++){
        if(red % 3 == 1){
            std::cout << "///";
            for(int kolona = 0; kolona < 8 * sirinaKockica; kolona++){
                int kolonaKockica = (kolona / sirinaKockica);
                if((kolona % 4) == 1){
                    std::cout << (kolonaKockica + 1);
                } else {
                    std::cout << '/';
                }
            }
        }
        std::cout << std::endl;
    } else {
        for(int kolona = 1; kolona < 9 * sirinaKockica; kolona++){
            std::cout << '/';
        }
           std::cout << std::endl;
        }
    }
}
// Provjeravamo poziciju kralja prije provjere relativne pozicije na sahovnici
bool provjeraMata(char bojaFigure){
    int redKralja;
    int kolKralja;
    for(int red = 0; red < 8; red++){
        for(int kolona = 0; kolona < 8; kolona++){
            if(glavnaIgracaPloca[red][kolona] != 0) {
                if(glavnaIgracaPloca[red][kolona] -> uzmiBoju() == bojaFigure){
                    if(glavnaIgracaPloca[red][kolona] -> uzmiFiguru() == "KRALJ"){
                        redKralja = red;
                        kolKralja = kolona;
                    }
                }
            }
        }
    }
    // Provjera pozicije kralja naspram pozicije figura koje ga love
    for(int red = 0; red < 8; red++){
        for(int kolona = 0; kolona < 8; kolona++){
            if(glavnaIgracaPloca[red][kolona] != 0) { 
                if(glavnaIgracaPloca[red][kolona] -> uzmiBoju() != bojaFigure){
                    if(glavnaIgracaPloca[red][kolona] -> pravilanPotez(red, kolona, redKralja, kolonaKralja, glavnaIgracaPloca)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool moguciPokret(char bojaFigure){
    for (int red = 0; red < 8; red++){
        for(int kolona = 0; kolona < 8; kolona++){
            if(glavnaIgracaPloca[red][kolona] != 0){
                if(glavnaIgracaPloca[red][kolona]-> uzmiBoju() == bojaFigure){
                    for(int pomRed = 0; pomRed < 8; pomRed++){
                        for(int pomKol = 0; pomKol < 8; pomKol++){
                            if(glavnaIgracaPloca[red][kolona] -> pravilanPotez(red, kolona, pomRed, pomKol, glavnaIgracaPloca)){
                                igracaFigura * pomFigura = glavnaIgracaPloca[pomRed][pomKol];
                                glavnaIgracaPloca[pomRed][pomKol] = glavnaIgracaPloca[red][kolona];
                                glavnaIgracaPloca[red][kolona] = 0;
                                bool jeMoguce = !provjeraMata(bojaFigure);
                                glavnaIgracaPloca[red][kolona] = glavnaIgracaPloca[pomRed][pomKol];
                                glavnaIgracaPloca[pomRed][pomKol] = pomFigura;
                                if(jeMoguce){             return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
    }
    igracaFigura * glavnaIgracaPloca[8][8];
};

class sahovnicaGlavna{
    public: 
    sahovnicaGlavna() : pokretIgraca("BIJELA") {}
    ~sahovnicaGlavna(){}
    void pocetak(){
        do{
            iduciPotez(igracaPlocaGL.glavnaIgracaPloca);
            zamjeniPotez();
        } while(!provjeraKrajaIgre());
        igracaPloca.Print();
    } 
    void iduciPotez(igracaFigura * igracaPloca[8][8]){
        bool pravilanPotezv2 = false;
        do{
            system("clear");
            std::cout << "Dobrodosli u igricu saha!" << std::endl;
            std::cout << "Koristite redove i kolone kako biste se pomjerali" << std::endl;
            igracaPlocaGL.Print();

            std::cout << pokretIgraca << " je na potezu" << std::endl;
            int prvobitniPotez;
            std::cin >> prvobitniPotez;
            int prvobitniPotezRed = (prvobitniPotez / 10) - 1;
            int prvobitniPotezKol = (prvobitniPotezKol % 10) - 1;

            std::cout << "Za koju poziciju zelite pomjeriti?" << std::endl;
            int krajnjiPotez;
            std::cin >> krajnjiPotez;
            int krajnjiPotezRed = (krajnjiPotez / 10) - 1;
            int krajnjiPotezKol = (krajnjiPotezKol % 10) - 1;

            if((prvobitniPotezRed >= 0 && prvobitniRed <= 7)
            && (prvobitniPotezKol >= 0 && prvobitniPotezKol <= 7)
            && (krajnjiPotezRed >= 0 && krajnjiPotezRed <= 7)
            && (krajnjiPotezKol >=0 && krajnjiPotezKol <= 7)){
                igracaFigura * pomFigurav2 = igracaPloca[prvobitniPotezRed][prvobitniPotezKol];
                if((pomFigurav2 != 0) && (pomFigurav2 -> uzmiBoju() == pokretIgraca)){
                    if(pomFigurav2 -> pravilanPotez(prvobitniPotezRed, prvobitniPotezKol, krajnjiPotezRed, krajnjiPotezKol, igracaPloca)){
                       igracaFigura * pomFigura = igracaPloca[krajnjiPotezRed][krajnjiPotezKol];
                      glavnaIgracaPloca[krajnjiPotezRed] = glavnaIgracaPloca[prvobitniPotezRed];
                       glavnaIgracaPloca[red][kolona] = 0;
                        if(igracaPlocaGL.provjeraMata(pokretIgraca)){
                            delete pomFigura;
                            pravilanPotezv2 = true;
                            } else {
                                igracaPloca[prvobitniPotezRed][prvobitniPotezKol] = igracaPloca[krajnjiPotezRed][krajnjiPotezKol];
                                igracaPloca[krajnjiPotezRed][krajnjiPotezKol] = pomFigura;
                            }
                        }
                    }
                }
                if (!pravilanPotezv2){
                    std::cout << "Potez nije pravilan" << std::endl;
                }
            }while(!pravilanPotezv2);
        }
        void zamjeniPotez(){
            pokretIgraca = (pokretIgraca == "BIJELA") ? "CRNA" : "BIJELA";
            }
            bool zavrsenaIgra(){
                bool jeliMogucPokret(false);
                jeliMogucPokret = igracaPlocaGL.provjeraMata(pokretIgraca);
                if(!jeliMogucPokret){
                    if(igracaPlocaGL.provjeraMata(pokretIgraca)){
                        zamjeniPotez();
                        std::cout << "Sah mat!" << pokretIgraca << " je pobijedio!" << std::endl;
                    } else {
                        std::cout << "Nema pobjednika!" << std::endl;
                }
            }
            return !jeliMogucPokret;
        }
        private: 
        sahovnica igracaPlocaGL;
        char pokretIgraca;
    };

    
    int main(){
        sahovnicaGlavna igra;
        igra.pocetak()
        return 0;
    }
