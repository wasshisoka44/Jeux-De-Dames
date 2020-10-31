CC=gcc
CFLAGS=
LDFLAGS=
EXEC=serveur client

all: $(EXEC)

serveur: serveur.o dame.o
	$(CC) -Wall -o $@ $^ $(LDFLAGS) -lm

client: client.o dame.o
	$(CC) -Wall -o $@ $^ $(LDFLAGS) -lm

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -lm

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)