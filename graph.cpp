//
// Created by alex on 5/20/21.
//

#include "graph.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>

namespace algorithms::graph {
    using namespace std;

    using adjacency_list_t = vector<vector<int>>;
    using adjacency_matrix_t = vector<vector<bool>>;

// Definition for a node.
    struct node_t {
        int val = 0;
        vector<node_t*> neighbors{};
        explicit node_t(int _val) {
            val = _val;
        }
        node_t(int _val, const vector<node_t*> & _neighbors) {
            val = _val;
            neighbors = _neighbors;
        }
    };

    node_t * init_graph(const adjacency_list_t & adjacency_list) {

        size_t al_size = adjacency_list.size();
        vector<node_t *> nodes(al_size);

        if(0 == al_size) {
            return new node_t(0);
        }

        for(int i = 0; i < al_size; ++i ) {
            nodes[i] = new node_t(i);
        }

        // connect all nodes as described in adjacency list
        for(int i = 0; i < al_size; ++i ) {
            for(auto n: adjacency_list[i]) {
                nodes[i]->neighbors.push_back(nodes[n]);
            }
        }
        return nodes[0];
    }

    void print_node(node_t * n) {
        cout << "\n Val: " << n->val << " | Neighbors: (";
        for(const auto nb: n->neighbors) {
            cout << nb->val << ", ";
        }
        cout << ")";
    }

    void  print_graph(node_t * n, vector<bool> & printed) {
        if (n == nullptr) { return; }
        print_node(n);
        printed[n->val] = true;
        for(const auto nb: n->neighbors) {
            if(!printed[nb->val]) {
                print_graph(nb, printed);
            }
        }
    }

    void print_graph_BFS(node_t * n, int nodes_number) {
        vector<bool> printed(nodes_number, false);

        print_graph(n, printed);
    }

    adjacency_matrix_t convert(adjacency_list_t l) {
        auto l_size = l.size();
        adjacency_matrix_t m(l_size, vector<bool>(l_size, false));

        for(auto i: l) {
            m[i[0]][i[1]] = true;
        }
        return m;
    }

    void print(adjacency_matrix_t & m) {
        cout << "\nPrint adjacency matrix:\n    ";
        auto m_size = m.size();
        for(auto i = 0; i < m_size; ++i) {
            cout << i << "  ";
        }
        cout << endl;
        for(auto i = 0; i < m_size; ++i) {
            cout << i << " | ";
            for(auto j = 0; j < m_size; ++j) {
                cout << m[i][j] << ", ";
            }
            cout << endl;
        }
    }

    void print(adjacency_list_t & l) {
        cout << "\nPrint adjacency list:\n";
        for(auto i: l) {
            cout << "{" << i[0] << ", " << i[1] << "}, ";
        }
        cout << endl;
    }

    node_t *clone_graph(node_t *n) {

        unordered_map<node_t *, node_t *> m;

        auto clone_graph_recursive = [&m] (auto& self, node_t *n) -> node_t * {

            if (n == nullptr) return nullptr;

            if (m.count(n)) {
                return m[n];
            }

            node_t * node_copy = new node_t(n->val);
            m[n] = node_copy;

            for (const auto &nb : n->neighbors) {
                node_copy->neighbors.push_back(self(self, nb));
            }
            return node_copy;
        };

        return clone_graph_recursive(clone_graph_recursive, n);
    }



    void test() {

        cout << "\ngraph test" << endl;

        vector<vector<int>> tree {{0, 1}, {0, 2}, {1, 2}};

        print(tree);

        auto m =  convert(tree);

        print(m);

        cout << "\ninit graph from adjacency list" << endl;

        node_t * graph = init_graph(tree);

        cout << "print graph:" << endl;

        print_graph_BFS(graph, tree.size());

    }
}