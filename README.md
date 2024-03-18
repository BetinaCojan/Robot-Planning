# Robot Planning

### Summary
Implementation of robot control functions for the management of objects in a warehouse. 
Creating data structures and combining them. Making the code as generic as possible to be used for a wider purpose and to avoid duplication.

### Purpose
The input data are read, which contain: the number of robots working in the warehouse, the dimensions of the warehouse, its content and all commands given by humans to the robots. 

The robots will have to execute each command separately, managing them according to priorities and storing them so they can return to the previous commands in case of need. Each robot will have its management, but there will be a general history for all commands executed in the warehouse.

### Implementation
The following data structures were created:
- Doubly Linked List (Used as a Deque)
- Resizable Array (Used as a Stack)

Class DoublyLinkedList is implemented using the Node struct, which represents each element from the list. The main functions of the DoublyLinkedList class are: to add to the beginning and the end of the list, to remove from the beginning and the end of the list and to return a specified element.

Class ResizableArray is implemented so that it can be used as a stack. It has the following main functionalities: deleting and adding elements only at the end of the list, returning the element at the end of the list and resizing it to the specified size.

Robots are implemented using struct and have the following attributes:
- ID
- the number of boxes they own
- the deque of commands to be executed. Deque is implemented using the DoublyLinkedList class

Class Warehouse contains the matrix with warehouse values, the vector of robots and the commands history stack.
The class implements the following main functions:
- AddGetBox (Depending on the priority given, the GET command will be added to the beginning or end of the command queue of the robot with the given ID)
- AddDropBox (The same functionality, but the command type will be specified as DROP)
- Execute (Executes the first command from the queue of a robot with the given ID)
- PrintCommands (Prints the commands from the queue of the given robot)
- LastExecutedCommand (Prints the last added command in the stack of commands history)
- Undo (Removes the last executed command from the stack history, puts the command back in the robot's command queue and performs the reverse operation for the command found)
- HowManyBoxes (Returns the number of boxes that the robot with the given ID has at that time)

The elements used for the ResizableArray and DoublyLinkedList classes are created generically to be able to store any kind of information. Thus, the tuples are stored and contain details about the robot, the position of the boxes in the warehouse and the priority of the given command.


--- 
**Author: Betina Cojan**
