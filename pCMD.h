#ifndef PCMD_H_
#define PCMD_H_

#include "irrlichtFWD.h"

/*FUNC: reads in arguments from commandline and applies them to the createdevice parameter structure.
  PARAM: count and value array of arguments.
  NOTE: commandline args should overwrite previously saved args.*/
irr::SIrrlichtCreationParameters processCMDArgs(int argCount, char* argValue[]);

#endif /* PCMD_H_ */
