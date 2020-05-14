#include "GIC.h"

GIC::GIC() : S("")
{
}

GIC :: GIC(const GIC& G) : S(G.S), T(G.T), N(G.N), P(G.P)
{
    ///
}

GIC & GIC :: operator = (const GIC& G)
{
    if(this != &G)
    {
        this -> S = G.S;
        this -> T = G.T;
        this -> N = G.N;
        this -> P = G.P;
    }
    return *this;
}

void GIC :: Pas1()
{
    /// pas 1 - i) -> eliminam simbolurile neutilizabile
    std :: set <std :: string> S1;
    /// pastram neterminalele care ajung la conditii de oprire (terminale) direct
    for(std :: string i : N)
    {
        int ok = 0;
        for(std :: string o : P[i])
        {
            for(std :: string t : T)
            {
                if(o.find(t) != std :: string :: npos)
                {
                    S1.insert(i);
                    ok = 1;
                    break;
                }
            }
            if(ok)
                break;
        }
    }
    /// sau indirect

    for( std :: string i : N)
    {
        int ok = 0;
        for(std :: string o : P[i])
        {
            for(std :: string c : S1)
            {
                if(o.find(c)!= std :: string :: npos)
                {

                    S1.insert(i);
                    break;
                    ok = 1;
                }
            }
            if(ok)
                break;
        }
    }
    /// daca un neternimal nu se afla in S1, inseamna ca este neutilizabil
    /// si trebuie sters

    std :: set <std ::string> Eliminare;
    for(std :: string i : N)
    {
        int ok = 0;
        for(std :: string s : S1)
            if(s == i)
                ok = 1;
        if(ok == 0)
        {
            Eliminare.insert(i);

            P.erase(i);
            N.erase(i);
        }
    }

    for(auto i : P)
    {
        std :: set <std :: string> newlocalP;
        for(std :: string c : i.second)
        {
            std :: string A = "";
            for(char x : c)
            {
                int ok = 0;
                for (std :: string e : Eliminare)
                {
                    for(char l : e)
                    {
                        if(x == l)
                            ok = 1;
                    }
                }
                if(!ok)
                    A += x;
            }
            newlocalP.insert(A);
        }
        i.second = newlocalP;
    }

    /// pas 1 - ii)
    /// elimin productiile inaccesibile

    std :: set <std :: string > S2;

    S2.insert(S);
    for(std :: string i : P[S]) /// avem neterminalele in care sigur ajungem din S
    {
        for(std:: string n : N)
            if(i.find(n)!= std :: string :: npos)
                S2.insert(n);
    }
    ///pentru fiecare neterminal din S verificam in care alte terminale mai putem ajunge
    for(std :: string i : S2)
    {
        if(i != S)
        {
            for(std :: string x : P[i])
                for(std ::string n : N)
                    if(x.find(n)!= std :: string :: npos)
                        S2.insert(n);
        }
    }

    ///elimin toate neterminalele si productiile care nu sunt in S2
    /// adica cele inaccesibile

    for(std :: string i : N)
    {
        int ok = 0;
        for(std :: string s : S2)
            if(s == i)
                ok = 1;
        if(ok == 0)
        {
            P.erase(i);
            N.erase(i);
        }
    }

    Eliminare.clear();
    S1.clear();
    S2.clear();
}
void GIC :: Pas2()
{

    /// pasul 2

    /// daca S -> S, adaugam S' -> S| lambda

    int ok = 0;
    for(std :: string i : P[S])
    {
        for(char x : i)
            if(x == 'S')
            {
                ok = 1;
                break;
            }
        if(ok)
            break;
    }

    if(ok)
    {
        N.insert("S'");
        P["S'"].insert("S");
        P["S'"].insert("lambda");
    }



    /// eliminare lambda-productiile

    std :: set <std :: string > S1;
    std :: set <std :: string > S2;
    std :: set <std :: string > Eliminare;

    /// o sa retin in S1 neterminalele care duc doar in lambda
    /// iar in S2 neterminalele care duc in productii mai mari > 1 si care il contin  si pe lambda

    for(i : P)
    {
        for(std :: string x : i.second)
        {
            if(x.find("lambda")!= std :: string :: npos)
            {
                if(i.second.size() == 1)
                    S1.insert(i.first);
                else
                    S2.insert(i.first);
            }
        }
    }

    /// 2 - i)

    for(std :: string i : N)
    {
        /// stergem toate neterminalele care au ca productie doar lambda

        for(std :: string s : S1)
            if(s == i)
            {
                Eliminare.insert(i);
                P.erase(i);
                N.erase(i);
            }
    }

    for(i : P)
    {
        std :: set <std :: string> newlocalP;
        for(std :: string c : i.second)
        {
            std :: string A = "";
            for(char x : c)
            {
                int ok = 0;
                for (std :: string e : Eliminare)
                {
                    for(l : e)
                    {
                        if(x == l)
                            ok = 1;
                    }
                }
                if(!ok)
                    A += x;
            }
            newlocalP.insert(A);
        }
        i.second = newlocalP;
    }

    /// 2 - ii)

    for(i : P)
    {
        std ::set <std ::string > newlocalS;
        for(s : S2)
        {
            /// pentru fiecare Neterminal care are lambda productie si genereaza cuvinte mai mari de 1
            /// elimin din productie pe lambda
            if(i.first == s)
            {
                for(std :: string x : i.second)
                {
                    if(x != "lambda")
                        newlocalS.insert(x);
                }
                i.second = newlocalS;
                newlocalS.clear();
            }
        }
    }

    /// pentru fiecare simbol neterminal, daca in dreapta sa avem productie in care apare un simbol
    /// care genera un cuvant mai mare de 1 si productia lambda
    /// inlocuim cu cele doua variatii posibile(cu/fara lambda)

    for(i : P)
    {
        for(std :: string c : i.second)
        {
            for(char j : c)
            {
                char gasit;
                int ok = 0;
                std :: string A = "";
                for(std :: string s : S2)
                {
                    for(char s1 : s)
                    {
                        if(s1 == j)
                        {
                            ok = 1;
                            gasit = s1;
                            break;
                        }
                    }
                    if(ok)
                        break;
                }
                if(ok)
                {
                    for(char t : c)
                        if(t != gasit)
                            A += t;
                    i.second.insert(A);
                }
            }
        }
    }
}
void GIC :: Pas3()
{
    /// eliminare redenumiri

    std :: set <std :: string> Eliminare;

    for(i : P)
    {
        std ::set <std ::string > newS;
        for(std :: string x : i.second)
        {
            std :: string Replace = "";
            if(x.size() == 1)
            {
                for(std :: string n : N)
                    if(x.find(n)!= std :: string :: npos)
                    {
                        Replace = x;
                        Eliminare.insert(Replace);
                    }
            }

            if(Replace != "")
            {
                if(P[Replace].size() == 1)
                {
                    int ok = 0;
                    for(std :: string r : P[Replace])
                    {
                        {
                            for(std :: string n : N)
                                if(n == r)
                                {
                                    ok = 1;
                                    break;
                                }
                        }
                    }
                    if(ok)
                    {
                        std :: set <std ::string> R2;
                        std :: string O;
                        while(P[Replace].size() ==1)
                        {
                            for(std :: string k :P[Replace])
                                O += k;
                            Replace = O;
                            // std :: cout << "R2 : " <<R2 << "\n";
                        }
                    }
                }
                for(std :: string p :P[Replace])
                    newS.insert(p);

            }
            else if(Replace == "")
                newS.insert(x);

        }
        i.second =(newS);
    }

    ///Daca un neterminal gasit ca redenumire mai sus, nu mai apare in dreapta altor productii, il eliminam

    for(std :: string e : Eliminare)
    {
        int ok = 0;
        for(i : P)
        {
            for(std :: string x : i.second)
            {
                if(x.find(e)!= std :: string :: npos)
                {
                    ok = 1;
                    break;
                }
            }
            if(ok)
                break;
        }
        if(ok == 0)
        {
            N.erase(e);
            P.erase(e);
        }
    }
}

void GIC :: Pas5()
{
    ///daca in productii apar terminale in cuvinte mai lungi de 1
    /// inlocuim terminalele de forma "a" din cuv "Ba" cu
    /// neterminale de forma "Xa", cu Xa -> a

    std ::set <std ::string > Nou;

    for(i : P)
    {
        std :: set <std ::string > newS;
        for(std :: string x : i.second)
        {
            std :: string A = "";
            std :: string B = "";
            if(x.size() > 1)
            {
                for(char c : x)
                {
                    int ok = 0;
                    for(std :: string t : T)
                    {
                        if(t.find(c) != std :: string ::npos)
                        {

                            A += "X";
                            A += c;
                            B += "X";
                            B += c;
                            std :: string g="";
                            g += c;
                            P[B].insert(g);
                            N.insert(B);
                            Nou.insert(B);
                            B.clear();
                            g.clear();
                            ok = 1;
                            break;

                        }
                    }
                    if(ok == 0)
                        A += c;
                }

            }
            if(A != "")
                newS.insert(A);
            else
                newS.insert(x);
        }
        i.second  = (newS);
        newS.clear();
    }

    /**
    unde avem
    cuvinte mai lungi, păstrăm doar primul neterminal din cuvânt şi îi alipim un neterminal nou,
    iar noul neterminal va avea o producţie cu membrul drept cuvântul pe care l-a înlocuit.

    */

    std :: map < std ::string, std :: string > D;
    std :: map < std ::string, std :: string > D1;
    int k = 1;

    for(i : P)
    {
        int dim;
        for(std :: string x : i.second)
        {
            dim = 0;
            for(std :: string n : N)
            {
                if(x.find(n) != std :: string :: npos)
                    dim ++;
            }
            if(dim > 2)
            {
                std :: string B = x, C, proba;
                while(dim > 2)                  /// se reia procedeul pana cand toate cuvintele ajung la lungimea 2.
                {
                    proba = B.substr(0, 2);
                    int  ok = 0;
                    for(f : Nou)
                    {
                        if(proba == f)
                            ok = 1;
                    }
                    if(ok)
                        C = B.substr(2, B.size() + 1);
                    else
                        C = B.substr(1, B.size() + 1);
                    ok = 1;
                    for(d : D)
                    {
                        if(d.second == C)
                            ok = 0;
                    }
                    if(ok)
                    {
                        std :: string Y = "Y";
                        Y += std ::to_string(k);
                        k ++;
                        D[Y] = C;
                    }
                    B = C;
                    dim --;
                }
            }
        }
    }

    D1 = D;
    int p, pmin;
    for(i : D)
    {
        pmin=1000;
        p = 1000;
        std :: string x, y, A;
        for(j : D)
        {
            A = "";
            if(i != j)
            {

                if(i.second.find(j.second) != std ::string ::npos)
                {
                    p = i.second.find(j.second);
                    if(pmin > p)
                    {
                        pmin = p;
                        x = j.second;
                        y = j.first;
                        ///A += i.second.substr(j.second.size()+1, i.second.size()-1)
                    }
                }

            }
        }
        if(pmin != 1000)
        {
            A += i.second.substr(0,pmin);
            A += y;

            i.second = A;
        }


    }
    /// inlocuiesc in gramatica noile productii pe care le-am retinut in D1

    for(i : P)
    {
        std ::set <std ::string > newR;
        for(std :: string x : i.second)
        {
            int poz, minpoz=10000;
            std :: string A = "", u;
            if(x.size() > 2)
            {
                for(d : D1)
                {
                    if(x.find(d.second) != std :: string::npos)
                    {
                        poz = x.find(d.second);
                        if(minpoz > poz)
                        {
                            u = d.first;
                            minpoz = poz;
                        }

                    }
                }
                A += x.substr(0, minpoz);
                A += u;
                newR.insert(A);
                A.clear();
            }
            else
                newR.insert(x);
        }
        i.second = newR;
    }
    for(i : D)
    {
        N.insert(i.first);
        P[i.first].insert(i.second);
    }

}
void GIC :: Afisare()
{

    for(auto i : getProductii())
    {
        std :: cout << i.first << " -> ";
        unsigned int l = 0;
        for(std :: string j : i.second)
        {
            l ++;
            if(l == i.second.size())
                std :: cout << j;
            else
                std :: cout << j << "|";
        }
        std :: cout << "\n";
    }

}


