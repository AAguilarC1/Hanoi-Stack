# Hanoi tower game solver 
This is an implementation of the Tower of Hanoi game solver using C. I'm using a stack based approach to solve the problem. 

The game consists of three rods where the disks are stacked in decreasing order of size on one rod (Normally the first rod to the left). The objective of the game is to move the entire stack of disks from the Source Rod (The first rod) to the Target Rod (The last rod to the right) with the aid from an Auxiliary Rod (The middle rod). The rules are as follows:

1. Only one disk can be moved at a time.
2. Each move consists of taking the upper disk from one of the stacks and placing it on top of another stack of an empty rod.
3. No larger disk may be placed on top of a smaller disk.
4. Only the topmost disk of a stack can be moved.

## How to build the code 
To build the code, you need to have the GCC compiler installed on your system, as well as Make. To compile the code run the following command in your terminal:

```bash
make build
```

This will create a build directory `build` and a binary folder `bin` with the executable file `Hanoi_Tower` inside it.

## How to run the code
To run the code, you can do this by running the following command 

```bash
make run
```

This will run the executable with the default number of disks which is 3. The output will be displayed in the terminal of the moves to take to solve the game.

To specify the number of disks you must add the `num_disks=<number_of_disks>` argument where `<number_of_disks>` is the number of disks you want to use. For example, to run the game with 5 disks, you would run the following command:

```bash
make run num_disks=5
```

## How to clean the build files
To clean the build files as well as the binary files, you can run the following command:

```bash
make clean
```
This will remove the contents from `build` and from `bin` directories from your project.

