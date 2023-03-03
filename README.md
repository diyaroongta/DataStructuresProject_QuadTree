# DataStructuresProject_QuadTree
End-of-semester project; code written in C on implementation of Quad Trees and Operations on It 

# Topic
Implementation of Quad Trees and Operations on It

# Introduction
Quadtree is a tree structure in which each internal node has at most four children. It is used to efficiently store the data in a 2-d space by recursively dividing it into four quadrants until the desired structure is achieved.

# What My Code Does
My code for quadtrees is a succesful implementation of the structure, along with certain operations/playing around that can be done on it.
I initialised the tree with 3 points which cover the current dimensions of the tree.
After that, the user has the options for the following operations that can be performed on it:
1. Searching for a point in the quadtree to see whether it lies within the dimensions of the tree
2. Inserting another point/node into the tree
3. Deleting a node from the tree
4. Printing the points contained in the quadtree at present
5. Finding the nearest neighbour for a point in the quadtree 

# How to run the code
There is only one c file attached in the zip file which contains all the functions of the quadtree.
If running on terminal, you need to initially compile the code using the "gcc -g3 -Wall -o first quadtreesproject.c", and then run it using "./first" command.
It will initially print the points that are pre-stored into the quadtree, and then will give the user a list of options to choose the operation they want to perform on it, and will continue to give users this option till they choose to exit/stop using the command 6.
Other than that, the code is very self explanatory and user-friendly.

# How I Tested The Code
I ran the code multiple times with differing inputs for the dimensions of the quadtree, the different functions of the tree, checking all the base cases, etc. For example, I checked the search function with both values present within the dimensions of the tree, as well as beyond. For the insertion function, I first inserted the element, and then printed the tree to see whether it had been successfully inserted. For the nearest neighbour function, the code gave the correct output for a bunch of different input nodes that I gave. The print function also reflected the tree with the correct points. Thus, there has been a thorough check of different cases in the code. 

One example is as follows: (the output of the test run)
The current structure of the quadtree is:
(50, 50)
(10, 20)
(60, 70)
To search, enter 1
To insert, enter 2
To delete, enter 3
To print, enter 4
To find nearest neighbor, enter 5
To stop, enter 6: 1
Enter the node to be searched: 70
70
The node is present.

To search, enter 1
To insert, enter 2
To delete, enter 3
To print, enter 4
To find nearest neighbor, enter 5
To stop, enter 6: 1
Enter the node to be searched: 100
100
The node is absent from the quadtree.

To search, enter 1
To insert, enter 2
To delete, enter 3
To print, enter 4
To find nearest neighbor, enter 5
To stop, enter 6: 2
Enter the node to be inserted: 80
90
Enter the level at which the node should be inserted: 0

Element successfully inserted.
To search, enter 1
To insert, enter 2
To delete, enter 3
To print, enter 4
To find nearest neighbor, enter 5
To stop, enter 6: 4
The nodes of the quadtree according to the levels are:
(50, 50)
(10, 20)
(60, 70)
(80, 90)
To search, enter 1
To insert, enter 2
To delete, enter 3
To print, enter 4
To find nearest neighbor, enter 5
To stop, enter 6: 3
Enter the node you want to delete: 50
50
Element successfully deleted.
To search, enter 1
To insert, enter 2
To delete, enter 3
To print, enter 4
To find nearest neighbor, enter 5
To stop, enter 6: 5
Enter the node you want to find the nearest neighbour of: 20
20
Nearest neighbor: (10, 20)
To search, enter 1
To insert, enter 2
To delete, enter 3
To print, enter 4
To find nearest neighbor, enter 5
To stop, enter 6: 4
The nodes of the quadtree according to the levels are:
(10, 20)
(60, 70)
(80, 90)
To search, enter 1
To insert, enter 2
To delete, enter 3
To print, enter 4
To find nearest neighbor, enter 5
To stop, enter 6: 6
