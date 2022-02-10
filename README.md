<img src="https://backdrop-engine.github.io/assets/logo.svg" alt="Backdrop logo" style="width: 160px; border-radius: 8px;" />

# Backdrop

Backdrop is a game-making tool designed for creating top-down action games similar to earlier entries of The Legend of Zelda series and the Ys series.

This repository contains the code for the game engine.

## Installation

Install the following dependencies:

* g++ (for C++14)
* [SFML (2.5.1)](https://www.sfml-dev.org/index.php) (for graphics)

## Development

To make a **development** build of the program, run the following command:

```sh
make dev
```

This will build the program to `./dev.exe`.

To make a **production** build of the program, run the following command:

```sh
make prod
```

This will build the program to `./game.exe`.
