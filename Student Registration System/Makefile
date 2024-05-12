CC = gcc
CFLAGS = -O2 -Wall
LINKFLAGS = -lm

OUTPUT = main.exe 
OBJECTS = main.o proje1.o

$(OUTPUT): $(OBJECTS)
	$(CC) $(OBJECTS) $(LINKFLAGS) -o $(OUTPUT)

main.o: main.c proje1.h
	$(CC) -c main.c $(CFLAGS)

proje1.o: proje1.c proje1.h
	$(CC) -c proje1.c $(CFLAGS)

run: $(OUTPUT)
	./$(OUTPUT) Öğrenci\ Bilgileri.txt

clean:
	rm -f *.o *~ *% *.*~ core $(OUTPUT) *.out *.prof
