#ifndef FSM_H
#include <Arduino.h>
#include <Fsm.h>
// #include "Fsm/Fsm.h"
#endif

typedef const char *(*GetNameCallback)(uint8_t);

class FsmManager
{
public:
  void begin(Fsm *fsm, const char *format = ">State: %s | %s\n")
  {
    _fsm = fsm;
    _format = format;
  }

  void trigger(uint8_t ev)
  {
    _lastEvent = ev;
    _fsm->trigger(ev);
  }

  void printState(uint8_t stateId, bool includeEvent = true)
  {
    if (_getStateNameCallback == nullptr)
    {
      Serial.printf("WARNING: _getStateNameCallback() callback not set!\n");
      return;
    }
    const char *stateName = _getStateNameCallback(stateId);

    if (includeEvent && _getEventNameCallback != nullptr)
    {
      Serial.printf(_format, stateName, _getEventNameCallback(_lastEvent));
    }
    else
    {
      Serial.printf(">State: %s\n", stateName);
    }
  }

  void setGetEventNameCallback(GetNameCallback cb)
  {
    _getEventNameCallback = cb;
  }

  void setGetStateNameCallback(GetNameCallback cb)
  {
    _getStateNameCallback = cb;
  }

  bool currentStateIs(uint8_t id)
  {
    return _fsm->getCurrentStateId() == id;
  }

private:
  Fsm *_fsm = nullptr;
  const char *_format;
  uint8_t _lastEvent = 0;
  const char *_stateNames;
  GetNameCallback _getEventNameCallback = nullptr;
  GetNameCallback _getStateNameCallback = nullptr;
};