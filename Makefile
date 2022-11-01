#define
OBJ = main.o gamea.o graphic.o core.o 
LIB = -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main
LIDBIR = -L"D:\Dev\SFML-2.5.1\lib"
INCDIR = -I"D:\Dev\SFML-2.5.1\include"

output: $(OBJ)
	g++ $(OBJ) -o output $(LIDBIR) $(LIB)
main.o: 
	g++ -c main.cpp $(INCDIR) -DSFML_STATIC
# game.o: game.cpp game.h
# 	g++ -c game.cpp $(INCDIR) -DSFML_STATIC
gamea.o: gamea.cpp gamea.h
	g++ -c gamea.cpp $(INCDIR) -DSFML_STATIC 
graphic.o: graphic.cpp graphic.h
	g++ -c graphic.cpp $(INCDIR) -DSFML_STATIC
core.o: core.cpp core.h
	g++ -c core.cpp $(INCDIR) -DSFML_STATIC
clean: 
	del *.o output.exe