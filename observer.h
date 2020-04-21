#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "info.h"
#include "state.h"

template <typename InfoType, typename StateType> class Subject;
class Square;

template <typename InfoType, typename StateType> class Observer {
 public:
  virtual void notify(Subject<InfoType, StateType> &whoFrom) = 0; // pass the Subject that called the notify method
  virtual ~Observer() = default;
};
#endif
