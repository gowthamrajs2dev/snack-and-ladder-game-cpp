# Snack and Ladder Game

This project is a C++ console-based implementation of a simple Snake and Ladder (referred to in the code as “Snack and Ladder”) game.

## Game Rules

- Players start moving only after they roll a `1`.
- Dice values range from `1` to `6`.
- Turns proceed in clockwise order.
- If a player rolls `1` or `5`, they get an extra chance.
- The board has fixed ladders and sliders.
- Gifts are marked on some boxes and are collected when landed on.
- The game ends when a player reaches box `30`.
- If a move overshoots `30`, that move is ignored.
- If no player reaches the destination, the result is treated as a tie.

## Fixed Board Elements

Ladders:
- `4 -> 9`
- `7 -> 19`
- `8 -> 28`
- `15 -> 26`

Sliders:
- `13 -> 2`
- `29 -> 20`
- `25 -> 14`

## Input Format

The program reads input in this order:

1. Number of players
2. Player names
3. Name of the starting player
4. Number of gift boxes
5. Gift box positions
6. Number of dice rolls
7. Roll sequence

Example:

```text
2
A B
A
2
5 10
10
1 4 5 2 3 1 6 2 5 1
```

## Output

The program prints each player's final status in this format:

```text
player name | current position | remaining count to win the game | gifts | sliders | ladders
```

If a player does not win, their name is printed at the end as a loser.

## Compile and Run

Compile:

```bash
g++ -std=c++17 main.cpp -o game
```

Run:

```bash
./game < input.txt
```

## Notes

- The game board is size `30`.
- The code stores positions using `1`-based indexing.
- The program currently uses fixed board setup inside the source file.
