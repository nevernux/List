/*
 * list.c
 *
 *  Created on: Nov 24, 2016
 *      Author: zhangyihong
 */
#include <list_my.h>
#include "FreeRTOS.h"
#include "stddef.h"
#include "list_my.h"
static ListNode   newNode(void * data);
static ListResult addNode(List list,ListNode node);
static ListResult insertNodeBeforeNode(ListNode insertNode,ListNode node);
static ListResult insertNodeAfterNode(ListNode insertNode,ListNode node);
static ListResult deleteNode(List list,ListNode node);
static ListResult deleteList(List list);
static ListNode   getNode(List list,uint32_t index);
static ListNode   getNextNode(ListNode node);
static ListNode   getPrevNode(ListNode node);
struct _Operations operations = {
		newNode,
		addNode,
		insertNodeBeforeNode,
		insertNodeAfterNode,
		deleteNode,
		deleteList,
		getNode,
		getNextNode,
		getPrevNode,
};
List newList(void)
{
	List list = List(List)listMalloc(sizeof(struct _List));
	if(list==NULL)return list;
	list->head = NULL;
	list->length = 0;
	list->ops = &operations;
	return list;
}
static ListNode newNode(void * data){
	ListNode node = List(ListNode)listMalloc(sizeof(struct _ListNode));
	if(node == NULL)return NULL;
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

static ListResult addNode(List list,ListNode node){
	ListNode pnode = list->head;
	if(node == NULL)return LIST_NO_MEM;
	if(pnode == NULL)
	{
		list->head = node;
		list->length+=1;
		return LIST_OK;
	}
	while(1)
	{
		if(pnode->next == NULL)
			{
				pnode->next = node;
				node->prev = pnode;
				list->length+=1;
				return LIST_OK;
			}else{
				pnode = pnode->next;
			}
	}
}

static ListResult insertNodeBeforeNode(ListNode insertNode,ListNode node)
{
	if(insertNode == NULL || node == NULL){
		return LIST_ERROR;
	}
	insertNode->prev = getPrevNode(node);
	getPrevNode(node)->next = insertNode;
	insertNode->next = node;
	node->prev = insertNode;

	return LIST_OK;
}
static ListResult insertNodeAfterNode(ListNode insertNode,ListNode node)
{
	if(insertNode == NULL || node == NULL){
			return LIST_ERROR;
		}
	insertNode->next = getNextNode(node);
	getNextNode(node)->prev = insertNode;
	node->next = insertNode;
	insertNode->prev = node;
	return LIST_OK;
}
static ListResult deleteNode(List list,ListNode node){
	if(node->prev == NULL)
	{
		list->head = getNextNode(node);
		list->head->prev = NULL;
	}else if(getNextNode(node)!=NULL)
	{
		getPrevNode(node)->next = getNextNode(node);
		getNextNode(node)->prev = getPrevNode(node);
	}else{
		getPrevNode(node)->next = NULL;
	}
	listFree(node->data);
	listFree(node);
	list->length-=1;
	return LIST_OK;
}
static ListResult deleteList(List list){
	while(1)
	{
		if(list->length == 0)
		{
			listFree(list);
			return LIST_OK;
		}
		else{
			deleteNode(list,list->head);
		}
	}
}
static ListNode  getNode(List list,uint32_t index){
	uint32_t i = 0;
	ListNode pnode = list->head;
	if(index>list->length-1)
	{
		return NULL;
	}else
	{
		for(;i<index;i++){
			if(pnode->next!=NULL)
				pnode = pnode->next;
			else
				return NULL;
		}
		return pnode;
	}
}
static ListNode  getNextNode(ListNode node){
	if(node!=NULL)
		return node->next;
	else
		return NULL;
}
static ListNode getPrevNode(ListNode node){
	if(node!=NULL)
			return node->prev;
		else
			return NULL;
}
