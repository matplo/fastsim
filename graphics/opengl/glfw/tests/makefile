srcs = $(wildcard *.c)
tgts = $(patsubst %.c,%,$(srcs))

all: $(tgts)

$(tgts): $(srcs)
	cc $@.c -o $@ -I/opt/local/include -L/opt/local/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

clean :
	@rm -fv $(tgts)
