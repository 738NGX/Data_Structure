#pragma once
#include <vector>

namespace Sufe
{
    class Edge;
    class Node
    {
    public:
        Node(int id, float val = 0);

        int NId() const { return m_nid; }

        friend std::ostream &operator<<(std::ostream &out, const Node &nd);
        friend class Graph;

    private:
        // modelling by outward edges, instead of general edge.
        // Not that one node has multiple outward arcs,
        // but an out arc maps to one node in terms of its source
        std::vector<Edge *> outArcs;

        // Note it is used in finding SCC, by which you don't need to reverse graph.
        std::vector<Edge *> inArcs;

        int m_nid;
        bool m_active;
        float m_key;
    };
}