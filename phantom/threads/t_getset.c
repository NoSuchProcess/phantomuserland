/**
 *
 * Phantom OS multithreading library.
 *
 * Copyright (C) 2009-2010 Dmitry Zavalishin, dz@dz.ru
 *
 * Thread attributes access.
 *
 * Licensed under CPL 1.0, see LICENSE file.
 *
**/

#include "thread_private.h"
#include <hal.h>
#include <threads.h>
#include <phantom_libc.h>


int get_current_tid(void)
{
    assert(threads_inited);
    return get_current_thread()->tid;
}

static phantom_thread_t * get_n_thread(int tid)
{
    assert(threads_inited);
    //assert(tid >=0 && tid <= MAX_THREADS);

    if( (tid <= 0) || (tid >= MAX_THREADS) )
        return 0;

    //assert(phantom_kernel_threads[tid] != 0);
    return phantom_kernel_threads[tid];
}


#define GETT() \
    phantom_thread_t *t = get_n_thread(tid); \
    if( t == 0 )                             \
    {                                        \
        ret = ESRCH;                         \
        goto err;                            \
    }


#define PRE_ANY()    \
    assert(threads_inited); \
    int ret = 0; \
    TA_LOCK();   \
    GETT()

#define POST()   \
    err:         \
    TA_UNLOCK(); \
    return ret;

#define FAIL(__err) do { ret = __err; goto err; } while(0)



#define PRE_CURR()    \
    assert(threads_inited); \
    int ret = 0; \
    TA_LOCK();   \
    phantom_thread_t * t = GET_CURRENT_THREAD(); \
    if( t == 0 )                             \
    {                                        \
        ret = ESRCH;                         \
        goto err;                            \
    }




errno_t t_set_owner( tid_t tid, void *owner )
{
    PRE_ANY()
    t->owner = owner;
    POST()
}

errno_t t_get_owner( tid_t tid, void **owner )
{
    assert(owner);
    PRE_ANY()
    *owner = t->owner;
    POST()
}



errno_t t_set_ctty( tid_t tid, struct wtty *ct )
{
    PRE_ANY()
    t->ctty = ct;
    POST()
}

errno_t t_get_ctty( tid_t tid, struct wtty **ct )
{
    PRE_ANY()
    *ct = t->ctty;
    POST()
}


errno_t t_set_pid( tid_t tid, pid_t pid )
{
    PRE_ANY()
    t->pid = pid;
    POST()
}

errno_t t_get_pid( tid_t tid, pid_t *pid )
{
    assert(pid);
    PRE_ANY()
    *pid = t->pid;
    POST()
}



errno_t t_set_priority( tid_t tid, int prio )
{
    assert( prio >= 0 && prio <= (THREAD_PRIO_HIGHEST|THREAD_PRIO_MOD_REALTIME) );
    PRE_ANY()
    if( t != GET_CURRENT_THREAD() )
    {
        printf("Warning! Not self in hal_set_thread_priority()\n");
        // wrong - thread possibly is on wrong run q!
        /*
         t_dequeue_runq(t);
         t_enqueue_runq(t);
         */
        //ret = EINVAL;        goto err;
        FAIL(EINVAL);
    }
    t->priority = prio;
    POST()
}

errno_t t_get_priority( tid_t tid, int *prio )
{
    assert(prio);
    PRE_ANY()
    *prio = t->priority;
    POST()
}

// -----------------------------------------------------------
// Process current thread only
// -----------------------------------------------------------



errno_t t_current_set_priority( int prio )
{
    assert( prio >= 0 && prio <= (THREAD_PRIO_HIGHEST|THREAD_PRIO_MOD_REALTIME) );
    PRE_CURR()
    t->priority = prio;
    POST()
}

errno_t t_current_get_priority(int *prio)
{
    assert(prio);
    PRE_CURR()
    *prio = t->priority;
    POST()
}


errno_t t_current_set_death_handler(void (*handler)( phantom_thread_t * ))
{
    PRE_CURR()
    t->death_handler = (void *)handler;
    POST()
}


errno_t t_current_set_name(const char *name)
{
    // dies on spin reenter
#if 0
    PRE_CURR()

    const char *old = t->name;
    t->name = name ? strdup( name ) : 0;
    if( old ) free((char *)old);

    POST()
#else
        // old impl
    assert(threads_inited);
    const char *old = GET_CURRENT_THREAD()->name;
    GET_CURRENT_THREAD()->name = name ? strdup( name ) : 0;
    if( old ) free((char *)old);
    return 0;
#endif
}



// mark myself as snapper thread
errno_t t_set_snapper_flag()
{
    static int cnt = 0;
    cnt++;
    assert(cnt == 1);

    PRE_CURR()
    t->thread_flags |= THREAD_FLAG_SNAPPER;
    POST()
/*
    TA_LOCK();

    phantom_thread_t * t = GET_CURRENT_THREAD();
    assert(t != 0);
    t->thread_flags |= THREAD_FLAG_SNAPPER;

    TA_UNLOCK();
    */
}


// -----------------------------------------------------------
// old - to rewrite & kill
// -----------------------------------------------------------



phantom_thread_t * get_current_thread(void)
{
    static phantom_thread_t dummy[MAX_CPUS];
    int ncpu = GET_CPU_ID();
    return percpu_current_thread[ncpu] ? percpu_current_thread[ncpu] : dummy + ncpu;
}



phantom_thread_t * get_thread(int tid)
{
    assert(threads_inited);
    assert(tid >=0 && tid <= MAX_THREADS);
    assert(phantom_kernel_threads[tid] != 0);
    return phantom_kernel_threads[tid];
}


#if 0
/**
 *
 * Set given thread's priority.
 *
**/

errno_t
hal_set_thread_priority( int tid, int prio )
{
    assert(threads_inited);
    assert( prio >= 0 && prio <= (THREAD_PRIO_HIGHEST|THREAD_PRIO_MOD_REALTIME) );
    phantom_thread_t * t = get_thread(tid);
    assert(t != 0);

    if( t != GET_CURRENT_THREAD() )
    {
        printf("Warning! Not self in hal_set_thread_priority()\n");
        // wrong - thread possibly is on wrong run q!
        /*
         t_dequeue_runq(t);
         t_enqueue_runq(t);
         */
        return EINVAL;
    }

    t->priority = prio;

    return 0;
}
#endif

#if 0
errno_t hal_set_current_thread_priority( int prio )
{
    assert(threads_inited);
    assert( prio >= 0 && prio <= (THREAD_PRIO_HIGHEST|THREAD_PRIO_MOD_REALTIME) );
    phantom_thread_t * t = GET_CURRENT_THREAD();
    t->priority = prio;
    return 0;
}

int hal_get_current_thread_priority()
{
    assert(threads_inited);
    phantom_thread_t * t = GET_CURRENT_THREAD();
    return t->priority;
}
#endif

/**
 *
 * Get thread's priority.
 *
** /


int
hal_get_thread_priority( int tid )
{
    assert(threads_inited);
    phantom_thread_t * t = get_thread(tid);
    assert(t != 0);
    return t->priority;
}
*/

/**
 *
 * Set (for current thread) a handler, which will be
 * called if thread is killed in some way.
 *
** /


void
hal_set_thread_death_handler(void (*handler)( phantom_thread_t * ))
{
    assert(threads_inited);
    GET_CURRENT_THREAD()->death_handler = (void *)handler;
}

*/


/**
 *
 * Set (for current thread) thread name.
 *
** /


void
hal_set_thread_name(const char *name)
{
    assert(threads_inited);
    const char *old = GET_CURRENT_THREAD()->name;
    GET_CURRENT_THREAD()->name = name ? strdup( name ) : 0;
    if( old ) free((char *)old);
}
*/

#if 0

struct wtty *get_thread_ctty( struct phantom_thread *t )
{
    assert(threads_inited);
    return t->ctty;
}

/*

void *get_thread_owner( struct phantom_thread *t )
{
    assert(threads_inited);
    return t->owner;
}


int get_thread_flags( struct phantom_thread *t )
{
    assert(threads_inited);
	return t->thread_flags;
}

*/

#endif

