/* -*- c++ -*- */

#define CBACON_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "cbacon_swig_doc.i"

%{
#include "cbacon/msk_demod.h"
#include "cbacon/msg_det.h"
%}


%include "cbacon/msk_demod.h"
GR_SWIG_BLOCK_MAGIC2(cbacon, msk_demod);
%include "cbacon/msg_det.h"
GR_SWIG_BLOCK_MAGIC2(cbacon, msg_det);
