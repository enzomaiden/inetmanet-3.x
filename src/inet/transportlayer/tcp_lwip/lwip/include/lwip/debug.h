/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#ifndef __LWIP_DEBUG_H__
#define __LWIP_DEBUG_H__

#include "lwip/arch.h"

namespace inet {

namespace tcp {

/** lower two bits indicate debug level
 * - 0 all
 * - 1 warning
 * - 2 serious
 * - 3 severe
 */
#define LWIP_DBG_LEVEL_ALL     0x00
#define LWIP_DBG_LEVEL_OFF     LWIP_DBG_LEVEL_ALL /* compatibility define only */
#define LWIP_DBG_LEVEL_WARNING 0x01 /* bad checksums, dropped packets, ... */
#define LWIP_DBG_LEVEL_SERIOUS 0x02 /* memory allocation failures, ... */
#define LWIP_DBG_LEVEL_SEVERE  0x03
#define LWIP_DBG_MASK_LEVEL    0x03

/** flag for LWIP_DEBUGF to enable that debug message */
#define LWIP_DBG_ON            0x80U
/** flag for LWIP_DEBUGF to disable that debug message */
#define LWIP_DBG_OFF           0x00U

/** flag for LWIP_DEBUGF indicating a tracing message (to follow program flow) */
#define LWIP_DBG_TRACE         0x40U
/** flag for LWIP_DEBUGF indicating a state debug message (to follow module states) */
#define LWIP_DBG_STATE         0x20U
/** flag for LWIP_DEBUGF indicating newly added code, not thoroughly tested yet */
#define LWIP_DBG_FRESH         0x10U
/** flag for LWIP_DEBUGF to halt after printing this debug message */
#define LWIP_DBG_HALT          0x08U

#ifndef LWIP_NOASSERT
#define LWIP_ASSERT(message, assertion) do { if(!(assertion)) \
  LWIP_PLATFORM_ASSERT(message); } while(0)
#else  /* LWIP_NOASSERT */
#define LWIP_ASSERT(message, assertion)
#endif /* LWIP_NOASSERT */

/** if "expression" isn't true, then print "message" and execute "handler" expression */
#ifndef LWIP_ERROR
#define LWIP_ERROR(message, expression, handler) do { if (!(expression)) { \
  LWIP_PLATFORM_ASSERT(message); handler;}} while(0)
#endif /* LWIP_ERROR */

#ifdef LWIP_DEBUG

// These constexpr funcion log predicates were put in place instead
// of the simple macros to silence approximately 450 instances of
// "warning: use of logical '&&' with constant operand [-Wconstant-logical-operand]"
// as seen here: https://travis-ci.org/inet-framework/inet/jobs/327767598
constexpr bool lwip_log_predicate(unsigned int debug, unsigned int debug_types_on, int debug_min_level)
{
  return ((debug) & LWIP_DBG_ON)
            && ((debug) & debug_types_on)
            && ((s16_t)((debug) & LWIP_DBG_MASK_LEVEL) >= debug_min_level);
}

constexpr bool lwip_halt_predicate(unsigned int debug)
{
  return (debug) & LWIP_DBG_HALT;
}

/** print debug message only if debug message type is enabled...
 *  AND is of correct type AND is at least LWIP_DBG_LEVEL
 */
#define LWIP_DEBUGF(debug, message) do { \
                               if (lwip_log_predicate(debug, LWIP_DBG_TYPES_ON, LWIP_DBG_MIN_LEVEL)) { \
                                 LWIP_PLATFORM_DIAG(message); \
                                 if (lwip_halt_predicate(debug)) { \
                                   while(1); \
                                 } \
                               } \
                             } while(0)

#else  /* LWIP_DEBUG */
#define LWIP_DEBUGF(debug, message)
#endif /* LWIP_DEBUG */

} // namespace tcp

} // namespace inet

#endif /* __LWIP_DEBUG_H__ */

