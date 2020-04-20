#include <iostream>
#include <string>

#include "graphicsdisplay.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay(): gd{500, 500} {
  for (int c = 0; c < 8; i++) {
    gd.drawBigString(50, 100, to_string(8 - c), 1);
    for (int r = 0; r < 8; i++) {
      if (c % 2 == 0 && r % 2 == 0) {
        gd.fillRectangle(50 * i, 200, 50, 250, 0);
      } else if (c % 2 == 0 &&  r % 2 != 0) {
        gd.fillRectangle(50 * i, 200, 50, 250, 1);
      } else if (c % 2 != 0 &&  r % 2 == 0) {
        gd.fillRectangle(50 * i, 200, 50, 250, 1);
      } else {
        gd.fillRectangle(50 * i, 200, 50, 250, 0);
      }
    }
  }
  for (char i = 'a'; i < 'h'; ++i) {
        gd.drawBigString(50, 100, to_string(i), 1);
    }
}



void GraphicsDisplay::notify(Subject<Info, State> &whoNotified) {

}




GraphicsDisplay::~GraphicsDisplay() {}
