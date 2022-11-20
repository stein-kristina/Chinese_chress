#include<bits/stdc++.h>
#include"board.hpp"

using namespace std;

void chess_board::init_board(){
  ifstream ifs;
  ifs.open("board.txt");
  string s1,s2;
  int i1,i2;
  while(ifs>>s1>>s2>>i1>>i2){
    cout<<s1<<' '<<s2<<' '<<i1<<' '<<i2<<endl;
  }
  ifs.close();
}

int main(){
  chess_board chessboard;
  chessboard.init_board();
  system("pause");
}