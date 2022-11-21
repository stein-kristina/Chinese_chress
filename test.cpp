#include <bits/stdc++.h>

using namespace std;
double soupServings(int n)
{

  int N = n/25;
  if(!N){
    return 0.625;
  }
  double dp[N+1][N+1];
  dp[0][0] = 0.5;
  for(int i=1;i<=N;i++){
    dp[0][i] = 1;//A必然先分配完
    dp[i][0] = 0;//B先分完 
  }
  for(int i=1;i<=N;i++){
    int a1 = i>=4? i-4:0;
    int b1 = i>=3? i-3:0;
    int c1 = i>=2? i-2:0;
    int d1 = i>=1? i-1:0;
    for(int j=1;j<=N;j++){
      int a2 = 0;
      int b2 = j>=1? j-1:0;
      int c2 = j>=2? j-2:0;
      int d2 = j>=3? j-3:0;
      dp[i][j] = 0.25 *(dp[a1][a2]+dp[b1][b2]+dp[c1][c2]+dp[d1][d2]);
    }
  }
  return dp[N][N];
}
int main()
{
  vector<vector<int>> a = {{0, 1}, {1, 2}, {2, 3}, {3, 4}}, b = {{1, 2}, {2, 3}, {3, 1}};

  system("pause");
}