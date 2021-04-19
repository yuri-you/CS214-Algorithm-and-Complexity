#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include <set>
using namespace std;
int signals[300000];
bool vertexs[100000];
//Please put this source code in the same directory with SCC.in
//And do NOT change the file name.
/*
This function computes the number of Strongly Connected Components in a graph
Args:
    n: The number of nodes in the graph. The nodes are indexed as 0~n-1
    edge: The edges in the graph. For each element (a,b) in edge, it means
          there is a directed edge from a to b
          Notice that there may exists multiple edge and self-loop
Return:
    The number of strongly connected components in the graph.
*/
int* _SCC;
vector<int> _size;
int mins(int a, int b) {
    return (a < b) ? a : b;
}
int Search(vector<vector<int>>& graph,int* DFN,int* LOW,int vetex,int& time,int& ans,stack<int>& s,bool* in_stack) {
    ++time;
    in_stack[vetex] = true;
    s.push(vetex);
    DFN[vetex] = LOW[vetex]=time;
    for (int k : graph[vetex]) {
        if (DFN[k]!=0) {// have explored
            if (in_stack[k])
                LOW[vetex] = mins(LOW[k], LOW[vetex]);
        }
        else{//haven't explored
            Search(graph, DFN, LOW, k, time, ans,s,in_stack);
            LOW[vetex] = mins(LOW[vetex], LOW[k]);
        }
    }
    if (DFN[vetex] == LOW[vetex]) {//vetex and its subtree is a SCC
        int total_size=0;
        int pop_node=s.top();
        in_stack[pop_node] = false;
        _SCC[pop_node] = ans;
        ++total_size;
        while (pop_node != vetex) {
            s.pop();
            pop_node = s.top();
            in_stack[pop_node] = false;
            _SCC[pop_node] = ans;
            ++total_size;
        }
        s.pop();//Pop this tree in the stack
        _size.push_back(total_size);
        ++ans;//The number of SCC increases
    }
    return LOW[vetex];
}
void SCC(int n, vector<pair<int,int>>& edge) {
    _SCC = new int[n];
    vector<vector<int>> graph;
    for (int i = 0; i < n; ++i) {
        graph.push_back(vector<int>());
    }
    for (pair<int,int> t : edge) {
        graph[t.first].push_back(t.second);
    }//change to the adjacency list
    int* DFN = new int[n];//The time explore the n
    int* LOW = new int[n];//The minimum time explore the n or its subtree
    bool* in_stack= new bool[n];
    memset(DFN, 0, n * sizeof(n));
    memset(in_stack, 0, (n) * sizeof(bool));
    int now = 0;
    int now_SCC = 0;
    int time = 0;
    stack<int> s;
    while (now <n) {
        if (DFN[now]==0) {
            Search(graph,DFN, LOW, now, time,now_SCC,s,in_stack);
        }
        ++now;
    }
    delete[] DFN;
    delete[] LOW;
    delete[] in_stack;
}
//Please do NOT modify anything in main(). Thanks!
int main()
{
    int m,n;
    vector<pair<int,int>> edge;
    ifstream gin;
    memset(vertexs, 0, sizeof(vertexs));
    gin.open("compare.txt");
    int all;
    gin >> all;
    for (int now = 0; now < all; ++now) {
        int num;
        gin >> num;
        for (int i = 0; i < num; ++i) {
            int v;
            gin >> v;
            signals[v] = now;
        }
    }
    for (int i = 0; i < all; ++i) {
        if (signals[i] == 3)
            cout << i << " ";
    }
    ifstream fin;
    ofstream fout;
    fin.open("SCC.in");
    cout<<fin.is_open()<<endl;
    fin>>n>>m;
    cout<<n<<" "<<m<<endl;
    int tmp1,tmp2;
    fout.open("SCC_disposal.csv");
    for(int i=0;i<m;i++)
    {
        fin>>tmp1>>tmp2;
        edge.push_back(pair<int,int>(tmp1,tmp2));
    }
    SCC(n, edge);
    set<pair<int,int>> dis;
    for (int i = 0; i < m; ++i) {
        pair<int,int> a = edge[i];
        if(_SCC[a.first]!=_SCC[a.second])dis.insert(make_pair(_SCC[a.first], _SCC[a.second]));
    }
    for (auto k : dis) {
        fout << k.first << "," << k.second << endl;
    }
    delete[]_SCC;
    fin.close();
    fout.close();
    ofstream another;
    return 0;
}
