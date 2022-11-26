#include <bits/stdc++.h>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : left(nullptr), right(nullptr), val(0) {}
};

class A
{
  int a;
  friend class B;
};
class B
{
public:
  void f(A &c)
  {
    cout << c.a;
  }
};
struct Node
{
  int dot, weigh;
  Node(int d, int w) : dot(d), weigh(w) {}
};

int reachableNodes(vector<vector<int>> &edges, int maxMoves, int n)
{
  int ans = 0;
  vector<vector<Node>> adj(n);
  for (int i = 0; i < edges.size(); i++)
  {
    adj[edges[i][0]].push_back(Node(edges[i][1], edges[i][2] + 1));
  }
  vector<int> dis(n, INT_MAX);
  dis[0] = 0;
  vector<bool> vis(n, false);
  vis[0] = true;
  auto cmp = [](const pair<int, int> &a, const pair<int, int> &b)
  {
    return a.second > b.second;
  };
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
  q.push({0, 0});
  while (!q.empty())
  {
    auto cur = q.top().first;
    q.pop();

    if (dis[cur] >= maxMoves)
      break;
    for (auto &next : adj[cur])
    {
      if (dis[next.dot] > dis[cur] + next.weigh)
      {
        dis[next.dot] = dis[cur] + next.weigh;
        q.push({next.dot, dis[next.dot]});
      }
    }
  }
  for (int i = 0; i < n; i++)
  {
    if (dis[i] <= maxMoves)
    {
      ans++;
    }
  }
  for (auto &e : edges)
  {
    // 让每条边的两个节点沿这条边往对方节点走，看看有多少个细分节点是可达的
    int a = e[0], b = e[1], cnta = 0, cntb = 0;

    if (dis[a] < maxMoves)
    {
      // 计算它往外还能多走几个细分节点
      cnta = min(e[2], maxMoves - dis[a]);
    }

    if (dis[b] < maxMoves)
    {
      cntb = min(e[2], maxMoves - dis[b]);
    }

    // 如果 cnta 和 cntb 有重叠，说明这条边上的细分节点都是可达的
    ans += min(e[2], cnta + cntb);
  }
  return ans;
}
typedef unsigned long long ll;
int main()
{

  system("pause");
}
