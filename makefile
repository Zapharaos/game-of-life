CC = gcc

IDIR = include
SDIR = src
ODIR = obj
BDIR = bin

CFLAGS = -Wall -g

vpath %.h $(IDIR)
vpath %.c $(SDIR)
vpath %.o $(ODIR)
	
main: main.o jeu.o io.o grille.o
	@mkdir -p $(BDIR)
	$(CC) $(CFLAGS) -o $(BDIR)/$@ $(ODIR)/main.o $(ODIR)/jeu.o $(ODIR)/io.o $(ODIR)/grille.o
	@echo "\n----> Compilation effectuée\n"

	rm -rf $(ODIR)
	@echo "\n----> Nettoyage (*.o) effectué\n"


%.o: %.c
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -o $(ODIR)/$@ -c $<

dist:
	@mkdir -p dist
	tar -J -cvf dist/MatthieuFreitag-GoL-v1.0.tar.xz grilles include src makefile Doxyfile doc README.md
	@echo "\n----> Archivage effectué\n"
clean:
	rm -rf $(ODIR)
	rm -rf $(BDIR)
	rm -rf dist
	@echo "\n----> Nettoyage effectué\n"

