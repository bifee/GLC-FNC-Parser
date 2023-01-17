#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <vector>
using namespace std;

int main()
{
    multimap<string, string> terminals;
    multimap<string, string>::iterator it;
    vector<string> vs;
    int P = 0;
    string s, sd, se, seta;
    bool loop = true;

    cin >> P;

    for (int i = 0; i < P; i++)
    {
        cin >> se >> seta >> sd;
        terminals.insert(pair<string, string>(se, sd)); // armazena as produçoes com pair em um multimap
    }
    while (loop)
    {
        cin >> s;
        if (s == "*")
        {
            return 0;
        }
        string aux = s;
        int trocas = 0;
        while (s != "S")
        {
            trocas = 0;
            for (int j = 0; j < s.length(); j++)
            { // percorre a palavra comparando os caracteres com os sd(simbolos da direita) do map
                vs.push_back(s);
                for (it = terminals.begin(); it != terminals.end(); it++)
                {
                    if (isupper(s[j]))
                    { // verifica se a palavra esta em simbolos terminais ou nao
                        if ((j + 1) != s.length())
                        { // caso esteja, analisa a palavra de duas em duas letras
                            string sub = s.substr(j, 2);
                            if (sub == it->second)
                            {
                                if (it->first == "S")
                                { // verifica se é possivel trocar por S, no caso de ter mais de uma produçao pra 1 simbolo se(simbolo da esquerda)
                                    if (s.length() == it->second.length())
                                    {
                                        s.replace(j, 2, it->first);
                                        trocas++;
                                        j = -1;
                                        break;
                                    }
                                }
                                else
                                {
                                    if (s.length() != it->second.length())
                                    {
                                        s.replace(j, 2, it->first);
                                        trocas++;
                                        j = -1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    else
                    { // senao, percorre uma por uma letra terminal, procurando uma produçao
                        string aux1(1, s[j]);
                        if (aux1 == it->second)
                        {
                            if (it->first != "S" || s.length() == it->second.length())
                            {
                                s.replace(j, 1, it->first);
                                trocas++;
                                break;
                            }
                            else
                            {
                                cout << aux << ": NAO" << endl; // se nao houver produçao para simbolos terminais, ja diz que nao pertence a linguagem
                                break;
                            }
                        }
                    }
                }
            }
            if (trocas == 0)
            {
                cout << aux << ": NAO" << endl;
                break;
            }
        }
        if (s == "S")
        {
            cout << aux << ": SIM" << endl;
            for (int i = vs.size() - 1; i >= 0; i--)
            {
                cout << vs[i] << endl;
            }
            cout << endl;
        }
        for (int l = vs.size() - 1; l >= 0; l--)
        {
            vs.pop_back();
        }
    }
    return 0;
}