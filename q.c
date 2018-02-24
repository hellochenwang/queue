#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT_SIZE 50 + 1

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
	unsigned int charArrSize = q->maxSize * MAX_ELEMENT_SIZE;
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

	memset(&q->elements[q->tail * MAX_ELEMENT_SIZE], 0, MAX_ELEMENT_SIZE);
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

unsigned int count(queue* q) {
	if (q->head <= q->tail) {
		return q->tail - q->head;
	} else {
		return q->maxSize - (q->head - q->tail);
	}
}

int main() {
	int ret;
	char* msg;

	queue* q = createQueue(3);

	msg = dequeue(q);
	printf("dequeue: %s, count: %d\n", msg, count(q));

	ret = enqueue(q, "first message");
	printf("enqueue: %d, count: %d\n", ret, count(q));

	ret = enqueue(q, "second message");
	printf("enqueue: %d, count: %d\n", ret, count(q));

	ret = enqueue(q, "third message");
	printf("enqueue: %d, count: %d\n", ret, count(q));

	ret = enqueue(q, "fourth message");
	printf("enqueue: %d, count: %d\n", ret, count(q));

	msg = dequeue(q);
	printf("dequeue: %s, count: %d\n", msg, count(q));

	msg = dequeue(q);
	printf("dequeue: %s, count: %d\n", msg, count(q));

	ret = enqueue(q, "fifth message");
	printf("enqueue: %d, count: %d\n", ret, count(q));

	msg = dequeue(q);
	printf("dequeue: %s, count: %d\n", msg, count(q));

	msg = dequeue(q);
	printf("dequeue: %s, count: %d\n", msg, count(q));

	msg = dequeue(q);
	printf("dequeue: %s, count: %d\n", msg, count(q));
}
