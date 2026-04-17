all: testlib

testlib: testlib.o primlib.o model.o view.o controller.o

	gcc -fsanitize=undefined -g $^ -o $@  -lSDL2_gfx `sdl2-config --libs` -lm

.c.o: 
	gcc -fsanitize=undefined -g -Wall -pedantic `sdl2-config --cflags` -c  $<

primlib.o: primlib.c primlib.h

model.o: model.c model.h settings.h

view.o: view.c view.h settings.h primlib.h model.h

controller.o: settings.h primlib.h model.h

testlib.o: testlib.c settings.h model.h view.h controller.h primlib.h

clean:
	-rm primlib.o testlib.o testlib model.o view.o controller.o