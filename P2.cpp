#include "P2.h"

void P2::PR_init(std::stringstream& ss, int seed, int num_equities, int num_clients, int num_orders, int arrival_rate) 
{
  P2::MersenneTwister mt;
  int max_price = 100, max_quantity = 50;
  mt.init_genrand(seed);
  long double timestamp = 0;
  unsigned long equity_num, client_num;
  for(int i = 0; i < num_orders; ++i) {
    unsigned long time_increase = (mt.genrand_int32() % arrival_rate + 1);
    timestamp += (1.0l / time_increase);
    equity_num = mt.genrand_int32() % num_equities;
    client_num = mt.genrand_int32() % num_clients;
    std::string buy_or_sell = mt.genrand_int32() % 2 ? "BUY" : "SELL";
    ss << int(timestamp) << " C" << client_num << ' ' << buy_or_sell << " E" << equity_num;
    ss << " $" << mt.genrand_int32() % max_price + 1 << " #" << mt.genrand_int32() % max_quantity + 1 << '\n';
  }
}


/**
 * C++ Mersenne Twister wrapper class written by
 * Jason R. Blevins <jrblevin@sdf.lonestar.org> on July 24, 2006.
 * Based on the original MT19937 C code by
 * Takuji Nishimura and Makoto Matsumoto.
 */

/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

/**
 * Constructor
 */
P2::MersenneTwister::MersenneTwister(void):
    mt_(new unsigned long[N]), mti_(N+1),
    init_key_(NULL), key_length_(0), s_(0),
    seeded_by_array_(false), seeded_by_int_(false)
{
    init_genrand(0);
}

/**
 * Destructor
 */
P2::MersenneTwister::~MersenneTwister(void)
{
    assert(mt_ != NULL);
    delete[] mt_;
    mt_ = NULL;
}

/**
 * Initializes the Mersenne Twister with a seed.
 *
 * \param s seed
 */
void P2::MersenneTwister::init_genrand(unsigned long s)
{
    mt_[0]= s & 0xffffffffUL;
    for (mti_=1; mti_<N; mti_++) {
        mt_[mti_] = 
      (1812433253UL * (mt_[mti_-1] ^ (mt_[mti_-1] >> 30)) + mti_); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt_[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt_[mti_] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
    // Store the seed
    s_ = s;
    seeded_by_array_ = false;
    seeded_by_int_ = true;
}

/**
 * Generates a random number on [0,0xffffffff]-interval
 *
 * \return random number on [0, 0xffffffff]
 */
unsigned long P2::MersenneTwister::genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti_ >= N) { /* generate N words at one time */
        int kk;

        if (mti_ == N+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt_[kk]&UPPER_MASK)|(mt_[kk+1]&LOWER_MASK);
            mt_[kk] = mt_[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt_[kk]&UPPER_MASK)|(mt_[kk+1]&LOWER_MASK);
            mt_[kk] = mt_[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt_[N-1]&UPPER_MASK)|(mt_[0]&LOWER_MASK);
        mt_[N-1] = mt_[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti_ = 0;
    }
  
    y = mt_[mti_++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}