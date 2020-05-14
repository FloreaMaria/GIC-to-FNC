#include <iostream>
#include <string>
#include <map>
#include <set>
#pragma once

class GIC
{
    std :: string S;
    std :: set<std :: string> T, N;
    std :: map<std :: string, std :: set<std :: string>> P;

public:

    GIC();
    GIC(const GIC&);
    virtual ~GIC() = default;

    void setStart(std :: string newStart){
        this -> S = newStart;
    }

    std :: string getStart()const{
        return this -> S;
    }

    void setNeterminale(std :: set <std :: string > newN){
        this -> N = newN;
    }

    std :: set< std :: string > getNeterminale() const{
        return this -> N;
    }

    void setTerminale(std :: set <std :: string > newT){
        this -> T = newT;
    }

    std :: set< std :: string > getTeterminale()const{
        return this -> T;
    }

    void setProductii(std :: map <std :: string, std :: set<std ::string>> prod){
            this -> P = prod;
    }

    std :: map<std ::string,std ::set<std::string>> getProductii()const{
        return this -> P;
    }

    void Pas1();
    void Pas2();
    void Pas3();
    void Pas5();
    void Pas6();
    void Afisare();
    GIC & operator =(const GIC&);
    friend std :: ostream& operator << (std :: ostream&, const GIC&);


};

