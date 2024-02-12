How to run the code with the Makefile:
```
make clean
make
./sfml-app
```


How to run the code without the Makefile:
```
g++ -c main.cpp Sprite.cpp SpriteCollection.cpp
g++ -o sfml-app main.o Sprite.o SpriteCollection.o -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
```
