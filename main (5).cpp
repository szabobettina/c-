#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>

using namespace std;
    double t[10][10];
    int n=0,m=0;
    string x[10],u[10];
    bool pozitiv( int&);
    bool generaloelem(int, int &);
    void SetColor(int);
    void printmatrix(int &, int &);

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
    string s[10];
    while(!be.eof()){
        bool jel=false;
        int szam;
        be>>szam;
        if(be.fail()){
            be.clear();
            be>>s[n];
            jel=true;
        }
        else{
            t[n][m]=szam;
            m++;
        }
        if(jel){
            if(s[n]=="max"){
                t[n][m]=0;
            }else{
                be>>szam;
                t[n][m]=szam;
                m=0;
                n++;
            }
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(j==m){
                cout.width(6);
                if(s[i]!="max")
                cout<<s[i];
            }
            if(i==n && j==m){
                cout<<" ";
            }else{
                cout.width(9);
                cout<<fixed;
                cout<<setprecision(2)<<t[i][j];
            }
        }
        cout<<endl;
    }

    cout<<endl<<"Normal feladat: "<<endl;
    string h;
    for(int i=0;i<m;i++){
        h="";
        x[i]="x";
        h+=i+49;
        x[i]+=h;
    }
    x[m]="b";
    for(int i=0;i<n;i++){
        h="";
        u[i]="u";
        h+=i+49;
        u[i]+=h;
    }
    u[n]="-z";
    int oszlop;
    bool megoldas=true;
    int sor;
    cout<<endl;
    while(pozitiv(oszlop)){
        bool vanpozitivelem=generaloelem(oszlop,sor);
        if(vanpozitivelem){
            printmatrix(sor, oszlop);
            double generalo = t[sor][oszlop];
            //cout<<generalo<<endl<<endl;
            for(int i=0;i<=n;i++){
                for(int j=0;j<=m;j++){
                    if(i!=sor && j!=oszlop){
                        t[i][j]=t[i][j]-(t[i][oszlop]*t[sor][j])/generalo;
                    }
                }
            }
            generalo = 1/t[sor][oszlop];
            for(int j=0;j<=m;j++){
                if(j!=oszlop){
                    t[sor][j] *= generalo;
                }
            }
            for(int i=0;i<=n;i++){
                if(i!=sor){
                    t[i][oszlop] *= (-1)*generalo;
                }
            }
            t[sor][oszlop] = 1/t[sor][oszlop];
            swap(x[oszlop],u[sor]);
            cout<<endl;
        }else{
            megoldas=false;
            break;
        }
    }
    cout<<"    ";
    for(int i=0;i<=m;i++){
        cout.width(9);
        if(x[i][0] == 'x'){
            SetColor(1);
        }else if (x[i][0] == 'u'){
            SetColor(6);
        }
        cout<<x[i];
        SetColor(15);
    }
    cout<<endl;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(j==0){
                cout.width(5);
                if(u[i][0] == 'x'){
                    SetColor(1);
                }else if (u[i][0] == 'u'){
                    SetColor(6);
                }
                cout<<u[i];
                SetColor(15);
            }
            cout.width(9);
            cout<<t[i][j];
        }
        cout<<endl;
    }
    cout<<endl;

    string megold[m];
    double ertek[m];
    int db=0;
    for(int i=0;i<n;i++){
        if(u[i][0] == 'x'){
            megold[db]=u[i];
            ertek[db]=t[i][m];
            db++;
        }
    }
    for(int i=0;i<m;i++){
        if(x[i][0] == 'x'){
            megold[db]=x[i];
            ertek[db]=0;
            db++;
        }
    }
    for(int i=db;i>0;i--){
        for(int j=0;j<i-1;j++){
            if(megold[j]>megold[j+1]){
                swap(megold[j],megold[j+1]);
                swap(ertek[j],ertek[j+1]);
            }
        }
    }
    if(!megoldas){
        cout<<"Nincs megoldas"<<endl;
    }else{
        bool null=false;
        for(int i=0;i<m;i++){
            if(t[sor][i]==0){
                null=true;
            }
        }
        if(null){
            cout<<"Alternativ optimum: "<<endl<<endl;
            for(int i=0;i<m;i++){
                cout.width(14);
                cout<<megold[i];
                cout<<" = ";
                cout<<ertek[i]<<endl;
            }
        }else{
            cout<<"Optimalis megoldas: "<<endl<<endl;
            for(int i=0;i<m;i++){
                cout.width(14);
                cout<<megold[i];
                cout<<" = ";
                cout<<ertek[i]<<endl;
            }
        }
        cout<<"        Max(z) = ";
        cout<<-t[n][m]<<endl;
    }
    return 0;
}


bool pozitiv(int & oszlop){
    bool van=false;
    for(int j=0;j<m;j++){
        if(t[n][j]>0){
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
        if(t[i][oszlop]>0){
            sor=i;
            van=true;
        }
    }
    if(van){
        for(int i=0;i<n;i++){
            if(t[i][oszlop]>0 && (t[i][m]/t[i][oszlop] <= t[sor][m]/t[sor][oszlop])){
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
            SetColor(1);
        }else if (x[i][0] == 'u'){
            SetColor(6);
        }
        cout<<x[i];
        SetColor(15);
    }
    cout<<endl;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(j==0){
                cout.width(5);
                if(u[i][0] == 'x'){
                    SetColor(1);
                }else if (u[i][0] == 'u'){
                    SetColor(6);
                }
                cout<<u[i];
                SetColor(15);
            }
            if(i==sor && j==oszlop){
                SetColor(2);
                cout.width(9);
                cout<<t[i][j];
                SetColor(15);
            }else{
                cout.width(9);
                cout<<t[i][j];
            }
        }
        cout<<endl;
    }
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
