#ifndef SmartCommands_h
#define SmartCommands_h

#include "Arduino.h"

class SmartCommands {
  public:
    void begin();
    void addCommand(String command, void (&f)(void));
		void addCommandWithFlag(String command, void (&f)(bool a));
		void addCommandWithCustom(String command, void (&f)(String a));
    void verify(String data);
		int SmartCommands::getNumberOfFunctions();
  private:
    typedef void (* GenericFunction)();
		typedef void (* GenericFunctionFlag)(bool a);
		typedef void (* GenericFunctionCustom)(String a);
    GenericFunction * funcs;
		GenericFunctionFlag * funcsFlag;
		GenericFunctionCustom * funcsCustom;
    String * commands;
		String * commandsFlag;
		String * commandsCustom;
    int nOfFuncs = 0;
		int nOfFuncsFlag = 0;
		int nOfFuncsCustom = 0;
};

#endif
