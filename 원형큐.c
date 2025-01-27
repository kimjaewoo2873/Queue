#include <stdio.h>
#include <stdlib.h>
 
#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return q->front == q->rear;
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void queue_print(QueueType* q) {
	printf("Queue(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front; // rear은 이미 나아가있으니, front로 있는 부분부터 출력하려고
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			printf("%d | ", q->data[i]);
			if (i == q->rear)  // 큐의 끝에 도달하면 종료
				break;
		} while (i != q->rear); // i가 rear에 도착하기 전까지 순회
	}
	printf("\n");
}

void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화 상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백 상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element peek(QueueType* q) { // 큐의 첫번째 원소 반환 함수
	if (is_empty(q))
		error("큐가 공백 상태입니다.");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main(void) {
	QueueType queue;
	int element;
	init_queue(&queue);
	printf("--데이터 추가 단계--\n");
	while (!is_full(&queue)) {
		printf("정수를 입력하시오: ");
		scanf("%d", &element);
		enqueue(&queue, element);
		queue_print(&queue);
	}
	printf("큐는 포화상태입니다.\n\n");

	printf("--데이터 삭제 단계--\n");
	while (!is_empty(&queue)) {
		element = dequeue(&queue);
		printf("꺼내진 정수: %d \n", element);
		queue_print(&queue);
	}
	printf("큐는 공백상태입니다.\n");
}
