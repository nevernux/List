/*
 * list.h
 *
 *  Created on: Nov 24, 2016
 *      Author: zhangyihong
 */

#ifndef LIST_MY_H_
#define LIST_MY_H_
#include "stm32f4xx_hal.h"

#define List(type) (type)
#define listMalloc	pvPortMalloc
#define listFree	vPortFree
typedef struct _List * List;
typedef enum {
	LIST_OK=0,
	LIST_NO_MEM,
	LIST_NULL,
	LIST_FULL,
	LIST_ERROR
}ListResult;
typedef struct _ListNode{
	void * data;
	struct _ListNode *prev;
	struct _ListNode *next;
}* ListNode;

typedef struct _Operations{
	ListNode  (* newNode)(void * data);
	ListResult(* addNode)(List list,ListNode node);
	ListResult(* insertNodeBeforeNode)(ListNode insertNode,ListNode node);
	ListResult(* insertNodeAfterNode)(ListNode insertNode,ListNode node);
	ListResult(* deleteNode)(List list,ListNode node);
	ListResult(* deleteList)(List list);
	ListNode  (* getNode)(List list,uint32_t index);
	ListNode  (* getNextNode)(ListNode node);
	ListNode  (* getPrevNode)(ListNode node);
}* Operations;

struct _List{
	ListNode head;
	uint32_t length;
	Operations ops;
};
extern List newList(void);
#endif /* LIST_H_ */
