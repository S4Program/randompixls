all: compile linkdebug

compile: 
	g++ -c main.cpp -I"D:\Prgrams\SFML\SFML-2.6.1\include" -DSFML_STATIC

link:
	g++ main.o -o main -L"D:\Prgrams\SFML\SFML-2.6.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

linkdebug:
	g++ main.o -o main -L"D:\Prgrams\SFML\SFML-2.6.1\lib" -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

clean:
	rm -f main *.o