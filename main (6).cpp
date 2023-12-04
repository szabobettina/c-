#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <iomanip>

using namespace std;

    int n,m;
    double tomb[10][10];
    void printkifizetesimatrix();
    string x[10],y[10];
    bool pozitiv( int&);
    bool generaloelem(int, int &);
    void bazistranszformacio();
    void printmatrix(int &, int &);
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
    printkifizetesimatrix();
    int indi=0, indj=0;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(tomb[i][j]<tomb[indi][indj]){
                indi=i;
                indj=j;
            }
        }
    }
    int c=0;
    if(tomb[indi][indj]<0){
        c=1-tomb[indi][indj];
    }
    cout <<"Atalakitott kifizetesi matrix (novekmeny: "<<c<<"):"<<endl;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            tomb[i][j]+=c;
        }
    }
    printkifizetesimatrix();
    cout<<"Jelenitsuk meg a szamitas menetet (I/N)?";
    string valasz;
    cin>>valasz;
    cout<<endl;
    for(int i=0;i<n;i++){
        tomb[i][m]=1;
    }
    for(int i=0;i<m;i++){
        tomb[n][i]=1;
    }
    tomb[n][m]=0;

    string h;
    for(int i=0;i<m;i++){
        h="";
        x[i]="y";
        h+=i+49;
        x[i]+=h;
    }
    x[m]="b";
    for(int i=0;i<n;i++){
        h="";
        y[i]="x";
        h+=i+49;
        y[i]+=h;
    }
    y[n]="-z";

    int oszlop;
    bool megoldas=true;
    int sor;
    while(pozitiv(oszlop)){
        generaloelem(oszlop,sor);
            if(valasz=="I"){
            printmatrix(sor, oszlop);
            }
            double generalo = tomb[sor][oszlop];
            for(int i=0;i<=n;i++){
                for(int j=0;j<=m;j++){
                    if(i!=sor && j!=oszlop){
                        tomb[i][j]=tomb[i][j]-(tomb[i][oszlop]*tomb[sor][j])/generalo;
                    }
                }
            }
            generalo = 1/tomb[sor][oszlop];
            for(int j=0;j<=m;j++){
                if(j!=oszlop){
                    tomb[sor][j] *= generalo;
                }
            }
            for(int i=0;i<=n;i++){
                if(i!=sor){
                    tomb[i][oszlop] *= (-1)*generalo;
                }
            }
            tomb[sor][oszlop] = 1/tomb[sor][oszlop];
            swap(x[oszlop],y[sor]);
    }
    if(valasz=="I"){
        cout<<"    ";
        for(int i=0;i<=m;i++){
            cout.width(9);
            if(x[i][0] == 'x'){
                SetColor(9);
            }else if (x[i][0] == 'y'){
                SetColor(2);
            }else{
                SetColor(4);
            }
            cout<<x[i];
            SetColor(15);
        }
        cout<<endl;
        for(int i=0;i<=n;i++){
            for(int j=0;j<=m;j++){
                if(j==0){
                    cout.width(5);
                    if(y[i][0] == 'x'){
                        SetColor(9);
                    }else if (y[i][0] == 'y'){
                        SetColor(2);
                    }else{
                    SetColor(4);
                    }
                    cout<<y[i];
                    SetColor(15);
                }
                cout.width(9);
                cout<<tomb[i][j];
            }
            cout<<endl;
        }
        cout<<endl;
    }

    cout<<"J1 jatekos strategia valasztasa: "<<endl;
    string megoldX[n];
    double ertekX[n];
    int dbX=0;
    for(int i=0;i<m;i++){
        if(x[i][0] == 'x'){
            megoldX[dbX]=x[i];
            ertekX[dbX]=-tomb[n][i];
            dbX++;
        }
    }
    for(int i=0;i<n;i++){
        if(y[i][0] == 'x'){
            megoldX[dbX]=y[i];
            ertekX[dbX]=0;
            dbX++;
        }
    }
    for(int i=dbX;i>0;i--){
        for(int j=0;j<i-1;j++){
            if(megoldX[j]>megoldX[j+1]){
                swap(megoldX[j],megoldX[j+1]);
                swap(ertekX[j],ertekX[j+1]);
            }
        }
    }
    //
    for(int i=0;i<dbX;i++){
        SetColor(2);
        cout.width(4);
        cout<<i+1;
        SetColor(15);
        cout<<" - ";
        SetColor(4);
        cout<<fixed;
        cout<<setprecision(0)<<-1/tomb[n][m]*ertekX[i]*100<<"% ";
        SetColor(15);
    }
    cout<<endl<<endl;

    cout<<"J2 jatekos strategia valasztasa: "<<endl;
    string megoldY[m];
    double ertekY[m];
    int dbY=0;
    for(int i=0;i<n;i++){
        if(y[i][0] == 'y'){
            megoldY[dbY]=y[i];
            ertekY[dbY]=tomb[i][m];
            dbY++;
        }
    }
    for(int i=0;i<m;i++){
        if(x[i][0] == 'y'){
            megoldY[dbY]=x[i];
            ertekY[dbY]=0;
            dbY++;
        }
    }
    for(int i=dbY;i>0;i--){
        for(int j=0;j<i-1;j++){
            if(megoldY[j]>megoldY[j+1]){
                swap(megoldY[j],megoldY[j+1]);
                swap(ertekY[j],ertekY[j+1]);
            }
        }
    }
    //
    for(int i=0;i<dbY;i++){
        cout.width(4);
        SetColor(2);
        cout<<i+1;
        SetColor(15);
        cout<<" - ";
        SetColor(4);
        cout<<fixed;
        cout<<setprecision(0)<<-1/tomb[n][m]*ertekY[i]*100<<"% ";
        SetColor(15);
    }

    cout<<endl<<endl<<"A jatek varhato erteke: "<<setprecision(2)<<-1/tomb[n][m]-c<<endl;
    return 0;
}

void printkifizetesimatrix(){
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
}

bool pozitiv(int & oszlop){
    bool van=false;
    for(int j=0;j<m;j++){
        if(tomb[n][j]>0){
            van=true;
            oszlop=j;
            break;
        }
    }
    return van;
}

bool generaloelem(int oszlop, int & sor){
    bool van=false;
    for(int i=0;i<n;i++){
        if(tomb[i][oszlop]>0){
            sor=i;
            van=true;
        }
    }
    if(van){
        for(int i=0;i<n;i++){
            if(tomb[i][oszlop]>0 && (tomb[i][m]/tomb[i][oszlop] <= tomb[sor][m]/tomb[sor][oszlop])){
                sor=i;
            }
        }
    }
    return van;
}
void printmatrix(int & sor, int & oszlop){
    generaloelem(oszlop, sor);
    cout<<"    ";
    for(int i=0;i<=m;i++){
        cout.width(9);
        if(x[i][0] == 'x'){
            SetColor(9);
        }else if (x[i][0] == 'y'){
            SetColor(2);
        }else{
             SetColor(4);
        }
        cout<<x[i];
        SetColor(15);
    }
    cout<<endl;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(j==0){
                cout.width(5);
                if(y[i][0] == 'x'){
                    SetColor(9);
                }else if (y[i][0] == 'y'){
                    SetColor(2);
                }else{
                    SetColor(4);
                }
                cout<<y[i];
                SetColor(15);
            }
            if(i==sor && j==oszlop){
                SetColor(5);
                cout.width(9);
                cout<<tomb[i][j];
                SetColor(15);
            }else{
                cout.width(9);
                cout<<fixed;
                cout<<setprecision(2)<<tomb[i][j];
            }
        }
        cout<<endl;
    }
    cout<<endl;
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
