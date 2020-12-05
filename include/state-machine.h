#ifndef FSM_H
#include <Arduino.h>
#include <Fsm.h>
#endif

namespace StateA
{
  enum Event
  {
    EVENT_0 = 0,
    EVENT_1,
    EVENT_2,
    EVENT_3,
    LastEvent,
  };
  const char *eventName[] = {
      "EVENT_0",
      "EVENT_1",
      "EVENT_2",
      "EVENT_3",
  };
  enum StateID
  {
    STATE_0 = 0,
    STATE_1,
    STATE_2,
    STATE_3,
    Last_StateID,
  };
  const char *stateName[] = {
      "STATE_0",
      "STATE_1",
      "STATE_2",
      "STATE_3",
  };

  elapsedMillis sinceStateStarted;

  void trigger(Event ev);

  State state0(
      STATE_0,
      [] {
        fsmManager.printState(STATE_0);
        sinceStateStarted = 0;
      },
      [] {
        if (sinceStateStarted > 3000)
        {
          fsmManager.trigger(EVENT_0);
        }
      },
      NULL);

  State state1(
      STATE_1,
      [] {
        fsmManager.printState(STATE_1);
        sinceStateStarted = 0;
      },
      [] {
        if (sinceStateStarted > 1000)
        {
          fsmManager.trigger(EVENT_1);
        }
      },
      NULL);

  State state2(
      STATE_2,
      [] {
        fsmManager.printState(STATE_2);
      },
      [] {
        if (sinceStateStarted > 1000)
        {
          Serial.printf("Current state is 2: %s\n", fsmManager.currentStateIs(STATE_2) ? "YES" : "NO");
          fsmManager.trigger(EVENT_2);
        }
      },
      NULL);

  State state3(
      STATE_3,
      [] {
        fsmManager.printState(STATE_3);
      },
      [] {
        if (sinceStateStarted > 3000)
        {
          fsmManager.trigger(EVENT_3);
        }
      },
      NULL);

  Fsm fsm(&state0);

  void addTransitions()
  {
    fsm.add_transition(&state0, &state1, EVENT_0, NULL);
    fsm.add_transition(&state1, &state2, EVENT_1, NULL);
    fsm.add_transition(&state2, &state3, EVENT_2, NULL);
    fsm.add_transition(&state3, &state0, EVENT_3, NULL);
  }
} // namespace StateA