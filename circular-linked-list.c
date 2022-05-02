/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node { // 노드 구조체
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h); // 리스트 초기화 함수
int freeList(listNode* h); // 리스트 동적 할당 해제 함수
int insertLast(listNode* h, int key); // 리스트 마지막에 노드 추가 함수
int deleteLast(listNode* h); // 리스트 마지막 노드 삭제 함수
int insertFirst(listNode* h, int key); // 리스트 첫번째 노드 추가 함수
int deleteFirst(listNode* h); // 리스트 첫번째 노드 삭제 함수
int invertList(listNode* h); // 리스트 노드 역순 재배치 함수

int insertNode(listNode* h, int key); // key 값 입력 받아 노드 추가 함수
int deleteNode(listNode* h, int key); // key 값 입력 받아 노드 삭제 함수

void printList(listNode* h); // 리스트 노드 출력 함수



int main()
{
	char command; // 명령어
	int key; // key 값
	listNode* headnode=NULL; // 헤드노드 NULL 초기화

	do{
		printf("\n[----- [Kim Hyeong Jin]  [2021041079] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z': // 메뉴 z
			initialize(&headnode); // 리스트 초기화 함수
			break;
		case 'p': case 'P': // 메뉴 p
			printList(headnode); // 리스트 노드 출력 함수
			break;
		case 'i': case 'I': // 메뉴 i
			printf("Your Key = ");
			scanf("%d", &key); // key 입력
			insertNode(headnode, key); // key 값보다 큰 값 노드 앞에 노드 추가 함수
			break;
		case 'd': case 'D': // 메뉴 d
			printf("Your Key = ");
			scanf("%d", &key); // key 입력
			deleteNode(headnode, key); // key 값 노드 삭제 함수
			break;
		case 'n': case 'N': // 메뉴 n
			printf("Your Key = ");
			scanf("%d", &key); // key 값 입력
			insertLast(headnode, key); // 리스트 마지막에 노드 추가 함수
			break;
		case 'e': case 'E': // 메뉴 e
			deleteLast(headnode); // 리스트 마지막 노드 삭제 함수
			break;
		case 'f': case 'F': // 메뉴 e
			printf("Your Key = ");
			scanf("%d", &key); // key 값 입력
			insertFirst(headnode, key); // 리스트 첫번째 노드 추가 함수
			break;
		case 't': case 'T': // 메뉴 t
			deleteFirst(headnode); // 리스트 첫번째 노드 삭제 함수
			break;
		case 'r': case 'R': // 메뉴 r
			invertList(headnode); // 리스트 노드 역순 재배치 함수
			break;
		case 'q': case 'Q': // 메뉴 q
			freeList(headnode); // 리스트 동적 할당 해제 함수
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 메뉴 q 시 반복문 탈출하여 종료

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h; // *h의 다음 노드 *h
	(*h)->llink = *h; // *h의 이전 노드 *h
	(*h)->key = -9999; // *h key 값에 임의 값 저장
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h) // h->rlink가 h인 경우
	{
		free(h); // h 할당 해제 후 종료
		return 1;
	}

	listNode* p = h->rlink; // p에 리스트 첫번째 노드 주소 저장

	listNode* prev = NULL; // prec NULL로 초기화
	while(p != NULL && p != h) {  // p가 NULL이 아니고 h가 아니면 반복
		prev = p; // prev가 p를 따르게 함
		p = p->rlink; // p 다음 노드 이동
		free(prev); // prev가 가리키는 노드 할당 해제
	}
	free(h); // h 할당 해제
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // h==NULL 이면
		printf("Nothing to print....\n"); // 에러 메시지 출력
		return;
	}

	p = h->rlink; // p가 첫번째 노드 가리키게 함

	while(p != NULL && p != h) { // p가 NULL이 아니고 h가 아니면
		printf("[ [%d]=%d ] ", i, p->key); // p가 가리키는 노드의 key 값 출력
		p = p->rlink; // p 다음 노드 이동
		i++; // i 증가
	}
	printf("  items = %d\n", i); // 노드 개수 출력


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); // 주소 출력

	i = 0;
	p = h->rlink; // 첫번째 노드 가리키게 함
	while(p != NULL && p != h) { // p가 NULL이 아니고 h가 아니면
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); // 주소 출력
		p = p->rlink; // p 다음 노드 이동
		i++; // i 증가
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1; // h가 NULL 이면 종료

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 추가할 노드 메모리 할당
	node->key = key; // node의 key에 입력받은 key 저장
	node->rlink = NULL; // NULL 초기화
	node->llink = NULL; // NULL 초기화

	if (h->rlink == h) /* 첫 노드로 삽입 */
	{
		h->rlink = node; //  h->rlink에 node 저장
		h->llink = node; // h->link에 node 저장
		node->rlink = h; // node의 rlink가 h를 가리키게 함
		node->llink = h; // node의 link가 h를 가리키게 함
	} else {
		h->llink->rlink = node; // h->link->rink에 node 저장
		node->llink = h->llink; // node의 link에 h의 link 저장
		h->llink = node; // h->link가 node를 가리키도록 함
		node->rlink = h; // node->rlink에 h 저장
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL) // h->link가 h와 같거나 h가 NULL이면
	{
		printf("nothing to delete.\n"); // 에러 메시지 출력
		return 1;
	}

	listNode* nodetoremove = h->llink; // 지울 노드 포인터가 마지막 노드를 가리키도록 함

	/* link 정리 */
	nodetoremove->llink->rlink = h; // 리스트 마지막 노드의 이전노드 rlink가 h를 가라키도록 함
	h->llink = nodetoremove->llink; // 헤드노드의 이전노드가 리스트 마지막 노드의 이전 노드가 되도록 함

	free(nodetoremove); // 지울 노드 포인터 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 추가할 노드 동적 할당
	node->key = key; // 추가할 노드의 key에 입력 받은 key 저장
	node->rlink = NULL; // NULL 초기화
	node->llink = NULL; // NULL 초기화


	node->rlink = h->rlink; // node의 다음노드가 리스트의 첫번째 노드가 되도록 함
	h->rlink->llink = node; // 리스트의 첫번째 노드의 이전노드가 node가 되도록 함
	node->llink = h; // node의 이전노드가 h가 되도록함
	h->rlink = node; // 리스트의 첫번째 노드가 node가 되도록 함


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h) // h가 NULL 또는 h->rlink가 h면
	{
		printf("nothing to delete.\n"); // 에러 메시지
		return 0;
	}

	listNode* nodetoremove = h->rlink; // 지울 노드 포인터가 리스트 첫번째 노드를 가리키도록 함

	/* link 정리 */
	nodetoremove->rlink->llink = h; // 리스트 첫번째 노드의 다음 노드의 link가 h를 가리키도록 함
	h->rlink = nodetoremove->rlink; // h의 다음노드가 리스트의 두번째 노드가 되도록 함

	free(nodetoremove); // 지울 노드 할당 해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) { // h->link가 h 또는 h가 NULL이면
		printf("nothing to invert...\n"); // 에러 메시지
		return 0;
	}
	listNode *n = h->rlink; // 노드를 가라키는 포인터
	listNode *trail = h; // middle 뒤 포인터
	listNode *middle = h; // n 뒤 포인터

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;

	while(n != NULL && n != h){ // n이 NULL이 아니고, n이 h와 다르면 반복
		trail = middle; // trail은 middle을 따름
		middle = n; // middle은 n을 따름
		n = n->rlink; // n 다음 노드 이동
		middle->rlink = trail; // middle 이전 노드가 trail이 가리키는 노드
		middle->llink = n; // middle 이전 노드가 n이 가리키는 노드
	}

	h->rlink = middle; // h의 다음 노드가 middle이 되도록 함

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 추가할 노드 할당
	node->key = key; // key 값 저장
	node->llink = node->rlink = NULL; // NULL 초기화

	if (h->rlink == h) // h->rlink가 h이면
	{
		insertFirst(h, key); // insertFirst 실행 후 종료
		return 1;
	}

	listNode* n = h->rlink; // 입력 받은 key값에 따르는 노드 포인터, h->rlink 저장

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) { // n이 NULL이 아니고 h가 아니면 반복
		if(n->key >= key) { // n이 가리키는 key가 입력 받은 key보다 크면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) { // n == h->rlink이면
				insertFirst(h, key); // insertFirst 실행
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; // node 다음 노드가 n이 가리키는 노드
				node->llink = n->llink; // node 이전 노드가 n의 이전 노드
				n->llink->rlink = node; // n의 이전노드의 다음노드가 node
				n->llink = node; // n의 이전노드가 node
			}
			return 0;
		}

		n = n->rlink; // key보다 큰 값 노드 찾지 못하면 다음 노드 이동
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); // insertLast 실행
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL) // h->rink == h 또는 h == NULL 이면
	{
		printf("nothing to delete.\n"); // 에러 메시지
		return 0;
	}

	listNode* n = h->rlink; // n이 가리키는 노드가 첫번째 노드가 되도록 함

	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); // deleteFirst 실행
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h); // deleteLast 실행
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; // n이 가리키는 노드의 이전노드의 다음노드가 n의 다음노드
				n->rlink->llink = n->llink; // n이 가리키는 노드의 이전노드의 다음노드가 n의 이전노드
				free(n); // n 할당 해제
			}
			return 0;
		}

		n = n->rlink; // key 값 노드가 없으면 다음노드 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key); // 에러 메시지와 key 값 출력 후 종료
	return 0;
}


