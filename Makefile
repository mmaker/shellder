include Makefile.in

$(EXE): $(addprefix src/, $(OBJS)) libshellder.a
	cd src; $(MAKE) $(MFLAGS)
	$(CC) -o $(EXE) libshellder.a $(LIBS)

libshellder.a:
	cd src; $(MAKE) $(MFLAGS)

all: $(EXE)


.PHONY:	clean


clean:
	find src -name '*.[oa]' -delete
	rm -f --  $(OBJS) $(EXE) libshellder.a


