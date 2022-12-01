# Introduction : Learning the Depth First Search (DFS) algorithm
I have been reading a book called "Data Structures for Game Programmers" by Ron Penton. 
As the title sugests, he goes over a wide range of topics and the DFS algorithm is just one of many. 
I would definitely recommend any programmer who wants to learn about algorithms and data structures to read this book.

For my own learning experience I followed the book's code whilst also changing a few things here and there. 
Further below I have added some of my own diagrams to help illustrate this complex topic. 

## DFS Test
///////INSERT DMAP PICTURE HERE//////
This project demonstrates the use of the graph type algorithm DFS and uses the following data structures: 
- Arrays
- Bit vectors. 

The Bitvector type uses bitwise operations as a means of marking and assessing which tiles (i.e. rooms) have been drawn or not. 
See the below image which illustrates each room’s unique number and what directions the player can travel to in each room.
//////INSERT NUMBERED DIR IMAGE HERE ////////

## Data Structures & Functions Utilized

Below I have listed the main data types used and their most frequently used functions. 
Some functions have been omitted as they should be self explanatory. 

#### Array class

| Data Structure Name |
| ------------------- |
| `Array2D`           |

| Type                                      |
| ----------------------------------------- |
| `class` type, `template <class Datatype>` |

| Members                        |
| ------------------------------ |
| `int m_height`, `int m_width`, |
| `Datatype* m_array`.           |       
|                                |

| Declared Example                         |
| ---------------------------------------- |
| ```c++                                   |
| Array2D<int> g_map( ROOMS, DIRECTIONS ); |
| ```                                      |


###### Construction:
```c++
{ m_array = new Datatype[ pWidth * pHeight ]; m_width = pWidth, m_h = pH }
```

######Frequently Used Functions

| Function Name | Type        |
| ------------- | ----------- |
| `Get`         | `Datatype&` |

| Parameters            |
| --------------------- |
| ```c++                |
| ( int x_p, bool y_p ) |
| ```                   |

######Description:
Returns the array’s index value based on it’s index location using the following expression:
return array[ y * width + x ];

Say we have a 2D array that is 2x4 (y, x): 
| Position 0  | Position 1 | Position 2 | Position 3 |
| ----------- | ---------- | ---------- | ---------- |
| Position 4  | Position 5 | Position 6 | Position 7 |

and we wish to access Position 6, we would use:
```c++
return array[ 1 * 4 + 2 ] = 6
```

This works due to the way arrays work in C++ i.e. 2D dynamic arrays are stored as a 1D array.

#### Bit vector class

| Data Structure Name | Type         |
| ------------------- | ------------ |
| Bitvector           | `class` type |

| Declare Example              |
| ---------------------------- |
| Bitvector g_marked( ROOMS ); |

| Members                    |
| -------------------------- |
| int m_size,                |
| unsigned long int* m_array |

###### Construction
```c++
{ m_array = 0, m_size = 0, Resize( p_size ); }
```

###### Frequently Used Functions

| Function Name: 						
| Set				

Parameters:
( int index_p, bool value_p )

Type:
void

Description: 
Sets a value for the bit vector’s m_array member. 
If you wish to see a further explanation I will in more detail near the end.

Name:
operator[]

Parameters:
( int index_p )

Type:
bool

Description:
This access operator is used to return a value that is either 1 or 0 (i.e. true or false respectively).
Again, if you want a detailed explanation, I will include this later on.

# Data Members Visualized
Below are the main objects used in this project, the tables have a name, followed by its type.
(Note: “?” means values have not been assigned yet):
...

# Array and Bitvector assignment
We have discussed the main objects, now we need to assign values to objects “map_g” and “marked_g”.
During the InitializeMap(map_g) method, all index values are set to -1 first, then the room exits are assigned:
..
Once these values are set they are not changed again. This may look confusing at first but we will break this down to understand what is going on. To clarify, the array’s indexes are ordered this way:
..
Say we want position 20 (which is value 5), to set this value it would look like the below code:
map_g.Get( 4, 1 ) = 5		{ return m_array[ 1 * 16 + 4];		 // this is position 20

After Bitvector’s ClearAll() method all values in the marked_g’s member are assigned to 0:
...
This method is called during the event loop & just before the DrawMap(...) method, which is where the main DFS algorithm is used.

# Array - Room Assignment
Below is a visualization of a 16 x 4 array where the Rooms are linked to other rooms going by their direction.
Note: # signifies -1.
...
...
An example of what it looks like visually. 

# Depth First Search Process Breakdown
The DFS algorithm is a recursive process where if it does call itself again, that means to say it will visit a node. 
In our case, the node == room. DFS will categorize nodes as either Visited (true) or Not Visited (false) 

This algorithm mark’s each vertex / path as visited and avoids repeating cycles. Let's look at the algorithm:
..
Below are the abbreviations and my own explanation of the algorithm:
G = Graph		u = node		v = vertex		E = Sigma (i.e. sum)

DFS( Graph, node )
     current node visited = true;			    // mark the node as visited.
     for each vertex element part of the Graph’s current node // loop through the vertex’s pointing to nodes.
	if vertex visited == false		               // i.e. the path to the current node has not been visited
			DFS( Graph, vertex )		   // Visit the node.

init ()
     for each node element part of the Graph		// Starting from node 1 to n..
	current node visited = false			// Set current node to false
     for each node part of the Graph			// Loop through all nodes
	Begin the DFS( Graph, node)

In this project, the algorithm is slightly modified but it largely the same:
➊DrawMap()
       DrawTile()					// Draw the room
       marked.SetBitValue()				// Mark current room as visited
       ⟳FOR (Direction=0; Dir < 4; Dir++) 		// Loop through the directions pointing to other rooms
       ⤷        RoomNum = GetRoomNum()			// Get the next room according to current direction
                 �IF (RoomNum != -1)				// If the room pointed to by the direction exists
                 ⤷          �IF (marked.BitValue == false)		// If this room has not been visited
                             ⤷        ➊DrawMap()			// Enter this room
                             
# DFS Traversal Process
We’ve discussed the algorithm in detail, now we will go over how it draws the rooms. 
The current drawn room (R) in the current drawn phase (draw) will be coloured yellow.
...
As you may have gathered from the traversal pattern, during the DFS draw phase we go  Up, Right, Down and Left. 
I will explain this in detail shortly.

# Drawing the Tiles / Sprites
Before we discuss the traversal pattern, I want to point something out in SDL. 
When a sprite is blitted onto the screen, it goes by the width and height of the sprite. 
For example, say we have a point of origin ( • ), it would be drawn across to the left and downward like so:
 •  ▸  ▸  ▸  ▸  ▶| x
 ▾		           |
 ▾		           |
 ▾		           |		A sprite of y and x dimensions
 ▾		           |
▼_  _  __  _  _ _•
y


Note: The coordinate system in SDL is different to a typical coordinate system, see below:

Typical coordinate system:				SDL’s coordinate system:
							•→	→	→
↑							↓

↑							↓

↑							↓
•→	→	→

With that explained, lefts go into detail how the tiles are drawn. 
A direction array is used to indicate the drawing point position for the tiles. It is as follows:

int directionArray[4][2] = 
//     UP       RIGHT    DOWN    LEFT
{ { 0, -64 }, { 64, 0 },  { 0, 64 }, { -64, 0 } };	// Number 64 represents the tile’s dimensions in pixels.

Let's see how this works. Note: to go up we decrease the y value and the opposite to go down.
Expression: x + value = new x coordinates			Expression: y + value = new y coordinates

IF dir = 0	// UP			
368  +                   0                           = 368			268 +             -64                           = 204  
x      +    directionArray[direction0][0] = 368, 		y     + directionArray[direction0][1] = 204

IF dir = 1	// RIGHT
368 	+              64                             = 432		268 +              0                                = 268 
x 	+ directionArray[direction1][0] = 432 		y     + directionArray[direction1][1] = 268

IF dir = 2	// DOWN
368 +                0                            = 368			268 +                 64                          = 332 
x     + directionArray[direction2][0] = 368 			y     + directionArray[direction2][1] = 332

IF dir = 3	// LEFT
368 +                     -64                    = 304 		     	268 +              0                              = 268 
x     + directionArray[direction3][0] = 304 			y     + directionArray[direction3][1] = 268

# Applications of the DFS Algorithm
After studying this algorithm, I would say that this algorithm could be suited to solve various scenarios such as:
Player inventory 
AI pathfinding
Puzzle solutions

Perhaps there are more applications I haven't thought of. 
It is interesting nonetheless how algorithms out there can provide solutions to complex problems. 

Ending notes
Thank you for reading, this took a while for me to fully grasp. 
I have always wanted to fully understand a pathfinding algorithm. 
Now that I do, I will apply it to my own projects. Hopefully this has been insightful for any readers out there.
