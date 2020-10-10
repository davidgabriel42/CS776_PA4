HDRS = type.h 

OBJS = xover.o eval.o gen.o init.o main.o  rep.o\
	stats.o  random.o  select.o utils.o 


CFLAGS =  -O1
CLIBS = -lm 

ga	: $(OBJS)
	gcc -o ga $(OBJS) $(CLIBS)

$(OBJS)	: $(HDRS)

clean	:
	rm -f *.o *~ ga


dist	: clean
	cd ..; tar cvzf ga.tgz ga


