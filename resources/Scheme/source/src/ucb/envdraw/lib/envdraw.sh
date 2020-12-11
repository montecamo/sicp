#!/bin/sh
# EnvDraw STk launcher

INSTHOME=/home/jmacd
STK_LIBRARY=$INSTHOME/lib/stk/3.1.1/
ENVDRAW_LIBRARY_PATH=$INSTHOME/work/envdraw/
STK_LOAD_PATH=$STK_LIBRARY/bin:$ENVDRAW_LIBRARY_PATH/lib/
SCHEME_LIBRARY_PATH=/usr/local/lib/slib/
export STK_LIBRARY
export STK_LOAD_PATH
export SCHEME_LIBRARY_PATH
export ENVDRAW_LIBRARY_PATH

if [ "$DISPLAY" = "" ] ;then
  echo You must run STk while running X.
  exit 1
else
  exec $INSTHOME/bin/stk -name stk -l stk-init $*
fi
