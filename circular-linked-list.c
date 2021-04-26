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
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
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
		printf("--------------[ �� �� �� ] ----------[ 2018038014 ]--------------\n");
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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h){
	listNode *findnode = h->rlink;				
	listNode *prev = NULL;
	while (findnode != NULL && findnode != h) {		// findnode�� NULL�� �ƴϸ�
		prev = findnode;							// findnode�� �����ϱ� ���� prev�� ���
		findnode = findnode->rlink;					// findnode�� ���� ���� �̵�
		free(prev);									// ���� ��� ���� 
	}
	free(h);							// ��� ����
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {
	listNode* newNode = (listNode*)malloc(sizeof(listNode));		//������ ��带 �����Ҵ��Ѵ�.
	listNode* findNode;												//��带 Ž���� ���
	newNode->key = key;												//�Է¹��� Ű���� ���ο� ��忡 ����										
	listNode* first;												//ó�� �ּҰ��� ������ ���
	first =h;														//first�� ó�� �ּҰ��� ����
	findNode = h;													//��� ���� Ž���ϱ� ���� Ž�� ��忡 ó�� �ּ� ���� ����
	while (findNode->rlink != NULL && findNode->rlink != first)		// lastNode�� �� ���� �����ų� �� ���� ������ ����
		findNode = findNode->rlink;									// ���� �ּҷ� �Ѿ

	newNode->llink = findNode;										// ���ο� ����� ���ʿ� ���� ��带 ��ġ��Ŵ
	newNode->rlink = first;											// ���ο� ����� �����ʿ� ����� ����Ŵ
	findNode->rlink = newNode;										// ������ ����� �����ʿ� ���ο� ��带 ��ġ��Ŵ
	first->llink =newNode;											// ����� ���ʿ� ���ο� ��带 ��ġ ��Ŵ
	
	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	listNode* first = h;
	listNode* prev = NULL;

	if(first == NULL)									//����� ����Ű�� ��尡 ������						
	{
		printf("��尡 ������ϴ�.\n");
		return 1;										// 0�� ��ȯ
	}
	if(first->rlink == h)								// ����� �ڱ� �ڽ��� ����ų��.
	{
		printf("��带 ����������ϴ�.\n");
		return 1;
	}
	
	while(h->rlink != first)
	{
		prev = h;											// ���� �ּҸ� ����
		h= h->rlink;										// ���� �ּҷ� �̵�
	}
	
	prev->rlink= first;										// ��������� ���� ��带 ����� ����
	first->llink = prev;										// ����� llink�� ���� ���� ����
	free (h);													// ������ ��带 ����

	
	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {
	listNode* newnode = (listNode*)malloc(sizeof(listNode));			// ����ڷκ��� ���ο� ���� �Է¹��� ��带 ���� �Ҵ��Ѵ�.
	newnode->key = key;													//���ο� ��带 �ʱ�ȭ�Ѵ�.
	newnode->rlink = NULL;
	newnode->llink = NULL;

	
	if(h->rlink == h)													// ����� ��� ���� ��
	{							
		h->rlink = newnode;												//����� ������带 newnode�� ����
		newnode->rlink = h;												//newnode�� ������带 ����� ����
		newnode->llink = h;												//newnode�� ������带 ����� ����
		h->llink = newnode;												//����� ������带 newnode�� ����
	}
	else{																// ��尡 �� �� �̻� ���� �� 
		newnode->rlink = h->rlink;										// newnode�� �����ʿ� h.rlink�� ��尡 ��ġ�ϰ� �Ѵ�.
		h->rlink->llink = newnode;										// h.rlink�� ����� ���ʿ� newnode�� ��ġ�ϰ� �Ѵ�.
		h->rlink = newnode;												// ����� �������� newnode�� ��ġ�ϰ� �Ѵ�.					
		newnode->llink = h;												// newnode�� ������ ����� ��ġ�ϰ� �Ѵ�.
	}

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	listNode* removenode = h->rlink;				// ù��° ��带 ����� ���� removenode ���� ù��° ����� ��ġ�� ��ġ ��Ų��.
	if(h->rlink == h)								// ���� ��� �ۿ� ������
	{
		printf("��带 ���� �� �����ϴ�.\n");
		return 1;
	}
	else if(h == NULL)								// ����� �������
	{
		printf("��尡 ������ϴ�.\n");
		return 1;
	}
	else											// �� �ܿ� ��� 
	{
		h->rlink = removenode->rlink;
		removenode->rlink->llink = h;
		free(removenode);

	}
	

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {
	listNode* first = h;	//  ó�� �ּҸ������ϴ� ���
	listNode* p;			//	���� ������ �ְ� ������ ������ �ٲ�� ������ h.rlist �ּҸ� ��� ���
	listNode* q;			//	�������� �������ֱ� ���� q,r����
	listNode* r;			
	p = h->rlink;			// ������ p�� h.rlist�� �ʱ�ȭ
	q = h;					// q
	r = NULL;			
	if(h ->rlink == h )
	{
		printf("��尡 ������ϴ�.\n");
		return 1;
	}
	while (p != first) {		// ����Ʈ��ù ��° ������ ��ũ�� ���� ���� ���� �̵��ϸ鼭 ��尣 ������ �ٲ۴�.
		r = q;				// r�� q�� �ּҰ� ����
		q = p;				// q�� p ����� ������ ����
		p = p->rlink;		// ���� ��带 ã�´�.
		q->rlink = r;		// q�� �����ʿ� r�� ��ġ ��Ŵ
		r->llink = q;		// r�� ���ʿ� q�� ��ġ��Ŵ.
	}
	first->rlink = q;	// �������� ��ġ�ϱ� ���ؼ� ����� �����ʿ� q�� ��ġ ��Ŵ	
	q->llink = first;	// q�� ���ʿ� ����� ��ġ



	return 0;
}



/**
 *  ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� 
 **/
int insertNode(listNode* h, int key) {
	listNode* newnode = (listNode*)malloc(sizeof(listNode));		// ��带 �Է¹��� ��� 
	listNode* findnode;												// ����Ʈ�� Ž���� ���
	listNode* pre = NULL;											// findnode�� ���� �ּҸ� ���� ���
	
	newnode->key = key;												// ����ڷκ��� �Է¹��� ��� �ʱ�ȭ
   	newnode->rlink = NULL;
    newnode->llink = NULL;

	if(h->rlink == h)									// ����� �������
	{
		h->rlink = newnode;
		newnode->llink = h;
		h->llink = newnode;
		newnode->rlink = h;
		
		
	}
	else												// ��尡 ������� ������
	{	
		findnode = h;
		while (findnode->rlink != h )
		{
			
			findnode=findnode->rlink;
			if(findnode->key >= newnode->key)
				break;
			pre = findnode;	
		}
		
		if( pre == NULL)				// ã�� ���� ó�� ������ ������ findnode�� ��������� �ּҰ��� ���� ���� �����Ƿ� 
		{
			h->rlink = newnode;
			newnode->llink = h;
			newnode->rlink = findnode;
			findnode -> llink = newnode;
		}
		else if (pre->rlink == h)		 // �Էµ� ���� �� �������� ����
		{
			findnode->rlink = newnode;
			newnode->llink = h;
			newnode->rlink = h;
			h->llink = newnode;
			
		}
		else								// �߰��� ���� ��� ����
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
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {
	listNode* findnode = NULL;						// Ž�� ���
	listNode* prev = NULL; 							// Ž�� ����� ���� ��� ����
	if(h->rlink == h)								// ��� �ۿ� ������
	{
		printf("��带 ���� �� �����ϴ�.\n");
		return 1;
	}
	else if(h == NULL)								// ����� �������
	{
		printf("��尡 ������ϴ�.\n");
		return 1;
	}
	else
	{
		findnode = h;								// ����� �ּҸ� findnode�� �����Ѵ�.
		while (findnode->rlink != h)				// Ž�� ��尡 ����� ���� �� ����
		{
			prev = findnode;						// Ž�� �ϱ����� ���� ��忡 Ž�� ����� �ּҸ� ����
			findnode= findnode->rlink;				// ���� �̵�
			if(findnode->key == key)				// Ž���ϴ� ���� �Է°��� ���� ��
				break;
								
			
		}
		if(prev == findnode)								// ���� ���� Ž����� ��ġ�� ���� ��
		{
			h->rlink = findnode->rlink;						
			findnode->rlink->llink = h;
			free(findnode);
		}
		else											// �׿ܿ� Ž���ϴ� ���� �߰��� ���� �� 
		{
			prev->rlink = findnode->rlink;
			findnode->rlink->llink = prev;
			free(findnode);
		}

	}
	return 0;
}


