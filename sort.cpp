//
// Created by alex on 6/18/21.
//

#include "sort.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <set>
#include <queue>

namespace algorithms::sort {
    using namespace std;

    template <typename T>
    vector<int> merge_sorted_arrays2(const vector<int>::iterator& v1, int v1_size, const vector<int>::iterator& v2, int v2_size) {
        vector<int> res;
        res.reserve(v1_size +  v2_size);
        int i1 = 0;
        int i2 = 0;

        while(i1 < v1_size && i2 < v2_size)  {

            if(v1[i1] < v2[i2]) {
                res.push_back(v1[i1++]);
            }
            else {
                res.push_back(v2[i2++]);
            }
        }

        while(i1 < v1_size) {
            res.push_back(v1[i1++]);
        }

        while(i2 < v2_size) {
            res.push_back(v2[i2++]);
        }

        return res;
    }

    template <typename T>
    std::vector<T> merge_sorted_arrays(std::vector<T> v1, std::vector<T> v2) {
        auto v1_size = v1.size();
        auto v2_size = v2.size();
        std::vector<T> res;
        res.reserve(v1_size + v1_size);

        int i1 = 0;
        int i2 = 0;
        while(i1 < v1_size && i2 < v2_size)  {

            if(v1[i1] < v2[i2]) {
                res.push_back(v1[i1++]);
            }
            else {
                res.push_back(v2[i2++]);
            }
        }

        while(i1 < v1_size) {
            res.push_back(v1[i1++]);
        }

        while(i2 < v2_size) {
            res.push_back(v2[i2++]);
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

    template <typename T>
    void print_vector(const vector<T> &v) {
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

    double get_median(vector<int> v) {
        auto v_size = v.size();

        if(v_size == 0) { return -1; }

        if(v_size%2) {
            return v[v_size / 2];
        }
        else {
            return static_cast<double>((v[v_size / 2]) + v[v_size / 2 + 1]) / 2;
        }
    }

    double get_median_sorted_arrays(vector<int> v1, vector<int> v2) {
        auto v1_size = v1.size();
        auto v2_size = v2.size();
        double res;
        return res;
    }

    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        multiset<int> window(nums.begin(), nums.begin() + k);
        auto mid = next(window.begin(), k / 2);
        vector<double> medians;
        for (int i=k; ; i++) {

            // Push the current median.
            medians.push_back((double(*mid) + *prev(mid, 1 - k%2)) / 2);

            // If all done, return.
            if (i == nums.size())
                return medians;

            // Insert nums[i].
            window.insert(nums[i]);
            if (nums[i] < *mid)
                mid--;

            // Erase nums[i-k].
            if (nums[i-k] <= *mid)
                mid++;
            window.erase(window.lower_bound(nums[i-k]));
        }
    }

    vector<double> medianSlidingWindow2(vector<int>& v, int k) {
        multiset<int> window(v.begin(), v.begin() + k);
        auto mid = next(window.begin(), k / 2);
        vector<double> medians;
        int v_size = v.size();
        for (int i=k; ;++i) {

            // Push the current median.
            // int p = ( k%2 == 0 ) ? *prev(mid) : 0;
            // medians.push_back( (double(*mid) + p) / 2 );
            medians.push_back( (double(*mid) + *prev(mid, 1 - k%2)) / 2);

            // If all done, return.
            if (i == v_size) {
                return medians;
            }

            // Insert v[i].
            window.insert(v[i]);
            if (v[i] < *mid) {
                mid--;
            }

            // Erase v[i-k].
            if (v[i - k] <= *mid) {
                mid++;
            }
            window.erase(window.lower_bound(v[i - k]));
        }
    }

    vector<double> medianSlidingWindow3(vector<int>& nums, int k) {
        vector<double> medians(nums.size() - k + 1);
        int j=0;
        std::multiset<int, std::greater<>> lo;
        std::multiset<int> hi;

        for (int i = 0; i < nums.size(); i++) {
            lo.insert(nums[i]);
            hi.insert(*lo.begin()); lo.erase(lo.begin());

            if (hi.size() > lo.size()) { lo.insert(*hi.begin()); hi.erase(hi.begin()); }

            if (lo.size() + hi.size() == k) {
                medians[j] = (lo.size()==hi.size()) ? (double)(*lo.begin() + *hi.begin()) / 2 : *lo.begin();

                auto l_found = lo.find(nums[j]);
                if(l_found != lo.end()) {
                    lo.erase(l_found);
                }
                else {
                    hi.erase(hi.find(nums[j]));
                }
                j++;
            }
        }
        return medians;
    }

    void test() {

        std::vector<int> v1 {1,2,3,4,5};
        std::vector<int> v2 {4,5,6,7,8,9};
        std::vector<int> v3 {1,2,3,4,5};
        std::vector<int> v4 {1, 9, 6, 4, 5}; // 5 inversions
        std::vector<int> v5 {1, 3, 4, 2}; // 2 inversions
        auto t = merge_sorted_arrays(v1, v2);

        cout << "\nMerge sorted arrays: " << endl;
        print_vector(t);
        cout << "\n----- " << endl;

        auto medians1 = medianSlidingWindow3(t, 4);
        auto medians2 = medianSlidingWindow(t, 4);
        auto medians3 = medianSlidingWindow2(t, 4);
        cout << "\nfind medians: " << endl;
        print_vector(medians1);
        cout << "\n----- " << endl;
        print_vector(medians2);
        cout << "\n----- " << endl;
        print_vector(medians3);
        cout << "\n----- " << endl;


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