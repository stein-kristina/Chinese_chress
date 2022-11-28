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

double largestSumOfAverages(vector<int> &nums, int k)
{
  int n = nums.size();
  double dp[n+1][k+1];//前n个数字划分k个的最大值
  memset(dp,0,sizeof(dp));
  double sum[n+1];
  sum[0] = 0;
  for(int i=1;i<=n;i++){
    sum[i] = sum[i-1] + nums[i-1];
    dp[i][1] = sum[i] / i;
  }
  for(int i=1;i<=n;i++){
    for(int j=2;j<=k;j++){
      for(int p=0;p<i;p++){
        dp[i][j] = max(dp[i][j],dp[p][k-1]+ (sum[i]-sum[p])/(i-p));
      }
    }
  }
  return dp[n][k];
}
typedef unsigned long long ll;
int main()
{

  system("pause");
}
