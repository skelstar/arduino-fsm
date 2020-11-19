// This file is part of arduino-fsm.
//
// arduino-fsm is free software: you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// arduino-fsm is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with arduino-fsm.  If not, see <http://www.gnu.org/licenses/>.

#ifndef FSM_H
#define FSM_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

struct State
{
  State(uint8_t id, void (*on_enter)(), void (*on_state)(), void (*on_exit)());
  State(void (*on_enter)(), void (*on_state)(), void (*on_exit)());
  State(void (*on_enter)());
  uint8_t id;
  void (*on_enter)();
  void (*on_state)();
  void (*on_exit)();
};

class Fsm
{
  typedef const char *(*GetEventNameCb)(int ev);
  typedef void (*EventTriggeredCb)(int ev);

public:
  Fsm(State *initial_state);
  ~Fsm();

  void add_transition(State *state_from, State *state_to, int event,
                      void (*on_transition)());

  void add_timed_transition(State *state_from, State *state_to,
                            unsigned long interval, void (*on_transition)());

  void check_timed_transitions();

  void trigger(int event);
  void run_machine();
  int lastEvent();
  State *get_current_state();
  uint8_t get_from_state();
  void setGetEventName(GetEventNameCb getEventNameCb);
  void setEventTriggeredCb(EventTriggeredCb eventTriggeredCb);
  void print(const char *stateName, bool includeEvent = true);

  bool revisit() { return _revisit; }

private:
  struct Transition
  {
    State *state_from;
    State *state_to;
    uint8_t state_to_id;
    int event;
    void (*on_transition)();
  };
  struct TimedTransition
  {
    Transition transition;
    unsigned long start;
    unsigned long interval;
  };

  static Transition create_transition(State *state_from, State *state_to,
                                      int event, void (*on_transition)());

  void make_transition(Transition *transition);

private:
  uint8_t m_from_id;
  uint8_t m_current_id;
  State *m_current_state;
  Transition *m_transitions;
  int m_num_transitions;
  bool _revisit;
  int _lastEvent;

  TimedTransition *m_timed_transitions;
  int m_num_timed_transitions;
  bool m_initialized;

  GetEventNameCb _getEventNameCb;
  EventTriggeredCb _eventTriggeredCb;
};

#endif
