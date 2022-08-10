//Contains the definitions that need to be evaluated before the main config file (lucidgloves-firmware.ino).
//These shouldn't need to be changed.

//Comm
#define COMM_SERIAL 0   
#define COMM_BTSERIAL 1 

//Encode
#define ENCODE_LEGACY 0
#define ENCODE_ALPHA  1

//Multiplexer
#define MUX(p) (p + 100)
#define UNMUX(p) (p % 100)
#define ISMUX(p) (p >= 100)
