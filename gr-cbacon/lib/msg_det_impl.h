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

#ifndef INCLUDED_CBACON_MSG_DET_IMPL_H
#define INCLUDED_CBACON_MSG_DET_IMPL_H

#include <cbacon/msg_det.h>

namespace gr {
  namespace cbacon {

    class msg_det_impl : public msg_det
    {
     private:
      // Nothing to declare in this block.
        uint16_t shreg;
        unsigned long msg_counter;
        unsigned long max_msg_len;
        
        bool is_message;
        bool invert_bit;
        
        uint16_t start_byte;
        uint16_t end_byte;
        uint16_t start_bit_mask;
        uint16_t end_bit_mask;

        bool parity_check(uint8_t byte);
        bool bytes_match(uint16_t byte1, uint16_t byte2, unsigned int tolerance);
        void write_out(std::string msg, unsigned char * out, unsigned long & oc); 
    public:
      msg_det_impl(std::string startbit, std::string endbit, int max_length);
      ~msg_det_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace cbacon
} // namespace gr

#endif /* INCLUDED_CBACON_MSG_DET_IMPL_H */

