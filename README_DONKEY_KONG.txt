Donkey Kong Game README

id1: 211696752 Edan Globus.
id2: 314950213 Matan Egel.

File data structure:

Player state: 0 – Death \ 1 – Game won \ 2 – Game Lose \ 4 – level won
Result:                    iteration, position, player state, score
Steps:  seed(randoms)      iteration, char 

**Game Modes**
-Save Mode:
Save the current game 
Cannot choose level, start from level  0 for a full game.
Save start from level 0 for a full game record and to be match with the NO MENU in -load mode.

-Load Mode:
Replay the latest game played on -save mode.
If step\result  file is empty then need to run a new -save mode. 

-Load -Silent Mode:
Run without displayed game. 
Check if the game played on -save mode is matching to the result file of the level.
If not then display the exact issue.

**Gameplay Instructions**
1. Climbing Ladders:  
   - To climb a ladder, first need to stand then press ‘w’ to climb.  
     - `W`: climbing up the ladder without stopping. (to be able to escape from Super Ghost on the ladder).
     - `X`: climbing down step by step

2. Mario's Movement While Falling:  
   - Mario can move left or right while falling to avoid obstacles or position himself for a safe landing.  
   - Use the following keys:
     - `A`: Move left
     - `D`: Move right

4. Scoring System:  
   - The score increases only after successfully completing a level.  
   - The score resets or continues when starting a new level.
   - Completing a level = (+10 points) || Death = (-2 points) || killing enemy (+5 points)

5. Mario's Death Conditions:  
   - Falling: Mario dies if he falls more than 5 floor levels.  
   - Barrel Collision: Mario dies if he gets hit by a barrel or barrel explosion his distance less then 2 squares or touching a ghost.

6. 'P' Hammer ability
    - When collecting the hammer ability available until death.
    - Hammer attack destroy enemy 3 square from Mario to his moving direction.
    -After Mario is dead he loses his hammer until next level.

**Screen Not Valid**

first we get all screen files to the file vector and then checking each screen before playing the level.
If the screen is not valid then a display message will appear. after,  going to the next screen if its a valid level you will play the level else message.

**validation check for:
1. Amount of Mario's\queens\Kong's on the board == 1 is valid else not valid.
2. check if each of the characters (exclude Mario: Mario can fall) include ghosts have a floor under them.
3. y=25 need to be a floor without holes.
4. Board is smaller then 25x80.
5.Q in the middle of the board - board not valid.
6.unrecognize char in the screen - board not valid.

**Bonus Features (section 1)**
1. Barrel Explosions:  
   - Barrels explode upon certain conditions, creating visual effects.
2. Random Barrel Directions:  
   - Barrels are thrown in random directions, adding unpredictability to the game.
3. Game Exit Option:  
   - Press a designated exit key ( `9`) to exit the game at any time while playing.
   
**Bonus Features (section 2)**
1. Game with colors.   
2. High score leading table (top 3).   
3. Hammer attack effect.
4. Random direction for barrel when falling on '^'. 
  
**Bonus Features (section 3)**
1. Super Ghost chasing after Mario algorithm.
SuperGhost climbing a ladder to match his floor level to Mario's.
When they are in the same floor level super ghost chase by x position.  

**Key Controls**
- `W`: Move up (climb ladder)
- `X`: Move down (climb ladder)
- `A`: Move left
- `D`: Move right
- `S`: STAND position
- `P`: Hammer Attack
- 'c': Add\Remove colors
- `ESC`: Pause the game
- '9': EXIT game

---

**How to Play**
1. Use the movement keys `W`, `A`, `S`, `D`, `X` to control Mario:
   - Move left/right while on the ground or falling.
   - Press `W`/`X` to climb ladders carefully.
2. Press `S` to align Mario on a ladder before climbing.
3. Avoid barrels, barrels explode when falling more then 8 levels.
3. Avoid ghosts.
4. Reach the '$' to complete the level and progress to the next.

