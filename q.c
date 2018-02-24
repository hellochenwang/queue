#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT_SIZE 255 + 1

typedef struct queueStru {
	_Atomic unsigned int head;
	_Atomic unsigned int tail;
	unsigned int maxSize;
	char* elements;
} queue;

queue* createQueue(int maxSize) {
	queue* q = (queue*)malloc(sizeof(queue));
	q->head = 0, q->tail = 0;
	q->maxSize = maxSize + 1;
	unsigned int charArrSize = maxSize * MAX_ELEMENT_SIZE;
	q->elements = (char*)malloc(charArrSize);
	memset(q->elements, 0, charArrSize);

	return q;
}

void freeQueue(queue* q) {
	free(q->elements);
	free(q);
}

int enqueue(queue* q, char* element) {
	int nextTail = (q->tail + 1) % q->maxSize;
	if (nextTail == q->head) {
		return -1;
	}

	strncpy(&q->elements[q->tail * MAX_ELEMENT_SIZE], element, MAX_ELEMENT_SIZE);

	q->tail = nextTail;
	return 1;
}

char* dequeue(queue* q) {
	if (q->head == q->tail) {
		return NULL;
	}
	int head = q->head;
	q->head = (q->head + 1) % q->maxSize;

	return &q->elements[head * MAX_ELEMENT_SIZE];
}

int main() {
	int ret;
	char* msg;

	queue* q = createQueue(3);

	msg = dequeue(q);
	printf("dequeue: %s\n", msg);

	ret = enqueue(q, "first message");
	printf("enqueue: %d\n", ret);

	ret = enqueue(q, "second message");
	printf("enqueue: %d\n", ret);

	ret = enqueue(q, "third message");
	printf("enqueue: %d\n", ret);

	ret = enqueue(q, "fourth message");
	printf("enqueue: %d\n", ret);

	msg = dequeue(q);
	printf("dequeue: %s\n", msg);

	msg = dequeue(q);
	printf("dequeue: %s\n", msg);

	msg = dequeue(q);
	printf("dequeue: %s\n", msg);

	msg = dequeue(q);
	printf("dequeue: %s\n", msg);

	msg = dequeue(q);
	printf("dequeue: %s\n", msg);
}