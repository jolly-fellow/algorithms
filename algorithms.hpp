#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "graph.hpp"
#include "list.hpp"
#include "sort.hpp"
#include <string>

namespace algorithms {



    int damerau_levenshtein_distance(const std::string & s1, const std::string & s2);

    void test();
}
#endif //ALGORITHMS_HPP
