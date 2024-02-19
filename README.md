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

```
g++ -c main.cpp Sprite.cpp SpriteCollection.cpp Arrive.cpp SteeringData.cpp
g++ -o sfml-app main.o Sprite.o SpriteCollection.o Arrive.o SteeringData.o -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
```

```
 1326  g++ -c main.cpp -o main.o
 1327  g++ -c Sprite.cpp -o Sprite.o
 1328  g++ -c SpriteCollection.cpp -o SpriteCollection.o
 1329  g++ -c Arrive.cpp -o Arrive.o
 1330  g++ -c SteeringData.cpp -o SteeringData.o
 1331  g++ -o sfml-app main.o Sprite.o SpriteCollection.o Arrive.oSteeringData.o -lsfml-graphics -lsfml-window -lsfml-system

```
