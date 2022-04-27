//
// Created by alex on 6/18/21.
//

#include "sort.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

namespace algorithms::sort {
    using namespace std;

    template <typename T>
    std::vector<T> merge_sorted_arrays(std::vector<T> v1, std::vector<T> v2) {
        auto v1_size = v1.size();
        auto v2_size = v2.size();
        std::vector<T> res;
        res.reserve(v1_size + v1_size);

        int i = 0, j = 0;
        while (i < v1_size && j < v2_size) {
            if (v1[i] < v2[j]) {
                res.push_back(v1[i++]);
            }
            else {
                res.push_back(v2[j++]);
            }
        }
        // copy remaining elements
        while (i < v1_size) {
            res.push_back(v1[i++]);
        }
        while (j < v2_size) {
            res.push_back(v2[j++]);
        }

        return res;
    }

    template <typename BidirIt, typename Compare = std::less<>>
    void merge_sort(BidirIt first, BidirIt last, Compare cmp = Compare {})
    {
        const auto n = std::distance(first, last);

        if (n > 1) {
            const auto middle = std::next(first, n / 2);

            merge_sort(first, middle, cmp);
            merge_sort(middle, last, cmp);

            std::inplace_merge(first, middle, last, cmp);
        }
    }

    // return number of inversions in the array (number of swaps need to sort the array)
    template <typename T>
    int inplace_merge_sorted_array(std::vector<T> & v, int low, int mid, int high) {
        std::vector<T> temp(high - low + 1);
        int k = 0, i = low, j = mid + 1;
        int inversions = 0;
        // while there are elements in the left and right runs
        while (i <= mid && j <= high) {
            if (v[i] < v[j]) {
                temp[k++] = v[i++];
            }
            else {
                temp[k++] = v[j++];
                inversions += (mid - i + 1);    // NOTE
            }
        }
        // copy remaining elements
        while (i <= mid) {
            temp[k++] = v[i++];
        }
        while (j <= high) {
            temp[k++] = v[j++];
        }
        // Assign sorted data stored in temp[] to a[].
        for (i = low; i <= high; i++) {
            v[i] = temp[i - low];
        }
        return inversions;
    }


//    template <typename BidirIt>
//    int merge_sort_count_inversions(BidirIt first, BidirIt last) {
    template <typename T>
    int merge_sort_count_inversions(std::vector<T> & v,  int low, int high) {
        int inversions = 0;

        if (low < high) {
            int mid = (low + high) / 2;

            inversions += merge_sort_count_inversions(v, low, mid);
            inversions += merge_sort_count_inversions(v, mid + 1, high);

            // std::inplace_merge(v.begin() + low, v.begin() + mid+1, v.begin() + high, std::less<>());
            // std::merge(first, middle, middle+1, last, out_first);
            //merge_count_inversions(first, middle, last, inversions);
            inversions += inplace_merge_sorted_array(v, low, mid, high);
        }
        return inversions;
    }

    void print_vector(const vector<int> &v) {
        for(auto i: v) {
            cout << i << " ";
        }
        cout << endl;
    }

    // Google interview task
    vector<int> task(vector<vector<int>> m) {

        std::map<int, pair<int,int>> my_map;

        int rows_num = m.size();
        int cols_num = m[0].size();

        vector<int> result;

        int curr_col = 0;
        int curr_row = 0;
        int curr_val = m[curr_row][curr_col];

        result.push_back(curr_val);

        // Init the map
        for (int i = 0; i < rows_num; ++i) {
            for (int j = 0; j < cols_num; ++j) {
                my_map[m[i][j]] = std::make_pair(i,j);
            }
        }

        auto res = my_map.upper_bound(curr_val);

        while(res != my_map.end()) {
            if(res->second.first == curr_row || res->second.second == curr_col) {
                // found next value
                curr_col = res->second.second;
                curr_row = res->second.first;
                curr_val = m[curr_row][curr_col];
                result.push_back(curr_val);
            }
            res = my_map.upper_bound(res->first);
        }

        return result;
    }

    void test() {

        std::vector<int> v1 {1,2,3,4,5};
        std::vector<int> v2 {4,5,6,7,8,9};
        std::vector<int> v3 {1,2,3,4,5};
        std::vector<int> v4 {1, 9, 6, 4, 5}; // 5 inversions
        std::vector<int> v5 {1, 3, 4, 2}; // 2 inversions
        auto t = merge_sorted_arrays(v1, v2);

        vector<vector<int>> matrix{{1,  -1,  0,  -2,  -3},

                                   {-4, -7,  4,  5,   -6},

                                   {8,  -10, -8, 6,   7},

                                   {2,  -21, 3,  -20, 18},

                                   {9,  -22, 10, -5,  14}};


//        auto res = task(matrix);

//        print_vector(res);

        cout << "\nSort test" << endl;
        print_vector(t);

//        vector<int> out {1,2,3,1,2,3};
//        vector<int> out2;
//        int invers = 0;
//        invers = merge_sort_count_inversions(v5, 0, v5.size()-1);
        // merge_sort(v4.begin(), v4.end());

//        auto middle = out.begin() + (out.end() - out.begin()) / 2;
//        merge_count_inversions(out.begin(), middle, out.end(), invers);

        // invers = MergeSort(v5, 0, v5.size()-1);
//        cout << "\nNumber inversions: " << invers <<  endl;
//        print_vector(v5);
    }
}