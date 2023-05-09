# connect_four
An implementation of Connect Four using the ATMega328P microcontroller for UNLV CpE 301L final project.
## Overview
Our final project is a combination of the LCD + keypad lab and the first lab which used Arduino code. We implemented a connect four game on the ATMega328P, with two users that will act as players whose turns alternate starting with player one's turn always. The 4x4 keypad will act as our game input and each player will take turns pressing buttons until one player can connect four in a row. The first row and four columns will be the input representing the top of the Connect Four game. Pressing any of the buttons in row one will drop an imaginary piece onto the imaginary game board. Our program will check if the opposing player has already occupied a certain spot and in that case, then the player can’t occupy that button anymore. Then the LCD will display which player has taken their turn and which button is pressed, as well as displaying the win condition or draw.
## Software
- Arduino IDE
## Hardware
- ATMega328P Development Board
- LCD Display
