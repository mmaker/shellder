include Makefile.in

$(EXE): libshellder.a
	$(CC) -o $(EXE) libshellder.a $(LIBS)

libshellder.a:
	cd src; $(MAKE) $(MFLAGS)

all: $(EXE)


.PHONY:	clean


clean:
	find src -name '*.[oa]' -delete
	rm -f --  $(OBJS) $(EXE)


