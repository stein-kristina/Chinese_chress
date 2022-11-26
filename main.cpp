#include <bits/stdc++.h>
#include "score.hpp"
#include "step.hpp"
#include "myboard.hpp"
score retval;//当前局面的评价值
#include "myboard.cpp"
#include "myboard2.cpp"
using namespace std;



int evaluate()//评价函数
{
  return retval.red_score + retval.rch_score - retval.bch_score;
}

step ans; //怎么走
int minmax(chess_board &chessboard, int depth, bool colour)
{ //最小最大搜索s
  int best = -1e9;
  vector<vector<Ctype*>> &it = colour ? chessboard.red:chessboard.black;
  if(it[3][0]->dead){//有帅死了
    return colour ? -1e9 : 1e9;//自己的死了，返回负无穷，否则返回正无穷
  }
  if (depth == 0)
  {
    return evaluate();
  }
  vector<chess_step> remain = chessboard.generlegalmove(colour);
  int val;
  for (auto &i : remain)
  {
    pair<int, int> dead = chessboard.makemove(i, colour);
    val = -minmax(chessboard, depth - 1, !colour);
    chessboard.unmakemove(i, dead, colour);
    if (val > best)
    {
      best = val;
      if (depth == 4)
        ans = step(i.fromx, i.fromy, i.tox, i.toy);
    }
  }
  return best;
}
int AlphaBeta(chess_board &chessboard, int depth, int alpha, int beta, bool colour)
{ //阿尔法beta搜索
  vector<vector<Ctype*>> &it = colour ? chessboard.red:chessboard.black;
  if(it[3][0]->dead){//有帅死了
    return colour ? -1e9 : 1e9;//自己的死了，返回负无穷，否则返回正无穷
  }
  if (depth == 0)
  {
    return evaluate();
  }
  vector<chess_step> remain = chessboard.generlegalmove(colour);
  int val;
  for (auto &i : remain)
  {
    pair<int, int> dead = chessboard.makemove(i, colour);
    val = -AlphaBeta(chessboard, depth - 1, -beta, -alpha, !colour);
    chessboard.unmakemove(i, dead, colour);

    if (val >= beta)
    {
      return beta;
    }
    if (val > alpha)
    {
      alpha = val;
      if (depth == 6){
        ans = step(i.fromx, i.fromy, i.tox, i.toy);
      }
    }
  }
  return alpha;
}

ofstream &operator<<(ofstream &of, step &should)
{
  of << should.x1 << ' ' << should.x2 << ' ' << should.y1 << ' ' << should.y2;
  return of;
}
ostream &operator<<(ostream &os, step &should)
{
  os << 8 - should.x1 << ' ' << 9 - should.x2 << ' ' << 8 - should.y1 << ' ' << 9 - should.y2;
  return os;
}
int main()
{
  chess_board chessboard;
  chessboard.init_board();
  clock_t sta, end;
  cout << "please start your operation:" << endl;
  sta = clock();
  minmax(chessboard, 4, true); //机器以为自己是红，我们看到的是黑，棋盘反转
  int alp = -1e9 , beta = 1e9;
  // AlphaBeta(chessboard, 6 , alp , beta , true);
  end = clock();
  cout << (double)(end - sta) << "ms\n";
  ofstream outf;
  outf.open("C:\\Users\\86189\\Desktop\\Chinese_chress\\chinachress\\move.txt");
  outf << ans;
  outf.close();
  cout << ans << '\n';
  return 0;
}