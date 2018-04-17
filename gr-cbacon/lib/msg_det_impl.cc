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
#include "msg_det_impl.h"

namespace gr {
  namespace cbacon {

    msg_det::sptr
    msg_det::make(std::string startbit, std::string endbit, int max_length)
    {
      return gnuradio::get_initial_sptr
        (new msg_det_impl(startbit, endbit, max_length));
    }

    /*
     * The private constructor
     */
    msg_det_impl::msg_det_impl(std::string startbit, std::string endbit, int max_length)
      : gr::block("Message Detection",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
        shreg = 0;
        msg_counter = 0;
        max_msg_len = max_length;
        invert_bit = false;
        is_message = false;
       
        //set start_byte
        start_byte = 0;
        start_bit_mask = 0;
        for(int i=0; i < startbit.length(); i++) {
            start_bit_mask >>= 1;
            start_bit_mask |= (1 << (16-1));
            start_byte <<= 1;
            if (startbit[i] == '0') {
                start_byte |= 0b0;
            } else {
                start_byte |= 0b1;
            }
        }
        start_byte <<= 16-startbit.length();

        //set end_byte
        end_byte = 0;
        end_bit_mask = 0;
        for(int i=0; i < endbit.length(); i++) {
            end_bit_mask >>= 1;
            end_bit_mask |= (1 << (16-1));
            end_byte <<= 1;
            if (endbit[i] == '0') {
                end_byte |= 0b0;
            } else {
                end_byte |= 0b1;
            }
        }
        end_byte <<= 16-endbit.length();

        //start_byte = 0b0010110000101100;
        //end_byte = 0b11111110;
    }

    /*
     * Our virtual destructor.
     */
    msg_det_impl::~msg_det_impl()
    {
    }

    void
    msg_det_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }


    bool msg_det_impl::parity_check(uint8_t byte) {
       uint8_t parity = (byte >> 7) & 0b1;
       uint8_t sum = 0;

       for(int i=0; i < 7; i++) {
            sum += (byte >> (i)) & 0b1;
       }

       return (sum%2) != parity;
    }

    bool msg_det_impl::bytes_match(uint16_t byte1, uint16_t byte2, unsigned int tolerance) {
        unsigned int errors = 0;
        for (int i = 0; i < 16; i++) {
            if (((byte1 >> i) & 0b1) != ((byte2 >> i) & 0b1)) {
                errors++;
            }
        }
        return (errors <= tolerance);
    }


    void msg_det_impl::write_out(std::string msg, unsigned char * out, unsigned long & oc) {
        for (int i = 0; i < msg.length(); i++) {
            out[oc++] = msg[i];
        }
    }


    int
    msg_det_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];
      unsigned long oc = 0;
      static unsigned long byte_errors = 0;

      for (int i=0; i < noutput_items; i++) {
        //but bit into shift register
        //LSB
        shreg >>= 1;
        if (invert_bit) {
            shreg |= ((in[i] & 0b1) ^1) << (16-1);
        } else {
            shreg |= (in[i] & 0b1) << (16-1);
        }

        //count bits if this is a message
        if (is_message) {
            msg_counter++;
        }
       
        //start byte is in shift register
        if (!is_message && bytes_match((shreg & start_bit_mask), start_byte, 1)) {
          is_message = true;  
        }
        else if (!is_message && bytes_match((shreg^0xFFFF) & start_bit_mask, start_byte, 1)) {
          is_message = true;
          invert_bit = true;
        }

        //if it is a message - true only if bit is complete in shift register
        if (is_message && (msg_counter % 8) == 0) { 

            //end bit is in shift register
            if ((shreg & end_bit_mask) == end_byte || msg_counter > max_msg_len*8 || byte_errors >= 5) {
                is_message = false;
                msg_counter = 0;
                byte_errors = 0;
            }


            //parity check failed
            if (!parity_check((uint8_t)(shreg >> 8))) {
                out[oc++] = '?';
                byte_errors++;
                continue; // no transmission of original symbol
            } else {
                byte_errors = 0;
            }


            //special characters
            switch((shreg >> 8) & 0x7F) {
                case 0b0000000:
                   write_out("<NUL>", out, oc);
                   break;
                case 0b0000001:
                    write_out("<SOH>", out, oc);
                    break;
                case 0b0000010:
                    write_out("<STX>", out, oc);
                    break;
                case 0b0000011:
                    write_out("<ETX>", out, oc);
                    break;
                case 0b0000100:
                    write_out("<EOT>", out, oc);
                    break;
                case 0b0000101:
                    write_out("<ENQ>", out, oc);
                    break;
                case 0b0000110:
                    write_out("<ACK>", out, oc);
                    break;
                case 0b0000111:
                    write_out("<BEL>", out, oc);
                    break;
                case 0b0001000:
                    write_out("<BS>", out, oc);
                    break;
                case 0b0001001:
                    write_out("\t", out, oc);
                    break;
                case 0b0001010:
                    write_out("\n", out, oc);
                    break;
                case 0b0001011:
                    write_out("<VT>", out, oc);
                    break;
                case 0b0001100:
                    write_out("<FF>", out, oc);
                    break;
                case 0b0001101:
                    write_out("<CR>", out, oc);
                    break;
                case 0b0001110:
                    write_out("<SO>", out, oc);
                    break;
                case 0b0001111:
                    write_out("<SI>", out, oc);
                    break;
                case 0b0010000:
                    write_out("<DLE>", out, oc);
                    break;
                case 0b0010001:
                    write_out("<DC1>", out, oc);
                    break;
                case 0b0010010:
                    write_out("<DC2>", out, oc);
                    break;
                case 0b0010011:
                    write_out("<DC3>", out, oc);
                    break;
                case 0b0010100:
                    write_out("<DC4>", out, oc);
                    break;
                case 0b0010101:
                    write_out("<NAK>", out, oc);
                    break;
                case 0b0010110:
                    write_out("<SYN>", out, oc);
                    break;
                case 0b0010111:
                    write_out("<ETB>", out, oc);
                    break;
                case 0b0011000:
                    write_out("<CAN>", out, oc);
                    break;
                case 0b0011001:
                    write_out("<EM>", out, oc);
                    break;
                case 0b0011010:
                    write_out("<SUB>", out, oc);
                    break;
                case 0b0011011:
                    write_out("<ESC>", out, oc);
                    break;
                case 0b0011100:
                    write_out("<FS>", out, oc);
                    break;
                case 0b0011101:
                    write_out("<GS>", out, oc);
                    break;
                case 0b0011110:
                    write_out("<RS>", out, oc);
                    break;
                case 0b0011111:
                    write_out("<US>", out, oc);
                    break;
                case 0b1111111:
                    write_out("<DEL>", out, oc);
                    break;
                default:
                    //push byte into shift register
                    out[oc++] = ((unsigned char) (shreg >> 8) & 0x7F );
                    break;
            }

            //msg delimiter
            if (!is_message) write_out("\n\n", out, oc);
        }

      }

      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return oc;
    }

  } /* namespace cbacon */
} /* namespace gr */

