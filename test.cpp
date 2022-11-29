#include <bits/stdc++.h>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : left(nullptr), right(nullptr), val(0) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
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
  int val;
  vector<Node*> child;
  Node(int val=0):val(val){}
};
Node * start = nullptr;
Node* turngraph(TreeNode *root,Node* dad,TreeNode *target){
  if(!root) return nullptr;
  Node * it = new Node(root->val);
  if(target->val == root->val) start = it;
  if(dad){
    it->child.push_back(dad);
  }
  Node* l = turngraph(root->left,it,target);
  Node * r = turngraph(root->right,it,target);
  if(l){
    it->child.push_back(l);
  }
  if(r) it->child.push_back(r);
  return it;
}
vector<int> distanceK(TreeNode *root, TreeNode *target, int k)
{
  turngraph(root,nullptr,target);
  unordered_set<Node*> seen;
  seen.insert(start);
  queue<Node*> Q;
  Q.push(start);
  int ceng = 0;
  vector<int> ans;
  while(!Q.empty()){
    int siz = Q.size();
    while(siz--){
      auto p = Q.front();
      Q.pop();
      for(auto &i :p->child){
        if(seen.find(i) == seen.end()){
          //vis
          Q.push(i);
          seen.insert(i);
          if(ceng == k){
            ans.push_back(i->val);
          }
        }
      }
    }
    if(ceng == k) break;
    ceng++;
  }
  return ans;
}
typedef unsigned long long ll;
int main()
{

  system("pause");
}
