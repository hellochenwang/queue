# queue
Lock-Free Single-Producer-Single-Consumer String Circular Queue in C

two threads, one thread adding to the queue, the other thread taking from the queue. no locking, no mutex operations.

steps to use:
1. set the maximum element size - #define MAX_ELEMENT_SIZE 255 + 1

2. createQueue(int maxSize) - maxSize is how many elements max does this queue hold.

3. enqueue/dequeue/count

4. freeQueue(q)
