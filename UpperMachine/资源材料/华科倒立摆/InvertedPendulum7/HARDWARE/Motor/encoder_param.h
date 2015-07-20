#ifndef _encoder_param_h
#define _encoder_param_h

//RE25 线数 100 减速比18
//MAXON 线数25  减速比333

#define MAXON1_CPR     			100
#define MAXON1_RATIO 			(float)185193/2197    //84//(185193/2197) GP22A 22mm
// #define MAXON1_SPEED_MAX		1250//125RPM
// #define MAXON1_SPEED_MIN		-1250

#define MAXON2_CPR   				100
#define MAXON2_RATIO			(float)192375/832 	231//(192375/832)GP22L 22MM
// #define MAXON2_SPEED_MAX    460//46RPM
// #define MAXON2_SPEED_MIN		-460//

#define MAXON_RE25_CPR			100
#define MAXON_RE25_RATIO		(float)624/35



#ifdef MAXON1

#endif

#ifdef MAXON2
#endif

#ifdef SANMEI
#endif

#define PI 3.1425926
#endif
