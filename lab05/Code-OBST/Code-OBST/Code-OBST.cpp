#include <iostream>

using namespace std;

#define MAX 10000

const int n = 7;
double p[n + 1] = {0,0.04,0.06,0.08,0.02,0.10,0.12,0.14};
double q[n + 1] = {0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05};
int root[n + 1][n + 1];//Record the root node of the optimal subtree
double e[n + 2][n + 2] = { 0 };//Record the expected cost of the subtree
double w[n + 2][n + 2] = { 0 };//Record the probability sum of the subtree

void optimal_binary_search_tree(double *p,double *q,int n)
{   
    for (int i = 1; i <= n; ++i) {
        w[i][i] = p[i] + q[i - 1] + q[i];
    }
    for (int i = 1; i <=n; ++i) {
        for (int j = 1; j <= n - i; ++j) {
            w[j][i + j] = w[j][j + i - 1] + p[j + i] + q[j + i];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n - i+1; ++j) {
            for (int k = 1; k <= i; ++k) {
                double left, right;
                if (k == 1) {
                    left = 2 * q[j - 1];
                }
                else {
                    left = e[j][j + k-2] + w[j][j + k-2];
                }
                if (k == i) {
                    right = 2 * q[j + i-1];
                }
                else {
                    right = e[j + k][j + i - 1] + w[j + k][j + i - 1];
                }
                
                double sum = left + right + p[j + k - 1];
                if (e[j][i + j - 1] == 0||e[j][i + j - 1] > sum) {
                    e[j][i + j - 1] = sum;
                    root[j][i + j - 1] = j + k - 1;
                }
            }
        }
    }
//The result is stored in e.
/*

Please write your code here.
*/

}

/*
You can print the structure of the optimal binary search tree based on root[][]
The format of printing is as follows:k2 is the root
k1 is the left child of k2
d0 is the left child of k1
d1 is the right child of k1
k5 is the right child of k2
k4 is the left child of k5
k3 is the left child of k4
d2 is the left child of k3
d3 is the right child of k3
d4 is the right child of k4
d5 is the right child of k5
*/
void construct_optimal_bst(int i, int j)
{
    if (i == 1 && j == n) {
        cout << root[1][n] << " is the root\n";
    }
    int root1 = root[i][j];
    if (root1 != i) {
        cout << root[i][root1 - 1] << " is the left child of " << root1 << endl;
        construct_optimal_bst(i, root1 - 1);
    }
    if (root1 != j) {
        cout<<root[root1+1][j]<< " is the right child of " << root1 << endl;
        construct_optimal_bst(root1 + 1,j);
    }
}
/*
Please write your code here.
*/


int main()
{
    optimal_binary_search_tree(p,q,n);
    cout<<"The cost of the optimal binary search tree is: "<<e[1][n]<<endl;
    cout << "The structure of the optimal binary search tree is: " << endl;
    construct_optimal_bst(1,n);
    return 0;
}
