#include <bits/stdc++.h>
#include <string>

using namespace std;

ifstream in("graf.in");
ofstream out("graf.out");

int i, j, nr_stari, nr_muchii, nod_start, nr_noduri_fin;
vector <pair < pair<int, int>, char>> LNFA;
vector <int> noduri_finale;
set <char> litere;
vector <list<int>> L_inchideri;
string matrice_adiacenta[1000][1000];

void showlist(list <int> lista)
{
    list <int> :: iterator itr;
    for(itr = lista.begin(); itr != lista.end(); ++itr)
        cout << *itr << " ";
}

int main()
{
    /////// CITIRE
    in >> nr_stari >> nr_muchii;
    for (i =  1; i <= nr_muchii; i++)
    {
        pair< pair<int, int>, char> pair1;
        in >> pair1.first.first >> pair1.first.second >> pair1.second;
        LNFA.push_back(pair1);
        matrice_adiacenta[pair1.first.first][pair1.first.second] +=pair1.second;
        litere.insert(pair1.second);
    }

    in >> nod_start >> nr_noduri_fin;

    for (i = 1; i <= nr_noduri_fin; i++)
    {
        int x;
        in >> x;
        noduri_finale.push_back(x);
    }

    ///////

    /*
    for (i = 0; i < nr_muchii; i++)
    {
        out << LNFA[i].first.first << " " << LNFA[i].first.second << " " << LNFA[i].second << '\n';
    }

    for (i = 0; i < nr_stari; i++)
    {
        for (j = 0; j < nr_stari; j++)
        {
            if (matrice_adiacenta[i][j].size() != 0)
                cout << matrice_adiacenta[i][j] << " ";
            else
                cout << "0 ";
        }
        cout << endl;
    }
    */

    /////// FAC LAMBDA_INCHIDERILE
    for (i = 0; i < nr_stari; i++)
    {
        list<int> lista;
        L_inchideri.push_back(lista);
    }

    for (i = 0; i < nr_stari; i++)
    {
        L_inchideri[i].push_front(i);
        for (j = 0; j < nr_stari; j++)
        {

            if (matrice_adiacenta[i][j].find("#") < matrice_adiacenta[i][j].size())
            {
                L_inchideri[i].push_front(j);
                list<int> copie;
                copie = L_inchideri[j];
                L_inchideri[i].merge(copie);
            }

        }
        L_inchideri[i].sort();
        L_inchideri[i].unique();
    }

    for (i = 0; i < nr_stari; i++)
    {
        list <int> :: iterator itr;
        for (itr = L_inchideri[i].begin(); itr != L_inchideri[i].end(); itr++)
        {
            for (j = 0; j < nr_stari; j++)
            {
                if (int(*itr) == j)
                {
                    list<int> copie;
                    copie = L_inchideri[j];
                    L_inchideri[i].merge(copie);
                    L_inchideri[i].sort();
                    L_inchideri[i].unique();
                }
            }
        }
    }

    ///////

    /*
    cout << endl;
    for (int k = 0; k < nr_stari; k++)
    {
        cout << "<q" << k << ">: ";
        showlist(L_inchideri[k]);
        cout << endl;
    }
    */

    /////// TRANSFORMARE AFD

    vector <vector <int>> inchideri_litere;
    vector <int> aux2;
    int ok = 1;
    for (i = 0; i < litere.size(); i++)
    {
        inchideri_litere.push_back(aux2);
    }

    for (i = 0; i < litere.size() - 1; i++)
    {
        int nr;
        list <int> :: iterator itr;
        for (itr = L_inchideri[0].begin(); itr != L_inchideri[0].end(); ++itr)
        {nr = 0;
            for (j = nr_stari - 1; j >= 0; j--)
            {
                if (matrice_adiacenta[int(*itr)][j].find(char(i + 97)))
                {
                    nr = nr*10 + j;

                }
            }
        }
        inchideri_litere[i].push_back(nr);
        cout << char(i + 97) << " " << nr << " \n";
    }

    return 0;
}
