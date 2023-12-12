#include <iostream>
#include "edge.h"
#include "node.h"

namespace Sufe
{
    Node::Node(int id, float val)
        : m_nid(id),
          m_active(true),
          m_key(val)
    {
    }

    std::ostream &operator<<(std::ostream &out, const Node &nd)
    {
        out << "Node #" << nd.NId() << ": ";
        for (auto arc : nd.outArcs)
        {
            out << "#" << arc->GetV()->NId() << ", ";
        }

        return out;
    }
}