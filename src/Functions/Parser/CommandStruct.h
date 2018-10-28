/*
 * CommandStruct.h
 *
 *  Created on: 28 Oct 2018
 *      Author: daniel
 */

#ifndef COMMANDSTRUCT_H_
#define COMMANDSTRUCT_H_

typedef void(*functionPointerType)(void);
struct commandStruct {
    char const *name;
    functionPointerType execute;
    char const *help;
};



#endif /* COMMANDSTRUCT_H_ */
