#include <iostream>
#include <vector>

using namespace std;


//  0  1  2  3  4  5  6  7
//  7  6  5  4  3  2  1  0


// O(1) space这种。不用太头铁说一次要把两个直接交换记住。。。一个一个换然后记录自己当前换到哪里也行。。。

// 0 1 2 3 4 5 6 7
// 7 1 2 3 4 5 6 7





void meandering_array(vector<int>& nums) {
    // https://www.geeksforgeeks.org/rearrange-array-maximum-minimum-form-set-2-o1-extra-space
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int max_idx = n - 1;
    int min_idx = 0;
    // store maximum element of array
    int max_elem = nums[n - 1] + 1;

    // traverse array elements
    for (int i = 0; i < n; i++) {
        // at even index : we have to put maximum element
        if (i % 2 == 0) {
            nums[i] += (nums[max_idx] % max_elem) * max_elem;
            max_idx--;
        }

            // at odd index : we have to put minimum element
        else {
            nums[i] += (nums[min_idx] % max_elem) * max_elem;
            min_idx++;
        }
    }

    // array elements back to it's original form
    for (int i = 0; i < n; i++)
        nums[i] = nums[i] / max_elem;
}



int main() {
    vector<int> nums{0, 1, 2, 3, 4, 5, 6, 7};
    meandering_array(nums);
    return 0;
}