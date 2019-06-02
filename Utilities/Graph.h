//
// Created by W on 2019/3/24 0024.
//

#ifndef CODINGINTERVIEW_GRAPH_H
#define CODINGINTERVIEW_GRAPH_H

#include <vector>
#include <set>
#include <map>
using namespace std;

// 定义节点
struct Edge;
struct Node
{
    int value;
    int in;
    int out;
    vector<Node*> nexts;
    vector<Edge*> edges; //关联边，出边
    Node(int Value): value(Value), in(0), out(0){}
};

// 定义边
struct Edge
{
    int weight;
    Node* from;
    Node* to;
    Edge(int Weight, Node* From, Node* To) {
        weight = Weight;
        from = From;
        to = To;
    }
};

// 定义图
struct Graph
{
    map<int, Node*> nodes;
    set<Edge*> edges;
    Graph() = default;
};

__declspec( dllexport ) Graph* createGraph(vector<vector<int> > matrix);
__declspec( dllexport ) void bfs(Node* node);
__declspec( dllexport ) void dfs(Node* node);
__declspec( dllexport ) vector<Node*> sortedTopology(Graph* graph);
__declspec( dllexport ) set<Edge*> kruskalMST(Graph* graph);
__declspec( dllexport ) set<Edge*> primMST(Graph* graph);

#endif //CODINGINTERVIEW_GRAPH_H
