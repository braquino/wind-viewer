CC=gcc
CFLAGS=-std=c11
INCLUDEDIRS=-Idep/include -Isrc
LIBDIRS=-Ldep/lib
LIBS=-lraylib -lglfw -lGL -lm -lpthread -ldl -lrt -lX11

build/wind-viewer: create-dir src/main.c build/test-wind-viewer build/obj/maputils.o
	$(CC) -o build/wind-viewer src/main.c build/obj/windpoint.o build/obj/station.o build/obj/maputils.o $(CFLAGS) $(INCLUDEDIRS) $(LIBDIRS) $(LIBS)

build/obj/maputils.o: src/maputils.c build/obj/windpoint.o build/obj/station.o
	$(CC) -o build/obj/maputils.o -c src/maputils.c build/obj/windpoint.o build/obj/station.o $(CFLAGS) $(INCLUDEDIRS)

build/obj/windpoint.o: src/windpoint.c
	$(CC) -o build/obj/windpoint.o -c src/windpoint.c $(CFLAGS) $(INCLUDEDIRS)

build/obj/station.o: src/station.c
	$(CC) -o build/obj/station.o -c src/station.c $(CFLAGS) $(INCLUDEDIRS)

build/test-wind-viewer: build/obj/unity.o build/obj/station.o tests/test_main.c
	$(CC) -o build/test-wind-viewer tests/test_main.c build/obj/windpoint.o build/obj/station.o build/obj/unity.o $(CFLAGS) $(INCLUDEDIRS) $(LIBDIRS) $(LIBS)

build/obj/unity.o: dep/src/unity.c
	$(CC) -o build/obj/unity.o -c dep/src/unity.c $(CFLAGS) $(INCLUDEDIRS) $(LIBDIRS)

create-dir:
	mkdir -p build
	mkdir -p build/obj