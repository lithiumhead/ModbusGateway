#ifndef _MFM384C_H_
#define _MFM384C_H_

#include <inttypes.h>

//Each Modbus Register is 16 bits in length

//Writeable Parameters (4xxxxx)	//Register Address Offset		//	Min Value	Max Value	Length		Data Structure
#define MFM384C_REGW_CT_PRIMARY	(1)								//	5			5000		1			Integer
#define MFM384C_REGW_RESET_KWH	(2)								//	0			1 			1			Integer

//Readable Parameters (3xxxxx)	//Register Address Offset		//	Min Value	Max Value	Length		Data Structure
#define MFM384C_REGR_V1N		(0)								//	0			350.0		2			Float
#define MFM384C_REGR_V2N		(2)								//	0			350.0		2			Float
#define MFM384C_REGR_V3N		(4)								//	0			350.0		2			Float
#define MFM384C_REGR_VLN_AVG	(6)								//	0			350.0		2			Float
#define MFM384C_REGR_V12		(8)								//	0			607.0		2			Float
#define MFM384C_REGR_V23		(10)							//	0			607.0		2			Float
#define MFM384C_REGR_V31		(12)							//	0			607.0		2			Float
#define MFM384C_REGR_VLL_AVG	(14)							//	0			607.0		2			Float
#define MFM384C_REGR_I1			(16)							//	0			5000.0		2			Float
#define MFM384C_REGR_I2			(18)							//	0			5000.0		2			Float
#define MFM384C_REGR_I3			(20)							//	0			5000.0		2			Float
#define MFM384C_REGR_I_AVG		(22)							//	0			5000.0		2			Float
#define MFM384C_REGR_KW1		(24)							//	-1750.00	1750.00		2			Float
#define MFM384C_REGR_KW2		(26)							//	-1750.00	1750.00		2			Float
#define MFM384C_REGR_KW3		(28)							//	-1750.00	1750.00		2			Float
#define MFM384C_REGR_KVA1		(30)							//	0			1750.00		2			Float
#define MFM384C_REGR_KVA2		(32)							//	0			1750.00		2			Float
#define MFM384C_REGR_KVA3		(34)							//	0			1750.00		2			Float
#define MFM384C_REGR_KVAR1		(36)							//	-1750.00	1750.00		2			Float
#define MFM384C_REGR_KVAR2		(38)							//	-1750.00	1750.00		2			Float
#define MFM384C_REGR_KVAR3		(40)							//	-1750.00	1750.00		2			Float
#define MFM384C_REGR_KW_TOTAL	(42)							//	-5250.00	5250.00		2			Float
#define MFM384C_REGR_KVA_TOTAL	(44)							//	0			5250.00		2			Float
#define MFM384C_REGR_KVAR_TOTAL	(46)							//	-5250.00	5250.00		2			Float
#define MFM384C_REGR_PF1		(48)							//	-0.99		1.00		2			Float
#define MFM384C_REGR_PF2		(50)							//	-0.99		1.00		2			Float
#define MFM384C_REGR_PF3		(52)							//	-0.99		1.00		2			Float
#define MFM384C_REGR_PF_AVG		(54)							//	-0.99		1.00		2			Float
#define MFM384C_REGR_FREQ		(56)							//	0			65.0		2			Float
#define MFM384C_REGR_KWH		(58)							//	0			99999999.9	2			Float
#define MFM384C_REGR_KVAH		(60)							//	0			99999999.9	2			Float
#define MFM384C_REGR_KVARH		(62)							//	0			99999999.9	2			Float

#endif //_MFM384C_H_