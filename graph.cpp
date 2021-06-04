//
// Created by alex on 5/20/21.
//

#include "graph.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

namespace algorithms::graph {
    using namespace std;

    using edge_list_t = vector<pair<int, int>>;
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



    node_t * make_graph(const adjacency_list_t & list) {

        size_t list_size = list.size();
        vector<node_t *> nodes(list_size);

        if(0 == list_size) {
            return new node_t(0);
        }

        for(int i = 0; i < list_size; ++i ) {
            nodes[i] = new node_t(i);
        }

        // connect all nodes as described in adjacency list
        for(int i = 0; i < list_size; ++i ) {
            for(auto n: list[i]) {
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

    void print_graph_DFS(node_t * n, int nodes_number) {
        vector<bool> printed(nodes_number, false);
        print_graph(n, printed);
    }

    void print_graph(node_t *n, int nodes_number) {
        vector<bool> printed(nodes_number, false);

        auto print_graph_dfs = [&printed] (auto& self, node_t *n) {
            if (n == nullptr) { return; }
            print_node(n);
            printed[n->val] = true;
            for(const auto nb: n->neighbors) {
                if(!printed[nb->val]) {
                    self(self, nb);
                }
            }
        };
        print_graph_dfs(print_graph_dfs, n);
    }

    void print_graph_iterative(node_t *n, int nodes_number) {
        if (n == nullptr) { return; }
        vector<bool> printed(nodes_number, false);
        queue<node_t*> q;
        q.push(n);

        while (!q.empty()) {
            auto node = q.front(); q.pop();
            if( ! printed[node->val]) {
                print_node(node);
                printed[node->val] = true;
                for (auto nb: node->neighbors) {
                    q.push(nb);
                }
            }
        }
    }

    adjacency_matrix_t make_matrix(const edge_list_t & l) {
        auto l_size = l.size();
        adjacency_matrix_t m(l_size, vector<bool>(l_size, false));

        for(auto [u, v]: l) {
            m[u][v] = true;
        }
        return m;
    }

    void print_matrix(const adjacency_matrix_t & m) {
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

    void print_edges(const edge_list_t & l) {
        cout << "\nPrint adjacency list:\n";
        for(auto [u, v]: l) {
            cout << "{" << u << ", " << v << "}, ";
        }
        cout << endl;
    }

    // Clone graph recursive DFS algorithm
    node_t *clone_graph(node_t *n) {

        unordered_map<node_t *, node_t *> m;

        auto clone_graph_dfs = [&m] (auto& self, node_t *n) -> node_t * {

            if (n == nullptr) { return nullptr; }

            // if we meet a pointer to already cloned node - return this pointer instead of cloning
            if (m.count(n)) { return m[n]; }

            node_t * node_copy = new node_t(n->val);
            m[n] = node_copy;

            for (const auto &nb : n->neighbors) {
                node_copy->neighbors.push_back(self(self, nb));
            }
            return node_copy;
        };

        return clone_graph_dfs(clone_graph_dfs, n);
    }

    // Clone graph iterative BFS algorithm
    node_t* clone_graph_iterative(node_t* node) {
        if (node == nullptr) {
            return nullptr;
        }
        // Make a hash table to save pointers to original and cloned nodes (original = key, cloned = value)
        unordered_map<node_t*, node_t*> table;
        // clone the start node and add the original and the clone to the table
        table[node] = new node_t(node->val);
        std::queue<node_t*> q;
        q.push(node);
        // Do Breath First Search for all other found nodes
        while (!q.empty()) {
            node_t* n = q.front();
            q.pop();
            // For each neighbor of the current node
            for (node_t* nb : n->neighbors) {
                // If the neighbor was not cloned
                if (!table.count(nb)) {
                    // clone the neighbor and add the original and the clone to the table
                    table[nb] = new node_t(nb->val);
                    // add the neighbor to the queue to process it's own neighbors in the future
                    q.push(nb);
                }
                // Here the neighbor is definitely cloned
                // table[nb] returns clone of the neighbor of the current node
                // table[n] returns clone of the current node
                // so add clone of the neighbor to neighbors of the clone of the current node
                table[n]->neighbors.push_back(table[nb]);
            }
        }
        return table[node];
    }

    adjacency_list_t convert(const edge_list_t & edges) {

        auto max_vertex = std::max_element(edges.begin(), edges.end(), [](const edge_list_t::value_type & a, const edge_list_t::value_type & b) { return max(a.first, a.second) < max(b.first, b.second); });

        int graph_size = (max(max_vertex->first, max_vertex->second)) + 1;

        adjacency_list_t graph(graph_size);

        for(auto [u, v] : edges) {
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        return graph;
    }

    // Returns the indexes for all articulation points in the graph even if the
    // graph is not fully connected.
    vector<int> find_cutpoints(const edge_list_t & edges) {

        adjacency_list_t graph = convert(edges);

        // number of nodes in the graph
        int graph_size = graph.size();
        // number of the current step of the graph traversal
        int timer = 0;
        // vertex with lowest visiting time reachable from the current vertex
        vector<int> lowest_time(graph_size);
        vector<int> vertex_walk_time(graph_size);
        // visited vertices
        vector<bool> visited(graph_size, false);
        // found articulation points
        vector<int> cutpoints;

        auto find_cutpoints_dfs = [&lowest_time, &vertex_walk_time, &visited, &timer, &graph, &cutpoints] (auto& self, int current, int parent = -1) -> void {
            visited[current] = true;
            vertex_walk_time[current] = lowest_time[current] = timer++;
            int children = 0; // number of outgoing edges from the current vertex
            // number of vertices connected ot the current vertex
            auto neighbors = graph[current].size();
            for (size_t i = 0; i < neighbors; ++i) {
                // neighbor vertex connected to the current vertex by directed edge outgoing from the current vertex
                int to_vertex = graph[current][i];
                // exclude parent vertex from the processing because we process directed graph
                if (to_vertex == parent) { continue; }
                // if we met already visited vertex
                if (visited[to_vertex]) {
                    lowest_time[current] = min(lowest_time[current], vertex_walk_time[to_vertex]);
                }
                else {
                    self(self, to_vertex, current);
                    lowest_time[current] = min(lowest_time[current], lowest_time[to_vertex]);

                    if (lowest_time[to_vertex] >= vertex_walk_time[current] && parent != -1) {
                        cutpoints.push_back(current);
                    }
                    ++children;
                }
            }
            // if parent is root vertex and it has more than one outgoing edge
            // this vertex is a cut point
            if (parent == -1 && children > 1) {
                cutpoints.push_back(current);
            }
        };

        find_cutpoints_dfs(find_cutpoints_dfs, 0);

        return cutpoints;
    }


    edge_list_t find_bridges(const edge_list_t & edges) {

        adjacency_list_t graph = convert(edges);

        // number of nodes in the graph
        int graph_size = graph.size();
        // number of the current step of the graph traversal
        int timer = 0;
        // vertex with lowest visiting time reachable from the current vertex
        vector<int> lowest_time(graph_size);
        vector<int> vertex_walk_time(graph_size);
        // visited vertices
        vector<bool> visited(graph_size, false);
        // found articulation points
        edge_list_t bridges;
        auto find_bridges_dfs = [&lowest_time, &vertex_walk_time, &visited, &timer, &graph, &bridges] (auto& self, int current, int parent = -1) -> void {
            visited[current] = true;
            vertex_walk_time[current] = lowest_time[current] = timer++;
            // number of vertices connected ot the current vertex
            auto neighbors = graph[current].size();
            for (size_t i = 0; i < neighbors; ++i) {
                // neighbor vertex connected to the current vertex by directed edge outgoing from the current vertex
                int to_vertex = graph[current][i];
                // exclude parent vertex from the processing because we process directed graph
                if (to_vertex == parent) { continue; }
                // if we met already visited vertex
                if (visited[to_vertex]) {
                    lowest_time[current] = min(lowest_time[current], vertex_walk_time[to_vertex]);
                }
                else {
                    self(self, to_vertex, current);
                    lowest_time[current] = min(lowest_time[current], lowest_time[to_vertex]);
                    if(lowest_time[to_vertex] > vertex_walk_time[current]) {
                        bridges.push_back({current, to_vertex});
                    }
                }
            }
        };

        for (int i = 0; i < graph_size; ++i) {
            if (!visited[i]) {
                find_bridges_dfs(find_bridges_dfs, i);
            }
        }

        return bridges;
    }

    void test() {

        cout << "\ngraph test" << endl;

        const edge_list_t tree {{0, 1}, {0, 2}, {1, 2}};

        const edge_list_t test{{0, 1},
        {0, 2},
        {1, 2},
        {2, 3},
        {3, 4},
        {2, 5},
        {5, 6},
        {6, 7},
        {7, 8},
        {8, 5}};

        const edge_list_t edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {2, 5}, {5, 6}, {3, 4}};

        print_edges(tree);

        auto m =  make_matrix(tree);

        print_matrix(m);

        cout << "\ninit graph from adjacency list" << endl;

        node_t * graph = make_graph(convert(tree));

        cout << "\nprint graph:" << endl;

        print_graph_iterative(graph, 3);

        cout << "\nclone graph:" << endl;

        auto clone = clone_graph(graph);

        print_graph(clone, 3);

        cout << "\nprint bridges:" << endl;

        print_edges(find_bridges(test));

    }
}