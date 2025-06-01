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
English version [here](https://github.com/abrisse16/42-subjects/blob/09a9091d4d9e0df1aca78dc66a9320e357b90008/common_core/cub3d/en.subject.pdf)
<br>
French version [here](https://github.com/abrisse16/42-subjects/blob/09a9091d4d9e0df1aca78dc66a9320e357b90008/common_core/cub3d/fr.subject.pdf)

</div>

---

## Table of contents

- [The project](#the-project)
	- [Project Objectives](#project-objectives)
	- [Display & Rendering](#display--rendering)
	- [Controls](#controls)
	- [Scene Description File (.cub)](#scene-description-file-cub)
		- [Required Elements](#required-elements)
		- [Map Requirements](#map-requirements)
	- [Bonus Features](#bonus-features)
- [How it Works](#how-it-works)
	- [Map parsing](#map-parsing)
	- [Raycasting](#raycasting)
- [Usage](#usage)
	- [Requirements](#requirements)
	- [Installation](#installation)
	- [Running the Game](#running-the-game)
- [Troubleshooting](#troubleshooting)
- [Resources, documentation and references](#resources-documentation-and-references)


## The project

**cub3D** is a 3D raycasting engine inspired by the legendary **Wolfenstein 3D** (1992), the first true First-Person Shooter in gaming history. Developed by the iconic duo John Carmack and John Romero at Id Software, Wolfenstein 3D revolutionized gaming and paved the way for classics like Doom, Duke Nukem 3D, and Quake.

In this project, we have to build a "realistic" 3D graphical representation of a maze from a first-person perspective. We to use **raycasting technique**, which is the same technique used in the original Wolfenstein 3D game, to render the maze in real-time.

### Project Objectives

Beyond creating a functional raycaster, this project aims to strengthen your skills in:
- **Rigorous C programming** following 42's coding standards
- **Mathematical algorithms** for 3D projection and collision detection  
- **Graphics programming** with MiniLibX (42's simplified graphics library) for window management, texture rendering, and event handling
- **Memory management** with proper allocation and deallocation
- **File parsing** and error handling for complex configuration files

### Display & Rendering

The program creates a dynamic 3D view inside a window where players can navigate through a maze. Key rendering features include:

- **Real-time 3D perspective** using raycasting algorithms
- **Directional wall textures** that change based on wall orientation (North, South, East, West)
- **Customizable floor and ceiling colors** defined in RGB format
- **Smooth window management** supporting minimize, resize, and window switching
- **Texture mapping** using XPM image files for authentic retro aesthetics

### Controls

Navigate through the maze using intuitive keyboard controls:
- **Arrow Keys** (`←` / `→`) : Rotate camera left and right
- **Movement Keys** (`W` / `A` / `S` / `D`) : Move forward, strafe left, backward, and strafe right
- **Escape Key** (`ESC`) : Exit the program cleanly
- **Window Close** (❌) : Close window and quit program
- **Minimap Toggle** (`M`) : Show/hide minimap overlay *(bonus feature)*

### Scene Description File (.cub)

The program accepts a scene description file with `.cub` extension containing all maze configuration:

#### Required Elements:
- **Wall Textures**: Four XPM texture files for each cardinal direction
  ```
  NO ./assets/walls/north_texture.xpm    # North wall texture
  SO ./assets/walls/south_texture.xpm    # South wall texture
  WE ./assets/walls/west_texture.xpm     # West wall texture
  EA ./assets/walls/east_texture.xpm     # East wall texture
  ```

- **Environment Colors**: RGB values (0-255) for floor and ceiling
  ```
  F 220,100,0    # Floor color (Orange)
  C 135,206,235  # Ceiling color (Sky Blue)
  ```

- **Map Layout**: 2D grid using 6 possible characters:
  - `0` : Empty space (walkable area)
  - `1` : Wall (solid barrier)
  - `N` / `S` / `E` / `W` : Player starting position and initial orientation

#### Map Requirements:
- Must be **completely surrounded by walls** (closed maze)
- **Exactly one player spawn point** must be defined
- **Flexible formatting** with spaces as valid map characters
- **Robust parsing** handling various spacing and line arrangements
- **Comprehensive error handling** for invalid configurations

### Bonus Features

Enhanced gameplay features include:
- **Wall collision detection** for realistic movement
- **Interactive minimap system** showing player position and maze layout


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

> **Note**: This project is designed to work on **Linux systems only**. It uses the Linux version of the MiniLibX library provided by 42 and will not work on macOS or Windows without modifications.

### Requirements

The following dependencies are required to compile and run the project:

- gcc
- make
- X11 include files (package xorg)
- XShm extension (package libxext-dev)
- BSD utility functions (package libbsd-dev)
- zlib1g-dev (for image handling)

You can install all the required dependencies with the following command (Debian/Ubuntu):

```sh
sudo apt-get update && sudo apt-get install gcc make xorg libxext-dev libbsd-dev zlib1g-dev
```

### Installation

Clone this repository:

```sh
git clone https://github.com/abrisse16/42-cub3d.git path/to/repository
```

In your local repository, run `make` to compile the project:

```sh
cd path/to/repository
make
```

### Running the Game

To run `cub3d`, use the following command:

```sh
./cub3d <map_file.cub>
```

Example:
```sh
./cub3d maps/map.cub
```

The game supports various map files with the `.cub` extension. Make sure your map file follows the format described in the [Description file](#description-file) section.

#### Color Format in .cub Files

For the floor and ceiling colors in the map description file, use the RGB format (0-255 for each component):
```
F 220,100,0    # Floor color (RGB)
C 225,30,0     # Ceiling color (RGB)
```

## Troubleshooting

If you encounter any issues while compiling or running the project, please check the following:

- **Compilation Errors**: Ensure that you have installed all the required dependencies listed in the [Requirements](#requirements) section. Use your package manager to install any missing libraries.
- **Segmentation Faults**: Usually related to map parsing issues, invalid textures files, or memory management errors. Check your map file follows the format specified in the [Description file](#description-file) section and the texture files are in valid XPM format.
- **Black Screen**: Check that your textures are correctly specified in the `.cub` file and that the paths to the texture files are correct. Ensure that the textures are in XPM format and are accessible by the program.
- **MiniLibX Errors**: This project uses the Linux version of MiniLibX, so it may not work with the macOS version.

## Resources, documentation and references

- [42 MiniLibX](https://github.com/42paris/minilibx-linux) - Linux version of the 42 MiniLibX library

---
<div align=center>
	<a href="mailto:abrisse@student.42.fr">abrisse@student.42.fr</a>
</div>