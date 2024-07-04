;/**************************************************************************/
;/*                                                                        */
;/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
;/*                                                                        */
;/*       This software is licensed under the Microsoft Software License   */
;/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
;/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
;/*       and in the root directory of this software.                      */
;/*                                                                        */
;/**************************************************************************/
;
;
;/**************************************************************************/
;/**************************************************************************/
;/**                                                                       */ 
;/** ThreadX Component                                                     */ 
;/**                                                                       */
;/**   Thread                                                              */
;/**                                                                       */
;/**************************************************************************/
;/**************************************************************************/

    EXTERN      _tx_thread_current_ptr
    EXTERN      _tx_timer_time_slice
    EXTERN      _tx_thread_schedule
#if (defined(TX_ENABLE_EXECUTION_CHANGE_NOTIFY) || defined(TX_EXECUTION_PROFILE_ENABLE))
    EXTERN      _tx_execution_thread_exit        
#endif

;/**************************************************************************/ 
;/*                                                                        */ 
;/*  FUNCTION                                               RELEASE        */ 
;/*                                                                        */ 
;/*    _tx_thread_system_return                           Cortex-A7/IAR    */ 
;/*                                                           6.3.0        */
;/*  AUTHOR                                                                */
;/*                                                                        */
;/*    William E. Lamie, Microsoft Corporation                             */
;/*                                                                        */
;/*  DESCRIPTION                                                           */
;/*                                                                        */ 
;/*    This function is target processor specific.  It is used to transfer */ 
;/*    control from a thread back to the ThreadX system.  Only a           */ 
;/*    minimal context is saved since the compiler assumes temp registers  */ 
;/*    are going to get slicked by a function call anyway.                 */ 
;/*                                                                        */ 
;/*  INPUT                                                                 */ 
;/*                                                                        */ 
;/*    None                                                                */ 
;/*                                                                        */ 
;/*  OUTPUT                                                                */ 
;/*                                                                        */ 
;/*    None                                                                */ 
;/*                                                                        */ 
;/*  CALLS                                                                 */ 
;/*                                                                        */ 
;/*    _tx_thread_schedule                   Thread scheduling loop        */ 
;/*                                                                        */ 
;/*  CALLED BY                                                             */ 
;/*                                                                        */ 
;/*    ThreadX components                                                  */ 
;/*                                                                        */ 
;/*  RELEASE HISTORY                                                       */ 
;/*                                                                        */ 
;/*    DATE              NAME                      DESCRIPTION             */
;/*                                                                        */
;/*  09-30-2020     William E. Lamie         Initial Version 6.1           */
;/*  10-31-2023     Yajun Xia                Modified comment(s),          */
;/*                                            Added thumb mode support,   */
;/*                                            resulting in version 6.3.0  */
;/*                                                                        */
;/**************************************************************************/
;VOID   _tx_thread_system_return(VOID)
;{
    RSEG    .text:CODE:NOROOT(2)
    PUBLIC  _tx_thread_system_return
#ifdef THUMB_MODE
    THUMB
#else
    ARM
#endif
_tx_thread_system_return

;   /* Save minimal context on the stack.  */
;
    PUSH    {r4-r11, lr}                ; Save minimal context

    LDR     r4, =_tx_thread_current_ptr ; Pickup address of current ptr
    LDR     r5, [r4]                    ; Pickup current thread pointer

#ifdef TX_ENABLE_VFP_SUPPORT
    LDR     r1, [r5, #144]              ; Pickup the VFP enabled flag
    CMP     r1, #0                      ; Is the VFP enabled?
    BEQ     _tx_skip_solicited_vfp_save ; No, skip VFP solicited save
    VMRS    r1, FPSCR                   ; Pickup the FPSCR
    STR     r1, [sp, #-4]!              ; Save FPSCR
    VSTMDB  sp!, {D16-D31}              ; Save D16-D31
    VSTMDB  sp!, {D8-D15}               ; Save D8-D15
_tx_skip_solicited_vfp_save:
#endif

    MOV     r0, #0                      ; Build a solicited stack type
    MRS     r1, CPSR                    ; Pickup the CPSR, T bit is always cleared by hardware
    TST     lr, #1                      ; Check if calling function is in Thumb mode
    IT      NE
    ORRNE   r1, #0x20                   ; Set the T bit so that the correct mode is set on return
    PUSH    {r0-r1}                     ; Save type and CPSR

#ifdef TX_ENABLE_FIQ_SUPPORT
    CPSID   if                          ; Disable IRQ and FIQ
#else
    CPSID   i                           ; Disable IRQ
#endif

#if (defined(TX_ENABLE_EXECUTION_CHANGE_NOTIFY) || defined(TX_EXECUTION_PROFILE_ENABLE))

;   /* Call the thread exit function to indicate the thread is no longer executing.  */

    BL      _tx_execution_thread_exit   ; Call the thread exit function
#endif
    MOV     r3, r4                      ; Pickup address of current ptr
    MOV     r0, r5                      ; Pickup current thread pointer
    LDR     r2, =_tx_timer_time_slice   ; Pickup address of time slice
    LDR     r1, [r2]                    ; Pickup current time slice

;   /* Save current stack and switch to system stack.  */

    STR     sp, [r0, #8]                ; Save thread stack pointer

;   /* Determine if the time-slice is active.  */

    MOV     r4, #0                      ; Build clear value
    CMP     r1, #0                      ; Is a time-slice active?
    BEQ     __tx_thread_dont_save_ts    ; No, don't save the time-slice

;   /* Save time-slice for the thread and clear the current time-slice.  */

    STR     r4, [r2]                    ; Clear time-slice
    STR     r1, [r0, #24]               ; Save current time-slice
;
;    }
__tx_thread_dont_save_ts
;
;    /* Clear the current thread pointer.  */
;    _tx_thread_current_ptr =  TX_NULL;
;
    STR     r4, [r3]                    ; Clear current thread pointer
    B       _tx_thread_schedule         ; Jump to scheduler!
;
;}
    END

