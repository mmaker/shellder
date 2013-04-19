include ../Makefile.in

%.o:  %.c
	$(ECHO) $(CC) $(CFLAGS) $+
	$(CC) $(CFLAGS) $+

../libshellder.a: $(OBJS)
	$(AR) $(ARFLAGS) ../libshellder.a $(OBJS)
	$(RANLIB) ../libshellder.a




