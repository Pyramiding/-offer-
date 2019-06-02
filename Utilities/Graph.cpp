//
// Created by W on 2019/3/24 0024.
//

#include "Graph.h"
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <stack>
#include <algorithm>
#include <queue>
using namespace std;

// 根据邻接矩阵生成图
// matrix矩阵每行为{边的权重，边的头结点，边的尾结点}
// matrix维度[边数，3]
Graph* createGraph(vector<vector<int> > matrix)
{
    Graph* graph = new Graph();
    for (int i = 0; i < matrix.size(); i++)
    {
        int weight = matrix[i][0];
        int from = matrix[i][1];
        int to = matrix[i][2];
        if (graph->nodes.find(from) == graph->nodes.end()) //查找头节点
            graph->nodes.insert({from, new Node(from)});

        if (graph->nodes.find(to) == graph->nodes.end()) //查找尾结点
            graph->nodes.insert({to, new Node(to)});

        Node* fromNode = graph->nodes[from];
        Node* toNode = graph->nodes[to];
        Edge* newEdge = new Edge(weight, fromNode, toNode);
        fromNode->nexts.push_back(toNode);
        fromNode->out++; //头结点出度增加
        toNode->in++; //尾结点入度增加
        fromNode->edges.push_back(newEdge);
        graph->edges.insert(newEdge);
    }
    return graph;
}


// 广度优先搜索BFS
void bfs(Node* node)
{
    if (node == nullptr)
        return;

    deque<Node*> Deque; //记录访问次序
    set<Node*> memo; //记录访问过的节点
    Deque.push_back(node);
    memo.insert(node);
    while (!Deque.empty()) {
        Node* cur = Deque.front();
        Deque.pop_front();
        printf("%d,", cur->value);
        for (Node* next: cur->nexts) { //逐次访问cur的邻接节点
            if (memo.find(next) == memo.end()) {
                memo.insert(next);
                Deque.push_back(next);
            }
        }
    }
}


// 广度优先搜索DFS
void dfs(Node* node) {
    if (node == nullptr)
        return;

    stack<Node*> Stack;
    set<Node*> memo;;
    Stack.push(node);
    memo.insert(node);
    printf("%d,", node->value);
    while (!Stack.empty()) {
        Node* cur = Stack.top();
        for (Node* next: cur->nexts) { //访问第一个邻接节点
            if (memo.find(next) == memo.end()) {
                Stack.push(cur);
                Stack.push(next);
                memo.insert(next);
                printf("%d,", next->value);
                break;
            }
        }
    }
}


// 拓扑排序
// 要求有向无环图
vector<Node*> sortedTopology(Graph* graph)
{
    map<Node*, int> inMap; //存储图中所有节点及其入度
    deque<Node*> zeroInQueue; //入度为0的点
    map<int, Node*>::iterator it = graph->nodes.begin();
    while (it != graph->nodes.end()) {
        inMap.insert({it->second, it->second->in});
        if (it->second->in == 0)
            zeroInQueue.push_back(it->second);
        it++;
    }
    vector<Node*> result;
    while (!zeroInQueue.empty()) {
        Node* cur = zeroInQueue.front();
        zeroInQueue.pop_front();
        result.push_back(cur); //结果中逐次加入入度为0的点
        for (Node* next: cur->nexts) {
            inMap[next]--; //更新入度
            if (inMap[next] == 0) { //节点入度为0，删除
                zeroInQueue.push_back(next);
            }
        }
    }
    return result;
}


// 最小生成树 Kruskal算法
// 并查集查找
class UnionFind
{
public:
    void makeSets(set<Node*> nodes)
    {
        fatherMap.erase(fatherMap.begin(), fatherMap.end());
        rankMap.erase(rankMap.begin(), rankMap.end());
        for (Node* node: nodes) {
            fatherMap.insert({node, node});
            rankMap.insert({node, 1});
        }
    }

    bool isSameSet(Node* a, Node* b) {
        return findFather(a) == findFather(b);
    }

    void Union(Node* a, Node* b)
    {
        if (a == nullptr || b == nullptr)
            return;

        Node* aFather = findFather(a);
        Node* bFather = findFather(b);
        if (aFather != bFather) {
            int aFrank = rankMap[aFather];
            int bFrank = rankMap[bFather];
            if (aFrank <= bFrank) {
                fatherMap[aFather] = bFather;
                rankMap[bFather] = aFrank + bFrank;
            } else {
                fatherMap[bFather] = aFather;
                rankMap[aFather] = aFrank + bFrank;
            }
        }
    }

private:
    Node* findFather(Node* n)
    {
        Node* father = fatherMap[n];
        if (father != n)
            father = findFather(father);

        fatherMap[n] = father;
        return father;
    }

    map<Node*, Node*> fatherMap;
    map<Node*, int> rankMap;
};

set<Edge*> kruskalMST(Graph* graph)
{
    UnionFind unionFind;
    set<Node*> nodeValue;
    map<int, Node*>::iterator it = graph->nodes.begin();
    while (it != graph->nodes.end())
        nodeValue.insert(it->second);

    unionFind.makeSets(nodeValue);
    priority_queue<Edge*, vector<Edge*>, greater<>> edgeSet;
    for (Edge* edge: graph->edges)
        edgeSet.push(edge);

    set<Edge*> result;
    while (!edgeSet.empty()) {
        Edge* edge = edgeSet.top();
        edgeSet.pop();
        if (!unionFind.isSameSet(edge->from, edge->to)) {
            result.insert(edge);
            unionFind.Union(edge->from, edge->to);
        }
    }
    return result;
}


// 最小生成树 prim算法
set<Edge*> primMST(Graph* graph)
{
    // 最小堆，记录与当前节点关联的边，选择最小权值边
    priority_queue<Edge*, vector<Edge*>, greater<>> edgeSet;
    set<Node*> memo; //记录访问过的节点
    set<Edge*> result;
    map<int, Node*>::iterator it = graph->nodes.begin();
    while (it != graph->nodes.end()) {
        if(memo.find(it->second) == memo.end()) {
            memo.insert(it->second);
            for(Edge* edge: it->second->edges)
                edgeSet.push(edge);
        }

        while(!edgeSet.empty()) {
            Edge* edge = edgeSet.top();
            edgeSet.pop(); //取值堆顶元素，最小权值边
            Node* toNode = edge->to;
            if(memo.find(toNode) == memo.end()) {
                memo.insert(toNode);
                result.insert(edge);
                for(Edge* nextEdge: toNode->edges)
                    edgeSet.push(nextEdge);
            }
        }
    }
    return result;
}
