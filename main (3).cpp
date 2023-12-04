#include <iostream>
#include <fstream>

using namespace std;
struct Auto{
    string ora, rendszam;
    int nap, azonosito, km,hajtas;
};

int main()
{
    Auto t[500];
    ifstream be("autok.txt");
    int db=0;
    while(!be.eof()){
        be>>t[db].nap>>t[db].ora>>t[db].rendszam>>t[db].azonosito>>t[db].km>>t[db].hajtas;
        //cout<<t[db].nap<<" "<<t[db].ora<<" "<<t[db].rendszam<<" "<<t[db].azonosito<<" "<<t[db].km<<" "<<t[db].hajtas<<endl;
        db++;
    }
    be.close();
    db--;
    int i=db-1;
    while(t[i].hajtas!=0){
        i--;
    }
    cout<<"2. feladat"<<endl;
    cout<<t[i].nap<<". nap rendszam: "<<t[i].rendszam<<endl<<endl;
    cout<<"3. feladat"<<endl;
    cout<<"Nap: ";
    int n;
    cin>>n;
    cout<<"Forgalom a(z) "<<n<<". napon: "<<endl;
    i=0;
    while(t[i].nap<=n){
        if(t[i].nap==n){
            cout<<t[i].ora<<" "<<t[i].rendszam<<" "<<t[i].azonosito;
            if(t[i].hajtas==0){
                cout<<" ki"<<endl;
            }
            else{
                cout<<" be"<<endl;
            }
        }
        i++;
    }
    int tomb[10];
    for(int i=0;i<10;i++){
        for(int j=0;j<db;j++){
            int b=t[j].rendszam[5]-48;
            if(i==b){
                tomb[i]++;
            }
        }
    }
    int m=0;
    for(int i=0;i<10;i++){
        if(tomb[i]%2!=0){
            m++;
        }
    }
    cout<<"4. feladat"<<endl;
    cout<<"A honap vegen "<<m<<" autot nem hoztak vissza"<<endl<<endl;
    cout<<"5. feladat"<<endl;
    tomb[10]={0};
    for(int i=0;i<10;i++){
        for(int j=0;j<db;j++){
            int b=t[j].rendszam[5]-48;
            if(i==b){
                int kezdet=t[j].km;
                int l=db-1;
                while((t[l].rendszam[5]-48)!=i){
                    l--;
                }
                int vege=t[l].km;
                cout<<t[l].rendszam<<" "<<vege-kezdet<<" km"<<endl;
                break;
            }
        }
    }
    int sz[100];
    int veg, kezdet;
    for(int i=500;i<=600;i++){
        int maxim=0;
        for(int j=0;j<db;j++){
            if(t[j].azonosito==i && t[j].hajtas==0){
                kezdet=t[j].km;
                j++;
                while(j<db && t[j].azonosito!=i){
                    j++;
                }
                veg=t[j].km;
            }
            if((veg-kezdet)>maxim){
                maxim=veg-kezdet;
            }
        }
        sz[i-500]=maxim;
    }
    int id=0;
    for(int i=0;i<100;i++){
        if(sz[i]>sz[id]){
            id=i;
        }
    }
    cout<<"6. feladat"<<endl;
    cout<<"A leghosszabb ut: "<<sz[id]<<" km, szemely: "<<id+500<<endl<<endl;
    cout<<"7. feladat"<<endl;
    cout<<"Rendszam: ";
    string rszam;
    cin>>rszam;
    string fajlnev=rszam+"_menetlevel";
    ofstream ki(fajlnev.c_str());
    for(int i=0;i<db;i++){
        if(t[i].rendszam==rszam && t[i].hajtas==0){
            ki<<t[i].azonosito<<"\t"<<t[i].nap<<".\t"<<t[i].ora<<"\t"<<t[i].km<<"\t";
            i++;
            while(i<db && t[i].rendszam!=rszam){
                i++;
            }
            ki<<t[i].nap<<".\t"<<t[i].ora<<"\t"<<t[i].km<<endl;
        }
    }
    cout<<"Menetlevel kesz"<<endl<<endl;
    return 0;
}
