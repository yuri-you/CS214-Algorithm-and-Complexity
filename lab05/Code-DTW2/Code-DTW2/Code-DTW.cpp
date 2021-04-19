#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
/*
The process to calculate the dynamic can be divided into four steps:
1.Create an empty cost matrix DTW with X and Y labels as amplitudes of the two series to be compared.
2.Use the given state transition function to fill in the cost matrix.
3.Identify the warping path starting from top right corner of the matrix and traversing to bottom left. The traversal path is identified based on the neighbor with minimum value.
i.e., When we reach the point (i, j) in the matrix, the next position is to choose the point with the smallest cost among (i-1,j-1), (i,j-1), and (i-1,j),
For the sake of simplicity, when the cost is equal, the priority of the selection is (i-1,j-1), (i,j-1), and (i-1,j) in order.
4.Calculate th time normalized distance. We define it as the average cost of the selected points.
*/
using namespace std;
vector<int> X1,Y1;
void warp_path(const vector<vector<int>>& data, vector<int>& ans, int n, int m,int constrain) {
    if (n == 0) {
        if (m != 0)warp_path(data, ans, n, m - 1, constrain);
    }
    else {
        if (m == 0)warp_path(data, ans, n - 1, m, constrain);
        else {
            int min = data[n - 1][m - 1];
            if (min > data[n - 1][m]&&abs(n-1-m)<=constrain)min = data[n - 1][m];
            if (min > data[n][m - 1] && abs(m - 1 - n) <= constrain)min = data[n][m - 1];
            if (min == data[n - 1][m - 1])warp_path(data, ans, n - 1, m - 1, constrain);
            else {
                if(min==data[n][m-1])warp_path(data, ans, n, m - 1, constrain);
                else {
                    warp_path(data, ans, n-1, m, constrain);
                }
            }
        }
    }
    cout << n << "," << m <<"   "<<data[n][m]<<" "<<X1[n]<<","<<Y1[m]<< endl;
    ans.push_back(data[n][m]);
}
double distance(vector<int> x, vector<int> y,int window_constrain) {
    int n = x.size();
    int m = y.size();
    vector<vector<int>> DTW;
    //Use the given state transition function to fill in the cost matrix.
    /*
    Please write your code here.
    
    */
    for (int i = 0; i < n; ++i) {
        DTW.push_back(vector<int>());
        for (int j = 0; j < n; ++j) {
            if (abs(i - j) > window_constrain) {
                DTW[i].push_back(-1);
                continue;
            }
            int d1, d2, d3;
            if (i == 0) {
                if (j == 0) {
                    d1 = d2 = d3 = 0;
                }
                else {
                    d2 = DTW[i][j - 1];
                    d1 = d3 = -1;
                }
            }
            else {
                if (j == 0) {
                    d1 = DTW[i - 1][j];
                    d2 = d3 = -1;
                }
                else {
                    d1 = DTW[i - 1][j];
                    d2 = DTW[i][j - 1];
                    d3 = DTW[i - 1][j - 1];
                }
            }
            if (d3 == -1) {
                if (d2 != -1)d3 = d2 + 1;
                else d3 = d1 + 1;
            }
            if (d1 < d3 && d1 != -1)d3 = d1;
            if (d2 < d3 && d2 != -1)d3 = d2;
            DTW[i].push_back(d3 + abs(x[i] - y[j]));
        }
    }
    vector<int> d;
    warp_path(DTW, d, n-1, m-1,window_constrain);
    //Identify the warping path.
    /*
    Please write your code here.
    */

    double ans = 0;
    cout << DTW[n - 1][m - 1] << endl;
    ans = double(DTW[n-1][m-1]) / d.size();
    //Calculate th time normalized distance
    /*
    Please write your code here.
    */
    return ans;
}

int main(){
	vector<int> X,Y;
	//test case 1
	X = {37,37,38,42,25,21,22,33,27,19,31,21,44,46,28};
	Y = {37,38,42,25,21,22,33,27,19,31,21,44,46,28,28};
    X1 = X, Y1 = Y;
	cout<<distance(X,Y,0)<<endl;
	//test case 2
	X = {11,14,15,20,19,13,12,16,18,14};
	Y = {11,17,13,14,11,20,15,14,17,14};
    X1 = X, Y1 = Y;
	cout<<distance(X,Y,1)<<endl;
	//Remark: when you modify the code to add the window constraint, the distance function has thus three inputs: X, Y, and the size of window w.
	return 0;
}
