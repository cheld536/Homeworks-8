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

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		printf("--------------[ 김 윤 희 ] ----------[ 2018038014 ]--------------\n");
		printf("----------------------------------------------------------------\n");
		

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	listNode *findnode = h->rlink;				
	listNode *prev = NULL;
	while (findnode != NULL && findnode != h) {		// findnode가 NULL이 아니면
		prev = findnode;							// findnode를 변경하기 전에 prev에 기억
		findnode = findnode->rlink;					// findnode를 다음 노드로 이동
		free(prev);									// 이전 노드 해제 
	}
	free(h);							// 헤더 해제
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* newNode = (listNode*)malloc(sizeof(listNode));		//삽입할 노드를 동적할당한다.
	listNode* findNode;												//노드를 탐색할 노드
	newNode->key = key;												//입력받은 키값을 새로운 노드에 저장										
	listNode* first;												//처음 주소값을 저장할 노드
	first =h;														//first에 처음 주소값을 저장
	findNode = h;													//헤드 부터 탐색하기 위해 탐색 노드에 처음 주소 값을 저장
	while (findNode->rlink != NULL && findNode->rlink != first)		// lastNode가 널 값을 만나거나 맨 앞을 만날때 까지
		findNode = findNode->rlink;									// 다음 주소로 넘어감

	newNode->llink = findNode;										// 새로운 노드의 왼쪽에 이전 노드를 위치시킴
	newNode->rlink = first;											// 새로운 노드의 오른쪽에 헤더를 가르킴
	findNode->rlink = newNode;										// 마지막 노드의 오른쪽에 새로운 노드를 위치시킴
	first->llink =newNode;											// 헤더의 왼쪽에 새로운 노드를 위치 시킴
	
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	listNode* first = h;
	listNode* prev = NULL;

	if(first == NULL)									//헤더가 가르키는 노드가 없을때						
	{
		printf("노드가 비었습니다.\n");
		return 1;										// 0을 반환
	}
	if(first->rlink == h)								// 헤더가 자기 자신을 가르킬때.
	{
		printf("노드를 지울수없습니다.\n");
		return 1;
	}
	
	while(h->rlink != first)
	{
		prev = h;											// 이전 주소를 저장
		h= h->rlink;										// 다음 주소로 이동
	}
	
	prev->rlink= first;										// 이전노드의 다음 노드를 헤더로 변경
	first->llink = prev;										// 헤더의 llink를 이전 노드로 변경
	free (h);													// 마지막 노드를 해제

	
	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* newnode = (listNode*)malloc(sizeof(listNode));			// 사용자로부터 새로운 값을 입력받을 노드를 동적 할당한다.
	newnode->key = key;													//새로운 노드를 초기화한다.
	newnode->rlink = NULL;
	newnode->llink = NULL;

	
	if(h->rlink == h)													// 헤더가 비어 있을 때
	{							
		h->rlink = newnode;												//헤더의 다음노드를 newnode로 설정
		newnode->rlink = h;												//newnode의 다음노드를 헤더로 설정
		newnode->llink = h;												//newnode의 이전노드를 헤더로 설정
		h->llink = newnode;												//헤더의 이전노드를 newnode로 설정
	}
	else{																// 노드가 한 개 이상 있을 때 
		newnode->rlink = h->rlink;										// newnode의 오른쪽에 h.rlink의 노드가 위치하게 한다.
		h->rlink->llink = newnode;										// h.rlink의 노드의 왼쪽에 newnode가 위치하게 한다.
		h->rlink = newnode;												// 헤더의 오른족에 newnode를 위치하게 한다.					
		newnode->llink = h;												// newnode의 왼쪽이 헤더가 위치하게 한다.
	}

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	listNode* removenode = h->rlink;				// 첫번째 노드를 지우기 위한 removenode 선언 첫번째 노드의 위치로 위치 시킨다.
	if(h->rlink == h)								// 만약 헤더 밖에 없을때
	{
		printf("노드를 지울 수 없습니다.\n");
		return 1;
	}
	else if(h == NULL)								// 헤더가 비었을때
	{
		printf("노드가 비었습니다.\n");
		return 1;
	}
	else											// 그 외에 경우 
	{
		h->rlink = removenode->rlink;
		removenode->rlink->llink = h;
		free(removenode);

	}
	

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	listNode* first = h;	//  처음 주소를저장하는 노드
	listNode* p;			//	헤드는 가만히 있고 나머지 노드들이 바뀌기 때문에 h.rlist 주소를 담는 노드
	listNode* q;			//	역순으로 변경해주기 위한 q,r노드들
	listNode* r;			
	p = h->rlink;			// 포인터 p를 h.rlist로 초기화
	q = h;					// q
	r = NULL;			
	if(h ->rlink == h )
	{
		printf("노드가 비었습니다.\n");
		return 1;
	}
	while (p != first) {		// 리스트의첫 번째 노드부터 링크를 따라 다음 노드로 이동하면서 노드간 연결을 바꾼다.
		r = q;				// r에 q의 주소값 전달
		q = p;				// q에 p 노드의 정보를 저장
		p = p->rlink;		// 다음 노드를 찾는다.
		q->rlink = r;		// q의 오른쪽에 r을 위치 시킴
		r->llink = q;		// r의 왼쪽에 q를 위치시킴.
	}
	first->rlink = q;	// 역순으로 배치하기 위해서 헤더의 오른쪽에 q를 위치 시킴	
	q->llink = first;	// q의 왼쪽에 헤더를 위치



	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {
	listNode* newnode = (listNode*)malloc(sizeof(listNode));		// 노드를 입력받을 노드 
	listNode* findnode;												// 리스트를 탐색할 노드
	listNode* pre = NULL;											// findnode의 이전 주소를 담을 노드
	
	newnode->key = key;												// 사용자로부터 입력받을 노드 초기화
   	newnode->rlink = NULL;
    newnode->llink = NULL;

	if(h->rlink == h)									// 헤더가 비었을때
	{
		h->rlink = newnode;
		newnode->llink = h;
		h->llink = newnode;
		newnode->rlink = h;
		
		
	}
	else												// 노드가 비어있지 않을때
	{	
		findnode = h;
		while (findnode->rlink != h )
		{
			
			findnode=findnode->rlink;
			if(findnode->key >= newnode->key)
				break;
			pre = findnode;	
		}
		
		if( pre == NULL)				// 찾는 값이 처음 값보다 작을때 findnode의 이전노드의 주소값이 저장 되지 않으므로 
		{
			h->rlink = newnode;
			newnode->llink = h;
			newnode->rlink = findnode;
			findnode -> llink = newnode;
		}
		else if (pre->rlink == h)		 // 입력된 값이 젤 마지막에 들어갈때
		{
			findnode->rlink = newnode;
			newnode->llink = h;
			newnode->rlink = h;
			h->llink = newnode;
			
		}
		else								// 중간에 값이 들어 갈때
		{
			pre->rlink=newnode;
			newnode->rlink = findnode;
			findnode->llink = newnode;
			newnode->llink = pre;
		}


	}


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode* findnode = NULL;						// 탐색 노드
	listNode* prev = NULL; 							// 탐색 노드의 이전 노드 저장
	if(h->rlink == h)								// 헤더 밖에 없을때
	{
		printf("노드를 지울 수 없습니다.\n");
		return 1;
	}
	else if(h == NULL)								// 헤더가 비었을때
	{
		printf("노드가 비었습니다.\n");
		return 1;
	}
	else
	{
		findnode = h;								// 헤더의 주소를 findnode에 저장한다.
		while (findnode->rlink != h)				// 탐색 노드가 헤더를 만날 때 까지
		{
			prev = findnode;						// 탐색 하기전에 이전 노드에 탐색 노드의 주소를 저장
			findnode= findnode->rlink;				// 다음 이동
			if(findnode->key == key)				// 탐색하는 값이 입력값과 같을 때
				break;
								
			
		}
		if(prev == findnode)								// 이전 노드와 탐색노드 위치가 같을 떄
		{
			h->rlink = findnode->rlink;						
			findnode->rlink->llink = h;
			free(findnode);
		}
		else											// 그외에 탐색하는 값이 중간에 있을 때 
		{
			prev->rlink = findnode->rlink;
			findnode->rlink->llink = prev;
			free(findnode);
		}

	}
	return 0;
}


