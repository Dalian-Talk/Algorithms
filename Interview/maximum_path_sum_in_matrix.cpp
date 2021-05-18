#include <iostream>
#include <vector>

using namespace std;

//  0  1  2
// 13 12 56
//  4  5  6

// 1
// 2
// 3


int maximum_path_sum_in_matrix(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

//    if (m == 1) {
//        int res = 0;
//        for (int i = 0; i < n; i++) {
//            res += matrix[i][0];
//        }
//        return res;
//    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == 0) {
                matrix[i][j] += max(matrix[i - 1][j], m == 1? INT_MIN : matrix[i - 1][j + 1]);
            }
            else if(j == m - 1) {
                matrix[i][j] += max(matrix[i - 1][j], m == 1? INT_MIN : matrix[i - 1][j - 1]);
            }
            else {
                matrix[i][j] += max(matrix[i - 1][j - 1], max(matrix[i - 1][j], matrix[i - 1][j + 1]));
            }

        }
    }
    int res = INT_MIN;
    for (int j = 0; j < m; j++) {
        res = max(res, matrix[n - 1][j]);
    }
    return res;
}


int main() {
//    vector<vector<int>> matrix{
//            {10, 10, 2, 0, 20,4},
//            {1, 0, 0, 30, 2, 5},
//            {0, 10, 4, 0, 2, 0},
//            {1, 0, 2, 20, 0, 4}
//    };
    vector<vector<int>> matrix{
            {1},
            {2},
            {3},
    };
    cout << maximum_path_sum_in_matrix(matrix) << endl;
    return 0;
}