/**
 * @file       <pseudo_random.hpp>
 * @brief      This source file holds implementation of PseudoRandomGenerator class. 
 * 
 *             This calss implements search algorithms needed for successfull completion of laboratory work 4.
 *
 * @author     Alexander Chudnikov (THE_CHOODICK)
 * @date       15-02-2023
 * @version    0.0.1
 * 
 * @warning    This library is under development, so there might be some bugs in it.  
 * @bug        Currently, there are no any known bugs. 
 * 
 *             In order to submit new ones, please contact me via admin@redline-software.xyz.
 * 
 * @copyright  Copyright 2023 Alexander. All rights reserved. 
 * 
 *             (Not really)
 */
#include "pseudo_random.hpp"


/**
 * First implementation of PRNG is based on Irwin-Hall distribution 
 * 
 *  f_{x}(x;n) = \frac{2}{2(n - 1)!}\sum^{n}_{k = 0} (-1)^k \binom{n}{k} sign (x- k)(x - k)^{n - 1}

 * Second PRNG id garbage, it's just XOR one
 */
