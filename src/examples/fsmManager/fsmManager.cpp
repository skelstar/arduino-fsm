#include <Arduino.h>
#include <elapsedMillis.h>
#include <shared-utils.h>
#include <Fsm.h>

#include <fsmManager.h>
FsmManager fsmManager;

#include "state-machine.h"

const char *getStateName(uint8_t ev)
{
  return ev >= StateA::Last_StateID ? "OUT OF RANGE" : StateA::stateName[ev];
}

const char *getEventName(uint8_t ev)
{
  return ev >= StateA::LastEvent ? "OUT OF RANGE" : StateA::eventName[ev];
}

//-----------------------------------------
void setup()
{
  Serial.begin(115200);
  Serial.printf("\n\nReady\n");

  fsmManager.begin(&StateA::fsm, "-->STATE: %s %s\n");
  fsmManager.setGetEventNameCallback(getEventName);
  fsmManager.setGetStateNameCallback(getStateName);

  StateA::addTransitions();
}
//-----------------------------------------
elapsedMillis sincePing, sinceSeededQueue, sinceFsm;
ulong seed = 0;

void loop()
{
  if (sinceFsm > 1000)
  {
    sinceFsm = 0;
    StateA::fsm.run_machine();
  }
}
//-----------------------------------------
