# Project Title

  

HANOI TOWERS SOLVER WITH ITERATIVE SOLUTION.

> classic 3x3 hanoi towers problem

```
_D1
__D2
___D3
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~
$ PEG 1      $ $ PEG 2      $ $ PEG 3      $
```
  

## Description


This is a step by step solver of the hanoi towers problems. The user enters the number of disks of pegs (any number between 3 and 30) and the program prints a detailed move-by-move solution either on the shell/terminal or an output txt file (the output depends on the input parameter in input.txt, the default is the .txt file). Input parameters are placed on the input.txt file and are explained in more detail in later section 'Parameters set' section. 

  
The output draws initial and final tower game status and can also print inbetween moves and steps that get you to the solution.

The exact output depends on the input parameters set on the input.txt file and is explained in the 'Parameters' section.

You can enter 3 pegs and 3 disks to see the solution of the classic 3x3 problem, but you can actually use/enter
any number of pegs and disks between 3 and 30, e.g. 5 disks with 4 pegs, 20 disks with 25 pegs, 13 pegs with 13 disks, 3 disks with 10 pegs, 28 disks with 4 pegs, etc. 

> Custom 9x6 hanoi towers problem

```
_D1                                                                                       
__D2                                                                                      
___D3                                                                                     
____D4                                                                                    
_____D5                                                                                   
______D6                                                                                  
_______D7                                                                                 
________D8                                                                                
_________D9                                                                               
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ 
$ PEG 1      $ $ PEG 2      $ $ PEG 3      $ $ PEG 4      $ $ PEG 5      $ $ PEG 6      $ 
```
  

## Getting Started

  

### Dependencies

  
- OS version: Unix/MacOs

- Dependencies: g++ compiler installed , with c++17 version support

You can install g++ with XCode: https://apps.apple.com/gr/app/xcode/id497799835?mt=12 and then

```
$ xcode-select --install
```
to download select xcode command line tools, including g+++

or install g++ seperately with homebrew

```
$ brew update
```
and then

```
$ brew install gcc
```  

### Installing

You can clone into any local directory with

```
$ git clone https://github.com/spyro005/HANOI-TOWERS.git
```

or just download the zip of the project from the github page and extract it into any local directory.

  
### Executing program

After you install the project onto a directory run the following commands from the parent folder

/HANOI \ TOWERS , that has the /main, /src, etc directories in it and the makefile.

Run 
```

XXX-MacXXX-XXX:HANOI TOWERS <username>$ make clean

```
to remove existing executables and object files


Run 
```
$ make
```

to create executable in /bin

Ignore any compilation warnings

 
From the same parent directory you can run

  
```
$ ./bin/hanoi
```

to run the executable that gets created in the /bin directory with the default parameters of the 'input.txt' and see the output in output.txt under /main directory or on the terminal


## Parameters set

On the /main/input.txt file set the values of the following parameters, by leaving a space between the name of the parameter and the integer you type (single digit for env. parameters , after NDISKS, NPEGS) as its value:

Recommended/default values are (for the environment variables after NDISKS, NPEGS):

### Recommended parameters in 'input.txt'  

In the following template, we have the recommended values for input game parameters.

Set NDISKS ( between 3 and 30 inclusive) to be the number of input disks to get from the first peg to the last following the rules

Set NPEGS (between 3 and 30 inclusive) to be the number of pegs that the disks have to traverse to get to the last peg following the game rules.


Values 3,3 for NDISKS, NPEGS respectively solve the classic hanoi tower games puzzle. You can enter any number you like to test.

  
### Parameter template


After NDISKS, NPEGS in the following template we have the recommended set of values for all the parameters:

```
NDISKS 3
NPEGS 3

DEBUG 1
STATUS 0
DRAW 1
DRAW_MOVES 1
PRINT_MOVES 1

REDIRECT_OUTPUT 1
```
- NDISKS : the number of disks in the game. Can be any integer greater or equal to 3 and less or equal to 30.

> To view the output for sample run, you can start with 3.

- NPEGS : the number of pegs in the game. Can be any integer greater or equal to 3 and less or equal to 30.

> To view the output for sample run, you can start with 3.


- DEBUG (recommended 1) : controls the level and frequency of the help/debug print messages.
> values are 0 for none debug prints,
> 1: for little (RECOMMENDED), prints game creation messages, solution moves one by one

> 2: for all (1) prints, plus detailed moves between pegs, plus pegs that are used in iterations , plus wrong > and unsuccessful moves error messages and disk moves (suggested for debugging errors, segmentation > faults and exceptions etc);

> 3: for (2) prints and also all debugging  

- STATUS (recommended 0) : controls the level and frequency of the non-graphical game status print messages.

> values are: 0 for no game status prints (RECOMMENDED ALONG WITH 1 IN 'DRAW_MOVES' AND 'DRAW' params),

> 1: for little (prints the non-graphical status ONLY at beggining and end of the solution),

> 2 :for detailed prints (prints non-graphical game status) at SOME main points inbetween solution moves,

> with the (1) prints (RECOMMENDED IF 0 in 'DRAW_MOVES')

> 3: for all prints (prints non-graphical game stauts after EVERY move of the solution, with all the (2) prints).

> Example print status after 2nd move in classic 3disk-3peg hanoi tower game:
 
```

GAME PEG STATUS

  

Status for peg named Peg 1 with order 1

Peg has the following disks:

Disk named 'Disk 3' with size (order) 3

  

Status for peg named Peg 2 with order 2

Peg has the following disks:

Disk named 'Disk 2' with size (order) 2

  

Status for peg named Peg 3 with order 3

Peg has the following disks:

Disk named 'Disk 1' with size (order) 1

No other pegs in game

```
 - DRAW (recommended 1) : controls the simple 2D graphical print of the game status at start and end of game .

>  values are:

> 0 : for no game status graphical print

> 1 : prints 2d graphics line game status where disks are lines with 'DX' format at the end (e.g. D5) to show .> disk size number. Graphical status is printed at start and end of game

> Example line graphical print at start of classic 3x3 hanoi tower problem:

```
_D1
__D2
___D3
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~
$ PEG 1      $ $ PEG 2      $ $ PEG 3      $
```

> 2 : prints 2d box graphic game status where disks are boxes with 'Disk X' format in the center (e.g. 'Disk > 4') which shows the disk size number. Box Graphical status is printed at start and end of game.

> Example box graphical print at end of classic 3x3 hanoi tower problem:


```
                        ___________ 
                        | DISK 1  | 
                        ^^^^^^^^^^^ 
                        ___________ 
                        | DISK 2  | 
                        ^^^^^^^^^^^ 
                        ___________ 
                        | DISK 3  | 
                        ^^^^^^^^^^^ 
~~~~~~~~~~~ ~~~~~~~~~~~ ~~~~~~~~~~~ 
$ PEG 1   $ $ PEG 2   $ $ PEG 3   $ 
~~~~~~~~~~~ ~~~~~~~~~~~ ~~~~~~~~~~~ 
```


 - DRAW_MOVES (RECOMMENDED 1): controls the simple 2D graphical print of the game status at every move of the game .

> values are:

> 0 : for no game status graphical print

>  1 : prints 2d graphics line game status where disks are lines with 'DX' format at the end (e.g. D5) to show .> disk size number. Graphical status is printed at start and end of game

  

> Example line graphical print after 2nd move in classic 3x3 hanoi tower problem:
```
___D3           __D2           _D1
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~
$ PEG 1 $      $ PEG 2 $      $ PEG 3 $
```

> 2 : prints 2d box graphic game status where disks are boxes with 'Disk X' format in the center (e.g. 'Disk > 4') which shows the disk size number. Box Graphical status is printed after every move of the game.

> Example box graphical print after 2nd move of classic 3x3 hanoi tower problem:

```

___________ ___________ ___________
| DISK 3 | | DISK 2 | | DISK 1 |
^^^^^^^^^^^ ^^^^^^^^^^^ ^^^^^^^^^^^
~~~~~~~~~~~ ~~~~~~~~~~~ ~~~~~~~~~~~
$ PEG 1 $   $ PEG 2 $     $ PEG 3 $
~~~~~~~~~~~ ~~~~~~~~~~~ ~~~~~~~~~~~

```

 - PRINT_MOVES (RECOMMENDED 1) : at the end of all game move and debug messages, prints all moves of the game

> line by line, one by one between pegs. This a sum print of all moves at the end, and it is different

> than having '1' next to 'DEBUG' that prints all moves inbetween final states of the game along possible > drawings

> 0 : for no move prints at the end.

> 1 : prints all moves at the end of the solution:

> Example sample sum move print at the end
 
```

Printing moves

  

#1) Move Disk 1 from Peg 1 to Peg 3

#2) Move Disk 2 from Peg 1 to Peg 2

#3) Move Disk 1 from Peg 3 to Peg 2

#4) Move Disk 3 from Peg 1 to Peg 3

#5) Move Disk 1 from Peg 2 to Peg 1

#6) Move Disk 2 from Peg 2 to Peg 3

#7) Move Disk 1 from Peg 1 to Peg 3
```

  -  REDIRECT_OUTPUT (RECOMMENDED 1): directs all the print output (std::cout for all print/debug/graphic messages and > statuses) on the shell/terminal (value 0) where the executable is run or the 'output.txt' (value 1) file under > /main

> values are 0: to print all output on the terminal

> 1: to redirect all output on the 'output.txt' file


## Example custom run with 7 disks and 5 pegs


> first 3 moves

```
INITIAL GAME DRAW AT CALL 1

_D1                                                                        
__D2                                                                       
___D3                                                                      
____D4                                                                     
_____D5                                                                    
______D6                                                                   
_______D7                                                                  
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ 
$ PEG 1      $ $ PEG 2      $ $ PEG 3      $ $ PEG 4      $ $ PEG 5      $ 

MOVE #1) Move Disk 1 from Peg 1 to Peg 3

                                                                           
__D2                                                                       
___D3                                                                      
____D4                                                                     
_____D5                                                                    
______D6                                                                   
_______D7                     _D1                                          
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ 
$ PEG 1      $ $ PEG 2      $ $ PEG 3      $ $ PEG 4      $ $ PEG 5      $ 

MOVE #2) Move Disk 2 from Peg 1 to Peg 2

                                                                           
                                                                           
___D3                                                                      
____D4                                                                     
_____D5                                                                    
______D6                                                                   
_______D7      __D2           _D1                                          
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ 
$ PEG 1      $ $ PEG 2      $ $ PEG 3      $ $ PEG 4      $ $ PEG 5      $ 

MOVE #3) Move Disk 1 from Peg 3 to Peg 2

                                                                           
                                                                           
___D3                                                                      
____D4                                                                     
_____D5                                                                    
______D6       _D1                                                         
_______D7      __D2                                                        
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ 
$ PEG 1      $ $ PEG 2      $ $ PEG 3      $ $ PEG 4      $ $ PEG 5      $ 

```

> Move #119 inbetween first and last move


```
MOVE #119) Move Disk 1 from Peg 2 to Peg 1

                                                                           
                                                                           
                                                                           
                                                                           
_D1                           _____D5                                      
__D2                          ______D6                                     
___D3          ____D4         _______D7                                    
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ 
$ PEG 1      $ $ PEG 2      $ $ PEG 3      $ $ PEG 4      $ $ PEG 5      $ 
```


> last 4 moves with line graphical print ('DRAW_MOVES' set to 1)


```
MOVE #251) Move Disk 3 from Peg 3 to Peg 5

                                                                           
                                                                           
                                                            ___D3          
                                                            ____D4         
                                                            _____D5        
                                             _D1            ______D6       
                                             __D2           _______D7      
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ 
$ PEG 1      $ $ PEG 2      $ $ PEG 3      $ $ PEG 4      $ $ PEG 5      $ 

MOVE #252) Move Disk 1 from Peg 4 to Peg 3

                                                                           
                                                                           
                                                            ___D3          
                                                            ____D4         
                                                            _____D5        
                                                            ______D6       
                              _D1            __D2           _______D7      
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ 
$ PEG 1      $ $ PEG 2      $ $ PEG 3      $ $ PEG 4      $ $ PEG 5      $ 

MOVE #253) Move Disk 2 from Peg 4 to Peg 5

                                                                           
                                                            __D2           
                                                            ___D3          
                                                            ____D4         
                                                            _____D5        
                                                            ______D6       
                              _D1                           _______D7      
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ 
$ PEG 1      $ $ PEG 2      $ $ PEG 3      $ $ PEG 4      $ $ PEG 5      $ 

MOVE #254) Move Disk 1 from Peg 3 to Peg 5

                                                            _D1            
                                                            __D2           
                                                            ___D3          
                                                            ____D4         
                                                            _____D5        
                                                            ______D6       
                                                            _______D7      
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ 
$ PEG 1      $ $ PEG 2      $ $ PEG 3      $ $ PEG 4      $ $ PEG 5      $ 

SOLVED GAME: true

```

> Moves print after final state

```
Printing moves 

#1) Move Disk 1 from Peg 1 to Peg 3
#2) Move Disk 2 from Peg 1 to Peg 2
#3) Move Disk 1 from Peg 3 to Peg 2
#4) Move Disk 3 from Peg 1 to Peg 3
#5) Move Disk 1 from Peg 2 to Peg 1
...
...

#249) Move Disk 2 from Peg 3 to Peg 4
#250) Move Disk 1 from Peg 5 to Peg 4
#251) Move Disk 3 from Peg 3 to Peg 5
#252) Move Disk 1 from Peg 4 to Peg 3
#253) Move Disk 2 from Peg 4 to Peg 5
#254) Move Disk 1 from Peg 3 to Peg 5

```

## Help

Ignore compilation warnings after running 'make'
  

## SOLVER ALGORITHM EXPLAINED IN DETAIL

To be added later
  

## Acknowledgments

  
Inspiration, code snippets, etc.

* Iterative algorithm for hanoi towers (pseudocode): [iterative-algorithm](https://www.geeksforgeeks.org/iterative-tower-of-hanoi/)  

* Redirect std::cout stream to file and read from shell input c++: [stream redirection](https://www.geeksforgeeks.org/redirect-cin-and-cout-to-files-in-cpp/)
