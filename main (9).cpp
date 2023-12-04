#include <iostream>
#include <fstream>

using namespace std;
 struct kave{
    int ar, kod, t[8];
    string nev;
 };
 struct tip {
    int tipuskod;
    string megnevezes;

 };
int main()
{
    ifstream be("kavezo.txt");
    kave t1[100];
    int i=0;
    while(!be.eof())
    {
        be >> t1[i].ar >> t1[i].nev >> t1[i].kod;
        for(int j=0;j<8;j++)
        {
            be >> t1[i].t[j];
        }
        i++;
    }
    be.close();
    ifstream be1("tipus.txt");
    tip t2[30];
    int j=0;
    while(!be1.eof())
    {
        be1 >> t2[j].tipuskod >> t2[j].megnevezes;
        j++;
    }
    be1.close();
    int maxi=t1[0].t[0];
    int het=0;
    int het1=0;
    for(int j=0;j<i-1;j++)
    {
        for(int k=0;k<8;k++)
        {
            if (t1[j].t[k] > maxi)
            {
                maxi=t1[j].t[k];
                het=j;
                het1=k;
            }
        }
    }
    cout<< het1+1 <<". heten "<<t1[het].nev<<" arubol fogyott "<<maxi<<endl<<endl;
    int ar1;
    int db=0;
    int art[i];
    string arnev[i];
    cin>>ar1;
    for(int j=0;j<i;j++)
    {
        if(t1[j].ar<=ar1)
        {
            arnev[db]=t1[j].nev;
            art[db]=t1[j].ar;
            db++;
        }
    }
    if (db==0)
    {
        cout<<"Nincs ilyen ar"<<endl<<endl;
    }
    else
    {
        for(int j=0;j<db;j++)
        {
            cout<<arnev[j]<<" "<<art[j]<<endl;
        }
    }
    cout<<endl;
    int t3[i];
    for(int j=0;j<i-1;j++)
    {
        int b=0;
        for(int k=0;k<8;k++)
        {
            b+=t1[j].t[k];
        }
        b*=t1[j].ar;
        t3[j]=b;
    }
    int m=0;
    for (int j=0; j<i-1;j++)
    {
        if(t3[j]>t3[m])
        {
            m=j;
        }
    }
    cout<<"A legtobb bevetelt hozo aru: "<<t1[m].nev<<endl;
    cout<<"Bevetel: "<<t3[m]<<endl<<endl;

    int t4[i];
    for(int j=0;j<8;j++)
    {
        int b=0;
        for(int k=0;k<i-1;k++)
        {
            b+=t1[k].t[j]*t1[k].ar;
        }
        t4[j]=b;
    }
    int mi=0;
    for (int j=0; j<8;j++)
    {
        if(t4[j]>t4[mi])
        {
            mi=j;
        }
    }
    cout<<"A legtobb bevetelt hozo het: "<<mi+1<<endl;
    cout<<"Bevetel: "<<t4[mi]<<endl<<endl;
    int arak[i];
    arak[0]=t1[0].ar;
    int a=1;
    for(int j=1;j<i-1;j++)
    {
        bool megvan=true;
        for(int k=0;k<j;k++)
        {
            if(t1[j].ar == arak[k])
            {
                megvan=false;
                break;
            }
        }
        if(megvan)
        {
            arak[a]=t1[j].ar;
            a++;
        }
    }
    cout<<"Arak: ";
    for(int i=0;i<a;i++)
    {
        cout<<arak[i]<<" ";
    }
    for(int p=0;p<j;p++)
    {
        ofstream ki (t2[p].megnevezes.c_str());
        for(int k=0;k<i-1;k++)
        {
            if(t2[p].tipuskod == t1[k].kod)
            {
                ki<<t1[k].ar<<" "<<t1[k].nev<<endl;
            }
        }
    }
    return 0;
}
