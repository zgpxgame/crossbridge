# $FreeBSD: src/lib/libthr/support/Makefile.inc,v 1.1.22.1.6.1 2010/12/21 17:09:25 kensmith Exp $

.PATH: ${.CURDIR}/support ${.CURDIR}/../libc/gen ${.CURDIR}/../libc/string
.PATH: ${.CURDIR}/../libc/${MACHINE_ARCH}/sys

CFLAGS+= -I${.CURDIR}/../libc/${MACHINE_ARCH}

SYSCALLS= thr_new

SYSCALL_SRC=   ${SYSCALLS:S/$/.S/}
SYSCALL_OBJ=   ${SYSCALLS:S/$/.So/}

${SYSCALL_SRC}:
	printf '#include "SYS.h"\nRSYSCALL(${.PREFIX})\n' > ${.TARGET}

LIBC_OBJS=

SOBJS+=	thr_libc.So
CLEANFILES+= ${SYSCALL_SRC} ${SYSCALL_OBJ} ${LIBC_OBJS}

thr_libc.So: ${SYSCALL_OBJ} ${LIBC_OBJS}
	${CC} -fPIC -nostdlib -o ${.TARGET} -r ${.ALLSRC}
