# Subsystems Initialization

The engine needs to initialize all subsystems before entering the main loop and finish them after ending the main loop.


## CommandChain

This program has a class named [CommandChain](../src/common/command.hpp) that easies this initialization process.
This class receives arguments organized in pairs responsible for allocating and deallocating resources.
When a resource does not need deallocation, the second argument is a null pointer.
This class ensures that only the allocated resources are deallocated when something goes wrong.
