
template <typename T>
class EnumManager
{
public:
  EnumManager(std::string *names)
  {
    _names = names;
    _numNames = sizeof(names);
  }

  void printNames()
  {
    Serial.printf("sizeof(names): %d\n", sizeof(_names));
    int num1 = sizeof(_names);
    for (int i = 0; i < num1; i++)
    {
      Serial.printf("%s\n", _names[i].c_str());
    }
  }

  const char *getName(uint8_t ev)
  {
    if (ev < _numNames)
      return _names[ev].c_str();
    return "WARNING: out of range";
  }

  T events;
  std::string *_names;
  uint8_t _numNames = 0;
};