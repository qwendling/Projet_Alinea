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

$(EXE) : $(OBJFILES)
	$(CC) -o $@ $^
	mv $@ $(BPATH)

$(OPATH)/%.o : $(CPATH)/%.c
	$(CC) $(CFLAGS) -c $< $(IFLAGS) -o $@
clean :
	rm $(OPATH)/* $(BPATH)/*
