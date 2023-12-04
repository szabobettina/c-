#include "Fa.h"

Fa::Fa()
{
    gyoker = NULL;
}

Fa::~Fa()
{
    faTorles(gyoker);
}

Fa::Fa(const Fa& other)
{
    gyoker = NULL;
    *this = other;
}

Fa& Fa::operator=(const Fa& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    faTorles(gyoker);
    egyenlo(rhs.gyoker);
    return *this;
}
void Fa::egyenlo(gElem *gy){
    if(gy != NULL){
        Insert(gy->adat);
        egyenlo(gy->bal);
        egyenlo(gy->jobb);
    }
}
bool Fa::Ures(){
    return gyoker == NULL;
}
bool Fa::Insert(int ujadat){
    if(Ures()){
        gElem * elem = new gElem;
        elem->adat = ujadat;
        elem->apa = NULL;
        elem->bal = NULL;
        elem->jobb = NULL;
        gyoker = elem;
        return true;
    }else{
            gElem *seged = gyoker;
            gElem *s1 = gyoker->apa;
            while(seged != NULL){
                s1 = seged;
                if(seged->adat > ujadat)
                    seged = seged->bal;
                else if(ujadat > seged->adat)
                    seged = seged->jobb;
                else
                    return false;
            }
            if(ujadat < s1->adat){
                gElem * elem = new gElem;
                elem->adat = ujadat;
                elem->apa = s1;
                s1->bal = elem;
                elem->bal = NULL;
                elem->jobb = NULL;
                return true;
            }else if(ujadat > s1->adat){
                gElem * elem = new gElem;
                elem->adat = ujadat;
                elem->apa = s1;
                s1->jobb = elem;
                elem->bal = NULL;
                elem->jobb = NULL;
                return true;
            }else if (ujadat == s1->adat){
                return false;
            }
    }
}
void Fa::rendezettKiir(gElem * gy ){
    if(!Ures()){
        if(gy->bal != NULL){
            rendezettKiir(gy->bal);
        }
        cout<<gy->adat<<" ";
        if(gy->jobb != NULL){
            rendezettKiir(gy->jobb);
        }
    }else{
        cout<<"Ures a fa"<<endl;
    }
}
void Fa::Kiir(){
    rendezettKiir(gyoker);
}
bool Fa::Keres(int k,gElem* & csomopont){
    gElem *seged = gyoker;
    while(seged != NULL){
        if(seged->adat == k){
            //cout<<seged->adat<<" ";
            csomopont = seged;
            return true;
        }else{
        if(seged->adat > k) seged = seged->bal;
        else if(k > seged->adat) seged = seged->jobb;
        }
    }
    return false;
}
int Fa::Max(){
    if(!Ures()){
        gElem* seged = gyoker;
        gElem* s1 = seged->apa;
        while(seged != NULL){
            s1=seged;
            seged=seged->jobb;
        }
        return s1->adat;
    }
    return 66666;
}
int Fa::Min(){
    if(!Ures()){
        gElem* seged = gyoker;
        gElem* s1 = seged->apa;
        while(seged != NULL){
            s1=seged;
            seged=seged->bal;
        }
        return s1->adat;
    }
    return 66666;
}
int Fa::Gyoker(){
    return gyoker->adat;
}
bool Fa::elemTorles(int tAdat){
    gElem * torles;
    if(Keres(tAdat,torles)){
        if(torles->bal == NULL && torles->jobb == NULL){
            if(torles->apa->adat > torles->adat)
                torles->apa->bal = NULL;
            else torles->apa->jobb = NULL;
            delete torles;
        }else if(torles->bal == NULL && torles->jobb != NULL){
            torles->jobb->apa = torles->apa;
            if(torles->apa->adat > torles->jobb->adat) torles->apa->bal = torles->jobb;
            else torles->apa->jobb = torles->jobb;
            delete torles;
        }else if(torles->bal != NULL && torles->jobb == NULL){
            torles->bal->apa = torles->apa;
            if(torles->apa->adat > torles->bal->adat) torles->apa->bal = torles->bal;
            else torles->apa->jobb = torles->bal;
            delete torles;
        }else{
            gElem * segedbal = torles->bal;
            while(segedbal->jobb != NULL){
                segedbal = segedbal->jobb;
            }
            gElem * segedjobb = torles->jobb;
            while(segedjobb->bal != NULL){
                segedjobb = segedjobb->bal;
            }
            if(abs(torles->adat - segedbal->adat) < abs(torles->adat - segedjobb->adat)){
                torles->adat = segedbal->adat;
                segedbal->apa->jobb = NULL;
                delete segedbal;
            }else{
                torles->adat = segedjobb->adat;
                segedjobb->apa->bal = NULL;
                delete segedjobb;
            }
        }
    }
}
void Fa::faTorles(gElem * gy){
    if(!Ures()){
        if(gy->bal != NULL){
            faTorles(gy->bal);
        }
        if(gy->jobb != NULL){
            faTorles(gy->jobb);
        }
        delete gy;
    }
    gyoker = NULL;
}
void Fa::Torles(){
    faTorles(gyoker);
}
int Fa::Elemszam(){
    int osszeg = 0;
    dbszam(gyoker, osszeg);
    return osszeg;
}
void Fa::dbszam(gElem * gy, int  & osszeg){
    if(gy != NULL){
        dbszam( gy->bal,osszeg);
        dbszam(gy->jobb,osszeg);
        osszeg ++;
    }
}
int Fa::melyseg(gElem * gy){
    if(gy == NULL) return 0;
    int b = melyseg(gy->bal);
    int j = melyseg(gy->jobb);
    if(b > j) return b+1;
    else return j+1;
}
int Fa::Melyseg(){
    return melyseg(gyoker);
}
bool Fa::kiegynsulyozott(gElem * gy){
    if(gy == NULL) return true;

    int b = melyseg(gy->bal);
    int j = melyseg(gy->jobb);

    if(abs(b-j) <= 1 && kiegynsulyozott(gy->bal) && kiegynsulyozott(gy->jobb)) return true;

    return false;
}
void Fa::Kiegyensulyozott(){
    if(kiegynsulyozott(gyoker))
        cout<< "Kiegyensulyozott"<<endl;
    else
        cout << "Nem kiegyensulyozott" << endl;
}
