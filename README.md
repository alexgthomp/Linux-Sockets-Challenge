# Linux IPC Challenge
## Objective
Create a Client Server program that communicates via an IPC Mechanism. The client will accept an input and send it to the server. The server will manipulate the text and return the results to the client. The Client will then print the formatted text.

## Text Manipulation

Insert a line break (\n) after the last word before the 80th character until no additional text remains.

## Requirements
* Client and Server must be different processes
* The input can be a maximum of 500 characters
* Truncate any text after 500 characters
* If a word is longer than 80 characters that word can be split at the 80th location

## Questions

* Which IPC mechanism did I choose and why?

  I chose sockets because they were the IPC mechanism that I had previous experiences implementing.

* What are the strengths and weaknesses of your chosen IPC mechanism?
  
  **Strengths**
  * Widely used

  **Weaknesses**
  * Relatively Basic means of communication

* Can your system scale to handle thousands of requests per second?

  No, because it has a listen queue of 10 meaning after 10 requests get queued it will start dropping them.
  In order to handle thousands of request per second the system would need to have bigger queue size and at the least need to   be multi threaded. It would probably be better to implement on a distributed system to maintain performance with scalability.

