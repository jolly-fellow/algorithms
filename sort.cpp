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

        int i = v1_size;
        int j = v2_size;
        while (i >= 0 || j >= 0) {

            if (v1[i] < v2[j]) {
                res.push_back(v2[j]);
                --j;
            }
            else {
                if (v1[i] == v2[j]) {
                    res.push_back(v1[i]);
                    --i;
                }
                res.push_back(v2[j]);
                --j;
            }

            if (i == 0) {
                while (j >= 0) {
                    res.push_back(v2[j]);
                    --j;
                }
            }
            if (j == 0) {
                while (i >= 0) {
                    res.push_back(v1[i]);
                    --i;
                }
            }
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

    void print_vector(const vector<int> &v) {
        for(auto i: v) {
            cout << i << " ";
        }
        cout << endl;
    }

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
        auto t = merge_sorted_arrays(v1, v2);

        vector<vector<int>> matrix{{1,  -1,  0,  -2,  -3},

                                   {-4, -7,  4,  5,   -6},

                                   {8,  -10, -8, 6,   7},

                                   {2,  -21, 3,  -20, 18},

                                   {9,  -22, 10, -5,  14}};


        auto res = task(matrix);

        print_vector(res);

        cout << "\nSort test" << endl;

    }
}