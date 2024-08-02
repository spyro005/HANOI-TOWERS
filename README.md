HANOI TOWERS ITERATIVE SOLUTION SOLVER

Enter the input number of disks (3 <= D <= 999) and input number of pegs (3 <= P <= 999 ) in "/main/input.txt" by placing integers next to the variables 'NDISKS', 'NPEGS' of 'input.txt' and see the solution output on your terminal or "/main/output.txt" , depending
if you choose to redirect output to 'output.txt' file (1 next to 'REDIRECT_OUTPUT' variable) or to your terminal (0 next to 'REDIRECT_OUTPUT' variable) 
Each solution move is represented on a simple 2d graphics peg representation with disks. Final game state is also printed.

in the parent project folder run (that has the makefile)

$ make clean
$ make

Ignore any compilation warnings

$ ./bin/hanoi 

see the output on 'output.txt' under /main folder.

Will look like this:

......

Move #7) Move Disk 1 from Peg 1 to Peg 3

                              _D1            
                              __D2           
                              ___D3          
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ 
$ PEG 1      $ $ PEG 2      $ $ PEG 3      $ 

SOLVED GAME: true

DRAWING FINAL GAME STATUS

                              _D1            
                              __D2           
                              ___D3          
~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~ 
$ PEG 1      $ $ PEG 2      $ $ PEG 3      $ 


 Printing moves 

#1) Move Disk 1 from Peg 1 to Peg 3
#2) Move Disk 2 from Peg 1 to Peg 2
#3) Move Disk 1 from Peg 3 to Peg 2
#4) Move Disk 3 from Peg 1 to Peg 3
#5) Move Disk 1 from Peg 2 to Peg 1
#6) Move Disk 1 from Peg 2 to Peg 1
#7) Move Disk 1 from Peg 1 to Peg 3

