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

#include <enumManager.h>
#include <iostream>

namespace StateB
{
  enum Event
  {
    STATEB_0 = 0,
    STATEB_1,
    STATEB_2,
    STATEB_3,
    Length
  };

  std::string names2[] = {
      "STATEB_0",
      "STATEB_1",
      "STATEB_2",
      "STATEB_3",
  };

  const char *names[] = {
      "STATEB_0",
      "STATEB_1",
      "STATEB_2",
      "STATEB_3",
  };

} // namespace StateB

EnumManager<StateB::Event> stateB(StateB::names2);

//-----------------------------------------
void setup()
{
  Serial.begin(115200);
  Serial.printf("\n\nReady\n");

  fsmManager.begin(&StateA::fsm, "-->STATE: %s | %s\n");
  fsmManager.setGetEventNameCallback([](uint8_t ev) {
    return ev >= StateA::LastEvent ? "OUT OF RANGE" : StateA::eventName[ev];
  });
  fsmManager.setGetStateNameCallback(getStateName);

  stateB.printNames();
  Serial.printf("getName: %s\n", stateB.getName(StateB::STATEB_0));
  Serial.printf("getName: %s\n", stateB.getName(10));

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
