#include "myboard.hpp"

#include <bits/stdc++.h>
using namespace std;

//以下都是产生合理做法的函数
const vector<vector<pair<int, int>>> canmove = {
    {{2, 2}, {2, -2}, {-2, -2}, {-2, 2}},                                     //象,需要特判不超过边界，红方的y不能过4,黑不过5
    {},                                                                       //炮,四条直线，可以隔山打牛
    {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}},                                     //士,对角线
    {{0, 1}, {-1, 0}, {1, 0}, {0, -1}},                                       //帅,上左右下
    {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}}, //马
    {{0, 1}, {-1, 0}, {1, 0}, {0, -1}},                                       //兵，特判，过边界就可以上下左右
    //车就不写了，没特判
}; //所有棋子走法的规则
bool chess_board::islimit(int &x, int &y, int &u, int &d, int &l, int &r, bool colour)
{
  if (x >= l && x <= r && y >= d && y <= u)
  {
    if (!board[x][y])
      return true; //没有棋子必定可以
    // if (board[x][y]->dead)
    //   return true; //该位置棋子是死的
    if (board[x][y]->colour == colour)
    {
      //棋子跟自己同色，必定不可以走
      return false;
    }
    return true; //不同色，可以走，就吃掉
  }
  return false;
} //判断棋子是否在边界内
vector<chess_step> chess_board::generlegalmove(bool colour)
{
  // col true为红，否则为黑
  vector<chess_step> ans;
  vector<vector<Ctype *>> &it = colour ? red : black; //选择棋子列表
  int up, down, left, right;                          //对应棋子的上下左右边界，闭区间
  for (int i = 0; i < 7; i++)
  { //遍历不同棋子
    int n = it[i].size();
    if(!n) continue;
    switch (i)
    {
    case 0:
    { // bishop象
      Ctype *p1 = nullptr;
      if (colour)
      {
        up = 4, down = 0, left = 0, right = 8; //红色
      }
      else
      {
        up = 9, down = 5, left = 0, right = 8; //黑色
      }
      for (int j = 0; j < n; j++)
      {
        p1 = it[i][j]; //选择一个象
        if (p1->dead)
          continue; //死了就不管了
        for (auto &one : canmove[i])
        {
          int ix = p1->x + one.first, iy = p1->y + one.second;
          if (islimit(ix, iy, up, down, left, right, colour))
          {
            int foot1 = (ix + p1->x) >> 1, foot2 = (iy + p1->y) >> 1;
            if (board[foot1][foot2])
              continue; //象脚被堵
            ans.push_back(chess_step(i, j, p1->x, p1->y, ix, iy));
          }
        }
      }
      break;
    }
    case 1:
    { //炮
      Ctype *p1 = nullptr;
      up = 9, down = 0, left = 0, right = 8;
      bool f1;
      f1 = true;
      for (int j = 0; j < n; j++)
      {
        p1 = it[i][j]; //选择一个炮
        if (p1->dead)
          continue; //死了就不管了
        for (int zuo = 1; zuo <= 8; zuo++)
        { //左移
          int ix = p1->x - zuo, iy = p1->y;
          if (ix >= 0 && ix <= 8 && iy >= 0 && iy <= 9)
          {
            if (board[ix][iy])
            {
              //有棋子
              for (int k = ix - 1; k >= 0; k--)
              { //坐标(k,iy)，寻找第一个能炸的
                if (!board[k][iy])
                  continue;
                else
                {
                  if (board[k][iy]->colour != colour)
                  {
                    //异色，可以炸
                    ans.push_back(chess_step(i, j, p1->x, p1->y, k, iy));
                  }
                  break;
                }
              }
              break;
            }
            else
              ans.push_back(chess_step(i, j, p1->x, p1->y, ix, iy));
          }
          else
            break; //不能下就break了
        }
        //炮有两种选择，一种是纯移动，一种是炸他
        for (int you = 1; you <= 8; you++)
        { //右移
          int ix = p1->x + you, iy = p1->y;
          if (ix >= 0 && ix <= 8 && iy >= 0 && iy <= 9)
          {
            if (board[ix][iy])
            {
              //有棋子
              for (int k = ix +1; k <= 8; k++)
              { //坐标(k,iy)，寻找第一个能炸的
                if (!board[k][iy])
                  continue;
                else
                {
                  if (board[k][iy]->colour != colour)
                  {
                    //异色，可以炸
                    ans.push_back(chess_step(i, j, p1->x, p1->y, k, iy));
                  }
                  break;
                }
              }
              break;
            }
            else
              ans.push_back(chess_step(i, j, p1->x, p1->y, ix, iy));
          }
          else
            break; //不能下就break了
        }
        for (int shang = 1; shang <= 9; shang++)
        { //上移
          int ix = p1->x , iy = p1->y + shang;
          if (ix >= 0 && ix <= 8 && iy >= 0 && iy <= 9)
          {
            if (board[ix][iy])
            {
              //有棋子
              for (int k = iy +1; k <= 9; k++)
              { //坐标(ix,k)，寻找第一个能炸的
                if (!board[ix][k])
                  continue;
                else
                {
                  if (board[ix][k]->colour != colour)
                  {
                    //异色，可以炸
                    ans.push_back(chess_step(i, j, p1->x, p1->y, ix, k));
                  }
                  break;
                }
              }
              break;
            }
            else
              ans.push_back(chess_step(i, j, p1->x, p1->y, ix, iy));
          }
          else
            break; //不能下就break了
        }
        for (int xia = 1; xia <= 9; xia++)
        { //下移
          int ix = p1->x , iy = p1->y - xia;
          if (ix >= 0 && ix <= 8 && iy >= 0 && iy <= 9)
          {
            if (board[ix][iy])
            {
              //有棋子
              for (int k = iy -1; k >=0; k--)
              { //坐标(ix,k)，寻找第一个能炸的
                if (!board[ix][k])
                  continue;
                else
                {
                  if (board[ix][k]->colour != colour)
                  {
                    //异色，可以炸
                    ans.push_back(chess_step(i, j, p1->x, p1->y, ix, k));
                  }
                  break;
                }
              }
              break;
            }
            else
              ans.push_back(chess_step(i, j, p1->x, p1->y, ix, iy));
          }
          else
            break; //不能下就break了
        }
      }
      break;
    }
    case 2:
    { //士
      Ctype *p1 = nullptr;
      if (colour)
      {
        up = 2, down = 0, left = 3, right = 5; //红色
      }
      else
      {
        up = 9, down = 7, left = 3, right = 5; //黑色
      }
      for (int j = 0; j < n; j++)
      {
        p1 = it[i][j]; //选择一个士
        if (p1->dead)
          continue; //死了就不管了
        for (auto &one : canmove[i])
        {
          int ix = p1->x + one.first, iy = p1->y + one.second;
          if (islimit(ix, iy, up, down, left, right, colour))
          {
            ans.push_back(chess_step(i, j, p1->x, p1->y, ix, iy));
          }
        }
      }
      break;
    }
    case 3:
    { //帅
      Ctype *p1 = nullptr;
      if (colour)
      {
        up = 2, down = 0, left = 3, right = 5; //红色
      }
      else
      {
        up = 9, down = 7, left = 3, right = 5; //黑色
      }
      for (int j = 0; j < n; j++)
      {                // 只有一个
        p1 = it[i][j]; //选择一个
        if (p1->dead)
          continue; //死了就不管了
        //飞将判定
        
          for(int k = 1 ; k <= 9 ; k++ ){
            int jk = colour ? k : -k;
            if(p1->y + jk < 0 || p1->y + jk > 9) break;
            Ctype * p2 =board[p1->x][p1->y + jk];
            if(!p2) continue;
            if(p2->type == 3){
              //可以飞将
              ans.push_back(chess_step(i, j, p1->x, p1->y, p1->x, p1->y+jk));
            }
            break;
          }
        
        for (auto &one : canmove[i])
        {
          int ix = p1->x + one.first, iy = p1->y + one.second;
          if (islimit(ix, iy, up, down, left, right, colour))
          {
            ans.push_back(chess_step(i, j, p1->x, p1->y, ix, iy));
          }
        }
      }
      break;
    }
    case 4:
    { //马
      Ctype *p1 = nullptr;
      up = 9, down = 0, left = 0, right = 8;
      for (int j = 0; j < n; j++)
      {
        p1 = it[i][j]; //选择一个
        if (p1->dead)
          continue; //死了就不管了
        for (auto &one : canmove[i])
        {
          int ix = p1->x + one.first, iy = p1->y + one.second;
          if (islimit(ix, iy, up, down, left, right, colour))
          {
            //判断马脚，一共四个
            if (one.second == 2 && board[p1->x][p1->y + 1])
            {
              continue;
            }
            else if (one.second == -2 && board[p1->x][p1->y - 1])
            {
              continue;
            }
            else if (one.first == 2 && board[p1->x + 1][p1->y])
            {
              continue;
            }
            else if (one.first == -2 && board[p1->x - 1][p1->y])
            {
              continue;
            }
            ans.push_back(chess_step(i, j, p1->x, p1->y, ix, iy));
          }
        }
      }
      break;
    }
    case 5:
    { //兵
      Ctype *p1 = nullptr;
      if (colour)
      {
        up = 9, down = 5, left = 0, right = 8; //红色
      }
      else
      {
        up = 4, down = 0, left = 0, right = 8; //黑色
      }
      for (int j = 0; j < n; j++)
      {
        p1 = it[i][j]; //选择一个bing
        if (p1->dead)
          continue; //死了就不管了
        if (colour)
        {
          int iy = p1->y +1;
          if (p1->y <= 4)
          {
            if(board[p1->x][iy] && board[p1->x][iy]->colour == colour){
              continue;//有棋子而且同色
            }
            ans.push_back(chess_step(i, j, p1->x, p1->y, p1->x, iy)); //没过河
            continue;
          }
        }
        else
        {
          int iy = p1->y -1;
          if (p1->y >= 5)
          {
            if(board[p1->x][iy] && board[p1->x][iy]->colour == colour){
              continue;//有棋子而且同色
            }
            ans.push_back(chess_step(i, j, p1->x, p1->y, p1->x, iy));
            continue;
          }
        }
        for (auto &one : canmove[i])
        {
          int ix = p1->x + one.first, iy = p1->y + one.second;
          if (colour && one.second == -1)
            continue; //红兵不能往回走
          if (!colour && one.second == 1)
            continue; //黑兵不能往回走
          if (islimit(ix, iy, up, down, left, right, colour))
          {
            ans.push_back(chess_step(i, j, p1->x, p1->y, ix, iy));
          }
        }
      }
      break;
    }
    case 6:
    { //车
      Ctype *p1 = nullptr;
      up = 9, down = 0, left = 0, right = 8;
      for (int j = 0; j < n; j++)
      {
        p1 = it[i][j]; //选择一个车
        if (p1->dead) continue;    //死了就不管了
        bool f = true; //用于截胡车的
        for (int zuo = 1; zuo <= 8; zuo++)
        { //左移
          int ix = p1->x - zuo, iy = p1->y;
          if (islimit(ix, iy, up, down, left, right, colour) && f)
          {
            if (board[ix][iy])
              f = false; //有棋子
            ans.push_back(chess_step(i, j, p1->x, p1->y, ix, iy));
          }
          else
            break; //不能下就break了
        }
        f = true;
        for (int you = 1; you <= 8; you++)
        { //右移
          int ix = p1->x + you, iy = p1->y;
          if (islimit(ix, iy, up, down, left, right, colour) && f)
          {
            if (board[ix][iy])
              f = false; //有棋子
            ans.push_back(chess_step(i, j, p1->x, p1->y, ix, iy));
          }
          else
            break; //不能下就break了
        }
        f = true;
        for (int shang = 1; shang <= 9; shang++)
        { //上移
          int ix = p1->x, iy = p1->y + shang;
          if (islimit(ix, iy, up, down, left, right, colour) && f)
          {
            if (board[ix][iy])
              f = false; //有棋子
            ans.push_back(chess_step(i, j, p1->x, p1->y, ix, iy));
          }
          else
            break; //不能下就break了
        }
        f = true;
        for (int xia = 1; xia <= 9; xia++)
        { //上移
          int ix = p1->x, iy = p1->y - xia;
          if (islimit(ix, iy, up, down, left, right, colour) && f)
          {
            if (board[ix][iy])
              f = false; //有棋子
            ans.push_back(chess_step(i, j, p1->x, p1->y, ix, iy));
          }
          else
            break; //不能下就break了
        }
      }
      break;
    }
    // Bishop,Cannon,Guard,King,Knight,Pawn,Rock
    default:
      break;
    }
  }
  return ans;
}