#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include <iostream>
#include <string>
#include <vector>

#include "square.h"
#include "board.h"
#include "state.h"
#include "observer.h"

class Square;

class TextDisplay: public Observer<Info, State> {
  std::vector<std::vector<char>> theDisplay;
 public:
  TextDisplay();
  void notify(Subject<Info, State> &whoFrom) override;
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif
