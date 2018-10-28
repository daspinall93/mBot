/*
 * ImuMei_constantDefs.h
 *
 *  Created on: 29 Jul 2018
 *      Author: dan
 */

#ifndef SRC_FUNCTIONS_IMUMEI_IMUMEI_CONSTANTDEFS_H_
#define MBOTSOURCE_FUNCTIONS_IMUMEI_IMUMEI_CONSTANTDEFS_H_

/* Values taken from MPU6000 register map and are dependant on
 * the range used (i.e 2g vs 16g) and register(s) are 16 bits
 * 2's complement values (i.e -32768 to 32768)
 */

#define LSBPERG 16384.0
#define LSBPERDEGS 131.0 // range = 250 deg/s/LSB



#endif /* SRC_FUNCTIONS_IMUMEI_IMUMEI_CONSTANTDEFS_H_ */
