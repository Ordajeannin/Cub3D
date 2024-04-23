# 3000 lines of c for ... WHAT?
Hey innocent adventurer!
You're going to explore our Cub3D, which is a _little_ fun project of the common core of 42 school
We had to create a basic raycaster, using the minilibx (a graphic lib "designed" for pedagogic purpose, _definitely_ efficient). Basically, it's a 3D render of a 2D map.
BUUUUUUT
The mandatory project is quite... boring? Frustrating. And we had some time, soooo...
Instead of having only 1 wall with 4 textures available, and 2 colors for floor and ceiling, you can have on a same map :
- more than 60 different characteres
- who can stand for different types of wall or floor
- with a ceiling... or with a sky!
- teleporters exist to
- multi-input enabled, feel free to walk + run + turn your head, on both x and y axis
- some key params, like speed and FPS can easily be modified in the ```includes/cub3d_bonus.h```
- player isn't a dot on the map, but considered as a cylinder

Some Cub3Ds are wayyyy more impressive than this one (take a look at https://github.com/ttranche/cub3D), but it was quite fun to do.
Implementations of sprites and animations could be a great addition to this project, maybe i/we will rework on it later!

# Installation 

```
git clone https://github.com/Ordajeannin/Cub3D
cd Cub3D
make
make bonus
```
if make doesn't work, be sure to have the mlx on your system or in the "mlx" directory

# Usage (mandatory part)

```
./cub3D <<map_name>>.cub
```
### Config of the map
feel free to change the map configuration, but remember the following rules :
- give the path of the texture you want to use, for each wall's orientation
- set the color for ceiling and floor, in a rgb format (255, 255, 255)
- your map should be "close"
- walls are 1, floor are 0
- use N, W, S, E for the player's spawn, and define spawn's orientation

### Correct version 
```
WE ./textures/map3/cobleM.xpm
NO ./textures/map3/brickM.xpm
EA  ./textures/map3/netherbrickM.xpm
SO	./textures/map3/woodM.xpm
F	200,100,50
C   10,100,200

11111111111111111111111111
10000000000000000000000001111111
110001011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111101111011101000000001
11000000110101011100001000001
10000000000000001100000000001
10000000000000001101010000001
1100000111010101111101111000111
11110111 1110101 101111010001
11111111 1111111 111111111111

```

### Input will running the game

- use w,a,s,d for the player movement
- use left/right to change the player's view's angle (in the x axis)
- use escape to... quit the game :(
# Usage (Bonus part)

```
./cub3D_bonus <<map_name>>.cub
```

### Config of the map
feel free to change the map configuration to, by editing your own .cub file! but again, remember those following rules
- You will be able to use every alphanum charactere to define a texture (NSEW still for the spawn)
- Set the list of your WALL, FLOOR, CEILING, and TELEP. First 3 speak for themselfs, we will explain later what does "TELEP" stand for.
- For your textures : 
	- create a directory with the same name as your map in the "textures" directory, then ```cd textures/<<map_name>>```
	- inside, you will have to create a directory for EACH character you use in the map, like below.
	- in those directory, put 4 .xpm files for walls, named : ```ea, no, so, we```
	- and 2 .xpm files for floor. the first one will be the floor himself, the second one will be the ceiling/the sky (based on your previous list) : ```ea, no```
- Unless the mandatory version, you can have floor, ceiling, and sky texture. BUT be aware for your previous list :
	- every floor, by default, will have a sky.
	- if you want a ceiling for your floor, put the texture in BOTH list!
- Remember, if you want to be able to walk on a till, it's a FLOOR one.
- You can have teleporters on your map, they work by peer, and should be in the floor list also (can be in the ceiling to, if you want). write them like ```[aA][XY][etc.etc.]
- Again, your map should be closed, and with only one player (N, S, W or E)

### Correct version, map
```
cute_house.cub
```

```
WALL=1;2;3;4;5;6
FLOOR=0;a;b;c;d;D;X;Y
CEILING=0;a;d;D;X
TELEP=[dD][XY]

                     11111111111111
                     10000000000001
                     600E0000000001
                     10000000000001
        4444444444444100000000000d1
       4cccccccccccc331111111111121
       4cccccccccccc3355555555555255555555
       4cccccccccccc55aaaaaaaaaaaDaaaaaaaa5
       4ccccccccccbbY2Xaaaaaaaaaaaaaaaaaaa5
       4cccccccccccc55aaaaaaaaaaaaaaaaaaaa5
       4cccccccccccc35aaaaaaaaaaaaaaaaaaaa5 
        4444444444444 55555555555555555555

```

### Correct version, texture tree

```
└── textures
    ├── cute_house
    │   ├── 0
    │   │   ├── ea.xpm
    │   │   └── no.xpm
    │   ├── 1
    │   │   ├── ea.xpm
    │   │   ├── no.xpm
    │   │   ├── so.xpm
    │   │   └── we.xpm
    │   ├── 2
    │   │   ├── ea.xpm
    │   │   ├── no.xpm
    │   │   ├── so.xpm
    │   │   └── we.xpm
    │   ├── 3
    │   │   ├── ea.xpm
    │   │   ├── no.xpm
    │   │   ├── so.xpm
    │   │   └── we.xpm
    │   ├── 4
    │   │   ├── ea.xpm
    │   │   ├── no.xpm
    │   │   ├── so.xpm
    │   │   └── we.xpm
    │   ├── 5
    │   │   ├── ea.xpm
    │   │   ├── no.xpm
    │   │   ├── so.xpm
    │   │   └── we.xpm
    │   ├── 6
    │   │   ├── ea.xpm
    │   │   ├── no.xpm
    │   │   ├── so.xpm
    │   │   └── we.xpm
    │   ├── a
    │   │   ├── ea.xpm
    │   │   └── no.xpm
    │   ├── b
    │   │   ├── ea.xpm
    │   │   └── no.xpm
    │   ├── c
    │   │   ├── ea.xpm
    │   │   └── no.xpm
    │   ├── d
    │   │   ├── ea.xpm
    │   │   └── no.xpm
    │   ├── D
    │   │   ├── ea.xpm
    │   │   └── no.xpm
    │   ├── X
    │   │   ├── ea.xpm
    │   │   └── no.xpm
    │   └── Y
    │       ├── ea.xpm
    │       └── no.xpm

```
### Config of the game
You can change some params in ```includes/cub3d_bonus.h``` 
look at the ```Define player``` list, and just change the value you want!
- Screen values... stand for themselfs (just remember to change HALF_WIDTH to, if you change SCREEN_WIDTH)
- DIST_WALK define your "speed", basically. 
- SPEED_UP define the "run" multiplicator
- TURN_RATE define by how many degrees the player turn his head
- FPS_MAX cannot set the number of fps, only the limit you want (for unknown reason, it's up to you)
- SPHERE define the ray of the cylinder you "are" as a player, for wall's collisions

### Input will running the game

- use w,a,s,d for the player movement
- use left/right arrows to change the player's view's angle (in the x axis)
- use up/down arrows to change the player's view's angle (in the y axis)
- press shift to run
- use r to stay in a 'run' mode
- remember, multi-input enabled!

