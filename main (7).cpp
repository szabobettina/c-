#include <iostream>
#include "Fa.h"

using namespace std;

int main()
{
    Fa f1;
    f1.Insert(6);
    f1.Insert(3);
    f1.Insert(1);
    f1.Insert(5);
    f1.Insert(9);
    f1.Insert(4);
    f1.Kiir();
    cout<<endl;
    //f1.Insert(6);
    f1.Kiir();
    cout<<endl;
    gElem *a;
    cout<< f1.Keres(5,a) << " " << a << endl;
    cout<< "f1 max: "<<f1.Max() << endl;
    cout<< "f1 min: "<< f1.Min() << endl;
    cout<< "f1 gyoker: "<< f1.Gyoker() << endl;
    cout<< "f1 elemszam: "<<f1.Elemszam() << endl;
    cout<< "f1 melyseg: "<<f1.Melyseg() << endl;
    f1.elemTorles(5);
    cout<<endl;
    f1.Kiir();
    cout<<endl;
    Fa f2(f1);
    cout<<"f2: ";
    f2.Kiir();
    cout <<". Gyoker:"<< f2.Gyoker() << endl;
    Fa f3;
    f3.Insert(5);
    f3.Insert(8);
    f3.Insert(7);
    f3.Insert(3);
    f3.Insert(2);
    cout<<"f3: ";
    f3.Kiir();
    cout<<endl;
    f3 = f1;
    cout<<"f3: ";
    f3.Kiir();
    cout<<endl;
    cout << "f1 ";
    f1.Kiegyensulyozott();
    cout << endl;
    f1.Torles();
    f1.Kiir();
    return 0;
}
