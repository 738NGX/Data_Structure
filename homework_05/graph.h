#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <climits>
#include <algorithm>
#include "node.h"
#include "edge.h"

namespace Sufe
{
    class Graph
    {
    public:
        // Build graph given vertices size
        Graph(int sz);

        // Release node/edge properly
        ~Graph();

        void AddEdge(int uid, int vid, float wt = 1.0);

        void Bfs(int start);
        void Dfs(int start);
        void DfsTime(int start);
        void Dfs_Iterative(int start);

        // TODO: implement FindScc()
        std::vector<std::vector<int>> FindScc();

        friend std::ostream &operator<<(std::ostream &out, const Graph &graph);

    private:
        // Disable Copy constructor and = overloading
        // TODO: implement them properly
        Graph(const Graph &other);
        Graph &operator=(const Graph &rhs);

        void DfsInternal(int uid, bool *visited);
        int DfsTimeInternal(int uid, int currentTime, bool *visited, std::pair<int, int> *travelTimes);

        // TODO: implement DFS traversal in transpose graph, by using inward edges
        void DfsReverseInternal(int uid, bool *visited, std::vector<int> *pScc);

        int getLatestNode(bool* visited);

        // a node with id is stored at index, equals to id.
        // When deleting a node, just mark it as not active, instead of deletion.
        std::vector<Node *> m_nodes;
        std::vector<Edge *> m_edges;

        std::pair<int, int> *travel_times;
    };
}
