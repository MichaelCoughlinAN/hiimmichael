#!/bin/sh
SCRIPTPATH=`dirname $0`
find "$1" -iname "*.js" -exec $SCRIPTPATH/replace-file.sh {} \;
find "$1" -iname "*.js.map" -exec $SCRIPTPATH/replace-file.sh {} \;
