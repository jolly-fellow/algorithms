#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <list>
#include <unordered_map>
#include <assert.h>
#include "algorithms.hpp"

namespace algorithms {
    using namespace std;
/*
def damerau_levenshtein_distance(s1, s2):
    d = {}
    lenstr1 = len(s1)
    lenstr2 = len(s2)
    for i in range(-1,lenstr1+1):
        d[(i,-1)] = i+1
    for j in range(-1,lenstr2+1):
        d[(-1,j)] = j+1

    for i in range(lenstr1):
        for j in range(lenstr2):
            if s1[i] == s2[j]:
                cost = 0
            else:
                cost = 1
            d[(i,j)] = min(
                           d[(i-1,j)] + 1, # deletion
                           d[(i,j-1)] + 1, # insertion
                           d[(i-1,j-1)] + cost, # substitution
                          )
            if i and j and s1[i]==s2[j-1] and s1[i-1] == s2[j]:
                d[(i,j)] = min (d[(i,j)], d[i-2,j-2] + cost) # transposition

    return d[lenstr1-1,lenstr2-1]
 */
/*
 *  Simple implementation of Wagner–Fischer algorithm which calculate full matrix returns the distance number
 *  https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm
 *  Complexity: time O(M*N) space O(M*N)
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            dp[i][0] = i;
        }
        for (int j = 1; j <= n; j++) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
                }
            }
        }
        return dp[m][n];
    }


    // Optimized implementation of Wagner–Fischer algorithm
    // Complexity: time O(M*N) space O( min(M,N) )
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size(), pre;
        vector<int> cur(n + 1, 0);
        for (int j = 1; j <= n; j++) {
            cur[j] = j;
        }
        for (int i = 1; i <= m; i++) {
            pre = cur[0];
            cur[0] = i;
            for (int j = 1; j <= n; j++) {
                int temp = cur[j];
                if (word1[i - 1] == word2[j - 1]) {
                    cur[j] = pre;
                } else {
                    cur[j] = min(pre, min(cur[j - 1], cur[j])) + 1;
                }
                pre = temp;
            }
        }
        return cur[n];
    }


 */

    /*
     *  Simple implementation of Wagner–Fischer algorithm which calculate full matrix returns the distance number
     *  https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm
     *  https://leetcode.com/problems/edit-distance/discuss/25846/C%2B%2B-O(n)-space-DP
     *  Complexity: time O(M*N) space O(M*N)
     */
    int levenshtein_distance_simple(const std::string & s1, const std::string & s2) {
        int m = s1.size(), n = s2.size();

        if(m == n == 0) return 0;
        if(m == 0) return n;
        if(n == 0) return m;

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));


        for (int i = 1; i <= m; i++) {
            dp[i][0] = i;
        }
        for (int j = 1; j <= n; j++) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::min({dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]}) + 1;
                }
            }
        }
        return dp[m][n];
    }

    // Optimized implementation of Wagner–Fischer algorithm
    // Complexity: time O(M*N) space O( min(M,N) )
    int levenshtein_distance(const std::string & s1, const std::string & s2) {
        int m = s1.size(), n = s2.size(), pre;

        if(m == n == 0) return 0;
        if(m == 0) return n;
        if(n == 0) return m;

        vector<int> cur(n + 1, 0);

        std::iota(cur.begin()+1, cur.end(), 1);

        for (int i = 1; i <= m; i++) {
            pre = cur[0];
            cur[0] = i;
            for (int j = 1; j <= n; j++) {
                int temp = cur[j];
                if (s1[i - 1] == s2[j - 1]) {
                    cur[j] = pre;
                }
                else {
                    cur[j] = min({pre, cur[j - 1], cur[j]}) + 1;
                }
                pre = temp;
            }
        }
        return cur[n];
    }

    // Actually this is not a Damerau–Levenshtein distance algorithms
    // this is an Optimal String Alignment distance or Restricted Edit Distance algorithms
    /*
     *  Damerau–Levenshtein distance with adjacent transpositions algorithm is implemented below.
     *  Adding transpositions adds significant complexity. The difference between the two algorithms consists in that
     *  the optimal string alignment algorithm computes the number of edit operations needed to make the strings equal
     *  under the condition that no substring is edited more than once, whereas the second one presents no such restriction.
     *  Take for example the edit distance between CA and ABC.
     *  The Damerau–Levenshtein distance LD(CA,ABC) = 2 because CA → AC → ABC,
     *  but the optimal string alignment distance OSA(CA,ABC) = 3
     *  because if the operation CA → AC is used, it is not possible to use AC → ABC because that would require
     *  the substring to be edited more than once, which is not allowed in OSA, and therefore the shortest sequence of
     *  operations is CA → A → AB → ABC. Note that for the optimal string alignment distance, the triangle inequality
     *  does not hold: OSA(CA,AC) + OSA(AC,ABC) < OSA(CA,ABC), and so it is not a true metric.
     *  For details read https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance
     *  http://neerc.ifmo.ru/wiki/index.php?title=%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D0%BE_%D1%80%D0%B0%D1%81%D1%81%D1%82%D0%BE%D1%8F%D0%BD%D0%B8%D0%B8_%D0%94%D0%B0%D0%BC%D0%B5%D1%80%D0%B0%D1%83-%D0%9B%D0%B5%D0%B2%D0%B5%D0%BD%D1%88%D1%82%D0%B5%D0%B9%D0%BD%D0%B0
     */
    int osa_distance(const std::string & s1, const std::string & s2) {
        int m = s1.size(), n = s2.size();

        if(m == n == 0) return 0;
        if(m == 0) return n;
        if(n == 0) return m;

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));


        for (int i = 1; i <= m; i++) {
            dp[i][0] = i;
        }
        for (int j = 1; j <= n; j++) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::min({dp[i - 1][j - 1],  // substitution
                                         dp[i][j - 1],         // insertion
                                         dp[i - 1][j]})        // deletion
                                                 + 1;          // cost
                    if ( (i > 1) && (j > 1) && (s1[i-1] == s2[j-2]) && (s1[i-2] == s2[j-1]) ) {
                        dp[i][j] = std::min(dp[i][j], dp[i - 2][j - 2] + 1);  // transposition
                    }
                }
            }
        }
        return dp[m][n];
    }

/*
int DamerauLevenshteinDistance(S: char[1..M], T: char[1..N]; deleteCost, insertCost, replaceCost, transposeCost: int):
    D: int[0..M + 1][0..N + 1]   // Динамика
    INF = (M + N) * max(deleteCost, insertCost, replaceCost, transposeCost)  // Большая константа

    // База индукции
    D[0][0] = INF
    for i = 0 to M
        D[i + 1][1] = i * deleteCost
        D[i + 1][0] = INF
    for j = 0 to N
        D[1][j + 1] = j * insertCost
        D[0][j + 1] = INF

    lastPosition: int[0..количество различных символов в S и T]
    //для каждого элемента C алфавита задано значение lastPosition[C]

    foreach (char Letter in (S + T))
        lastPosition[Letter] = 0

    for i = 1 to M
        last = 0
        for j = 1 to N
            i' = lastPosition[T[j]]
            j' = last
            if S[i] == T[j]
                D[i + 1][j + 1] = D[i][j]
                last = j
            else
                D[i + 1][j + 1] = min(D[i][j] + replaceCost, D[i + 1][j] + insertCost, D[i][j + 1] + deleteCost)
            D[i + 1][j + 1] = min(D[i + 1][j + 1], D[i'][j'] + (i - i' - 1) ⋅

 deleteCost + transposeCost + (j - j' - 1) ⋅

 insertCost)
        lastPosition[S[i]] = i

    return D[M][N]
 */

    struct costs_t {
        int del = 1;
        int insert = 1;
        int replace = 1;
        int transpose = 1;
    };

    int damerau_levenshtein_distance(const std::string & s1, const std::string & s2, costs_t & costs, int alphabet = 256) {
        int m = s1.size(), n = s2.size();

        if( (m == n) && (m == 0) ) return 0;
        if(m == 0) return n;
        if(n == 0) return m;

        vector<vector<int>> dp(m + 2, vector<int>(n + 2, 0));

        const int INF = (m + n) * std::max({costs.del, costs.insert, costs.replace, costs.transpose}); // big constant

        dp[0][0] = INF;
        for (int i = 0; i <= m; ++i) {
            dp[i + 1][1] = i * costs.del;
            dp[i + 1][0] = INF;
        }

        for (int j = 0; j <= n; ++j) {
            dp[1][j + 1] = j * costs.insert;
            dp[0][j + 1] = INF;
        }

        // for each element of the alphabet of symbols in the strings
        vector<int> last_row(alphabet, 0);

        // Fill out the table
        for (int row = 1; row <= m; row++) {
            // The current character in `source`; this and `ch_t` below both have to
            // be unsigned so that they can be used as an index to last_row no
            // matter what their values
            unsigned char ch_s = s1[row-1];

            // The last column this row where the character in `source` matched the
            // character in `target`; as with last_row, zero denotes no match yet
            int last_match_col = 0;

            for (int col = 1; col <= n; col++) {
                // The current character in `target`
                unsigned char ch_t = s2[col-1];

                // The last place in `source` where we can find the current
                // character in `target`
                int last_matching_row = last_row[ch_t];

                int cost = (ch_s == ch_t) ? 0 : 1;

                // Calculate the distances of all possible operations
                int dist_add = dp[row][col+1] + 1;
                int dist_del = dp[row+1][col] + 1;
                int dist_sub = dp[row][col] + cost;

                // This took me a while to figure out. What this calculates is the
                // cost of a transposition between the current character in `target`
                // and the last character found in both strings.
                //
                // All characters between these two are treated as either additions
                // or deletions.
                //
                // NOTE: Damerau-Levenshtein allows for either additions OR
                // deletions between the transposed characters, NOT both. This is
                // not explicitly prevented, but if both additions and deletions
                // would be required between transposed characters -- this is if
                // neither
                //
                //     `(row - last_matching_row - 1)`
                //
                // nor
                //
                //     `(col - last_match_rol - 1)`
                //
                // is zero -- then adding together both addition and deletion costs
                // will cause the total cost of a transposition to become higher
                // than any other operation's cost.
                int dist_trans = dp[last_matching_row][last_match_col]
                                 + (row - last_matching_row - 1) + 1
                                 + (col - last_match_col - 1);

                // Find the minimum of the distances
                int min = dist_add;
                if (dist_del < min)
                    min = dist_del;
                if (dist_sub < min)
                    min = dist_sub;
                if (dist_trans < min)
                    min = dist_trans;

                // Store the minimum as the cost for this cell
                dp[row+1][col+1] = min;

                // If there was a match, update the last matching column
                if (cost == 0) {
                    last_match_col = col;
                }
            }
            // Update the entry for this row's character
            last_row[ch_s] = row;
        }
        // Extract the bottom right-most cell -- that's the total distance
        return dp[m+1][n+1];
    }

    template<typename KEY_T, typename VAL_T = KEY_T>
    class LRU_cache_t {
    using kv_pair = std::pair<VAL_T, typename std::list<KEY_T>::iterator>;
    private:
        std::list<KEY_T> keys;
        unordered_map <KEY_T, kv_pair> map;
        int cache_size;

    public:
        LRU_cache_t(int size) : cache_size(size) {
            assert(cache_size > 0);
        }

        void add(const KEY_T & key, const VAL_T & value) {
            auto pos = map.find(key); // find the key in the map
            if (pos == map.end()) {   // if the key was not found adding the new key and value
                keys.push_front(key); // add the key to the list
                map.emplace(key, make_pair(value, keys.begin())); // add the pair key-value to the map
//                map[key] = {value, keys.begin() };
                if (map.size() > cache_size) {    // if the cache is full
                    map.erase(keys.back());       // remove the last used key-value pair from the cache
                    keys.pop_back();
                }
            }
            else {  // if the key was found
                // move the key from the back of the list to the front
                keys.splice(keys.begin(), keys, pos->second.second);
                map.emplace(key, make_pair(value, keys.begin())); // add the pair key-value to the map
//                map[key] = {value, keys.begin() };
            }
        }

        std::optional<VAL_T> get(const KEY_T & key) {
            auto pos = map.find(key);
            if (pos == map.end()) {
                return {};
            }
            // move the key from the back of the list to the front
            keys.splice(keys.begin(), keys, pos->second.second);
            map.emplace(key, make_pair(pos->second.first, keys.begin() )); // add the pair key-value to the map
//            map[key] = {pos->second.first, keys.begin() };
            return pos->second.first;
        }

        void print() const {
            cout << "\n";
            for(auto & i : map) {
                cout << i.first << " " << i.second.first << "\n";
            }
            cout << "\n";
        }

    };

    void test() {

        cout << "cache test\n";
        LRU_cache_t<int, int> cache(3);
        cache.add(1,1);
        cache.add(2,2);
        cache.get(1);
        cache.add(3,3);
        cache.add(4,4);
        cache.get(1);
        cache.add(5,5);
        cache.add(6,6);
        cache.get(1);
        cache.add(7,7);
        cache.add(8,8);
        cache.get(1);
        cache.add(9,9);
        cache.print();

        LRU_cache_t<int, string> cache2(3);

        cache2.add(1, "one");
        cache2.add(2, "two");
        cache2.add(3, "three");
        cache2.add(4, "four");
        cache2.print();


//        std::cout << R"(levenshtein_distance("fuck", "duck") = )"  << levenshtein_distance("fuck", "duck") << " expected 1" << std::endl;
        costs_t costs;
        std::cout << R"(damerau_levenshtein_distance("CA", "ABC") = )"  << damerau_levenshtein_distance("CA", "ABC", costs) << " expected 2" << std::endl;
        std::cout << "Test finished!" << std::endl;
    }

}