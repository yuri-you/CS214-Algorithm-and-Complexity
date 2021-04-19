#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include<ctime>
#include<cstdlib>
using namespace std;
int main()
{
    int m, n;
    vector<pair<int, int>> edge;
    ifstream fin;
    ofstream fout;
    fin.open("SCC.in");
    cout << fin.is_open() << endl;
    fin >> n >> m;
    fout.open("SCC2.in");
    cout << n << " " << m << endl;
    fout << n << " " << m << endl;
    int tmp1, tmp2;
    for (int i = 0; i < m; i++)
    {
        fin >> tmp1 >> tmp2;
        edge.push_back(pair<int, int>(tmp1, tmp2));
    }
    fin.close();
    srand(time(0));
    random_shuffle(edge.begin(), edge.end());
    for (int i = 0; i < m; i++)
    {
        fout << edge[i].first <<" "<< edge[i].second<<endl;
    }
    fout.close();
    return 0;
}
