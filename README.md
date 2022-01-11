# Backdrop

Backdrop is a game-making tool designed for creating top-down action games similar to earlier entries of The Legend of Zelda series and the Ys series.

This repository contains the code for the game engine.

## Installation

Install the following dependencies:

* g++ (for C++14)
* [SFML (2.5.1)](https://www.sfml-dev.org/index.php) (for graphics)

In Ubuntu, this can be done with:

```sh
sudo apt-get install build-essential gdb libsfml-dev
```

## Development

Run the following command to build the project:

```sh
make
```

This creates the executable `main.out`, which can be opened with:

```sh
./main.out
```

**Note:** WSL2 (Windows 10) doesn't have a native X11 display. To run a build on WSL2, download [Xming](http://www.straightrunning.com/XmingNotes/) and follow the steps in **Setting up X11 for WSL2 (Windows 10)** once per terminal.

### X11 Setup for WSL2 (Windows 10)

#### Step 1

Get your local IP address with the following command **in Powershell**:

```powershell
(ipconfig | Select-String -Pattern 'WSL' -Context 1, 5).Context.PostContext | Select-String -Pattern 'IPv4'
```

#### Step 2

Run the following commands **in WSL2**:

```sh
sudo service ssh start
export DISPLAY=<IP_ADDRESS_FROM_STEP_1>:0.0
```

#### Step 3

Open XLaunch with the default settings + no access control.
