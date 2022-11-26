#include "myboard.hpp"
#include"step.hpp"
#include "score.hpp"
#include<bits/stdc++.h>
using namespace std;

// Bishop,Cannon,Guard,King,Knight,Pawn,Rock
void chess_board::init_board(){
  chess_index["Bisshop"]=0;
  chess_index["Cannon"]=1;
  chess_index["Guard"]=2;
  chess_index["King"]=3;
  chess_index["Knight"]=4;
  chess_index["Pawn"]=5;
  chess_index["Rock"]=6;
  //初始化哈希表
  ifstream ifs;
  ifs.open("C:\\Users\\86189\\Desktop\\Chinese_chress\\chinachress\\board.txt");
  if(!ifs.is_open()){
    cout<<"打开文件失败！"<<endl;
    return ;
  }
  string s1,s2;
  int i1,i2,sel;
  Ctype *p;
  while(ifs>>s1>>s2>>i1>>i2){
    sel = chess_index[s2];
    if(s1 == "Red"){
      p = new Ctype(true,sel,i1,i2,false);
      red[sel].push_back(p);
      retval.rch_score += chess_weigh[sel];//红棋加分
    }
    else{
      p = new Ctype(false,sel,i1,i2,false);
      black[sel].push_back(p);
      retval.bch_score += chess_weigh[sel];
    }
    board[i1][i2] = p;
    retval.red_score += chess_score[sel][i2][i1];//位置加权
  }
  ifs.close();
}

pair<int,int> chess_board::makemove(chess_step &tar,bool colour){
  /*
    返回一个棋子列表中的位置，若makemove的过程中没有棋子死亡则为<-1,-1>，否则为i,j，对应死亡的棋子列表
  */
  pair<int,int> ans = {-1,-1};
  Ctype *dead = board[tar.tox][tar.toy];
  vector<vector<Ctype*>> &it = colour ? black:red;//选择要死的那边的颜色
  int type = dead ? dead->type : -1;//要死的棋子的类型 ，可能没棋子死
  if(dead){//不为空，有棋子要死！因为是合法的，已经判断颜色了，颜色必不同
    for(int i=0;i<it[type].size();i++){
      Ctype *ele = it[type][i];
      if(ele->x == tar.tox && ele->y == tar.toy){
        //找到那个将死的棋子
        ele->dead = true;//死了
        ans = {type,i};//死的棋子在那边的列表位置
        break;
      }
    }
    //有棋子死了，棋子分数必然发生变化
    if(colour){//红下黑死
      retval.bch_score -= chess_weigh[dead->type];
    }
    else{
      retval.rch_score -= chess_weigh[dead->type];
    }
  }
  if(colour){//权值修改
    //到我了
    retval.red_score = retval.red_score - chess_score[tar.typei][tar.fromy][tar.fromx] + chess_score[tar.typei][tar.toy][tar.tox];
  }
  vector<vector<Ctype*>> &player = colour ? red : black;
  Ctype *move = player[tar.typei][tar.typej];
  move->x = tar.tox,move->y = tar.toy;
  board[tar.fromx][tar.fromy] = 0;
  board[tar.tox][tar.toy]=move;
  return ans;
}

void chess_board::unmakemove(chess_step &tar,pair<int,int> &dead,bool colour){
  vector<vector<Ctype*>> &it = colour ? black:red;//选择要死的那边的颜色

  vector<vector<Ctype*>> &player = colour ? red : black;
  Ctype *back = player[tar.typei][tar.typej];
  Ctype *relive = 0;//重生
  if(dead != make_pair(-1,-1)){
    //有棋子死了
    relive = it[dead.first][dead.second];//dead是死亡棋子在那边的位置
    relive ->dead = false;//活啦

    if(colour){//红下黑死
      retval.bch_score += chess_weigh[dead.first];
    }
    else{
      retval.rch_score += chess_weigh[dead.first];
    }
  }
  if(colour){//权值修改
    //到我了
    retval.red_score = retval.red_score + chess_score[tar.typei][tar.fromy][tar.fromx] - chess_score[tar.typei][tar.toy][tar.tox];
  }
  back->x = tar.fromx,back->y = tar.fromy;
  board[tar.fromx][tar.fromy] = back;
  board[tar.tox][tar.toy] = relive;
}