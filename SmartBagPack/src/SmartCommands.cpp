#include "SmartCommands.h"

void SmartCommands::begin() {
  funcs = new GenericFunction[1];
  funcsFlag = new GenericFunctionFlag[1];
	funcsCustom = new GenericFunctionCustom[1];
  commands = new String[1];
  commandsFlag = new String[1];
	commandsCustom = new String[1];
}

void SmartCommands::addCommandWithCustom(String command, void (&f)(String a)) {
  if (nOfFuncsCustom > 0) {
    GenericFunction * bpFunctions = funcsCustom;
    String * bpCommands = commandsCustom;

    funcsCustom = new GenericFunction[nOfFuncsCustom + 1];
    commandsCustom = new String[nOfFuncsCustom + 1];

    for (int i = 0; i < nOfFuncsCustom; i++) {
      funcsCustom[i] = bpFunctions[i];
      commandsCustom[i] = bpCommands[i];
    }
  }

  funcsCustom[nOfFuncsCustom] = f;
  commandsCustom[nOfFuncsCustom] = command;

  nOfFuncsCustom++;
}

void SmartCommands::addCommandWithFlag(String command, void (&f)(bool a)) {
  if (nOfFuncsFlag > 0) {
    GenericFunctionFlag * bpFunctions = funcsFlag;
    String * bpCommands = commandsFlag;

    funcsFlag = new GenericFunctionFlag[nOfFuncsFlag + 1];
    commandsFlag = new String[nOfFuncsFlag + 1];

    for (int i = 0; i < nOfFuncsFlag; i++) {
      funcsFlag[i] = bpFunctions[i];
      commandsFlag[i] = bpCommands[i];
    }
  }

  funcsFlag[nOfFuncsFlag] = f;
  commandsFlag[nOfFuncsFlag] = command;

  nOfFuncsFlag++;
}

void SmartCommands::addCommand(String command, void (&f)(void)) {
  if (nOfFuncs > 0) {
    GenericFunction * bpFunctions = funcs;
    String * bpCommands = commands;

    funcs = new GenericFunction[nOfFuncs + 1];
    commands = new String[nOfFuncs + 1];

    for (int i = 0; i < nOfFuncs; i++) {
      funcs[i] = bpFunctions[i];
      commands[i] = bpCommands[i];
    }
  }

  funcs[nOfFuncs] = f;
  commands[nOfFuncs] = command;

  nOfFuncs++;
}

void SmartCommands::verify(String data) {
  for (int i = 0; i < nOfFuncs; i++) {
    if (data.equals(commands[i])) {
      GenericFunction f = funcs[i];
      f();
    }
  }

  for (int i = 0; i < nOfFuncsFlag; i++) {
    if (data.substring(0, data.length() - 1).equals(commandsFlag[i])) {
      GenericFunctionFlag f = funcsFlag[i];

      if (data[data.length() - 1] == '1') {
        f(true);
      } else {
        f(false);
      }
    }
  }

	for (int i = 0; i < nOfFuncsCustom; i++) {
		int index = data.indexOf(commandsCustom[i]);
    if (index != -1) {
      GenericFunctionCustom f = funcsCustom[i];

			f(data.substring(commandsCustom[i].length(), data.length()));
    }
  }
}

int SmartCommands::getNumberOfFunctions() {
  return nOfFuncs + nOfFuncsFlag + nOfFuncsCustom;
}
