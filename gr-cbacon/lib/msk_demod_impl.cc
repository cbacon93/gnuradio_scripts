/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "msk_demod_impl.h"

namespace gr {
  namespace cbacon {

    msk_demod::sptr
    msk_demod::make(float samp_rate, float baud_rate)
    {
      return gnuradio::get_initial_sptr
        (new msk_demod_impl(samp_rate, baud_rate));
    }

    /*
     * The private constructor
     */
    msk_demod_impl::msk_demod_impl(float _samp_rate, float _baud_rate)
      : gr::block("msk_demod",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
        last_zero = 0;
        last_value = 0;
        mean = 0;
        meansq = 0;
        accumulation = 0;
        time = 0;

        baud_rate = _baud_rate;
        samp_rate = _samp_rate;
    }

    /*
     * Our virtual destructor.
     */
    msk_demod_impl::~msk_demod_impl()
    {
    }

    void
    msk_demod_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    int
    msk_demod_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        unsigned char *out = (unsigned char *) output_items[0];
        unsigned int oc = 0;
        
        for (int i = 0; i < noutput_items; i++) {
            //calculate means
            time++;
            mean = mean*0.999 + in[i]*0.001;
            meansq = meansq*0.999 + in[i]*in[i]*0.001;
            
            //squelch
            //if (meansq < 0.1) { last_value = in[i]; continue; }
            
            //wave goes through zero
            if ((last_value <= mean && in[i] > mean) || (last_value >= mean && in[i] < mean)) {
                if (time-last_zero < (samp_rate/baud_rate)*0.70f) { accumulation = 0; last_value = in[i]; continue; }

                //std::cout << time - last_zero << " - " << meansq << std::endl;

                //get time
                last_zero = time;
                
                //wave goes through zero - decide
                if (accumulation > 0) {
                    out[oc++] = 0;
                } else {
                    out[oc++] = 1;
                }
                accumulation = 0;
            }
            
            //count last half of wave
            if (time-last_zero > (samp_rate/baud_rate)/2.0) {
                accumulation += in[i] - mean;
            }
            
            //save last value
            last_value = in[i];
        }
        
        
        

      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      //return noutput_items;
      return oc;
    }

  } /* namespace cbacon */
} /* namespace gr */

