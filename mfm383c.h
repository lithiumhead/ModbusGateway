#ifndef _MFM383C_H_
#define _MFM383C_H_

#include <inttypes.h>

//Each Modbus Register is 16 bits in length

//Writeable Parameters (4xxxxx)	//Register Address Offset		//	Min Value	Max Value	Length		Data Structure
#define MFM383C_REGW_CT_PRIMARY	(1)								//	5			5000		1			Integer
#define MFM383C_REGW_RESET_KWH	(2)								//	0			1 			1			Integer

//Readable Parameters (3xxxxx)	//Register Address Offset		//	Min Value	Max Value	Length		Data Structure
#define MFM383C_REGR_V1N		(1)								//	0			350.0		2			Float
#define MFM383C_REGR_V2N		(3)								//	0			350.0		2			Float
#define MFM383C_REGR_V3N		(5)								//	0			350.0		2			Float
#define MFM383C_REGR_VLN_AVG	(7)								//	0			350.0		2			Float
#define MFM383C_REGR_V12		(9)								//	0			607.0		2			Float
#define MFM383C_REGR_V23		(11)							//	0			607.0		2			Float
#define MFM383C_REGR_V31		(13)							//	0			607.0		2			Float
#define MFM383C_REGR_VLL_AVG	(15)							//	0			607.0		2			Float
#define MFM383C_REGR_I1			(17)							//	0			5000.0		2			Float
#define MFM383C_REGR_I2			(19)							//	0			5000.0		2			Float
#define MFM383C_REGR_I3			(21)							//	0			5000.0		2			Float
#define MFM383C_REGR_I_AVG		(23)							//	0			5000.0		2			Float
#define MFM383C_REGR_KW1		(25)							//	-1750.00	1750.00		2			Float
#define MFM383C_REGR_KW2		(27)							//	-1750.00	1750.00		2			Float
#define MFM383C_REGR_KW3		(29)							//	-1750.00	1750.00		2			Float
#define MFM383C_REGR_KVA1		(31)							//	0			1750.00		2			Float
#define MFM383C_REGR_KVA2		(33)							//	0			1750.00		2			Float
#define MFM383C_REGR_KVA3		(35)							//	0			1750.00		2			Float
#define MFM383C_REGR_PF1		(37)							//	-0.99		1.00		2			Float
#define MFM383C_REGR_PF2		(39)							//	-0.99		1.00		2			Float
#define MFM383C_REGR_PF3		(41)							//	-0.99		1.00		2			Float
#define MFM383C_REGR_PF_AVG		(43)							//	-0.99		1.00		2			Float
#define MFM383C_REGR_FREQ		(45)							//	0			65.0		2			Float
#define MFM383C_REGR_KWH		(47)							//	0			99999999.9	2			Float
#define MFM383C_REGR_KVAR1		(49)							//	-1750.00	1750.00		2			Float
#define MFM383C_REGR_KVAR2		(51)							//	-1750.00	1750.00		2			Float
#define MFM383C_REGR_KVAR3		(53)							//	-1750.00	1750.00		2			Float
#define MFM383C_REGR_KW_TOTAL	(55)							//	-5250.00	5250.00		2			Float
#define MFM383C_REGR_KVA_TOTAL	(57)							//	0			5250.00		2			Float
#define MFM383C_REGR_KVAR_TOTAL	(59)							//	-5250.00	5250.00		2			Float
#define MFM383C_REGR_STATUS		(61)							//	X			X			1			Integer

//Status Bits
#define MFM383C_STATUS_PHASE1_CT_REV 0x0001
#define MFM383C_STATUS_PHASE2_CT_REV 0x0002
#define MFM383C_STATUS_PHASE3_CT_REV 0x0004

#endif //_MFM383C_H_