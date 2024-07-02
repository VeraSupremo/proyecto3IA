

#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include "State.h"

// # evaluations performed
int evals;

// minimax search (negamax variant)
//
// return state value [-WIN - WIN]in VIEW of the PLAYER to MOVE
// I.e., if MAX is to move and MAX wins, return WIN
//       if MAX is to move and MAX loses, return -WIN
//       if MAX is to move and game is a draw, return 0
//       if MIN is to move and MIN wins, return WIN
//       if MIN is to move and MIN loses, return -WIN
//       if MIN is to move and game is a draw, return 0
//
// also store best move in best_x, best_y ; (-1,-1) if no move available
int negamax(const State &st, int &best_x, int &best_y, int height)
{
  best_x = best_y = -1; // no move yet 
  evals++;

  // if game ended or height reached, return value
  // if ( ) {
  // }

  //IMPLEMENTAR
  
  //return state score
  return 0;
}

// return state value [-WIN - WIN]in VIEW of the PLAYER to MOVE
int alphabeta(const State &st, int &best_x, int &best_y, int height, int alpha, int beta)
{
  //IMPLEMENTAR
  return 0;
}

// solve position given in state st and print the following to stdout:
// - first print the state
// - then if a player already won without making a move,
//   print "a player already won"
// - otherwise, print "draw" if no moves are available
// - otherwise, print "p wins with (x,y)" for player-to-move p (x or o) and
//   a best move (x,y) if player p wins
// - otherwise, print "p draws with (x,y)" for player-to-move p (x or o) and
//   a best move (x,y) if player p draws
// - otherwise, print "p loses" if player-to-move p (x or o) loses
void solve(const State & st)
{
  cout<<"**********************NEW BOARD*****************************"<<endl;
  for(int i=2;i<8;i+=2){
    cout<<"===================Depth: "<<i<<"========================"<<endl;
    evals=0;
    st.print();
    int v = st.win();
    if (v != 0) {
      cout << "a player already won";
    } else if (st.full()) {
      cout << "draw";
    } else {
      int best_x, best_y;
      char tm = State::DISP[st.get_to_move() + 1];
      int v = negamax(st, best_x, best_y,i);
      if (v > 0) {
        cout << tm << " wins with (" << best_x << "," << best_y << ")";
      } else if (v == 0) {
        cout << tm << " draws with (" << best_x << "," << best_y  << ")";
      } else {
        cout << tm << " loses";
      }
    }
    cout <<endl<< "Negamax Visited nodes: "<<evals<<endl;


    evals=0;
    //st.print();
    v = st.win();
    if (v != 0) {
      cout << "a player already won";
    } else if (st.full()) {
      cout << "draw";
    } else {
      int best_x, best_y;
      char tm = State::DISP[st.get_to_move() + 1];
      int v = alphabeta(st, best_x, best_y,i, -100000, 100000);
      if (v > 0) {
        cout << tm << " wins with (" << best_x << "," << best_y << ")";
      } else if (v == 0) {
        cout << tm << " draws with (" << best_x << "," << best_y  << ")";
      } else {
        cout << tm << " loses";
      }
    }
    cout <<endl<< "Alphabeta Visited nodes: "<<evals<<endl;
    }

}


    std::vector<string> boards3
  {
    "--- \
     --- \
     ---", // x draws with (0,0)

    "--- \
     -o- \
     ---", // x draws with (0,0)

    "--- \
     --o \
     ---", // x draws with (0,1)

    "-oo \
     ooo \
     ooo", // a player already won
  
    "xox \
     oxo \
     oxo", // draw

    "--o \
     -oo \
     ---", // x loses

    "oxo \
     xx- \
     oox", // x wins with (2,1)

    "-xo \
     oox \
     xoo", // x draws with (0,0)

    "--- \
     -x- \
     ---"  // x wins with (0,0)
};
   std::vector<string> boards4
  {
    "-x-o \
     ooxo \
     oox- \
     xoo-",

    "---- \
     ---- \
     ---- \
     ----"



  };
   std::vector<string> boards5
  {
    "----- \
     ----- \
     ----- \
     ----- \
     -----"
  };

void test(){
  for (const string & s : boards3) {
    // construct state from string
    // also catch exception and print
    // error message
    try {
      State st;
      st.set(s);
      st.print();
      cout<<st.win()<<endl;
      solve(st);
      cout << endl;
    }
    catch (InputException & e) {
      cerr << "corrupt input: " << s << endl;
    }
  }
}

void play(){
  State st;
  while(!st.full() && st.win()==0){
    st.print();cout<<endl;
    int best_x, best_y;
    //int v = alphabeta(st, best_x, best_y,6,-10000,10000);
    int v = negamax(st, best_x, best_y,4);
    assert(st.make_move(best_x,best_y));

    st.print();cout<<endl;
    if(!st.full() && st.win()==0){
      //v = alphabeta(st, best_x, best_y,2,-10000,-10000);
      v = negamax(st, best_x, best_y,4);
      assert(st.make_move(best_x,best_y));  
    }

  }
  st.print();
}      
  
int main()
{
  test();
  //play();

  return 0;

}
