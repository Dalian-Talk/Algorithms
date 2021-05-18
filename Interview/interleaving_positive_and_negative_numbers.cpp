#include <iostream>
#include <vector>

using namespace std;


void interleaving_positive_and_negative_numbers(vector<int>& nums) {
    vector<int> res;
    int nega_count = 0;
    int posi_count = 0;
    for (auto n : nums) {
        if (n < 0) {
            nega_count++;
        }
        else {
            posi_count++;
        }
    }
    bool flag = nega_count >= posi_count;
    int nega_idx = 0;
    int posi_idx = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (flag) {
            while (nums[nega_idx] > 0) {
                nega_idx++;
            }
            res.push_back(nums[nega_idx++]);
            nega_count--;
            flag = !flag;
        }
        else {
            while (nums[posi_idx] < 0) {
                posi_idx++;
            }
            res.push_back(nums[posi_idx++]);
            posi_count--;
            flag = !flag;
        }
    }
    for (auto r : res) {
        cout << r << ' ';
    }
}

void interleaving_positive_and_negative_numbers1(vector<int>& nums) {
    int length = nums.size();
    int posi_count = 0;

    for (auto& n : nums) {
        if (n > 0) {
            posi_count++;
        }
    }

    int posi_idx = 0;
    int nega_idx = 1;
    if (posi_count <= length / 2) {
        posi_idx = 1;
        nega_idx = 0;
    }

    while (posi_idx < length && nega_idx < length) {
        while (posi_idx < length && nums[posi_idx] > 0) {
            posi_idx += 2;
        }
        while (nega_idx < length && nums[nega_idx] < 0) {
            nega_idx += 2;
        }
        if (posi_idx < length && nega_idx < length) {
            swap(nums[posi_idx], nums[nega_idx]);
        }

    }

    for (auto n: nums) {
        cout << n << ' ';
    }
}

//  0  1  2  3  4  5  6  7  8
//  a  b  c  d  e  f  g  h  i

// posi_idx = 0
// nega_idx = 1
//  正 负 正  负 正 负  正 负 正







int main() {
    vector<int> nums{-1, -2, 7, 8, 9};
    interleaving_positive_and_negative_numbers(nums);
    cout << endl;
    interleaving_positive_and_negative_numbers1(nums);
    return 0;
}

