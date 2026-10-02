*This project has been created as part of the 42 curriculum by vpoka, hasaliho.*

# cub3D

A real-time 3D maze game rendered with raycasting, inspired by Wolfenstein 3D.

## Description

cub3D is a small first-person maze explorer that draws its 3D view with raycasting — the same trick used by Wolfenstein 3D. Instead of a real 3D engine, it casts one ray per screen column, finds where the ray hits a wall, and draws a textured vertical slice scaled by distance. The result is a smooth 3D-looking scene written in plain C with MiniLibX.

The project exists as a 42 graphics assignment: a hands-on way to learn how early-90s engines rendered 3D worlds, and to practice parsing, math, and event-driven C programming.

Features:

- DDA raycasting engine with textured walls and distance scaling
- Configurable floor and ceiling colors
- WASD movement, arrow-key rotation, sprint, and collision detection
- Real-time minimap with player position and orientation
- `.cub` map parser with validation and error reporting
- Rebuild-time log levels for debugging

## Instructions

### Prerequisites

- C compiler (`cc`, GCC or Clang)
- `make`
- MiniLibX installed system-wide (the project links `-lmlx`; it is not bundled in the repository)
- X11 development libraries (`libX11`, `libXext`)
- Linux/Unix

### Build

```bash
git clone https://github.com/HandsomeCarrot/42-cub3d.git
cd 42-cub3d
make
```

### Build targets

| Target | Effect |
|--------|--------|
| `make` | Build the project |
| `make run` | Rebuild and run with `assets/maps/valid/basic.cub` |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and the executable |
| `make re` | Rebuild everything |
| `make error` / `warning` / `info` / `debug` | Rebuild with `LOGGING_LEVEL` 0–3 |

### Usage

The program takes exactly one argument: a `.cub` map file.

```bash
./cub3d <map_file.cub>
```

Example:

```bash
./cub3d assets/maps/valid/basic.cub
```

### Map format

Maps are defined in `.cub` files: a small header followed by the map layout. Example (from `assets/maps/valid/basic.cub`):

```
NO ./assets/textures/xpm/Wood_128.xpm
SO ./assets/textures/xpm/Metal_128.xpm
WE ./assets/textures/xpm/Futuristic_128.xpm
EA ./assets/textures/xpm/Stone_128.xpm

F 220,100,0
C 225,30,0

111111   111111
100011   100001
101011111100001
1011000N0001101
100001111110101
100001   110001
111111   111111
```

Map elements:

- `NO`, `SO`, `WE`, `EA`: North, South, West, East wall textures (`.xpm` files)
- `F`: Floor color (RGB, 0–255)
- `C`: Ceiling color (RGB, 0–255)
- `1`: Wall
- `0`: Empty space
- `N`, `S`, `E`, `W`: Player start position and orientation

Rules (enforced by the parser):

- The map must be closed/surrounded by walls; otherwise the program exits with an error.
- Spaces are valid parts of the map.
- Except for the map content, elements may appear in any order and be separated by empty lines; the map must always be last.
- On any misconfiguration the program exits cleanly and prints an explicit error message to stderr.

Sample maps live in `assets/maps/valid/` and `assets/maps/invalid/` (the latter for testing the parser).

### Controls

| Key | Action |
|-----|--------|
| `W` / `↑` | Move forward |
| `S` / `↓` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` / `→` | Rotate camera |
| `Shift` (hold) | Sprint |
| `ESC` | Quit |

Clicking the window's close button also quits cleanly.

## Resources

- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Raycasting tutorial by Lode Vandevenne](https://lodev.org/cgtutor/raycasting.html)

### AI usage

AI was used by vpoka for commit messages, documentation and this README.

## Project structure

```
cub3d/
├── assets/
│   ├── maps/          # Sample maps (valid/ and invalid/)
│   └── textures/      # Wall textures (.xpm)
├── include/           # Headers (common/, parsing/, raycaster/)
├── src/
│   ├── cleanup/       # Memory management
│   ├── logging/       # Debug logging system
│   ├── parsing/       # .cub config, map parsing and validation
│   ├── raycaster/     # Rendering, movement, minimap
│   └── main.c
├── libft/             # Custom C library (incl. get_next_line)
└── Makefile
```

## Status

Finished — 100/100 points.

## Credits

- vpoka — parsing, infrastructure, integration
- hasaliho — raycasting engine, movement, minimap
