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


#ifndef INCLUDED_CBACON_MSG_DET_H
#define INCLUDED_CBACON_MSG_DET_H

#include <cbacon/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace cbacon {

    /*!
     * \brief <+description of block+>
     * \ingroup cbacon
     *
     */
    class CBACON_API msg_det : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<msg_det> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of cbacon::msg_det.
       *
       * To avoid accidental use of raw pointers, cbacon::msg_det's
       * constructor is in a private implementation
       * class. cbacon::msg_det::make is the public interface for
       * creating new instances.
       */
      static sptr make(std::string startbit, std::string endbit, int max_length);
    };

  } // namespace cbacon
} // namespace gr

#endif /* INCLUDED_CBACON_MSG_DET_H */

