//
// Created by alex on 5/20/21.
//

#include "graph.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <functional>
#include <list>

namespace algorithms::graph {
    using namespace std;

    using edge_list_t = vector<pair<int, int>>;
    using adjacency_list_t = vector<vector<int>>;
    using adjacency_matrix_t = vector<vector<bool>>;

    // forward declarations
    adjacency_list_t convert(const edge_list_t & edges, bool directed);


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

    using callback_t = void (int);
    // do dfs and call the callback function to process each node
    void recursive_dfs(adjacency_list_t &graph, callback_t & callback) {
        // number of nodes in the graph
        int graph_size = graph.size();
        // visited vertices
        vector<bool> visited(graph_size, false);

        std::function<void(int)> dfs = [&dfs, &visited, &graph, &callback](int current) {
            callback(current);
            visited[current] = true;
            for (auto nb: graph[current]) {
                dfs(nb);
            }
        };

        dfs(0);
    }

    // iterative_bfs
    void iterative_bfs(adjacency_list_t &graph, callback_t & callback) {
        // number of nodes in the graph
        int graph_size = graph.size();
        // visited vertices
        vector<bool> visited(graph_size, false);

        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            auto node = q.front(); q.pop();
            if( ! visited[node]) {
                callback(node);
                visited[node] = true;
                for (auto nb:  graph[node]) {
                    q.push(nb);
                }
            }
        }
    }


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

    // If directed == true Converts pairs of nodes to directed graph where edges directed from the left node to the right one.
    // If directed == false converts pairs of nodes to undirected graph where the nodes connected to both directions
    adjacency_list_t convert(const edge_list_t & edges, bool directed = false) {

        auto max_vertex = std::max_element(edges.begin(), edges.end(), [](const edge_list_t::value_type & a, const edge_list_t::value_type & b) { return max(a.first, a.second) < max(b.first, b.second); });

        int graph_size = (max(max_vertex->first, max_vertex->second)) + 1;

        adjacency_list_t graph(graph_size);

        for(auto [u, v] : edges) {
            graph[u].push_back(v);
            if( ! directed) {
                graph[v].push_back(u);
            }
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
/*

vector<bool> visited;
long long vertices=0;
vector<list<long long> > G;

void DFS(long long u){
    if(visited[u]) return ;
    visited[u]=true;
    vertices++;
    for(auto i: G[u])
        if(!visited[i])
            DFS(i);
}

int journeyToMoon(int n, vector<vector<int>> v) {

    long long ans=n*(n-1)/2;
    visited.resize(n,false);
    G.resize(n);

    for(int i = 0; i < v.size(); ++i){
        G[v[i][0]].push_front(v[i][1]); G[v[i][1]].push_front(v[i][0]);
    }

    for(long long i=0;i<n;i++){
        vertices=0;
        DFS(i);
        ans=ans-vertices*(vertices-1)/2;
    }
    return ans;
}
 * */


    int journeyToMoon(int n, vector<vector<int>> v) {
        vector<bool> visited(n, false);
        int vertices = 0;
        // total number of combinations of pairs which is possible to make from the given number of astronauts
        int result = n * (n - 1) / 2;
        vector<std::list<int>> graph(n);

        // dfs traversal through the graph
        std::function<void(int)> dfs = [&dfs, &visited, &graph, &vertices](int current) {
            if (visited[current]) {
                return;
            }
            visited[current] = true;
            vertices++;
            for (auto i: graph[current]) {
                if (!visited[i]) {
                    dfs(i);
                }
            }
        };

        // build a graph
        for (auto & i : v) {
            graph[i[0]].push_front(i[1]);
            graph[i[1]].push_front(i[0]);
        }
        // traverse through the graph and count vertices.
        // each time when we return from the dfs we have
        // counted number of vertices in the traversed subgraph
        // each subgraph contains astronauts from the same country
        for (int i = 0; i < n; i++) {
            vertices = 0;
            dfs(i);
            // then subtract from the total number of combinations of pairs a number of the combinations for the
            // current country.
            if(vertices > 1) {
                result -= vertices * (vertices - 1) / 2;
            }
        }
        // as result we have a number of combinations of pairs of the astronauts from different countries.
        return result;
    }


    vector<int> topological_sort(const edge_list_t & edges) {
        // converting to directed graph where edges directed from the left node to the right one.
        adjacency_list_t graph = convert(edges, true);
        // number of nodes in the graph
        int graph_size = graph.size();
        vector<int> result;
        result.reserve(graph_size);
        // visited vertices
        vector<bool> visited(graph_size, false);

        std::function<void(int)> dfs = [&dfs, &visited, &graph, &result](int current) {
            visited[current] = true;
            for (auto nb: graph[current]) {
                if(!visited[nb]) {
                    dfs(nb);
                }
            }
            result.push_back(current);
        };

        for (int i = 0; i < graph_size; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }

        std::reverse(result.begin(), result.end());
        return result;
    }
    // 704982702
    // 49994998


    void print_vector(const vector<int> &v) {
        for(auto i: v) {
            cout << i << " ";
        }
        cout << endl;
    }

    void test() {
        vector<vector<int>> v {
                {1,2},
                {3,4}
        };

        cout << "\nastro test " << journeyToMoon(10000, v) << "\n";


        cout << "\ngraph test" << endl;
        const edge_list_t top_sort_test {{5, 2}, {5, 0}, {4, 0}, {4, 1}, {2, 3}, {3, 1}};

        auto result = topological_sort(top_sort_test);

        cout << "test topological_sort()\n";

        print_vector(result);

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