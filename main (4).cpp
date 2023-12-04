#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>

using namespace std;
    int n,m;
    int tomb[10][10];
    int * sorminimum();
    int * oszlopmaximum();
    int * Max(int *,int &);
    int* Min(int *, int &);
    void SetColor(int);

int main()
{
    string feladatszam;
    cout<<endl;
    ifstream be;
    do{
        system("cls");
        cout<<"Add meg a feladat sorszamat: ";
        cin>>feladatszam;
        string fajlnev="feladat";
        fajlnev+=feladatszam;
        fajlnev+=".txt";
        be.open(fajlnev.c_str());
        if(be.fail()){
            SetColor(4);
            cout<<"Hiba! A fajl nem talalhato."<<endl;
            SetColor(15);
            Sleep(1000);
        }
    }while(be.fail());
    cout<<endl;
    int db=0,ei=0,ej=0;
    while(!be.eof()){
        if(db<1){
            be>>n>>m;
            db++;
        }else{
            be>>tomb[ei][ej];
            ej++;
            if(ej==m){
                ej=0;
                ei++;
            }
        }
    }
    cout<<"A J1 jatekos strategiai: ";
    for(int i=0;i<n;i++){
        SetColor(2);
        cout<<i+1<<" ";
        SetColor(15);
    }
    cout<<endl;
        cout<<"A J2 jatekos strategiai: ";
    for(int i=0;i<m;i++){
        SetColor(2);
        cout<<i+1<<" ";
        SetColor(15);
    }
    cout<<endl<<endl;
    cout<<"Kifizetesi matrix: "<<endl;
    int jKetto=n/2, jEgy=m/2;
    if(n%2!=0){
        jKetto=(n/2)+1;
    }
    if(m%2!=0){
        jEgy=(m/2)+1;
    }
    cout.width(6+jEgy*3);
    SetColor(1);
    cout<<"J2"<<endl;
    SetColor(15);
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(i==0){
                if(j==0){
                    cout.width(9);
                }else{
                    SetColor(2);
                    cout<<j;
                    SetColor(15);
                    cout.width(3);
                }
            }else{
                if(j==0){
                    if(i==jKetto){
                        SetColor(1);
                        cout<<"J1";
                        SetColor(15);
                        cout.width(3);
                        SetColor(2);
                        cout<<i;
                        SetColor(15);
                        cout.width(3);
                    }else{
                        cout.width(3);
                        cout<<"     ";
                        SetColor(2);
                        cout<<i;
                        SetColor(15);
                        cout.width(3);
                    }

                }else{
                    cout<<tomb[i-1][j-1];
                    cout.width(3);
                }
            }
        }
        cout<<endl;
    }
    cout<<endl<<endl;
    int * sorMinTomb=sorminimum();
    cout.width(6+jEgy*3);
    SetColor(1);
    cout<<"J2"<<endl;
    SetColor(15);
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(i==0){
                if(j==0){
                    cout.width(9);
                }else{
                    SetColor(2);
                    cout<<j;
                    SetColor(15);
                    cout.width(3);
                }
            }else{
                if(j==0){
                    if(i==jKetto){
                        SetColor(1);
                        cout<<"J1";
                        SetColor(15);
                        cout.width(3);
                        SetColor(2);
                        cout<<i;
                        SetColor(15);
                        cout.width(3);
                    }else{
                        cout.width(3);
                        cout<<"     ";
                        SetColor(2);
                        cout<<i;
                        SetColor(15);
                        cout.width(3);
                    }

                }else{
                    if(j==m){
                        cout<<tomb[i-1][j-1];
                        cout.width(3);
                        SetColor(6);
                        cout<<sorMinTomb[i-1];
                        SetColor(15);
                        cout.width(3);
                    }else{
                        cout<<tomb[i-1][j-1];
                        cout.width(3);
                    }
                }
            }
        }
        cout<<endl;
    }
    int * oszlopMaxTomb=oszlopmaximum();
    for(int i=0;i<m;i++){
        if(i==0){
            cout.width(9);
            SetColor(6);
            cout<<oszlopMaxTomb[i];
            SetColor(15);
        }else{
            cout.width(3);
            SetColor(6);
            cout<<oszlopMaxTomb[i];
            SetColor(15);
        }
    }
    cout<<endl;
    int dbmax,dbmin;
    int *StJ1 = Max(sorMinTomb, dbmax);
    //cout<<endl;
    int *StJ2 = Min(oszlopMaxTomb, dbmin);
    cout<<endl;
    cout<<"Legjobb strategiak, jatek erteke "<<endl;
    cout.width(4);
    SetColor(1);
    cout<<"J1";
    cout.width(4);
    cout<<"J2"<<endl;
    SetColor(15);
    for(int i=0;i<dbmax;i++){
        for(int j=0;j<dbmin;j++){
            cout.width(4);
            SetColor(2);
            cout<<StJ1[i]+1;
            cout.width(4);
            cout<<StJ2[j]+1;
            cout.width(4);
            SetColor(15);
            cout<<tomb[StJ1[i]][StJ2[j]];
            if(sorMinTomb[StJ1[i]]==oszlopMaxTomb[StJ2[j]]){
                SetColor(12);
                cout<<" - egyensulyi pont"<<endl;
                SetColor(15);
            }else{
                cout<<endl;
            }
        }
    }
    return 0;
}
int * sorminimum(){
    int *t=NULL;
    for (int i=0;i<n;i++){
        int minj=0;
        for(int j=0;j<m;j++){
               if(tomb[i][j]<tomb[i][minj]){
                minj=j;
               }
        }
        t=(int *)realloc(t,sizeof(int)*(i+1));
        t[i]=tomb[i][minj];
    }
    return t;
}
int * oszlopmaximum(){
    int *t=NULL;
    for (int j=0;j<m;j++){
        int maxi=0;
        for(int i=0;i<n;i++){
            if(tomb[i][j]>tomb[maxi][j]){
                maxi=i;
            }
        }
        t=(int *)realloc(t,sizeof(int)*(j+1));
        t[j]=tomb[maxi][j];
    }
    return t;
}
int * Max(int *t, int  &db){
    int *p=NULL;
    int ind=0;
    db=0;
    for(int i=0;i<n;i++){
        if(t[i]>t[ind]){
           ind=i;
        }
    }
    p=(int*)realloc(p,sizeof(int)*(db+1));
    p[db]=ind;
    db++;
    for(int i=0;i<n;i++){
        if(t[i]==t[ind] && ind!=i){
            p=(int*)realloc(p,sizeof(int)*(db+1));
            p[db]=i;
            db++;
        }
    }
    return p;
}
int * Min(int *t, int  &db){
    int *p=NULL;
    int ind=0;
    db=0;
    for(int j=0;j<m;j++){
        if(t[j]<t[ind]){
           ind=j;
        }
    }
    p=(int*)realloc(p,sizeof(int)*(db+1));
    p[db]=ind;
    db++;
    for(int j=0;j<m;j++){
        if(t[j]==t[ind] && ind!=j){
            p=(int*)realloc(p,sizeof(int)*(db+1));
            p[db]=j;
            db++;
        }
    }
    return p;
}
void SetColor(int ForgC){
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
