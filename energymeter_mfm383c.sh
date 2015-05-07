#!/bin/bash

# compilation command
# gcc -I /usr/include/modbus mfm383c.c -lmodbus -o mfm383c.out

# Xively Configuration:
API_KEY="c631a5562a9dc0e28c8894c9c7f16f7ca69e5f74dba268aa1b35dcc622a332c5"
FEED_ID="583418838"

register_names=( "KWH" "V1N" "V2N" "V3N" "I1" "I2" "I3" "FREQ" "KW_TOTAL" "KVA_TOTAL" )
array_len=${#register_names[@]}

logger 'Reading Registers from Selec MFM383C over RS485/Modbus'
echo 'Reading Registers from Selec MFM383C over RS485/Modbus'
echo 'Baud 19200 | Data bits 8 | Parity bits N | Stop bits 1 | Port /dev/ttyUSB0'
echo 'Slave ID 1 | Response timeone 1 second | Byte timeout 1 second'
echo '--------------------------------------------------------------------------'
echo ''

DATA_JSON="{"
DATA_JSON="$DATA_JSON"$'\n'"  \"version\":\"1.0.0\","
DATA_JSON="$DATA_JSON"$'\n'"   \"datastreams\" : ["

for (( i=0; i<${array_len}; i++ ));
do
	# Send two Ping request packets and 4 seconds timeout
	register_value=$(/home/pi/mfm383c/mfm383c.out -p ${register_names[$i]})
	return_value=$?
	case $return_value in
		0)  #Register read successfully
			logger "Selec MFM383C register read successfully ${register_names[$i]} = $register_value"
			DATA_JSON="$DATA_JSON"$'\n'"     { \"id\" : \"${register_names[$i]}\","
			DATA_JSON="$DATA_JSON"$'\n'"      \"current_value\" : \"$register_value\""
			if [ $((i)) = $((array_len-1)) ]; then
				DATA_JSON="$DATA_JSON"$'\n'"    }"
			else
				DATA_JSON="$DATA_JSON"$'\n'"    },"
			fi
			;;
		1)  #Reading register failed: Incorrect command line parameters
			logger "Selec MFM383C register read error: Incorrect command line parameters"
			;;
		2)  #Reading register failed: Modbus library error
			logger "Selec MFM383C register read error: Modbus library error"
			;;
		3)  #Reading register failed: Modbus serial error
			logger "Selec MFM383C register read error: Modbus serial error"
			;;
		*)  #Reading register failed
			logger "Selec MFM383C register read error"
			;;
	esac
done

DATA_JSON="$DATA_JSON"$'\n'"  ]"
DATA_JSON="$DATA_JSON"$'\n'"}"

echo $DATA_JSON

curl --max-time 5 \
--request PUT \
--data "$DATA_JSON" \
--header "X-ApiKey: $API_KEY" \
--verbose \
http://api.xively.com/v2/feeds/"$FEED_ID"
