# Voracious Snake
This is an app-like form of classic snake game which we used to play in our android phones in 90s and 2000s.
App was built on purpose of Low-level programming laboratories at the university.
## Implementation
The game was written in C language and SFML 2.5.1 library.
## Running the project
Download the Release directory and run the .exe file just as any other application.
## Project tree
1. `main.cpp` - logic of forming the window, draws whole menu, handles evens and reacts on chosen option
2. `playGame.cpp` - contains all functions and variables necessary to running the game

   *`struct Snake` - snake's body segment, array of structs `snake[]` contains coordinates of each segment
   
   *`struct Fruit` - coordinates of currently shown fruit
3. `functions.cpp` - contains definitions of auxiliary functions responsible for displaying the end game screen and the exit box
## References
Fonts: https://www.1001freefonts.com/
Snake images: https://www.pngwing.com/
Snake body segments: https://rembound.com/
Background, game over and fireworks image: https://www.shutterstock.com/
