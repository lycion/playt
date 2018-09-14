#!/bin/bash
CONFIGURATION_SHELL_NAME=$(pwd)"/configuration_info.sh"

if [ ! -f $CONFIGURATION_SHELL_NAME ]; then
    printf "Cannot find %s\n" $CONFIGURATION_SHELL_NAME
    exit 1;
fi

. $CONFIGURATION_SHELL_NAME

COIN_PID_DIR=$COIN_DATA_DIR

if [ -f $COIN_PID_DIR"/playtd.pid" ]; then
    playtd_pid=`cat $COIN_PID_DIR"/playtd.pid"`
    printf "Found playtd pid: %s\n" $playtd_pid
    printf "Stopping playtd"
    kill -9 $playtd_pid
#    rm -r $COIN_PID_DIR"/playtd.pid"

#    while true; do
#        [ ! -d "/proc/$playtd_pid/fd" ] && break
#	printf "."
#	sleep .5
#   done

    printf "\nPlaytd Stopped.\n"
else
    printf "Cannot find playtd\n"
fi

