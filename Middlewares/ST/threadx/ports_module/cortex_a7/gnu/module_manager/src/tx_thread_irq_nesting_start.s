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
/**   Thread                                                              */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

    .syntax unified
#if defined(THUMB_MODE)
    .thumb
#else
    .arm
#endif

IRQ_DISABLE     =       0x80                    // IRQ disable bit
MODE_MASK       =       0x1F                    // Mode mask
SYS_MODE_BITS   =       0x1F                    // System mode bits

    .text
    .align 2
/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _tx_thread_irq_nesting_start                         ARMv7-A        */
/*                                                           6.3.0        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function is called by the application from IRQ mode after      */
/*    _tx_thread_context_save has been called and switches the IRQ        */
/*    processing to the system mode so nested IRQ interrupt processing    */
/*    is possible (system mode has its own "lr" register).  Note that     */
/*    this function assumes that the system mode stack pointer was setup  */
/*    during low-level initialization (tx_initialize_low_level.s).        */
/*                                                                        */
/*    This function returns with IRQ interrupts enabled.                  */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    ISRs                                                                */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  09-30-2020     William E. Lamie         Initial Version 6.1           */
/*  04-25-2022     Zhen Kong                Updated comments,             */
/*                                            resulting in version 6.1.11 */
/*  10-31-2023     Yajun Xia                Updated comments,             */
/*                                            Added thumb mode support,   */
/*                                            resulting in version 6.3.0  */
/*                                                                        */
/**************************************************************************/
#if defined(THUMB_MODE)
    .thumb_func
#endif
    .global  _tx_thread_irq_nesting_start
    .type    _tx_thread_irq_nesting_start,function
_tx_thread_irq_nesting_start:
    MOV     r3,lr                               // Save ISR return address
    MRS     r0, CPSR                            // Pickup the CPSR
    BIC     r0, r0, #MODE_MASK                  // Clear the mode bits
    ORR     r0, r0, #SYS_MODE_BITS              // Build system mode CPSR
    MSR     CPSR_c, r0                          // Enter system mode
    STMDB   sp!, {r1, lr}                       // Push the system mode lr on the system mode stack
                                                //   and push r1 just to keep 8-byte alignment
    BIC     r0, r0, #IRQ_DISABLE                // Build enable IRQ CPSR
    MSR     CPSR_c, r0                          // Enter system mode
    BX      r3                                  // Return to caller
