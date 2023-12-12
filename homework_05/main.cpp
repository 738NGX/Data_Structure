#include <iostream>
#include "graph.h"

using namespace std;

int main()
{
    Sufe::Graph scc(9);
    scc.AddEdge(0, 1);
    scc.AddEdge(0, 2);
    scc.AddEdge(1, 2);
    scc.AddEdge(2, 3);
    scc.AddEdge(3, 1);
    scc.AddEdge(3, 4);
    scc.AddEdge(3, 7);
    scc.AddEdge(3, 8);
    scc.AddEdge(4, 5);
    scc.AddEdge(5, 6);
    scc.AddEdge(6, 7);
    scc.AddEdge(7, 4);
    scc.AddEdge(7, 8);

    // display outward edges of each nodes
    cout << scc << endl;

    // find all SCCs and display in group
    scc.FindScc();

    return 0;
}
