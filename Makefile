CC = g++
CFLAGS = 
INCLUDES = include/*.h

SRCS = src/*.cpp
OBJS = $(SRCS:.c=.o)
LIBS = -lglut -lGL -lGLU 
 
MAIN = carrom

all: $(MAIN)


$(MAIN): $(OBJS) 
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
.c.o:
	@$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	@$(RM) *.o *~ $(MAIN) 

depend: $(SRCS)
	makedepend $(INCLUDES) $^
