CC = g++
IPath = -ID:/Studium/labworks-2/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include
LPath = -LD:/Studium/labworks-2/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/bin -lsfml-graphics-d-2 -lsfml-window-d-2 -lsfml-system-d-2

lab03: main.o SFMLlesson.o pool_fill.o 
	$(CC) -o lab03.exe main.o SFMLlesson.o pool_fill.o $(IPath) $(LPath)

SFMLlesson.o:
	$(CC) -o SFMLlesson.o -c SFMLlesson.cpp $(IPath) 

pool_fill.o:
	$(CC) -o pool_fill.o -c pool_fill.cpp $(IPath) 

main.o: SFMLlesson.cpp pool_fill.cpp 
	$(CC) -o main.o -c main.cpp $(IPath) $(LPath)