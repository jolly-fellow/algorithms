#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "graph.hpp"
#include "list.hpp"

namespace algorithms {

    class string;

    int damerau_levenshtein_distance(const string & s1, const string & s2);

    void test();
}
#endif //ALGORITHMS_HPP
