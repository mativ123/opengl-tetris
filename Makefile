main: obj/main.o obj/glad.o obj/EBO.o obj/Texture.o obj/shader.o obj/VAO.o obj/VBO.o obj/stb.o
	g++ --std=c++20 $(wildcard obj/*.o) -o main -lglfw -Icommon/include -lGL

obj/main.o: main.cpp
	g++ --std=c++20 -c main.cpp -lglfw -Icommon/include -lGL
	mv main.o obj/

obj/glad.o: common/glad.c
	g++ --std=c++20 -c common/glad.c -Icommon/include
	mv glad.o obj/

obj/EBO.o: common/EBO.cpp
	g++ --std=c++20 -c common/EBO.cpp -Icommon/include
	mv EBO.o obj/

obj/Texture.o: common/Texture.cpp
	g++ --std=c++20 -c common/Texture.cpp -Icommon/include
	mv Texture.o obj/

obj/shader.o: common/shader.cpp
	g++ --std=c++20 -c common/shader.cpp -Icommon/include
	mv shader.o obj/

obj/VAO.o: common/VAO.cpp
	g++ --std=c++20 -c common/VAO.cpp -Icommon/include
	mv VAO.o obj/

obj/VBO.o: common/VBO.cpp
	g++ --std=c++20 -c common/VBO.cpp -Icommon/include
	mv VBO.o obj/

obj/stb.o: common/stb.cpp
	g++ --std=c++20 -c common/stb.cpp -Icommon/include
	mv stb.o obj/
