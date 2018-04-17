#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/Users/marcel/Documents/Coding/gnuradio/gr-cbacon/lib
export PATH=/Users/marcel/Documents/Coding/gnuradio/gr-cbacon/build/lib:$PATH
export DYLD_LIBRARY_PATH=/Users/marcel/Documents/Coding/gnuradio/gr-cbacon/build/lib:$DYLD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-cbacon 
