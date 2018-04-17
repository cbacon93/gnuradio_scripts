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


#ifndef INCLUDED_CBACON_MSK_DEMOD_H
#define INCLUDED_CBACON_MSK_DEMOD_H

#include <cbacon/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace cbacon {

    /*!
     * \brief <+description of block+>
     * \ingroup cbacon
     *
     */
    class CBACON_API msk_demod : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<msk_demod> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of cbacon::msk_demod.
       *
       * To avoid accidental use of raw pointers, cbacon::msk_demod's
       * constructor is in a private implementation
       * class. cbacon::msk_demod::make is the public interface for
       * creating new instances.
       */
      static sptr make(float samp_rate=100000, float baud_rate = 2400);
    };

  } // namespace cbacon
} // namespace gr

#endif /* INCLUDED_CBACON_MSK_DEMOD_H */

