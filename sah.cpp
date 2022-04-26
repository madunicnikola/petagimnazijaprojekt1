// Klasa za sve biblioteke potrebne u sahu

#include <iostream>
#include <stdlib.h>

// Logike igrace figure, pravila igre i njenih dozvoljenih poteza 

class igracaFigura {
public:
    igracaFigura(char bojaFigure) : glavnaBojaFigure(bojaFigure) {
        ~igracaFigura(){}
        virtual char uzmiFiguru() = 0;
        char uzmiBoju(){
            return glavnaBojaFigure;
        }
    }
    bool pravilanPotez(int IzvRed, int IzvKol, int krajRed, int krajKol, igracaFigura * sahovnica[8][8]){
        igracaFigura * zavDest = sahovnica[krajRed][krajKol];
        if((zavDest == NULL) || (glavnaBojaFigure != zavDest->uzmiBoju())){
            return pravilneKockice(IzvRed, IzvKol, krajRed, krajKol, sahovnica);
        }
        return false;
    }
private: 
    virtual bool pravilneKockice(int IzvRed, int IzvKol, int krajRed, int krajKol, igracaFigura * sahovnica[8][8]) = 0;
    char glavnaBojaFigure; 
};

// Klasa za igracu figuru pijuna, koji se moze kretati samo na jednu kockicu, u gornjem smjeru

class  pijun : public igracaFigura {
public:
    pijun(char bojaFigure) : igracaFigura(bojaFigure) {
        ~pijun(){}
        char uzmiFiguru(){
            return 'PIJUN';
        }
    };
    bool pravilneKockice(int IzvRed, int izvKol, int krajRed, int krajKol, igracaFigura * sahovnica[8][8]){
        igracaFigura * zavDest = sahovnica[krajRed][krajKol];
        // Uslov ukoliko je zavrsno polje prazno
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
        }
        return false;
    } 
};

