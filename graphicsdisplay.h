#ifndef _GRAPHICSDISPLAY_H_
#define _GRAPHICSDISPLAY_H_

#include <iostream>
#include <string>
#include <vector>

#include "square.h"
#include "board.h"
#include "state.h"
#include "observer.h"
#include "window.h"
#include "piece.h"



class Square;

class GraphicsDisplay: public Observer<Info, State> {
  Xwindow gd;
 public:
  GraphicsDisplay();
  void notify(Subject<Info, State> &whoNotified) override;
  ~GraphicsDisplay();
  
};


#endif
