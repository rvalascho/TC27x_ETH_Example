/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
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

#include "opt.h"
#include "sys.h"
#include "stats.h"
#include "debug.h"

#include "FreeRTOS.h"
#include "task.h"

#include "IfxCpu_bf.h"

#if !NO_SYS

static u32_t get_time_ms(void)
{
  portTickType ticks;

  if ((__mfcr(CPU_ICR) & (IFX_CPU_ICR_CCPN_MSK << IFX_CPU_ICR_CCPN_OFF)) != 0)
  {
    ticks = xTaskGetTickCountFromISR();
  }
  else
  {
    ticks = xTaskGetTickCount();
  }

  return TICK_TO_MSEC(ticks);
}

/*
 * Creates and returns a new semaphore. 
 * The "count" argument specifies the initial state of the semaphore.
 */
err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
  *sem = xSemaphoreCreateBinary();

  if (*sem == NULL)
  {
    SYS_STATS_INC( sem.err );
    return ERR_MEM;
  }

  if (count == 0U)
  {
    xSemaphoreTake(*sem, 1UL);
  }
  SYS_STATS_INC_USED( sem );    
  
  return ERR_OK;
}

void sys_sem_free(sys_sem_t *sem)
{
  SYS_STATS_DEC(sem.used);      
  vSemaphoreDelete(*sem);
}

/*
 * Blocks the thread while waiting for the semaphore to be
 * signaled. If the "timeout" argument is non-zero, the thread should
 * only be blocked for the specified time (measured in
 * milliseconds).
 *
 * If the timeout argument is non-zero, the return value is the number of
 * milliseconds spent waiting for the semaphore to be signaled. If the
 * semaphore wasn't signaled within the specified time, the return value is
 * SYS_ARCH_TIMEOUT. If the thread didn't have to wait for the semaphore
 * (i.e., it was already signaled), the function may return zero.
 *
 * Notice that lwIP implements a function with a similar name,
 * sys_sem_wait(), that uses the sys_arch_sem_wait() function.
 */

u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
  u32_t time_start , time_end;

  time_start = get_time_ms();

  if (timeout != 0)
  {
    if (xSemaphoreTake(*sem, MSEC_TO_TICK(timeout)) == pdTRUE )
    {
      time_end = get_time_ms();     
      return (time_end - time_start);
    }
    else
    {
      return SYS_ARCH_TIMEOUT;
    }
  }
  else // must block without a timeout
  {
    while (xSemaphoreTake(*sem, portMAX_DELAY) != pdTRUE);
    time_end = get_time_ms();

    return (((time_end - time_start) == 0) ? 1 : (time_end - time_start));
  }
}

void sys_sem_signal(sys_sem_t *sem)
{
  portBASE_TYPE taskToWake = pdFALSE;

  if ((__mfcr(CPU_ICR) & (IFX_CPU_ICR_CCPN_MSK << IFX_CPU_ICR_CCPN_OFF)) != 0)
  {
    if (xSemaphoreGiveFromISR(*sem, &taskToWake) == pdTRUE)
    {
      portYIELD_FROM_ISR(taskToWake);
    }

  }
  else
  {
    xSemaphoreGive(*sem);
  }
}

int sys_sem_valid(sys_sem_t *sem)                                               
{
  return (*sem != 0 ? 1 : 0);
}

void sys_sem_set_invalid(sys_sem_t *sem)                                        
{                                                                               
  *sem = 0;                                                          
} 

/*-----------------------------------------------------------------------------------*/                                                                                                                                                                

#if LWIP_COMPAT_MUTEX == 0

err_t sys_mutex_new(sys_mutex_t *mutex)
{
  *mutex = xSemaphoreCreateMutex();
  if (*mutex == NULL)
  {
    SYS_STATS_INC( mutex.err );
    return ERR_MEM;
  }

  SYS_STATS_INC_USED( mutex );
  
  return ERR_OK;
}

void sys_mutex_free(sys_mutex_t *mutex)
{
  SYS_STATS_DEC( mutex.used );
      
  vSemaphoreDelete(*mutex);
}

void sys_mutex_lock(sys_mutex_t *mutex)
{
  while (xSemaphoreTake(*mutex, portMAX_DELAY) != pdPASS);
}

void sys_mutex_unlock(sys_mutex_t *mutex)
{
  xSemaphoreGive(*mutex);
}

#endif /*LWIP_COMPAT_MUTEX*/

/*-----------------------------------------------------------------------------------*/                                              

err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{ 
  *mbox = xQueueCreate(size, sizeof(void *));

  if (*mbox == NULL)
  {
    return ERR_MEM;
  }
  
  SYS_STATS_INC_USED(mbox);
  return ERR_OK;
}

void sys_mbox_free(sys_mbox_t *mbox)
{
  if (uxQueueMessagesWaiting(*mbox))
  {
    SYS_STATS_INC(mbox.err);
  }

  vQueueDelete(*mbox);
  SYS_STATS_DEC(mbox.used);
}

void sys_mbox_post(sys_mbox_t *mbox, void *msg)
{
  if ((__mfcr(CPU_ICR) & (IFX_CPU_ICR_CCPN_MSK << IFX_CPU_ICR_CCPN_OFF)) != 0)
  {
    xQueueSendToBackFromISR(*mbox, &msg, NULL);
  }
  else
  {
    while (xQueueSendToBack( *mbox, &msg, portMAX_DELAY ) != pdTRUE);
  }
}

err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{
  if ((__mfcr(CPU_ICR) & (IFX_CPU_ICR_CCPN_MSK << IFX_CPU_ICR_CCPN_OFF)) != 0)
  {
    if (xQueueSendToBackFromISR(*mbox, &msg, NULL) == pdTRUE)
    {
      return ERR_OK;      
    }
  }
  else
  {
    if (xQueueSendToBack(*mbox, &msg, portMAX_DELAY) == pdTRUE)
    {
      return ERR_OK;
    }
  }

  SYS_STATS_INC(mbox.err);

  return ERR_MEM;
}

/*
 * Blocks the thread until a message arrives in the mailbox, but does
 * not block the thread longer than "timeout" milliseconds (similar to
 * the sys_arch_sem_wait() function). The "msg" argument is a result
 * parameter that is set by the function (i.e., by doing "*msg =
 * ptr"). The "msg" parameter maybe NULL to indicate that the message
 * should be dropped.
 *
 * The return values are the same as for the sys_arch_sem_wait() function:
 * Number of milliseconds spent waiting or SYS_ARCH_TIMEOUT if there was a
 * timeout.

 * Note that a function with a similar name, sys_mbox_fetch(), is
 * implemented by lwIP.
 */

u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{
  u32_t time_start , time_end;

  time_start = get_time_ms();

  if (timeout != 0)
  {
    if (xQueueReceive(*mbox, &(*msg), MSEC_TO_TICK(timeout)) == pdTRUE )
    {
      time_end = get_time_ms();     
      return (time_end - time_start);
    }
    else
    {
      *msg = NULL;
      return SYS_ARCH_TIMEOUT;
    }
  }
  else // must block without a timeout
  {
    while (xQueueReceive(*mbox, &(*msg), portMAX_DELAY) != pdTRUE){}

    time_end = get_time_ms();
    return (((time_end - time_start) == 0) ? 1 : (time_end - time_start));
  }
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
  if ((__mfcr(CPU_ICR) & (IFX_CPU_ICR_CCPN_MSK << IFX_CPU_ICR_CCPN_OFF)) != 0)
  {
    if (xQueueReceiveFromISR(*mbox, &(*msg), NULL) == pdTRUE)
    {
      return ERR_OK;
    }  
  }
  else
  {
    if (xQueueReceive(*mbox, &(*msg), 0 ) == pdTRUE)
    {
      return ERR_OK;
    }
  }

  return SYS_MBOX_EMPTY;
}


int sys_mbox_valid(sys_mbox_t *mbox)          
{      
  return (*mbox != 0 ? 1 : 0);
}        

void sys_mbox_set_invalid(sys_mbox_t *mbox)   
{                                             
  *mbox = 0;                      
}                                             

/*-----------------------------------------------------------------------------------*/                                              

/*
 * Create new thread 
 */
sys_thread_t sys_thread_new(const char *name, lwip_thread_fn function, void *arg, int stacksize, int prio)
{
  TaskHandle_t taskHandler;
  
  if (xTaskCreate(function, name, stacksize, arg, prio, &taskHandler) == pdPASS)
  {
    return taskHandler;
  }
  else
  {
    return (sys_thread_t)0;
  }
}

#if SYS_LIGHTWEIGHT_PROT

/*
 * This optional function does a "fast" critical region protection and returns
 * the previous protection level. This function is only called during very short
 * critical regions. An embedded system which supports ISR-based drivers might
 * want to implement this function by disabling interrupts. Task-based systems
 * might want to implement this by using a mutex or disabling tasking. This
 * function should support recursive calls from the same task or interrupt. In
 * other words, sys_arch_protect() could be called while already protected. In
 * that case the return value indicates that it is already protected.
 */

sys_prot_t sys_arch_protect(void)
{
  portENTER_CRITICAL();
  return 1;
}

void sys_arch_unprotect(sys_prot_t pval)
{
  (void)pval;
  portEXIT_CRITICAL();
}

#endif /* SYS_LIGHTWEIGHT_PROT */

/*
 * This function returns the current time in milliseconds
 */

u32_t sys_now(void)
{
  return get_time_ms();
}

void sys_init(void)
{
}

#endif /* !NO_SYS */
