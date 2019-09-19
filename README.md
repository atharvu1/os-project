# os-project
This repository contains the solution of the Sleeping Teaching Assistant problem given in the book "Operating System Concepts: By Abraham Silberschatz, Peter B Galvin and Gerg Gange".

## Problem Statement : 

A university computer science department has a teaching assistant (TA) who helps undergraduate students with their programming assignments during regular office hours. The TA's office is rather small and has room for only one desk with a chair and computer. There are three chairs in the hallway outside the office where students can sit and wait if the TA is currently helping another student. When there are no students who need help during office hours, the TA sits at the desk and takes a nap. If a student arrives during office hours and finds the TA sleeping, the student must awaken the TA to ask for help. If a student arrives and finds the TA currently helping another student, the student sits on one of the chairs in the hallway and waits. If no chairs are available, the student will come back at a later time.

## How to run
1. Since this file contains addtional C libraries you need to compile it by using extra [OPTIONS]
  Example : 
  ```bash
  $gcc -pthread sleeping-assistant.c
  ```
  Since in my case the file name is sleeping-assistant.c, you can replace it by your's filename.
2. To run 
  ```bash
   $./a.out
  ```
  
  For any query please feel free to [mail](mailto:atharvu1@gmail.com) me
 
