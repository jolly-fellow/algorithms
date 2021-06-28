//
// Created by alex on 6/18/21.
//

#include "sort.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

namespace algorithms::list {
    using namespace std;

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

    void test() {

        cout << "\nSort test" << endl;

    }
}