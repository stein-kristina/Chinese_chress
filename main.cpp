#include<bits/stdc++.h>
#include"step.hpp"
#include"myboard.hpp"
#include"myboard.cpp"
#include"myboard2.cpp"
using namespace std;


int evaluate(){
  return 1;
}//评价函数
step ans;//怎么走
int minmax(chess_board & chessboard,int depth,bool colour){//最小最大搜索s
  int best = INT_MIN;
  if(depth == 0){
    return evaluate();
  }
  vector<chess_step> remain = chessboard.generlegalmove(colour);
  int val;
  for(auto &i : remain){
    pair<int,int> dead = chessboard.makemove(i,colour);
    val = -minmax(chessboard,depth-1,!colour);
    chessboard.unmakemove(i,dead,colour);
    if(val > best){
      best = val;
      if(depth == 4) ans = step(i.fromx,i.fromy,i.tox,i.toy);
    }
  }
  return best;
}
ofstream & operator<<(ofstream & of,step & should){
  of<<should.x1<<' '<<should.x2<<' '<<should.y1<<' '<<should.y2;
  return of;
}
int main(){
  chess_board chessboard;
  chessboard.init_board();
  clock_t sta,end;
  cout<<"please start your operation:";
  sta = clock();
  minmax(chessboard,4,false);//黑色开始
  end = clock();
  cout<<(double)(end-sta)<<"ms\n";
  ofstream outf;
  outf.open("C:\\Users\\86189\\Desktop\\Chinese_chress\\Debug\\move.txt");
  outf<<ans<<endl;
  outf.close();
  system("pause");
}