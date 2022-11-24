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
typedef unsigned long long ll;
int main()
{
  int n, h;
  cin >> n >> h;
  //动态规划
  // dp[i][j]为用i个点做搜索树高度为j的树个数
  ll dp[37][37];
  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1; // 0节点高度0树个数为0
  for (int i = 1; i <= n; i++)
  { //枚举总结点数
    for (int l = 0; l < i; l++)
    {
      //枚举左子树点数
      int r = i - 1 - l; //右子树点数
      for (int j = 0; j <= l; j++)
      { //左子树高度
        for (int k = 0; k <= r; k++)
        { //右子树高度
          dp[i][max(j, k) + 1] += dp[l][j] * dp[r][k];
        }
      }
    }
  }
  ll ans = 0;
  for (int i = h; i <= n; i++)
  {
    ans += dp[n][i];
  }
  cout << ans << endl;
  system("pause");
}
