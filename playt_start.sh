#!/bin/bash

CONFIGURATION_SHELL_NAME=$(pwd)"/configuration_info.sh"

if [ ! -f $CONFIGURATION_SHELL_NAME ]; then
    printf "Cannot find %s\n" $CONFIGURATION_SHELL_NAME
    exit 1;
fi

. $CONFIGURATION_SHELL_NAME

printf "Starting Playtd daemon...\n"

#nohup $COIN_BIN_DIR/playtd -debug &
#daemon
#$COIN_BIN_DIR/playtd -debug
#app
$COIN_BIN_DIR/qt/playt-qt -debug

#COIN_PID=$!
#echo $COIN_PID > $COIN_DATA_DIR/playtdse.pid

#printf "  * Process ID : \t%s\n" $COIN_PID
printf "  * Path to Bin : \t%s\n" $COIN_BIN_DIR
printf "  * Path to Config : \t%s\n" $COIN_DATA_DIR
printf "  * Path to Data : \t%s\n" $COIN_DATA_DIR

printf "\nSuccessfully Started.\n"
