#ifndef CHRESS_BOARD
#define CHRESS_BOARD
#include <bits/stdc++.h>
using namespace std;
enum chess
{
  Bishop = 0,
  Cannon,
  Guard,
  King,
  Knight,
  Pawn,
  Rock
}; //哈希表
unordered_map<string, int> chess_index;
//象，炮，士，帅，马，兵，车
struct Ctype
{//棋子类型
  bool colour;//颜色，true为红，false为黑
  int type;//棋子类型
  int x, y;//位置
  bool dead; // true就死了，false活着
  Ctype(bool c,int t,int x, int y, bool f) :colour(c),type(t), x(x), y(y), dead(f){}
};
class chess_board
{
private:
  Ctype* board[9][10];//棋盘
  vector<vector<Ctype*>> black; //黑方棋子
  vector<vector<Ctype*>> red;   //红方棋子
  //上述两个vector均用于产生合理的步数

public:
  chess_board()
  {
    memset(board,0,sizeof(board));//初始化全部nullptr
    black.resize(7);
    red.resize(7);
  }
  void init_board();//初始化棋盘

  bool islimit(int &x,int &y,int &u,int &d,int &l,int &r,bool colour);
  vector<chess_step> generlegalmove(bool colour);//产生所有合理走法
  
  friend int AlphaBeta(chess_board &chessboard, int depth, int alpha, int beta, bool colour);
  friend int minmax(chess_board &chessboard, int depth, bool colour);

  pair<int,int> makemove(chess_step &tar,bool colour);
  void unmakemove(chess_step &tar,pair<int,int> &dead,bool colour);
};
#endif