#
# MAIN CONFIGURATION
#

EXEC = sudoku_solver
OBJECTS = 
PROJECT_NAME = CHPS_0701_PROJET

#
# SUFFIXES
#

.SUFFIXES: .c .o

#
# OBJECTS
#

EXEC_O = $(EXEC:=.o)
OBJECTS_O = $(OBJETS) $(EXEC_O)

#
# ARGUMENTS AND COMPILER
#

CC = gcc
CCFLAGS_STD = -Wall -O3 #-Werror
CCFLAGS_DEBUG = -D _DEBUG_
CCFLAGS = $(CCFLAGS_STD)
CCLIBS = -lncurses -fopenmp

#
# RULES
#

all: msg $(OBJECTS) $(EXEC_O)
	@echo "Create executables..."
	@for i in $(EXEC); do \
	$(CC) -o $$i $$i.o $(OBJECTS) $(CCLIBS); \
	done
	@echo "Done."

msg:
	@echo "Create objects..."

debug: CCFLAGS = $(CCFLAGS_STD) $(CCFLAGS_DEBUG)
debug: all

#
# DEFAULT RULES
#

.c.o: .h
	@cd $(dir $<) && ${CC} ${CCFLAGS} -c $(notdir $<) -o $(notdir $@)

#
# GENERAL RULES
#

clean:
	@echo "Delete objects, temporary files..."
	@rm -f $(OBJECTS) $(EXEC_O)
	@rm -f *~ *#
	@rm -f $(EXEC)
	@rm -f dependancies
	@echo "Done."
#
# CREATE ARCHIVE
#

ARCHIVE_FILES = *

archive: clean
	@echo "Create archive $(PROJECT_NAME)_$(shell date '+%y%m%d.tar.gz')..."
	@REP=`basename "$$PWD"`; cd .. && tar zcf $(PROJECT_NAME)_$(shell date '+%y%m%d.tar.gz') $(addprefix "$$REP"/,$(ARCHIVE_FILES))
	@echo "Done."