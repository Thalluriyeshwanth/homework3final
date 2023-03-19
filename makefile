CC = gcc
CFLAGS = -Wall -g
OBJS = search.o
SEARCH = fileinfo.o
EXECS = search
TARGETFOLDER = projects

build : search
	./$^ -f docx 3 -t f -E "tar cvf docx.tar" $(TARGETFOLDER)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(EXECS): $(OBJS) $(SEARCH)
	$(CC) $(CFLAGS) -o $@ $^
	rm $^