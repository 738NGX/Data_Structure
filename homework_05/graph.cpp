#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <climits>
#include <algorithm>
#include "graph.h"

using namespace std;

namespace Sufe
{
    Graph::Graph(int sz)
    {
        for (int i = 0; i < sz; i++)
        {
            Node *nd = new Node(m_nodes.size());
            m_nodes.push_back(nd);
        }
    }

    Graph::~Graph()
    {
        for (auto nd : m_nodes)
        {
            delete nd;
        }

        for (auto arc : m_edges)
        {
            delete arc;
        }
    }

    void Graph::AddEdge(int uid, int vid, float wt)
    {
        int total = m_nodes.size();
        assert(uid < total && vid < total);

        Node *U = m_nodes.at(uid);
        Node *V = m_nodes.at(vid);

        Edge *arc = new Edge(m_edges.size(), U, V, wt);
        U->outArcs.push_back(arc);

        // add inward edges for SCC algorithm
        V->inArcs.push_back(arc);

        m_edges.push_back(arc);
    }

    ostream &operator<<(ostream &out, const Graph &graph)
    {
        for (auto nd : graph.m_nodes)
        {
            out << *nd << std::endl;
        }
        return out;
    }

    void Graph::Bfs(int start)
    {
        bool *visited = new bool[m_nodes.size()]{false};
        cout << "Start BFS search:" << endl;

        std::queue<int> que;
        que.push(start);
        visited[m_nodes[start]->NId()] = true;

        while (!que.empty())
        {
            int sz = que.size();
            while (sz-- > 0)
            {
                Node *U = m_nodes[que.front()];
                que.pop();
                cout << "#" << U->NId() << ", ";

                for (auto arc : U->outArcs)
                {
                    int vid = arc->GetV()->NId();
                    if (!visited[vid])
                    {
                        visited[vid] = true;
                        que.push(vid);
                    }
                }
            }
            cout << endl;
        }
        delete[] visited;
    }

    void Graph::Dfs_Iterative(int start)
    {
        cout << "\n Start DFS iterative search:" << endl;
        bool *visited = new bool[m_nodes.size()]{false};

        stack<int> stk;
        stk.push(start);

        while (!stk.empty())
        {
            int uid = m_nodes.at(stk.top())->NId();
            stk.pop();
            if (!visited[uid])
            {
                visited[uid] = true;
                cout << "#" << uid << ", ";

                for (auto arc : m_nodes.at(uid)->outArcs)
                {
                    stk.push(arc->GetV()->NId());
                }
            }
        }

        cout << endl;
        delete[] visited;
    }

    void Graph::Dfs(int start)
    {
        cout << "\n Start DFS search:" << endl;
        bool *visited = new bool[m_nodes.size()]{false};

        // TODO: should call DfsInternal multiple times to traverse all nodes
        DfsInternal(start, visited);
        for(size_t i=0;i<m_nodes.size();i++)
        {
            if(!visited[i]) DfsInternal(i,visited);
        }

        cout << endl;
        delete[] visited;
    }

    void Graph::DfsInternal(int uid, bool *visited)
    {
        visited[uid] = true;
        cout << "#" << uid << ", ";

        for (auto arc : m_nodes.at(uid)->outArcs)
        {
            int vid = arc->GetV()->NId();
            if (!visited[vid])
            {
                DfsInternal(vid,visited);
            }
        }
    }

    void Graph::DfsTime(int start)
    {
        cout << "\n Start DFS Time search:" << endl;
        bool *visited = new bool[m_nodes.size()]{false};
        pair<int, int> *travelTimes = new pair<int, int>[m_nodes.size()];

        // TODO: should call DfsTimeInternal multiple times to traverse all nodes
        int currentTime=DfsTimeInternal(start,0,visited,travelTimes);
        for(size_t i=0;i<m_nodes.size();i++)
        {
            if(!visited[i])
            {
                currentTime=DfsTimeInternal(i,currentTime,visited,travelTimes);
            }
        }
        cout << endl;
        for(size_t i=0;i<m_nodes.size();i++)
        {
            cout<<"("<<travelTimes[i].first<<","<<travelTimes[i].second<<") ";
        }
        cout << endl;
        delete[] visited;
        delete[] this->travel_times;
        this->travel_times=travelTimes;
    }

    int Graph::DfsTimeInternal(
        int uid, int currentTime,
        bool *visited, pair<int, int> *travelTimes)
    {
        visited[uid] = true;
        travelTimes[uid].first = currentTime;
        cout << "#" << uid << ", ";

        for (auto arc : m_nodes[uid]->outArcs)
        {
            int vid = arc->GetV()->NId();
            if (!visited[vid])
            {
                currentTime = DfsTimeInternal(vid, currentTime + 1, visited, travelTimes);
            }
        }

        travelTimes[uid].second = ++currentTime;
        return currentTime;
    }

    vector<vector<int>> Graph::FindScc()
    {
        vector<vector<int>> results;

        // TODO: Do something here
        //       1. Do DFS + travel times until all nodes are visited
        //          (do not follow DfsTime directly, where it only do one DFS traversal)
        //       2. keep end times of each node and clear visited array
        //       3. while having unvisited nodes
        //       4.    starting from last finished (and unvisited) node
        //       5.    use inArcs to do traversal of graph (DfsReverseInternal)
        //       6.    save each DFS tree as a SCC to output results
        
        bool *visited = new bool[m_nodes.size()]{false};
        vector<int> *pScc=new vector<int>[m_nodes.size()]{{}};
        int counter=0;

        DfsTime(7);
        while(getLatestNode(visited)!=-1)
        {
            DfsReverseInternal(getLatestNode(visited),visited,pScc+counter);
            counter++;
        }
        cout<<"Strong Connected Components are"<<endl;
        for(int i=0;i<counter;i++)
        { 
            results.push_back(pScc[i]);
            for(auto node:pScc[i]) cout<<"#"<<node<<",";
            cout<<endl;
        }

        delete[] visited;
        delete[] pScc;
        return results;
    }

    void Graph::DfsReverseInternal(int uid, bool *visited, std::vector<int> *pScc)
    {
        // TODO: Do something here
        //       DFS traversal on transpose graph, by inward edges
        visited[uid] = true;
        pScc->push_back(uid);
        for (auto arc : m_nodes.at(uid)->inArcs)
        {
            int vid = arc->GetU()->NId();
            if (!visited[vid])
            {
                DfsReverseInternal(vid,visited,pScc);
            }
        }
    }

    int Graph::getLatestNode(bool* visited)
    {
        int max=0,max_idx=-1;
        for(size_t i=0;i<m_nodes.size();i++)
        {
            if(visited[i]==true) continue;
            if(travel_times[i].second>max)
            {
                max=travel_times[i].second;
                max_idx=i;
            }
        }
        return max_idx;
    }
}