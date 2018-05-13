/** @file libpriqueue.c
 */

#include <stdlib.h>
#include <stdio.h>

#include "libpriqueue.h"


/**
  Initializes the priqueue_t data structure.

  Assumtions
    - You may assume this function will only be called once per instance of priqueue_t
    - You may assume this function will be the first function called using an instance of priqueue_t.
  @param q a pointer to an instance of the priqueue_t data structure
  @param comparer a function pointer that compares two elements.
  See also @ref comparer-page
 */
void priqueue_init(priqueue_t *q, int(*comparer)(const void *, const void *))
{
	q->size = 0;
	q->comparer = comparer;
	q->head = NULL;
}


/**
  Inserts the specified element into this priority queue.

  @param q a pointer to an instance of the priqueue_t data structure
  @param ptr a pointer to the data to be inserted into the priority queue
  @return The zero-based index where ptr is stored in the priority queue, where 0 indicates that ptr was stored at the front of the priority queue.
 */
int priqueue_offer(priqueue_t *q, void *ptr)
{
	struct node *newnode = malloc( sizeof( struct node ) );
	struct node *prevnode = NULL;
	newnode->data = ptr;
	q->size++;
	if( q->head == NULL )
	{
		q->head = newnode;
		newnode->next = NULL;
		return 0;
	}
	else
	{
		int count = 0;
		tempnode = q->head;
		do {
			if( q->comparer( ptr, tempnode->data ) <= 0 ) // if insert is true
			{
				if( !count ) // should be inserted in the head
				{
					newnode->next = q->head;
					q->head = newnode;
					return count;
				}
				else
				{
					prevnode->next = newnode;
					newnode->next =  tempnode;
					return count;
				}
			}
			count++;
			prevnode = tempnode;
			tempnode = tempnode->next;
		} while( tempnode != NULL
		);

		prevnode->next = newnode; // insert node when it reaches the back end
		newnode->next = NULL;
		return count;
	}
}


/**
  Retrieves, but does not remove, the head of this queue, returning NULL if
  this queue is empty.

  @param q a pointer to an instance of the priqueue_t data structure
  @return pointer to element at the head of the queue
  @return NULL if the queue is empty
 */
void *priqueue_peek(priqueue_t *q)
{
	if( !q->size )
	{
		return NULL;
	}
	else
	{
		return q->head;
	}
}


/**
  Retrieves and removes the head of this queue, or NULL if this queue
  is empty.

  @param q a pointer to an instance of the priqueue_t data structure
  @return the head of this queue
  @return NULL if this queue is empty
 */
void *priqueue_poll(priqueue_t *q)
{
	void *temp;
	tempnode = q->head;
	if( !q->size )
	{
		return NULL;
	}
	else
	{
		q->head = tempnode->next;
		temp = tempnode->data;
		free( tempnode );
		q->size--;
		return ( temp );
	}
}


/**
  Returns the element at the specified position in this list, or NULL if
  the queue does not contain an index'th element.

  @param q a pointer to an instance of the priqueue_t data structure
  @param index position of retrieved element
  @return the index'th element in the queue
  @return NULL if the queue does not contain the index'th element
 */
void *priqueue_at(priqueue_t *q, int index)
{
	int count = 0;
	tempnode = q->head;
	if( index >= q->size )
	{
		return NULL;
	}
	else
	{
		while( count < index )
		{
			tempnode = tempnode->next;
			count++;
		}
		return tempnode->data;
	}
	return NULL;
}


/**
  Removes all instances of ptr from the queue.

  This function should not use the comparer function, but check if the data contained in each element of the queue is equal (==) to ptr.

  @param q a pointer to an instance of the priqueue_t data structure
  @param ptr address of element to be removed
  @return the number of entries removed
 */
int priqueue_remove(priqueue_t *q, void *ptr)
{
	if( !q->size )
	{
		return 0;
	}
	else
	{
		int count = 0;
		tempnode = q->head;
		struct node *prevnode = NULL;
		struct node *temp = NULL;
		int tempsize = q->size;
		for( int i = 0; i < tempsize; i++ )
		{
			if( tempnode->data == ptr ) // Match!!! Start deleting node
			{
				temp = tempnode; // make a backup so we don't loss track of the node
				if( q->head == tempnode ) // if it is the first node of the queue
				{
					q->head = tempnode->next;
				}
				else
				{
					prevnode->next = tempnode->next; // connect between 0+i and 2+i nodes
				}
				tempnode = tempnode->next; // have to do this before free, else tempnode doesn't know where next node is
				free( temp );
				q->size--;
				count++;
			}
			else
			{
				tempnode = tempnode->next; // don't touch this!!! I know you think you can put this outside of else, but memory will be bad
			}
			prevnode = tempnode;
		}
		return count;
	}
}


/**
  Removes the specified index from the queue, moving later elements up
  a spot in the queue to fill the gap.

  @param q a pointer to an instance of the priqueue_t data structure
  @param index position of element to be removed
  @return the element removed from the queue
  @return NULL if the specified index does not exist
 */
void *priqueue_remove_at(priqueue_t *q, int index)
{
	if( !q->size || q->size < index )
	{
		return NULL;
	}
	else
	{
		int count = 0;
		void *temp;
		tempnode = q->head; // made a copy of head address
		while( count != index )
		{
			tempnode = tempnode->next;
			count++;
		}
		temp = tempnode->data; //made a copy of element
		free( tempnode );
		q->size--;
		return temp; // can't do this????
	}
}


/**
  Returns the number of elements in the queue.

  @param q a pointer to an instance of the priqueue_t data structure
  @return the number of elements in the queue
 */
int priqueue_size(priqueue_t *q)
{
	if( !q->size )
	{
		return 0;
	}
	return q->size;
}


/**
  Destroys and frees all the memory associated with q.

  @param q a pointer to an instance of the priqueue_t data structure
 */
void priqueue_destroy(priqueue_t *q)
{
	if( !q->size )
	{
		return;
	}
	else
	{
		tempnode = q->head;
		struct node *prevnode;
		while( tempnode != NULL )
		{
			prevnode = tempnode;
			tempnode = tempnode->next;
			free( prevnode );
			q->size--;
		}
		q->head = NULL;
		return;
	}
}
