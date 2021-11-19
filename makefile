CC = gcc

IDIR = include
SDIR = src
ODIR = obj
BDIR = bin
LDIR = lib
DDIR = dist

MODE=CAIRO

ifeq ($(TYPE), MAC)
	CPPFLAGS = -L /usr/X11/lib -I/usr/X11/include -I/usr/X11/include/cairo -Iinclude
else
	CPPFLAGS = -Iinclude -I/usr/include/cairo
endif

ifeq ($(MODE), TEXTE)
	CFLAGS = -Iinclude
else
	LDFLAGS = -lcairo -lm -lX11
	CFLAGS = $(CPPFLAGS)
endif

CFLAGS += -Wall -g -o

vpath %.h $(IDIR)
vpath %.c $(SDIR)
vpath %.o $(ODIR)
	
main: main.o jeu.o io.o grille.o
	@mkdir -p $(BDIR)

	@mkdir -p $(LDIR)
	ar -crv $(LDIR)/libjeu.a $(ODIR)/jeu.o $(ODIR)/grille.o

	$(CC) -D $(MODE) $(CFLAGS) $(BDIR)/$@ $(ODIR)/main.o $(ODIR)/jeu.o $(ODIR)/io.o $(ODIR)/grille.o $(LDFLAGS)
	@echo "\n----> Compilation effectuée\n"

	rm -f $(ODIR)/*.o
	@echo "\n----> Nettoyage (*.o) effectué\n"

%.o: %.c
	@mkdir -p $(ODIR)
	$(CC) -D $(MODE) $(CFLAGS) $(ODIR)/$@ -c $<

dist:
	@mkdir -p $(DDIR)
	tar -J -cvf $(DDIR)/MatthieuFreitag-GoL-v5.0.tar.xz grilles include src lib makefile Doxyfile doc Niveaux README.md 
	@echo "\n----> Archivage effectué\n"

clean:
	rm -rf $(ODIR)
	rm -rf $(BDIR)
	rm -rf $(LDIR)
	rm -rf $(DDIR)
	@echo "\n----> Nettoyage effectué\n"

	rm -rf $(ODIR)
	@echo "\n----> Nettoyage (*.o) effectué\n"

doxy:
	rm -rf doc
	doxygen Doxyfile
	@echo "\n----> Doxygen effectué\n"

