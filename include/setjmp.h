/**
 *
 * Phantom OS
 *
 * Copyright (C) 2005-2011 Dmitry Zavalishin, dz@dz.ru
 *
 * Setjmp buffer definition. Arch dep.
 *
 *
**/


#ifndef _MACH_SETJMP_H_PROCESSED_
#define _MACH_SETJMP_H_PROCESSED_ 1

#ifdef ARCH_ia32
/*
 * Setjmp/longjmp buffer for i386.
 */

/* XXX The original definition of jmp_buf[] causes problems using
 * libthreads when linked against NetBSD and FreeBSD's libc because
 * it's too small.  When cthreads calls _setjmp, it gets the libc
 * version which saves more state than it's expecting and overwrites
 * important cthread data. =( This definition is big enough for all
 * known systems so far (Linux's is 6, FreeBSD's is 9 and NetBSD's is
 * 10).  
 */
#if 0
#define _JBLEN 6
#else
#define _JBLEN 10
#endif
#endif


#ifdef ARCH_arm
// TODO float!
// In fact we store r4-r14 = 11 i + 12+1f
#define _JBLEN 96
#endif

#ifdef ARCH_amd64
#define	_JBLEN	12		// Size of the jmp_buf on AMD64. 
#endif

#ifdef ARCH_mips
#define	_JBLEN	64*8		// Size of the jmp_buf on MIPS - 64 regs 64 bits each
#endif

#ifndef _JBLEN
# error setjmp arch
#endif

typedef int jmp_buf[_JBLEN];


extern int setjmp (jmp_buf) __attribute__((returns_twice));
extern void longjmp (jmp_buf, int);
extern int _setjmp (jmp_buf) __attribute__((returns_twice));
extern void _longjmp (jmp_buf, int);

#endif /* _MACH_SETJMP_H_PROCESSED_ */




/*
 * Original i386 copyright:
 *
 * Mach Operating System
 * Copyright (c) 1993 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

