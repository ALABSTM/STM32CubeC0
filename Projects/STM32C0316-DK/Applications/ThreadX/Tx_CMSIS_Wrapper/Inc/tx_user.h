/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/

/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** ThreadX Component                                                     */
/**                                                                       */
/**   User Specific                                                       */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

/**************************************************************************/
/*                                                                        */
/*  PORT SPECIFIC C INFORMATION                            RELEASE        */
/*                                                                        */
/*    tx_user.h                                           PORTABLE C      */
/*                                                           6.1.11       */
/*                                                                        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This file contains user defines for configuring ThreadX in specific */
/*    ways. This file will have an effect only if the application and     */
/*    ThreadX library are built with TX_INCLUDE_USER_DEFINE_FILE defined. */
/*    Note that all the defines in this file may also be made on the      */
/*    command line when building ThreadX library and application objects. */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     William E. Lamie         Initial Version 6.0           */
/*  09-30-2020      Yuxin Zhou              Modified comment(s),          */
/*                                            resulting in version 6.1    */
/*  03-02-2021      Scott Larson            Modified comment(s),          */
/*                                            added option to remove      */
/*                                            FileX pointer,              */
/*                                            resulting in version 6.1.5  */
/*  06-02-2021      Scott Larson            Added options for multiple    */
/*                                            block pool search & delay,  */
/*                                            resulting in version 6.1.7  */
/*  10-15-2021      Yuxin Zhou              Modified comment(s), added    */
/*                                            user-configurable symbol    */
/*                                            TX_TIMER_TICKS_PER_SECOND   */
/*                                            resulting in version 6.1.9  */
/*  04-25-2022      Wenhui Xie              Modified comment(s),          */
/*                                            optimized the definition of */
/*                                            TX_TIMER_TICKS_PER_SECOND,  */
/*                                            resulting in version 6.1.11 */
/*                                                                        */
/**************************************************************************/

#ifndef TX_USER_H
#define TX_USER_H

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* Define various build options for the ThreadX port.  The application should either make changes
   here by commenting or un-commenting the conditional compilation defined OR supply the defines
   though the compiler's equivalent of the -D option.

   For maximum speed, the following should be defined:

        TX_MAX_PRIORITIES                       32
        TX_DISABLE_PREEMPTION_THRESHOLD
        TX_DISABLE_REDUNDANT_CLEARING
        TX_DISABLE_NOTIFY_CALLBACKS
        TX_NOT_INTERRUPTABLE
        TX_TIMER_PROCESS_IN_ISR
        TX_REACTIVATE_INLINE
        TX_DISABLE_STACK_FILLING
        TX_INLINE_THREAD_RESUME_SUSPEND

   For minimum size, the following should be defined:

        TX_MAX_PRIORITIES                       32
        TX_DISABLE_PREEMPTION_THRESHOLD
        TX_DISABLE_REDUNDANT_CLEARING
        TX_DISABLE_NOTIFY_CALLBACKS
        TX_NOT_INTERRUPTABLE
        TX_TIMER_PROCESS_IN_ISR

   Of course, many of these defines reduce functionality and/or change the behavior of the
   system in ways that may not be worth the trade-off. For example, the TX_TIMER_PROCESS_IN_ISR
   results in faster and smaller code, however, it increases the amount of processing in the ISR.
   In addition, some services that are available in timers are not available from ISRs and will
   therefore return an error if this option is used. This may or may not be desirable for a
   given application.  */

/* Override various options with default values already assigned in tx_port.h. Please also refer
   to tx_port.h for descriptions on each of these options.  */

#define TX_MAX_PRIORITIES                64
#define TX_THREAD_USER_EXTENSION         ULONG               tx_thread_detached_joinable;
/*#define TX_TIMER_THREAD_STACK_SIZE                1024*/
/*#define TX_TIMER_THREAD_PRIORITY                0*/

/*#define TX_MINIMUM_STACK                200*/

/* Determine if timer expirations (application timers, timeouts, and tx_thread_sleep calls
   should be processed within the a system timer thread or directly in the timer ISR.
   By default, the timer thread is used. When the following is defined, the timer expiration
   processing is done directly from the timer ISR, thereby eliminating the timer thread control
   block, stack, and context switching to activate it.  */

#define TX_TIMER_PROCESS_IN_ISR

/* Determine if in-line timer reactivation should be used within the timer expiration processing.
   By default, this is disabled and a function call is used. When the following is defined,
   reactivating is performed in-line resulting in faster timer processing but slightly larger
   code size.  */

/*#define TX_REACTIVATE_INLINE*/

/* Determine is stack filling is enabled. By default, ThreadX stack filling is enabled,
   which places an 0xEF pattern in each byte of each thread's stack.  This is used by
   debuggers with ThreadX-awareness and by the ThreadX run-time stack checking feature.  */

#define TX_DISABLE_STACK_FILLING

/* Determine if preemption-threshold should be disabled. By default, preemption-threshold is
   enabled. If the application does not use preemption-threshold, it may be disabled to reduce
   code size and improve performance.  */

#define TX_DISABLE_PREEMPTION_THRESHOLD

/* Determine if global ThreadX variables should be cleared. If the compiler startup code clears
   the .bss section prior to ThreadX running, the define can be used to eliminate unnecessary
   clearing of ThreadX global variables.  */

#define TX_DISABLE_REDUNDANT_CLEARING

/* Determine if the notify callback option should be disabled. By default, notify callbacks are
   enabled. If the application does not use notify callbacks, they may be disabled to reduce
   code size and improve performance.  */

#define TX_DISABLE_NOTIFY_CALLBACKS

/* Determine if the tx_thread_resume and tx_thread_suspend services should have their internal
   code in-line. This results in a larger image, but improves the performance of the thread
   resume and suspend services.  */

/*#define TX_INLINE_THREAD_RESUME_SUSPEND*/

/* Determine if the internal ThreadX code is non-interruptable. This results in smaller code
   size and less processing overhead, but increases the interrupt lockout time.  */

#define TX_NOT_INTERRUPTABLE

/* Determine if the trace event logging code should be enabled. This causes slight increases in
   code size and overhead, but provides the ability to generate system trace information which
   is available for viewing in TraceX.  */

/*#define TX_ENABLE_EVENT_TRACE*/

/* Determine if block pool performance gathering is required by the application. When the following is
   defined, ThreadX gathers various block pool performance information. */

/*#define TX_BLOCK_POOL_ENABLE_PERFORMANCE_INFO*/

/* Determine if byte pool performance gathering is required by the application. When the following is
   defined, ThreadX gathers various byte pool performance information. */

/*#define TX_BYTE_POOL_ENABLE_PERFORMANCE_INFO*/

/* Determine if event flags performance gathering is required by the application. When the following is
   defined, ThreadX gathers various event flags performance information. */

/*#define TX_EVENT_FLAGS_ENABLE_PERFORMANCE_INFO*/

/* Determine if mutex performance gathering is required by the application. When the following is
   defined, ThreadX gathers various mutex performance information. */

/*#define TX_MUTEX_ENABLE_PERFORMANCE_INFO*/

/* Determine if queue performance gathering is required by the application. When the following is
   defined, ThreadX gathers various queue performance information. */

/*#define TX_QUEUE_ENABLE_PERFORMANCE_INFO*/

/* Determine if semaphore performance gathering is required by the application. When the following is
   defined, ThreadX gathers various semaphore performance information. */

/*#define TX_SEMAPHORE_ENABLE_PERFORMANCE_INFO*/

/* Determine if thread performance gathering is required by the application. When the following is
   defined, ThreadX gathers various thread performance information. */

/*#define TX_THREAD_ENABLE_PERFORMANCE_INFO*/

/* Determine if timer performance gathering is required by the application. When the following is
   defined, ThreadX gathers various timer performance information. */

/*#define TX_TIMER_ENABLE_PERFORMANCE_INFO*/

/* Define if the execution change notify is enabled. */

/*#define TX_TIMER_TICKS_PER_SECOND                100*/

/* Defined, the basic parameter error checking is disabled. */

/*#define TX_DISABLE_ERROR_CHECKING*/

/* Determine if there is a FileX pointer in the thread control block.
   By default, the pointer is there for legacy/backwards compatibility.
   The pointer must also be there for applications using FileX.
   Define this to save space in the thread control block.
*/

/*#define TX_NO_FILEX_POINTER*/

/* Determinate if the basic alignment type is defined. */

/*#define ALIGN_TYPE_DEFINED*/

/* Define basic alignment type used in block and byte pool operations. */

/*#define ALIGN_TYPE  ULONG*/

/* Define the TX_MEMSET macro to the standard library function. */

/*#define TX_MEMSET  memset((a),(b),(c))*/

/* Define if the safety critical configuration is enabled. */

/*#define TX_SAFETY_CRITICAL*/
/* Define the CMSIS RTOS2 stack size */
#define RTOS2_BYTE_POOL_STACK_SIZE              3 * 1024

/* define the CMSIS RTOS2 heap size */

#define RTOS2_BYTE_POOL_HEAP_SIZE               4 * 1024

/* USER CODE BEGIN 2 */
/* This define defines the type of memory allocation. */
#define USE_DYNAMIC_MEMORY_ALLOCATION

/*#define USE_MEMORY_POOL_ALLOCATION*/
/* USER CODE END 2 */
#endif
