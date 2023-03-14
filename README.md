<h1 align="center">
	🕹️Cub3D
 42cursus project🕹️
</h1>



<p align="center">
<img align="center" src="https://user-images.githubusercontent.com/40967731/225049319-46642cea-374a-40a3-9e4f-dfed374fceee.png" width="800" height="400">
</p>

<h3 align="center">
	<a href="#about">About</a>
	<span> · </span>
	<a href="#projetstructure"> Project Structure </a>
	<span> · </span>
	<a href="#setting">Setting</a>
	<span> · </span>
	<a href="#usage">Usage</a>
</h3>

<h2 id="about">
About
</h2>

> The goal is to create a 3D graphic representation of a ***labyrinth*** in first person view using the principles of **ray-casting**.

<h2 id="projetstructure">
Project Structure
</h2>

```
.
├── 📁include/
│   └── *.h
├── 📁libft/
│   └── libft.a
├── 📁map/ 
│   └── *.cub
├── 📁minilibx-linux/
│   └── libmlx.a
├── 📁src/ 
│   └── *.c
├── 📁texture/
│   └── *.xpm
└── MakeFile
```


* [**📂 libft:**](libft/) My implementation of some of the Standard C Library functions compiled into a library
* [**📂 map:**](map/) 2D representation of the map with sprites and the player
* [**📂 minilibx:**](minilibx-linux/) MinilibX, is a simple X-Window (X11R6) programming API in C
* [**📂 src:**](src/) Source file
* [**📂 texture:**](texture/) Texture for Wall and Sprite/

<h2 id="setting">
⚙️ Settings
</h2>

<h3>
Command
</h3>

| KEY           | Action        |
| ------------- |:-------------:|
| `ESC`         | exit game     |
| `Q`           | move left     |
| `D`           | move right    |
| `Z`           | move forward  |
| `S`           | move backward |
| `→`           | turn right    |
| `←`           | turn left     |

<h3>
Map
</h3>

| Character      | Description   |
| -------------  |:-------------:|
| `1`            | wall          |
| `0`            | floor         |
| `2`            | sprite #1     |
| `N`/`E`/`W`/`S`| player initial position + orientation|
| `NO`            | north texture file         |
| `SO`            | south texture file|
| `WE`            | west  texture file|
| `EA`            | east  texture file|
| `F`            | floor rgb color |
| `C`            | celling rgb color|

<h2 id="usage">
🔨 Usage
</h2>

```shell
Make && ./Cub3D [your-map.cub]
```

