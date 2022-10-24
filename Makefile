#define
CPP = game.cpp
HEA = game.h
OBJ = main.o game.o
LIB = -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main
LIDBIR = -L"D:\Dev\SFML-2.5.1\lib"
INCDIR = -I"D:\Dev\SFML-2.5.1\include"

output: $(OBJ)
	g++ $(OBJ) -o output $(LIDBIR) $(LIB)
main.o: 
	g++ -c main.cpp $(INCDIR) -DSFML_STATIC
game.o: $(CPP) $(HEA)
	g++ -c $(CPP) $(INCDIR) -DSFML_STATIC
clean: 
	del *.o output.exe