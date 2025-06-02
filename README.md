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

1. **Scene Description Parsing** - Extract texture paths and color configurations
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
player_x = (grid_x * TILE_SIZE) + (TILE_SIZE / 2)
player_y = (grid_y * TILE_SIZE) + (TILE_SIZE / 2)
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

- **Map Structure** (`t_map`): Contains the validated 2D grid, calculated dimensions, and player starting direction
- **Player Structure** (`t_player`): Holds precise spawn coordinates and initial orientation derived from the map character
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

Raycasting is a rendering technique that creates the illusion of 3D perspective from a 2D map by projecting a 3D space onto a 2D plane. This is the same foundational technique that powered the famous Wolfenstein 3D, creating the first-person shooter genre.

The core principle involves casting virtual rays from the player's position across their field of view and calculating distances to walls. These distances are then used to determine the height at which walls should appear on screen, creating the perspective effect where closer objects appear larger and distant objects appear smaller.

#### The Fundamental Algorithm

Raycasting operates on a **column-by-column rendering strategy**. For each vertical column of pixels on the screen, a single ray is cast from the player's position. The intersection distance of this ray with the nearest wall determines the height of the wall column to be rendered.

#### Core Rendering Concepts

**Perspective Projection Mathematics**: The algorithm relies on the inverse relationship between distance and apparent size. A wall at distance `d` appears with height proportional to `1/d`, creating natural perspective scaling.

**Field of View Distribution**: Rays are distributed across the player's field of view (typically 60 degrees) with each ray corresponding to one screen column. The angular spacing between rays is calculated as `FOV / screen_width`.

**Grid-Based World Representation**: The game world is represented as a uniform grid where each cell is either empty (walkable) or contains a wall. This discrete representation simplifies collision detection and ray intersection calculations.

#### The DDA Algorithm Foundation

The raycasting implementation is built upon the **Digital Differential Analysis (DDA) algorithm**, a highly efficient method for determining which grid squares a line traverses. Originally developed for rasterizing lines on pixel grids, DDA is perfectly suited for raycasting because it guarantees that **every wall the ray encounters will be detected** without missing any intersections.

**Why DDA Over Naive Ray Tracing?**

Traditional ray tracing approaches use fixed step sizes, advancing the ray by a constant distance at each iteration. However, this method has critical flaws:

- **Wall Penetration Risk**: If the step size is too large, rays can pass completely through thin walls without detection
- **Precision vs Performance Trade-off**: Smaller step sizes reduce miss probability but dramatically increase computational cost
- **Infinite Precision Requirement**: Perfect accuracy would require infinitely small steps, making the approach computationally impossible

**The DDA Solution**

DDA eliminates these problems by **adapting step sizes dynamically** based on the grid structure. Instead of using constant increments, the algorithm calculates the exact distance to the next grid line intersection, ensuring:

- **Zero Miss Rate**: Every wall intersection is mathematically guaranteed to be detected
- **Optimal Efficiency**: Only the minimum necessary calculations are performed
- **Perfect Precision**: Wall hits are detected at their exact intersection points

**Grid-Line Intersection Strategy**

The algorithm operates on the principle that walls in a grid-based world always align with grid boundaries. Therefore, any ray-wall collision must occur at either:
- **Horizontal grid lines** (boundaries between vertically adjacent cells)
- **Vertical grid lines** (boundaries between horizontally adjacent cells)

By stepping from grid line to grid line rather than using arbitrary increments, DDA ensures comprehensive wall detection while maintaining computational efficiency.

#### The Nine-Step Raycasting Process

**1. Ray Direction Calculation**
For each screen column, the corresponding ray angle is computed relative to the player's viewing direction. The algorithm distributes rays evenly across the field of view, with the central ray aligned with the player's facing direction.

**Ray Angle Calculation:**
```
ray_angle = player_angle - atan((column_index - screen_width / 2) / distance_projection)

where:
distance_projection = (screen_width / 2) / tan(FOV / 2)
```

This formula ensures that:
- Central rays align with the player's viewing direction
- Edge rays create the proper field of view spread
- Angular distribution maintains perspective consistency

**2. Directional Analysis**
Each ray's trajectory is analyzed to determine its cardinal direction components using trigonometric evaluation. This determines whether the ray is traveling upward/downward and leftward/rightward, which influences both the intersection algorithm and texture selection logic.

**Direction Determination Formulas:**
```
is_facing_up = (ray_angle > 0 && ray_angle < PI)
is_facing_left = (ray_angle > PI/2 && ray_angle < 3*PI/2)
```

**3. Horizontal Grid Intersection Algorithm**
The algorithm employs a **DDA-based grid-stepping technique** to find where the ray intersects horizontal grid lines. This approach implements the core DDA principle by calculating exact distances to grid boundaries rather than using fixed step sizes.

Starting from the player position, the algorithm:
1. **Identifies the first horizontal grid line** the ray will cross based on the ray's direction
2. **Calculates the exact intersection point** using trigonometric relationships
3. **Determines optimal step sizes** to jump precisely from one grid line to the next
4. **Iteratively steps along grid boundaries** until hitting a wall or reaching map limits

**Why This Approach Works:**
- **Guaranteed Detection**: Since walls align with grid boundaries, checking every grid line intersection ensures no walls are missed
- **Adaptive Stepping**: Step sizes automatically adjust to the ray's angle, maintaining efficiency across all directions
- **Mathematical Precision**: Intersections are calculated exactly, not approximated through sampling

The stepping process uses **trigonometric relationships** to determine both the intersection points and the incremental steps needed to move from one grid line to the next.

**Horizontal Intersection:**

*First Intersection Point:*
```
first_y = floor(player_y / TILE_SIZE) * TILE_SIZE
if (!is_facing_up) first_y += TILE_SIZE

first_x = player_x + (player_y - first_y) / tan(ray_angle)
```

*Incremental Steps:*
```
step_y = TILE_SIZE * (is_facing_up ? -1 : 1)
step_x = TILE_SIZE / tan(ray_angle)
```

*Next Intersection Points:*
```
next_x = current_x + step_x
next_y = current_y + step_y
```

**4. Vertical Grid Intersection Algorithm**
A parallel DDA process calculates intersections with vertical grid lines using analogous trigonometric relationships. This dual-axis approach ensures complete coverage of all possible wall intersections.

**Vertical Intersection:**

*First Intersection Point:*
```
first_x = floor(player_x / TILE_SIZE) * TILE_SIZE
if (!is_facing_left) first_x += TILE_SIZE

first_y = player_y + (player_x - first_x) * tan(ray_angle)
```

*Incremental Steps:*
```
step_x = TILE_SIZE * (is_facing_left ? -1 : 1)
step_y = TILE_SIZE * tan(ray_angle)
```

**DDA Intersection Strategy:**
The algorithm simultaneously traces both horizontal and vertical grid line intersections, creating two potential collision points for each ray. This dual-tracking approach is fundamental to DDA's reliability:

- **Horizontal Stepping**: Detects walls that form the top/bottom boundaries of grid cells
- **Vertical Stepping**: Detects walls that form the left/right boundaries of grid cells
- **Comprehensive Coverage**: Together, these ensure every possible wall orientation is detected

The closest intersection from either stepping process determines the final wall hit, guaranteeing that the ray stops at the first wall it encounters regardless of the wall's orientation within the grid.

**5. Distance Comparison and Selection**
The algorithm compares the distances from the player to both intersection points and selects the closer collision:

**Distance Calculation Formulas:**
```
horizontal_distance = sqrt[(hit_x - player_x)^2 + (hit_y - player_y)^2]
vertical_distance = sqrt[(hit_x - player_x)^2 + (hit_y - player_y)^2]

hit_distance = min(horizontal_distance, vertical_distance)
```

This determines both the final ray distance and whether the ray hit a horizontal or vertical wall face, which is crucial for texture selection.

**6. Fisheye Distortion Correction**
Raw ray distances create a **fisheye effect** where walls appear curved at screen edges. The algorithm corrects this by calculating the **perpendicular distance** to the wall plane rather than the direct ray distance. This correction uses the cosine of the angle difference between the ray and the player's forward direction.

**Mathematical correction formula:**
```
corrected_distance = hit_distance × cos(ray_angle - player_angle)
```

This correction eliminates the barrel distortion that would otherwise make straight walls appear curved.

**7. Wall Height Projection**
The corrected distance is converted to screen space using **perspective projection**. The algorithm calculates how tall the wall should appear on screen based on its distance from the viewer.

**Wall Height Formula:**
```
projected_height = (TILE_SIZE / corrected_distance) × distance_projection

where:
distance_projection = (screen_width / 2) / tan(FOV / 2)
```
**Projection relationship:**
- **Closer walls** (small distance): Appear taller, potentially filling the entire screen height
- **Distant walls** (large distance): Appear shorter, creating depth perception
- **Projection scaling factor**: Maintains consistent perspective across different screen resolutions

The wall is positioned to be vertically centered on the screen, with its height extending equally above and below the horizon line.

**8. Texture Selection Strategy**
Based on the intersection analysis, the algorithm determines which wall face was hit. The **directional selection logic** works as follows:

- **Horizontal hits**: Determine if the ray hit the top or bottom of a wall cell
- **Vertical hits**: Determine if the ray hit the left or right side of a wall cell
- **Texture mapping**: Each cardinal direction (North, South, East, West) corresponds to a specific texture

This creates **directional lighting effects** where different wall faces can have different appearances, enhancing visual depth.

**9. Texture Coordinate Mapping**
The algorithm maps 2D texture coordinates onto the 3D wall surface using **parametric coordinate transformation**:

**Horizontal Texture Coordinate (X-axis) Formulas:**

*For Horizontal Wall Hits:*
```
if (is_facing_up)
	texture_x = (hit_x % TILE_SIZE) × (texture_width / TILE_SIZE)
else
	texture_x = (TILE_SIZE - 1 - (hit_x % TILE_SIZE)) × (texture_width / TILE_SIZE)
```

*For Vertical Wall Hits:*
```
if (is_facing_left)
	texture_x = (TILE_SIZE - 1 - (hit_y % TILE_SIZE)) × (texture_width / TILE_SIZE)
else
	texture_x = (hit_y % TILE_SIZE) × (texture_width / TILE_SIZE)
```

**Vertical Texture Coordinate (Y-axis) Formulas:**

*Screen-to-Texture Mapping:*
```
distance_from_top = current_pixel_y - (projected_height / 2) - (screen_height / 2)
texture_y = distance_from_top × (texture_height / projected_height)
```

*Ensuring Valid Texture Bounds:*
```
texture_y = max(0, min(texture_height - 1, texture_y))
```

**Texture Sampling Formula:**
```
pixel_color = texture_data[texture_y × texture_width + texture_x]
```

**Coordinate Mapping Logic:**
- **Horizontal Mapping**: Determines which vertical slice of the texture to display based on the exact hit position within the wall cell
- **Vertical Mapping**: For each screen pixel in the wall column, calculates the corresponding texture row
- **Dynamic scaling**: Texture coordinates adapt to wall distance, ensuring proper stretching/compression

**Texture Sampling and Rendering**: The final step reads the appropriate pixel color from the texture image data and writes it to the screen buffer.

#### Performance Optimization Strategies

**Single Ray Per Column**: Instead of casting multiple rays per pixel, the algorithm casts exactly one ray per screen column, significantly reducing computational overhead while maintaining visual quality.

**Grid-Aligned Calculations**: By aligning the world to a regular grid, intersection calculations become more efficient and predictable.

**Incremental Stepping**: Rather than testing every possible intersection point, the algorithm uses calculated step sizes to jump efficiently between grid lines.

**Pre-computed Trigonometry**: Angle-based calculations are optimized through lookup tables or pre-computed values where possible.

#### Visual Quality Enhancements

**Texture Filtering**: The coordinate mapping system ensures smooth texture appearance across different distances and viewing angles.

**Consistent Perspective**: The mathematical correction algorithms maintain realistic perspective scaling across the entire field of view.

This raycasting implementation delivers **real-time 3D rendering performance** while maintaining the authentic retro aesthetic that defined early 3D gaming. The algorithm balance computational efficiency with visual quality, creating an immersive first-person experience from a fundamentally 2D world representation.

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