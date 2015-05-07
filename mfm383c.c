#include <stdio.h> //Defines core input and output functions: printf(), scanf(), getchar(), puchar(), gets(), puts() etc.
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>		//Required for isprint()

#include <modbus.h>
#include "mfm383c.h"

#define MFM383C_CONFIG_BAUDRATE		19200
#define MFM383C_CONFIG_DATA_BITS	8
#define MFM383C_CONFIG_PARITY_BITS	'N'
#define MFM383C_CONFIG_STOP_BITS	1
#define MFM383C_CONFIG_PORT			"/dev/ttyUSB0"
#define MFM383C_CONFIG_SLAVE_ID		1
#define MFM383C_CONFIG_RESPONSE_TIMEOUT_S	1		//Default is 0
#define MFM383C_CONFIG_RESPONSE_TIMEOUT_US	0		//Default is 500000
#define MFM383C_CONFIG_BYTE_TIMEOUT_S		1		//Default is 0
#define MFM383C_CONFIG_BYTE_TIMEOUT_US		0		//Default is 500000

#define RETURN_SUCCESS					0
#define RETURN_FAIL_PARAM				1
#define RETURN_FAIL_MODBUS_LIB			2
#define RETURN_FAIL_MODBUS_SERIAL		3

struct timeval response_timeout = {MFM383C_CONFIG_RESPONSE_TIMEOUT_S,MFM383C_CONFIG_RESPONSE_TIMEOUT_US};
struct timeval byte_timeout = {MFM383C_CONFIG_BYTE_TIMEOUT_S,MFM383C_CONFIG_BYTE_TIMEOUT_US};

modbus_t *ctx;

void swap_uint16(uint16_t *a, uint16_t *b) {
	uint16_t swap;
	swap = *a;
	*a = *b;
	*b = swap;
}

int main(int argc, char **argv) {
	uint16_t register_set[2]={0};
	int reg_addr = 0;
	char *param_string = NULL;
	int passed_flag;
	
	while ((passed_flag = getopt(argc, argv, "p:")) != -1) {
		switch (passed_flag) {
			case 'p': {
				param_string = optarg;
			} break;
			case '?': {
				if (optopt == 'p')
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint(optopt))
					fprintf(stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
				return RETURN_FAIL_PARAM;
			} break;
			default: {
				fprintf(stderr, "Invalid command line argument.\n");
				return RETURN_FAIL_PARAM;
			} break;
		};
	}
	if(param_string == NULL) {
		fprintf(stderr, "Option -p requires an argument.\n");
		return RETURN_FAIL_PARAM;
	}
		
	ctx = modbus_new_rtu(MFM383C_CONFIG_PORT, MFM383C_CONFIG_BAUDRATE, MFM383C_CONFIG_PARITY_BITS, MFM383C_CONFIG_DATA_BITS, MFM383C_CONFIG_STOP_BITS);// Creates new Modbus RTU connection
	//modbus_set_debug(ctx, TRUE);	
	
	if (modbus_connect(ctx) == -1) {
        	fprintf(stderr, "Modbus serial connection failed: %s\n", modbus_strerror(errno));
        	modbus_free(ctx);
        	return RETURN_FAIL_MODBUS_LIB;
    } else {
		
		modbus_set_byte_timeout(ctx, &byte_timeout);
		modbus_set_response_timeout(ctx, &response_timeout);
		
		//modbus_get_byte_timeout(ctx, &byte_timeout);
		//modbus_get_response_timeout(ctx, &response_timeout);
		//printf("\nByte Timeout: %d seconds %d microseconds",byte_timeout.tv_sec, byte_timeout.tv_usec);
		//printf("\nResponse Timeout: %d seconds %d microseconds\n",response_timeout.tv_sec, response_timeout.tv_usec);
		
		if(modbus_set_slave(ctx, MFM383C_CONFIG_SLAVE_ID)==-1){
		    fprintf(stderr, "Modbus modbus_set_slave() failed: %s\n", modbus_strerror(errno));
        	modbus_free(ctx);
			return RETURN_FAIL_MODBUS_LIB;
		} else {			
			if(strcmp(param_string,"V1N") == 0) {
				reg_addr = MFM383C_REGR_V1N;
			} else if(strcmp(param_string,"V2N") == 0) {
				reg_addr = MFM383C_REGR_V2N;
			} else if(strcmp(param_string,"V3N") == 0) {
				reg_addr = MFM383C_REGR_V3N;
			} else if(strcmp(param_string,"VLN_AVG") == 0) {
				reg_addr = MFM383C_REGR_VLN_AVG;
			} else if(strcmp(param_string,"V12") == 0) {
				reg_addr = MFM383C_REGR_V12;
			} else if(strcmp(param_string,"V23") == 0) {
				reg_addr = MFM383C_REGR_V23;
			} else if(strcmp(param_string,"V31") == 0) {
				reg_addr = MFM383C_REGR_V31;
			} else if(strcmp(param_string,"VLL_AVG") == 0) {
				reg_addr = MFM383C_REGR_VLL_AVG;
			} else if(strcmp(param_string,"I1") == 0) {
				reg_addr = MFM383C_REGR_I1;
			} else if(strcmp(param_string,"I2") == 0) {
				reg_addr = MFM383C_REGR_I2;
			} else if(strcmp(param_string,"I3") == 0) {
				reg_addr = MFM383C_REGR_I3;
			} else if(strcmp(param_string,"I_AVG") == 0) {
				reg_addr = MFM383C_REGR_I_AVG;
			} else if(strcmp(param_string,"KW1") == 0) {
				reg_addr = MFM383C_REGR_KW1;
			} else if(strcmp(param_string,"KW2") == 0) {
				reg_addr = MFM383C_REGR_KW2;
			} else if(strcmp(param_string,"KW3") == 0) {
				reg_addr = MFM383C_REGR_KW3;
			} else if(strcmp(param_string,"KVA1") == 0) {
				reg_addr = MFM383C_REGR_KVA1;
			} else if(strcmp(param_string,"KVA2") == 0) {
				reg_addr = MFM383C_REGR_KVA2;
			} else if(strcmp(param_string,"KVA3") == 0) {
				reg_addr = MFM383C_REGR_KVA3;
			} else if(strcmp(param_string,"PF1") == 0) {
				reg_addr = MFM383C_REGR_PF1;
			} else if(strcmp(param_string,"PF2") == 0) {
				reg_addr = MFM383C_REGR_PF2;
			} else if(strcmp(param_string,"PF3") == 0) {
				reg_addr = MFM383C_REGR_PF3;
			} else if(strcmp(param_string,"PF_AVG") == 0) {
				reg_addr = MFM383C_REGR_PF_AVG;
			} else if(strcmp(param_string,"FREQ") == 0) {
				reg_addr = MFM383C_REGR_FREQ;
			} else if(strcmp(param_string,"KWH") == 0) {
				reg_addr = MFM383C_REGR_KWH;
			} else if(strcmp(param_string,"KVAR1") == 0) {
				reg_addr = MFM383C_REGR_KVAR1;
			} else if(strcmp(param_string,"KVAR2") == 0) {
				reg_addr = MFM383C_REGR_KVAR2;
			} else if(strcmp(param_string,"KVAR3") == 0) {
				reg_addr = MFM383C_REGR_KVAR3;
			} else if(strcmp(param_string,"KW_TOTAL") == 0) {
				reg_addr = MFM383C_REGR_KW_TOTAL;
			} else if(strcmp(param_string,"KVA_TOTAL") == 0) {
				reg_addr = MFM383C_REGR_KVA_TOTAL;
			} else if(strcmp(param_string,"KVAR_TOTAL") == 0) {
				reg_addr = MFM383C_REGR_KVAR_TOTAL;
			} else {
				fprintf(stderr, "%s is not a valid register name\n",param_string);
				return RETURN_FAIL_PARAM;
			}
			
			//Read the specified register
			if(modbus_read_input_registers(ctx, reg_addr, 2, register_set)==-1){
				fprintf(stderr, "Slave Read failed: %s\n", modbus_strerror(errno));
				modbus_free(ctx);
				return RETURN_FAIL_MODBUS_SERIAL;        
			} else {
				swap_uint16(&register_set[0],&register_set[1]);
				fprintf(stdout,"%f\n", *((float*)&register_set[0]));
				modbus_free(ctx);
				return RETURN_SUCCESS;
			}
			
			modbus_free(ctx);
			return RETURN_FAIL_MODBUS_SERIAL;  
		}   	
	}
}