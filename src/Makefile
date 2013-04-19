include ../Makefile.in

OBJS=shell.o utils.o process.o dbg.o

%.o:  %.c
	$(ECHO) $(CC) $(CFLAGS) $+
	$(CC) $(CFLAGS) $+

../libshellder.a: $(OBJS)
	$(AR) $(ARFLAGS) ../libshellder.a shell.o utils.o process.o dbg.o
	$(RANLIB) ../libshellder.a




