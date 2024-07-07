#include "State.h"
#include <functional>


  // initialize empty board
  // MAX to move
  State::State()
  {
    sq = { {} };
    to_move = MAX;
    filled = 0;
  }

  // return true if board is full
  bool State::full() const
  {
    return filled >= SIZE;
  }
  
  // initialize state from string (MAX to move)
  // throw InputExceptiuon when you encounter
  // an error in s
  void State::set(const string & s)
  {
    // create input stream from string, now you can use >>, etc.
    // like for cin
    istringstream is(s);
    char c;

    to_move = MAX;
    filled = 0;

    for (int y=0; y < M; ++y) {
      for (int x=0; x < N; ++x) {
        is >> c;
        if (!is) {
          throw InputException();
        }
        if      (c == DISP[1+MAX]) { sq[y][x] = MAX; ++filled; }
        else if (c == DISP[1+MIN]) { sq[y][x] = MIN; ++filled; }
        else                         { sq[y][x] = 0; }
      }
    }
    is >> c;
    if (is) {
      // trailing character(s)
      throw InputException();
    }
  }
  
  // print state to cout
  // format:
  //
  //  xox
  //  o-x
  //  xxo
  //  x (8)
  //
  // last line: player to move, number of filled squares
  // followed by new-line
  void State::print() const
  {
    for (int y=0; y < M; ++y) {
      for (int x=0; x < N; ++x) {
        cout << DISP[sq[y][x] + 1];
      }
      cout << endl;
    }
    // print player to move and #filled squares
    cout << DISP[to_move + 1]
         << " (" << filled << ")"
         << endl;
  }
  

  // returns an estimate on who is winning. Positive values up to WIN means current player is winning, 
  // negative values down to -WIN means opponent is winning, 
  // 0 means draw.           da una estimacion de quien va ganando o si van empatados
  int State::eval() const
  {
    //IMPLEMENTAR
    int score= 0; 
    //ahora toca recorrer los sentidos del tablero(?)       se utilizaran x e y para horizontal y diagonal ^w^
   for(int y= 0; y <N; ++y){
      for(int x= 0; x <M; ++x){
        //ahora diagonal
        for(int yY = -1; yY<=1; ++yY){
          for(int xX = -1; xX <= 1; ++xX){
            if(xX == 0 && yY== 0) continue;// esto evita que se este viendo la misma posicion ^w^
            int cuentaMAX= 0,cuentaMIN = 0,cuentaVacia = 0;
            for(int i= 0; i< K;++i){
              int xX = x+i*xX;
              int yY = y+ i*yY;
              if(xX < 0 || xX >= N || yY < 0 || yY >= M) break;

              if(State.sq[yY][xX] == MAX ){
                cuentaMAX++;  //suma un min cad avez que hay un x
              } 
              else if(State.sq[yY][xX] == MIN ){
                cuentaMIN++; //suma un min cad avez que hay un o
              } 
              else cuentaVacia++;
              // ahora se evaluaran para entregar puntajes el codigo evalua dos vecesl la linea por ende el puntaje sera 5 + 5 
              if(cuentaMAX == K-1 && cuentaVacia == 1){
                score += 5;
              } 
              if(cuentaMIN == K-1 && cuentaVacia == 1){
                score -= 5;
              } 
              
            }
          }
        }
      }
    }
    return score * to_move;
  }

  int State::win() const
{
  //IMPLEMENTAR
    int score= 0;
    // score += 5; cout<<"SUMA"<<endl;
    //ahora toca recorrer los sentidos del tablero(?)       se utilizaran x e y para horizontal y diagonal ^w^
    for(int y= 0; y <N; ++y){
      for(int x= 0; x <M; ++x){
        //ahora diagonal
        for(int yY = -1; yY<=1; ++yY){
          for(int xX = -1; xX <= 1; ++xX){

            if(xX == 0 && yY== 0) continue;// esto evita que se este viendo la misma posicion ^w^
            int cuentaMAX= 0,cuentaMIN = 0,cuentaVacia = 0;
            for(int i= 0; i< K;++i){
              // cout<<"x: "<<x<<" y: "<<y<<" i: "<<i<<" xX: "<<xX<<" yY: "<<yY<<endl;
              int _xX = x+i*xX;
              int _yY = y+i*yY;
              // cout<<"_xX: "<<_xX<<" _yY: "<<_yY<<endl;
              if(_xX < 0 || _xX >= M || _yY < 0 || _yY >= N) break;
              if(sq[_yY][_xX] == MAX ){
                cuentaMAX++;
              } 
              else if(sq[_yY][_xX] == MIN ){
                cuentaMIN++;
              } 
              else cuentaVacia++;

              // cout<<"cuentaMAX: "<<cuentaMAX<<" cuentaMIN: "<<cuentaMIN<<" cuentaVacia: "<<cuentaVacia<<"["<<y<<"]["<<x<<"]"<<endl; 
              // ahora se evaluaran para entregar puntajes, ver mañana ando morido de sueño
              if(cuentaMAX == K && cuentaVacia == 0){ 
                return 10;
              }
              if(cuentaMIN == K && cuentaVacia == 0){
                return -10;
              }
            }
          }
        }
      }
    }
    // score * to_move
    return 0;
}

  // make move (x, y) for player to_move
  // and return true iff move is legal
  // pre-condition: x, y within range
  bool State::make_move(int x, int y)
  {
    assert(x >= 0 && x < M && y >= 0 && y < N);
    auto &c = sq[y][x];
    if (c) {
      return false; // already occupied
    }
    
    c = to_move;
    to_move = - to_move;
    ++filled;
    return true;
  }

  // return player to move
  int State::get_to_move() const
  {
    return to_move;
  }
  
  

// how pieces are displayed ...
// MIN, empty, MAX
const array<char, 3> State::DISP = {{ 'o', '-', 'x' }};
