#pragma once

#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <array>


using namespace std;

// thrown when set() encounters an illegal input
struct InputException { };

class State
{
public:

  // players  
  enum Players { MIN = -1, MAX = 1 };

  // winning points
  static const int WIN = 1000;

  // edge length
  static const int M = 3;
  static const int N = 3;
  static const int K = 3;
  // number of squares
  static const int  SIZE = M*N;

  // how pieces are displayed ... see below
  // MIN, empty, MAX
  static const array<char, 3> DISP;

  // initialize empty board
  // MAX to move
  State();

  // return true if board is full
  bool full() const;
  
  // initialize state from string (MAX to move)
  // throw InputExceptiuon when you encounter
  // an error in s
  void set(const string & s);
  
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
  void print() const;
  
  // return MAX if MAX won, MIN if MIN won, and 0 otherwise
  int win() const;

  // Returns WIN if player to move wins, -WIN if he loses, and 
  // a value in between otherwise. The idea is that if the game seems tied, it returns 0, 
  // if player to move is winning it returns a positive number between 1 and WIN-1, 
  // and negative for losing.
  int eval() const;

  // make move (x, y) for player to_move
  // and return true iff move is legal
  // pre-condition: x, y within range
  bool make_move(int x, int y);

  // return player to move
  int get_to_move() const;
  
  //TODO: check https://en.cppreference.com/w/cpp/utility/hash
  //asegurese de incluir toda la informacion relevante en el hash
  unsigned int hash() const;
private:

  // MAX or MIN to move  
  int to_move;

  // squares (2d array)
  // stores MAX,0,MIN values
  // bounds are checked in debug mode
  // and sq[y][x] = 0 works
  array<array<signed char, M>, N> sq;

  // number of non-empty squares
  int filled;           
};





