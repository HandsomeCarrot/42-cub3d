# cub3D

A 3D maze game built with raycasting techniques, inspired by Wolfenstein 3D. This project was developed as part of the 42 school curriculum to explore fundamental computer graphics concepts including raycasting, texture mapping, and real-time rendering.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Map Format](#map-format)
- [Controls](#controls)
- [Work Distribution](#work-distribution)
- [Technical Details](#technical-details)

## Overview

cub3D renders a 3D perspective inside a maze using raycasting. The player navigates through the environment with textured walls, customizable floor and ceiling colors, and smooth movement mechanics including collision detection.

## Features

- **Raycasting Engine**: Real-time 3D rendering using DDA (Digital Differential Analysis) algorithm
- **Texture Mapping**: Wall textures with proper perspective correction
- **Movement System**:
  - WASD movement with smooth collision detection
  - Arrow key rotation
  - Sprint functionality (hold Shift)
- **Minimap**: Real-time overhead view with player position and orientation
- **Map Parsing**: Robust `.cub` file parser with comprehensive error handling
- **Collision Detection**: Radius-based wall collision with smooth sliding

## Installation

### Prerequisites
- GCC or Clang compiler
- Make
- MiniLibX (included in project)
- Linux/Unix system (X11 required, for MLX)

### Build
```bash
# Clone the repository
git clone https://github.com/HandsomeCarrot/42-cub3d.git
cd 42-cub3d

# Compile the project
make

# Run with a map file
./cub3d assets/maps/valid/basic.cub
```

### Build Targets
```bash
make        # Build the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Rebuild everything
make run    # Build and run with default map
```

## Usage

```bash
./cub3d [map_file.cub]
```

Example:
```bash
./cub3d assets/maps/valid/basic.cub
```

## Map Format

Maps are defined in `.cub` files with the following structure:

```
NO ./assets/textures/xpm/wood.xpm
SO ./assets/textures/xpm/metal.xpm
WE ./assets/textures/xpm/brick.xpm
EA ./assets/textures/xpm/stone.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111110111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N01
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Map Elements
- `NO`, `SO`, `WE`, `EA`: North, South, West, East wall textures (`.xpm` files)
- `F`: Floor color (RGB: 0-255)
- `C`: Ceiling color (RGB: 0-255)
- `1`: Wall
- `0`: Empty space
- `N`, `S`, `E`, `W`: Player starting position and orientation

## Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` / `→` | Rotate camera |
| `Shift` | Sprint (hold) |
| `ESC` | Exit game |

## Work Distribution

This project was a collaborative effort between **Viktor (HandsomeCarrot)** and **Hamza (hamza-salihovic)**. Here's how we divided the work:

### Viktor's Responsibilities
- **Map Parsing System** (Complete parsing module)
  - `.cub` file validation and parsing
  - Texture path extraction and validation
  - RGB color parsing for floor/ceiling
  - Map layout validation (closed walls, valid characters)
  - Player position detection and validation
  - Comprehensive error handling and logging
- **Project Infrastructure**
  - Makefile setup with color-coded logging
  - Build system and dependency management
  - Logging system with multiple log levels
  - Memory management and cleanup functions
  - Test suite for map validation
- **Code Integration**
  - Module connection between parsing and raycaster
  - Data structure design and definitions
  - Header organization and includes

### Hamza's Responsibilities
- **Raycasting Engine** (Complete rendering system)
  - DDA algorithm implementation for ray casting
  - Wall intersection and distance calculations
  - Texture mapping and rendering
  - Column rendering with proper height calculation
- **Player Movement and Controls**
  - WASD movement system
  - Rotation mechanics (keyboard/mouse)
  - Collision detection (radius-based)
  - Sprint functionality
  - Smooth movement with sliding
- **Minimap System**
  - Overhead view rendering
  - Player position visualization
  - Ray visualization on minimap
  - Scaling and positioning
- **Graphics Setup**
  - MiniLibX initialization
  - Image buffer management
  - Hook system setup
  - Frame rendering loop

## Technical Details

### Raycasting Algorithm
The engine uses the DDA (Digital Differential Analysis) algorithm to cast rays from the player's position and detect wall intersections. Each vertical stripe of the screen represents one ray cast into the scene.

### Key Components

#### Parsing Module (`src/parsing/`)
- **Config Parsing**: Extracts texture paths and colors
- **Map Parsing**: Validates and loads map layout
- **Player Initialization**: Detects spawn point and orientation
- **Validation**: Ensures maps are enclosed and properly formatted

#### Raycaster Module (`src/raycaster/`)
- **Ray Casting**: DDA implementation for wall detection
- **Texture Mapping**: Retrieves correct texture pixels based on wall hit position
- **Rendering**: Draws vertical slices with proper perspective
- **Movement**: Handles player input and collision

#### Data Structures
```c
typedef struct s_game {
    t_mlx       mlx;            // MiniLibX context
    t_player    player;         // Player position and direction
    char        **map;          // Map layout
    int         floor_color;    // Floor RGB
    int         ceiling_color;  // Ceiling RGB
    int         map_width;
    int         map_height;
} t_game;
```

### Performance Optimizations
- Efficient texture lookup with bytes-per-pixel calculation
- Minimized division operations in rendering loop
- Pre-calculated delta distances for DDA
- Optimized collision detection with radius checks

## Project Structure
```
42-cub3d/
├── assets/
│   ├── maps/          # Test maps (valid/invalid)
│   └── textures/      # Wall texture files (.xpm)
├── include/           # Header files
│   ├── cub3d.h
│   ├── common/
│   ├── parsing/
│   └── raycaster/
├── src/
│   ├── cleanup/       # Memory management
│   ├── logging/       # Debug logging system
│   ├── parsing/       # Map and config parsing
│   └── raycaster/     # Rendering engine
├── libft/             # Custom C library
└── Makefile
```

## Resources

- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)

## Authors

- **Viktor** ([HandsomeCarrot](https://github.com/HandsomeCarrot)) - Parsing, infrastructure, integration
- **Hamza** ([hamza-salihovic](https://github.com/hamza-salihovic)) - Raycasting engine, movement, minimap
