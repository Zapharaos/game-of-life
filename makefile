CC = gcc

IDIR = include
SDIR = src
ODIR = obj
BDIR = bin

CFLAGS = -g -o

vpath %.h $(IDIR)
vpath %.c $(SDIR)
vpath %.o $(ODIR)
	
main: main.o jeu.o io.o grille.o
	@mkdir -p $(BDIR)
	$(CC) $(CFLAGS) $(BDIR)/$@ $(ODIR)/main.o $(ODIR)/jeu.o $(ODIR)/io.o $(ODIR)/grille.o
	@echo "\n----> Compilation effectuée\n"

%.o: %.c
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) $(ODIR)/$@ -c $<

dist:
	@mkdir -p dist
	tar -J -cvf dist/MatthieuFreitag-GoL-v2.0.tar.xz grilles include src makefile Doxyfile doc Niveaux README.md
	@echo "\n----> Archivage effectué\n"
clean:
	rm -rf $(ODIR)
	rm -rf $(BDIR)
	rm -rf dist
	@echo "\n----> Nettoyage effectué\n"

	rm -rf $(ODIR)
	@echo "\n----> Nettoyage (*.o) effectué\n"

doxy:
	rm -rf doc
	doxygen Doxyfile
	@echo "\n----> Doxygen effectué\n"

	

