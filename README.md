# Robot-Planning

Simulation of a warehouse where robots receive commands to handle boxes. 

Using generic data structures like Deque (based on DoublyLinkedList) and Stack (based on ResizableArray) to manage queues and stacks during command execution. 

"GET" and "DROP" commands are queued and handled, and "EXECUTE" commands are handled via the stack, allowing UNDO functionality to be implemented and the state of the repository and bots to be updated. The results are displayed in the "robots.out" file.
