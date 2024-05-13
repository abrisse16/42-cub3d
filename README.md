<div align=center>

# cub3D

### 42 Common Core / circle #4
<i>Our first RayCaster with MiniLibX
<br>
This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever.</i>

##

### Final grade
[![abrisse's 42 cub3d Score](https://badge.nimon.fr/api/v2/clw51aj8x026501rzp5ef4x2f/project/3105810)](https://github.com/Nimon77/badge42)

### Subject
English version [here](https://github.com/abrisse16/42-subjects/blob/7385a594afd19b06ab40ed62b5e8c818d2d8bd21/cub3d-subject-v10.en.pdf)
<br>
French version [here](https://github.com/abrisse16/42-subjects/blob/7385a594afd19b06ab40ed62b5e8c818d2d8bd21/cub3d-subject-v10.fr.pdf)

</div>

---

## Table of contents

- [The project](#the-project)
	- [Display](#display)
	- [Controls](#controls)
	- [Description file](#description-file)
- [How it Works](#how-it-works)
	- [Map parsing](#map-parsing)
	- [Raycasting](#raycasting)
- [Usage](#usage)
- [Resources, documentation and references](#resources-documentation-and-references)


## The project

In this project, we have to create a 3D representation of a maze from a first person perspective. We have to use the raycasting technique, which is the same technique used in the famous game Wolfenstein 3D.

### Display

The program must display a dynamic view inside a window, and the player must be able to move inside the maze.
We must be able to display different textures on the walls that vary depending on the orientation of the wall (North, South, East, West) and set a different color for the floor and the ceiling.

### Controls

The player must be able to move inside the maze using the keyboard. The following controls must be implemented :
- `Left` and `Right` arrow keys : rotate the camera left and right
- `W` and `S` keys : move forward and backward
- `A` and `D` keys : strafe left and right
- `ESC` key : quit the program
- `M` key : show/hide the minimap (bonus)

### Description file

The program must take as argument a description file with the `.cub` extension. This file contains all the information needed to generate the maze and the textures.

It must contain the following elements :
- The path to the `.xpm` files for the textures of the walls. There must be 4 different textures, one for each orientation of the walls.
- The colors of the floor and the ceiling in RGB format.
- The map, surrounded by walls and composed of only 6 possible characters :
	- `0` : empty space
	- `1` : wall
	- `N`, `S`, `E` or `W` : player starting position and spawning orientation


## How it Works

### Map parsing

<p align=center>
	🚧 UNDER CONSTRUCTION 🚧
</p>

### Raycasting

What is raycasting ?

Raycasting is a rendering technique used to create a 3D perspective in a 2D map. It is based on the projection of a 3D space onto a 2D plane. It is the same technique used in the famous game Wolfenstein 3D.
The principle is to cast a ray from the player's position in the direction of the view, and to calculate the distance between the player and the first wall encountered by the ray. This distance is then used to calculate the height of the wall to be displayed on the screen.
From a chosen field of view and a chosen resolution, we can calculate the angle between each ray. We can then cast a ray for each column of pixels on the screen and determine the height of the wall to be displayed in each column.


For each render frame, we need to know the following information :
- The player's position
- The player's orientation
- The field of view, constant for the whole game
- The resolution of the screen, constant for the whole game

With that, for each ray, we can use the following algorithm.

1. Determine the angle of the ray. The angle is determined by the orientation of the player and the field of view. This information permits to determine if the ray is going to intersect the faces north or south of the wall or the faces east or west of the wall.

2. Determine the coordinates of the first horizontal intersection of the ray with a wall.

	2.1. Determine the coordinates of the first horizontal intersection of the ray with the horizontal grid lines of the map.
	
	2.2. Determine the horizontal (x) and vertical (y) step of the intersection of the ray and horizontal grid lines of the map.

	2.3. Until the coordinates of the intersection is not a wall, add the step to the coordinates of the intersection.

3. Determine the coordinates of the first vertical intersection of the ray with a wall, using the same algorithm as for the horizontal intersection.

At this point, we have the coordinates of the intersection of the ray with the first horizontal face of the wall and the coordinates of the intersection of the ray with the first vertical face of the wall.

5. Determine the distance between the player and each intersection. Determine which intersection is the closest to the player.

6. Determine the height of the wall to be displayed on the screen. The height is determined by the distance between the player and the intersection. The closer the intersection is to the player, the higher the wall will be displayed on the screen.

7. Knowing the ray angle and if the ray intersects the horizontal or vertical faces of the wall, we can determine which texture to display on the wall.

<p align=center>
	🚧 UNDER CONSTRUCTION 🚧
</p>

## Usage

Clone this repository :

```sh
git clone https://github.com/abrisse16/42-minishell.git path/to/repository
```

In your local repository, run `make`

To run `cub3d`, use the following command :

```sh
./cub3d <map_file.cub>
```

## Resources, documentation and references


---
<div align=center>
	<a href="mailto:abrisse@student.42.fr">abrisse@student.42.fr</a>
</div>