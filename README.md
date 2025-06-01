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

Map parsing is the critical first phase of the cub3D engine, responsible for reading and validating the scene description file (`.cub`) to extract all necessary configuration data. The parsing algorithm follows a **sequential two-phase approach** that ensures data integrity before proceeding to the rendering phase.

#### Parsing Strategy Overview

The parser implements a **state-driven parsing algorithm** that processes the file in two distinct phases:

1. **Scene Description Parsing** - Extract environment configuration
2. **Map Data Parsing** - Process and validate the maze layout

#### Phase 1: Scene Description Parsing

The parser reads the file line by line, analyzing each line to determine its content type. During this phase, the system looks for **six mandatory elements** that must appear before the map data:

**Texture Path Extraction**: The parser identifies texture definition lines by their prefixes (`NO`, `SO`, `WE`, `EA`) and extracts the corresponding file paths. Each line is split on whitespace, validated to ensure it contains exactly two elements (the identifier and the path), and the path is stored for later texture loading.

**Color Configuration Processing**: Floor (`F`) and ceiling (`C`) color lines are parsed using a more complex algorithm. The system:
- Splits the line to isolate the RGB values string
- Validates the comma-separated format by counting separators
- Converts each RGB component to integer values
- Ensures all values fall within the valid range (0-255)

**Progress Tracking**: The parser maintains a counter (`data_count`) that increments with each successfully parsed element. This counter serves as a state indicator - when it reaches 6, the parser knows all required scene description elements have been found and switches to map parsing mode.

#### Phase 2: Map Data Processing

Once all scene description elements are identified, the remaining lines constitute the map data. The parser employs a **linked list collection strategy** to handle variable map sizes efficiently.

**Dynamic Map Collection**: The parser continues reading lines but now stores them in a linked list structure rather than processing them immediately. This approach allows for maps of any size without pre-allocation.

**Map Dimensioning Algorithm**: Before creating the final map structure, the parser calculates optimal dimensions by:
- Counting total lines for height determination
- Scanning all lines to find the maximum width
- Accounting for potential trailing newlines and whitespace

**Memory Layout Conversion**: The linked list is then converted to a 2D character array for efficient random access during gameplay. Each line is copied while preserving spatial relationships and padding shorter lines to maintain rectangular structure.

#### Map Validation System

The validation system implements a **multi-layered verification approach** with four critical validation stages:

**1. Structural Integrity Validation**
The parser first removes any leading empty lines while ensuring the map isn't entirely empty. It then scans through the remaining content to detect invalid empty lines within the map body, which would create undefined behavior during traversal.

**2. Character Set Validation and Player Detection**
The algorithm performs a comprehensive scan of every character in the map grid:
- **Character Validation**: Ensures only valid characters (`0`, `1`, `N`, `S`, `E`, `W`, ` `, `\n`) are present
- **Player Spawn Detection**: Identifies exactly one player starting position among the directional characters
- **Coordinate Calculation**: Converts the grid position to world coordinates using the tile size constant

The player position is calculated using the formula:
```
player.x = (grid_x * TILE_SIZE) + (TILE_SIZE / 2)
player.y = (grid_y * TILE_SIZE) + (TILE_SIZE / 2)
```

**3. Topological Enclosure Validation**
The most sophisticated validation ensures the map forms a closed, traversable space. The algorithm:
- Identifies all walkable spaces (empty areas and player positions)
- For each walkable cell, verifies that all four cardinal directions contain either walls or other valid spaces
- Prevents edge cases where players could "escape" the map boundaries
- Uses a **boundary checking algorithm** that considers map edges as implicit walls

**4. Resource Validation**
The final validation phase verifies that all referenced resources are valid:
- **File Extension Verification**: Ensures all texture paths point to `.xpm` files
- **Path Accessibility**: Basic validation that paths are properly formatted
- **Color Range Validation**: Confirms RGB values are within display range (0-255)

#### Data Structure Population Strategy

Upon successful validation, the parser populates the main engine data structures using a **hierarchical approach**:

- **Map Structure**: Contains the validated 2D grid, calculated dimensions, and player starting direction
- **Player Structure**: Holds precise spawn coordinates and initial orientation derived from the map character
- **Texture Registry**: Stores file paths as strings for deferred loading during graphics initialization
- **Environment Configuration**: RGB color arrays for efficient rendering calculations

#### Error Handling Philosophy

The parsing system employs a **fail-fast validation strategy** with descriptive error reporting:

- **Immediate Termination**: Any validation failure stops parsing immediately
- **Contextual Error Messages**: Specific feedback indicates exactly what validation failed
- **State Preservation**: Memory cleanup ensures no partial states persist after failures
- **Comprehensive Coverage**: Every possible malformation has a corresponding error case

This robust parsing architecture ensures that only perfectly valid, playable maps proceed to the rendering pipeline, eliminating runtime errors and undefined behavior during gameplay while providing clear feedback for map creation and debugging.

### Raycasting

#### What is raycasting?

Raycasting is a rendering technique used to create a 3D perspective in a 2D map. It is based on the projection of a 3D space onto a 2D plane. It is the same technique used in the famous game Wolfenstein 3D.

The principle is to cast a ray from the player's position in the direction of the view, and to calculate the distance between the player and the first wall encountered by the ray. This distance is then used to calculate the height of the wall to be displayed on the screen.

From a chosen field of view and a chosen resolution, we can calculate the angle between each ray. We can then cast a ray for each column of pixels on the screen and determine the height of the wall to be displayed in each column.

#### Required Information Per Frame

For each render frame, we need to know the following information:
- **Player's position** (`t_point coord` in `t_player`)
- **Player's orientation** (`float angle` in `t_player`)
- **Field of view** (constant for the whole game, defined as `FOV_ANGLE 60` degrees)
- **Screen resolution** (constant for the whole game, determined by window size)

#### The Raycasting Algorithm

For each ray cast (one per screen column), the following algorithm is implemented in our source files:

**1. Ray Direction Calculation** (`cast_all_rays()` in `raycasting.c`)

The angle of each ray is calculated using the player's viewing angle and the field of view:
```c
ray_angle = data->player.angle - atan((i - data->num_rays / 2) / data->distance_projection);
```

The ray direction flags are determined:
- `is_facing_up`: true if angle is between 0 and π
- `is_facing_left`: true if angle is between π/2 and 3π/2

**2. Horizontal Grid Line Intersection** (`horizontal_intercept()` in `ray_intercept.c`)

2.1. **First intersection calculation**: Find where the ray intersects horizontal grid lines
```c
ray->inter.y = floor(data->player.coord.y / TILE_SIZE) * TILE_SIZE;
if (!ray->is_facing_up)
    ray->inter.y += TILE_SIZE;
ray->inter.x = data->player.coord.x + (data->player.coord.y - ray->inter.y) / tan(ray->angle);
```

2.2. **Step calculation**: Determine incremental steps
```c
ray->step.y = TILE_SIZE * (ray->is_facing_up ? -1 : 1);
ray->step.x = TILE_SIZE / tan(ray->angle);
```

2.3. **Wall detection**: Step through grid lines until hitting a wall
```c
while (ray->inter.x > 0 && ray->inter.x < data->map.width * TILE_SIZE &&
       ray->inter.y > 0 && ray->inter.y < data->map.height * TILE_SIZE) {
    if (has_wall_at(data, ray->inter.x, ray->inter.y - ray->is_facing_up)) {
        ray->horz_hit_found = 1;
        set_point(&ray->horz_hit_coord, ray->inter.x, ray->inter.y);
        return;
    }
    ray->inter.x += ray->step.x;
    ray->inter.y += ray->step.y;
}
```

**3. Vertical Grid Line Intersection** (`vertical_intercept()` in `ray_intercept.c`)

The same algorithm is applied for vertical grid lines:
- Calculate first vertical intersection point
- Determine incremental steps
- Step through until hitting a wall

**4. Distance Comparison** (`get_shorter_distance()` in `raycasting.c`)

Calculate distances from player to both intersection points and choose the closest:
```c
if (ray->horz_hit_distance < ray->vert_hit_distance) {
    set_point(&ray->hit_coord, ray->horz_hit_coord.x, ray->horz_hit_coord.y);
    ray->hit_distance = ray->horz_hit_distance;
    ray->was_hit_horizontal = 1;
} else {
    set_point(&ray->hit_coord, ray->vert_hit_coord.x, ray->vert_hit_coord.y);
    ray->hit_distance = ray->vert_hit_distance;
}
```

**5. Fisheye Effect Correction** (`render_walls()` in `render_walls.c`)

To prevent the fisheye distortion effect, the perpendicular distance is calculated:
```c
data->rays[x].wall_distance = data->rays[x].hit_distance * cos(data->rays[x].angle - data->player.angle);
```

**6. Wall Height Projection**

The projected wall height on screen is calculated using the corrected distance:
```c
data->rays[x].projected_height = (TILE_SIZE / data->rays[x].wall_distance) * data->distance_projection;
```

**Why closer walls appear taller:**
- **Inverse relationship**: Wall height is inversely proportional to distance (`TILE_SIZE / wall_distance`)
- **Distance = 64 units**: Wall appears at full screen height
- **Distance = 128 units**: Wall appears at half screen height  
- **Distance = 256 units**: Wall appears at quarter screen height
- **Distance projection factor**: `data->distance_projection` is calculated as `(win_width/2) / tan(FOV/2)`, which maintains correct perspective scaling

**Screen positioning**: The wall is centered vertically on screen:
```c
texture_data.offset_y = (data->graph.win_height / 2) - ((int)data->rays[x].projected_height / 2);
texture_data.height = (data->graph.win_height / 2) + ((int)data->rays[x].projected_height / 2);
```

**7. Texture Selection** (`get_texture_to_render()` in `render_walls.c`)

Based on the ray direction and hit type, the appropriate texture is selected:
```c
if (ray->was_hit_horizontal) {
    if (ray->is_facing_up)
        return (data->graph.north_texture);  // North wall texture
    else
        return (data->graph.south_texture);  // South wall texture
} else {
    if (ray->is_facing_left)
        return (data->graph.west_texture);   // West wall texture
    else
        return (data->graph.east_texture);   // East wall texture
}
```

**8. Texture Mapping** (`get_color_x()` and `get_color_y()` in `get_color.c`)

The exact texture coordinates are calculated to map the 2D texture onto the 3D wall surface:

**Horizontal Texture Coordinate (X):**
```c
// For horizontal wall hits (hitting top/bottom of wall)
if (ray->was_hit_horizontal) {
    if (ray->is_facing_up)
        texture_data->color_x = ((int)ray->hit_coord.x % TILE_SIZE) * (texture.width / TILE_SIZE);
    else
        texture_data->color_x = (TILE_SIZE - 1 - ((int)ray->hit_coord.x % TILE_SIZE)) * (texture.width / TILE_SIZE);
}
// For vertical wall hits (hitting left/right side of wall)
else {
    if (ray->is_facing_left)
        texture_data->color_x = (TILE_SIZE - 1 - ((int)ray->hit_coord.y % TILE_SIZE)) * (texture.width / TILE_SIZE);
    else
        texture_data->color_x = ((int)ray->hit_coord.y % TILE_SIZE) * (texture.width / TILE_SIZE);
}
```

- **Purpose**: Determines which vertical slice of the texture to use
- **Calculation**: Uses the remainder of the hit position within the tile (`% TILE_SIZE`)
- **Scaling**: Multiplies by texture width ratio to map tile coordinates to texture coordinates
- **Direction handling**: Reverses texture for certain orientations to maintain consistent lighting

**Vertical Texture Coordinate (Y):**
```c
ray->distance_from_top = ray->y + ((int)ray->projected_height / 2) - (data->graph.win_height / 2);
texture_data->color_y = ray->distance_from_top * ((float)texture.height / ray->projected_height);
```

- **Purpose**: Determines which horizontal slice of the texture to use for each screen pixel
- **Screen mapping**: `distance_from_top` calculates how far the current pixel is from the top of the wall
- **Texture scaling**: The ratio `(texture.height / ray->projected_height)` scales the texture to fit the projected wall height
- **Stretching behavior**: 
  - Close walls: Texture appears normal size
  - Far walls: Texture is compressed vertically
  - Very close walls: Texture is stretched, showing only a portion of the full texture

**Texture Sampling:**
```c
return (*(int *)(texture.addr + (texture_data->color_y * texture.line_len + 
                texture_data->color_x * (texture.bpp / 8))));
```

This directly reads the pixel color from the texture image data at the calculated coordinates.

**9. Pixel Rendering**

For each pixel column, the texture is sampled and drawn to the screen buffer using the calculated coordinates and selected texture.

#### Implementation Details

- **Grid-based collision detection**: The world is divided into uniform tiles (`TILE_SIZE`)
- **DDA-like algorithm**: Digital Differential Analyzer approach for efficient ray-grid intersection
- **Texture caching**: Wall textures are pre-loaded and stored in `t_img` structures
- **Performance optimization**: Only one ray per screen column is cast (typically 640-1920 rays per frame)
- **Memory management**: Ray data is stored in a dynamically allocated array (`t_ray *rays`)

This implementation provides real-time 3D rendering performance while maintaining the authentic retro aesthetic of early 3D games.

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