
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
  // 0 means draw.
  int State::eval() const
  {
    //IMPLEMENTAR
    
    return 0;
  }

  // returns WIN if MAX won, -WIN if MIN won and 0 otherwise.
  int State::win() const
  {
    //IMPLEMENTAR

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
