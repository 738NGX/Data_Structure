#pragma once

namespace Sufe
{
    class Node;
    class Edge
    {
    public:
        Edge(int id, Node *src, Node *dst, float weight = 1.0)
            : m_eid(id),
              m_active(true),
              m_weight(weight)
        {
            m_src = src;
            m_dst = dst;
        }

        Node *GetU() const { return m_src; }
        Node *GetV() const { return m_dst; }
        float GetWeight() const { return m_weight; }

        int EId() const { return m_eid; }

    private:
        int m_eid;
        bool m_active;
        float m_weight;

        // Not that below is weak reference to Node.
        // Edge does not own life of Node, so do not destroy in Edge destructor.
        // Graph own life of Nodes and Edges.
        Node *m_src;
        Node *m_dst;
    };
}
