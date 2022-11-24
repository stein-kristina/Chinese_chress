#ifndef STEP_STEP
#define STEP_STEP

struct step
{
  int x1,x2;
  int y1,y2;
  //x1,x2->y1,y2
  step(int a1=0,int a2=0,int b1=0,int b2=0):x1(a1),x2(a2),y1(b1),y2(b2){}
  step& operator=(step && other){
    x1=other.x1,x2=other.x2,y1=other.y1,y2=other.y2;
    return *this;
  }
};

//什么棋子，从哪里走到哪里,用于产生合理步数
struct chess_step
{
  int typei,typej;//对应red，black棋子列表里的
  int fromx,fromy;
  int tox,toy;//从哪里来，到哪里去
  chess_step(){}
  chess_step(int a,int b,int c,int d,int e,int f):typei(a),typej(b),fromx(c),fromy(d),tox(e),toy(f){}
};

#endif