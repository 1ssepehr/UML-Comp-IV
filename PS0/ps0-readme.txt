/**********************************************************************
 *  ps0-readme template                                                   
 *  Hello World Assignment                       
 **********************************************************************/

Your name:
    Seyedsepehr Madani

Operating system you're using (Linux, OS X, or Windows):
    Linux Ubuntu 20.04

IDE or text editor you're using:
    Visual Studio Code

Hours to complete assignment:
    7.5 Hours


/**********************************************************************
 *  Part of Assignment 0 is to read the collaboration policy in syllabus.
 *  
 *  If you haven't done this, please do so now.
 *
 *  Read the University policy Academic Integrity,
 *  and answer the following question:
 *
 * There are six examples of academic misconduct, labeled (a) through
 * (f). Other than (a), "Seeks to claim credit for the work or efforts
 * of another without authorization or citation," which of these do you
 * think would most apply to this class, and why? Write approx. 100-200
 * words.
 *
 * Note: there is no single correct answer to this. I am looking for
 * your opinion.
 *******************************************************************
I would say item (f), "assists other students in any of these acts".
Students get in touch with other very frequently, complaining about some 
assignment or a quiz they can't quite finish on their own and ask for help.
And well, in many cases students see that they can get away with giving each
other the answers. The network of students helping each other cheat through
assignments, quizzes, etc. is uncommonly large.


/**********************************************************************
 *  List whatever help (if any) you received from TAs, the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
I did this assignment on my own, only with browsing the tutorials and 
docs online.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
None.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
This project uses a Makefile.
Here is the structure:

PS0
├── assets
│   └── all images for textures in sprites
├── src
│   └── all .hpp & .cpp files here
├── ps0-readme.txt (this file)
└── Makefile

`make' will create ./obj and ./bin, and the final executable will be in:
    ./bin/sfml-app

The project is a simple space game. You are a spaceship, avoiding incoming
asteroids.

Move your ship with Arrow ←↑→↓ keys. No guns, firing, etc. (yet.)
Collisions are NOT pixel perfect. TODO for later.

Enjoy!