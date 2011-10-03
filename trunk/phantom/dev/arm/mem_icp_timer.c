/**
 *
 * Phantom OS
 *
 * Copyright (C) 2005-2011 Dmitry Zavalishin, dz@dz.ru
 *
 * Integrator/CP timer driver.
 *
 *
**/


#define DEBUG_MSG_PREFIX "icp_tmr"
#include <debug_ext.h>
#define debug_level_flow 10
#define debug_level_error 10
#define debug_level_info 10

#include <arm/memio.h>

#include <sys/libkern.h>
#include <phantom_libc.h>
#include <time.h>

// use timer 2, fixed 1MHz

//#define BASE 0x13000000
#define BASE 0x13000100
//#define BASE 0x13000200

#define TMR_REG_LOAD             0x0
#define TMR_REG_VALUE            0x4
#define TMR_REG_CONTROL          0x8
#define TMR_REG_INT_CLR          0xC
#define TMR_REG_RIS             0x10
#define TMR_REG_MIS             0x14
#define TMR_REG_BG_LOAD         0x18


#define TMR_CTL_ONESHOT         (1<<0)
#define TMR_CTL_SIZE32          (1<<1)

#define TMR_CTL_PRESCALE_1      0x0
#define TMR_CTL_PRESCALE_16     (1<<2)
#define TMR_CTL_PRESCALE_256    (3<<2)
//#define TMR_CTL_PRESCALE_

#define TMR_CTL_IE              (1<<5)
#define TMR_CTL_PERIOD          (1<<6)
#define TMR_CTL_ENABLE          (1<<7)



#define SETUP (TMR_CTL_PRESCALE_1|TMR_CTL_PERIOD|TMR_CTL_ENABLE|TMR_CTL_SIZE32)

static int usec_per_tick = 10000; // 100 Hz


static void timer_int_handler(void *arg)
{
    (void) arg;

    // This, possibly, can lead to lost timer interrupts.
    W32( BASE+TMR_REG_CONTROL, SETUP );
    W32( BASE+TMR_REG_INT_CLR, 0 );
    //putchar('|');
    hal_time_tick(usec_per_tick);
    W32( BASE+TMR_REG_CONTROL, SETUP|TMR_CTL_IE );

    if( R32( BASE+TMR_REG_RIS ) )
        printf("Timer interrupt lost!\n");

}


void icp_timer0_init(int freq)
{
    // TODO hardcoded interrupt
    int irq = 6;

    if( hal_irq_alloc( irq, &timer_int_handler, 0, HAL_IRQ_SHAREABLE ) )
    {
        SHOW_ERROR( 0, "IRQ %d is busy", irq );
        return;
    }

    usec_per_tick = freq*1000;

    int count = 1000000/freq; // 1 MHz/freq

    W32( BASE+TMR_REG_LOAD, count );
    W32( BASE+TMR_REG_CONTROL, SETUP|TMR_CTL_IE );
}


