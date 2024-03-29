vpath %.h include
vpath %.c src
vpath %.o obj
vpath main_enssemble bin

CC = gcc
CFLAGS = -g -Wall -Wextra
IFLAGS = -Iinclude
EXE = minicas
CFILES = $(wildcard $(CPATH)/*.c)
OBJFILES = $(patsubst $(CPATH)/%.c, $(OPATH)/%.o,$(CFILES))
OPATH = obj
CPATH = src
BPATH = bin

$(BPATH)/$(EXE) : $(OBJFILES)
	$(CC) -o $@ $^

$(OPATH)/%.o : $(CPATH)/%.c
	$(CC) $(CFLAGS) -c $< $(IFLAGS) -o $@

test:$(BPATH)/$(EXE)
	./bin/minicas < test.txt

test-valgrind:$(BPATH)/$(EXE)
	valgrind --leak-check=full ./bin/minicas < test.txt

clean :
	rm $(OPATH)/* $(BPATH)/* config.gp data.dat
# DO NOT DELETE

$(OPATH)/cmd.o: include/cmd.h
$(OPATH)/cmd.o: include/operation.h
$(OPATH)/cmd.o: include/Matrix.h
$(OPATH)/Matrix.o: include/Matrix.h
$(OPATH)/operation.o: include/operation.h
$(OPATH)/operation.o: include/Matrix.h
