#include <iostream>
#include <set>
#include <string>
#include<map>
#include "GIC.h"

using namespace std;


int main()
{
    GIC A;
    string S ="S";
    set<string> N;
    set<string> T;
    map<string, set<string> > P;

    N.insert("B");
    N.insert("S");
    N.insert("D");
    N.insert("F");
    N.insert("G");
    N.insert("H");

    T.insert("a");
    T.insert("b");
    T.insert("c");
    T.insert("d");
    T.insert("e");
    T.insert("f");
    T.insert("g");

    P["S"].insert("aBcDeF");
    P["S"].insert("HF");
    P["S"].insert("HBc");
    P["B"].insert("lambda");
    P["B"].insert("b");
    P["D"].insert("d");
    P["D"].insert("lambda");
    P["F"].insert("G");
    P["G"].insert("f");
    P["G"].insert("g");
    P["H"].insert("lambda");

    A.setStart(S);
    A.setNeterminale(N);
    A.setTerminale(T);
    A.setProductii(P);

    std :: cout << "GRAMATICA GIC : \n";
    A.Afisare();

    A.Pas1();
    A.Pas2();
    A.Pas3();
    A.Pas1();
    A.Pas5();
    std :: cout << "GRAMATICA IN FNC : \n";
    A.Afisare();

    return 0;
}
