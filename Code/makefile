CC=gcc
CFLAGS=
LDFLAGS=
EXEC=dame serveur client

all: $(EXEC)

serveur: serveur.o
	$(CC) -o $@ $^ $(LDFLAGS) -lm

client: client.o
	$(CC) -o $@ $^ $(LDFLAGS) -lm

dame: dame.o
	$(CC) -o $@ $^ $(LDFLAGS) -lm

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -lm

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)