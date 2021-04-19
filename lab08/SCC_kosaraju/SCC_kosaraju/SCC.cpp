#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;
stack<int> s;
struct vertex {
    bool explore, explore2;
    vertex() :explore(false),explore2(false) {}
};
void DFS1(vector<vector<int>>& graph, vertex* v,int vertex) {
    v[vertex].explore = true;
    for (auto k : graph[vertex]) {
        if (!v[k].explore) {
            DFS1(graph, v, k);
        }
    }
    s.push(vertex);
}
void DFS2(vector<vector<int>>& graph, vertex* v, int vertex) {
    v[vertex].explore2 = true;
    for (auto k : graph[vertex]) {
        if (!v[k].explore2) {
            DFS2(graph, v, k);
        }
    }
}
int SCC(int n, vector<pair<int,int>>& edge) {
    vector<vector<int>> graph;
    vector<vector<int>> anti_graph;
    for (int i = 0; i < n; ++i) {
        graph.push_back(vector<int>());
        anti_graph.push_back(vector<int>());
    }
    for (pair<int,int> t : edge) {
        graph[t.first].push_back(t.second);
        anti_graph[t.second].push_back(t.first);
    }//change to the adjacency list
    vertex* v = new vertex[n];
    int now = 0;
    int ans = 0;
    while (now < n) {
        if (!v[now].explore) {
            DFS1(anti_graph,v,now);
        }
        ++now;
    }
    while (!s.empty()) {
        int v1 = s.top();
        s.pop();
        if (!(v[v1].explore2)) {
            DFS2(graph, v, v1);
            ++ans;
        }
    }
    delete[]v;
    return ans;
}
//Please do NOT modify anything in main(). Thanks!
int main()
{
    int m,n;
    vector<pair<int,int>> edge,another;
    ifstream fin;
    ofstream fout;
    fin.open("SCC.in");
    cout<<fin.is_open()<<endl;
    fin>>n>>m;
    cout<<n<<" "<<m<<endl;
    int tmp1,tmp2;
    for(int i=0;i<m;i++)
    {
        fin>>tmp1>>tmp2;
        edge.push_back(pair<int,int>(tmp1,tmp2));
    }
    fin.close();
    int ans=SCC(n,edge);
    fout.open("SCC.out");
    fout<<ans<<'\n';
    cout << ans;
    fout.close();
    return 0;
}
