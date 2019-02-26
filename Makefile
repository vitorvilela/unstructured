EXE_DIR = .
SRC_DIR = .
INCLUDE_DIR = .

CC = icc

EXEC = NonStructured

CFLAGS = -O1 -c -w -traceback -g

C_CMD	=	$(CC) $(CFLAGS)
C_CMD += $(addprefix -I ,$(INCLUDE_DIR))

LINKER_C	= $(CC) $(LFLAGS)

MAIN = main.o

C_OBJS = structures.o \
	 misc.o \
	 init.o \
	 numerical.o \
	 boundary.o \
	 $(MAIN)

NonStructured:	Makefile $(C_OBJS) 
		$(LINKER_C) *.o -o $(EXEC)

main.o: main.c
	$(C_CMD) main.c
structures.o: structures.c
	$(C_CMD) structures.c
misc.o: misc.c
	$(C_CMD) misc.c
init.o: init.c
	$(C_CMD) init.c
numerical.o: numerical.c
	$(C_CMD) numerical.c
boundary.o: boundary.c
	$(C_CMD) boundary.c

	
clean:
	rm -f Makefile~
	rm -f *.mod
	rm -f *.o
	rm -f *.h~
	rm -f *.c~
	rm -f *.vtk~
	rm -f *.node~
	rm -f *.ele~
	rm -f *.edge~
	rm -f $(EXE_DIR)/$(EXEC)

run:
	$(EXE_DIR)/$(EXEC)

