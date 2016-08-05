/**
 *
 * @author  TRANTUAN
 * @email   trantuan24bk@gmail.com
 * @website www.dnelab.com
 *
 * @version 1.0
 * @history 
 * 		27/06/2016: First created.
 */
#include <stdio.h>
#include <stdlib.h>
#include "RingBuffer.h"

/**
 * Constructor.
 * Param : size 	Size of ring buffer.
 */
RingBuffer::RingBuffer(uint16_t size)
{
	pBuffer = new ringbuf_t[size];

	if(pBuffer != 0)
		buffer_size = size;
	else
		buffer_size = 0;

	empty();
}

/**
 * Destructor.
 */
RingBuffer::~RingBuffer()
{
	delete[] pBuffer;
}

/**
 * Check to see if the program has enough memory to allocate for ring buffer.
 * Param : None.
 * Return: 1 	Empty.
 * 		   0 	Not empty.
 */
uint8_t RingBuffer::isValid(void)
{
	if(pBuffer == 0)
		return 0;

	return 1;
}

/**
 * Check the ring buffer to see it's empty or not.
 * Param : None.
 * Return: 1 	Empty.
 * 		   0 	Not empty.
 */
uint8_t RingBuffer::isEmpty(void)
{
	if(index_head == index_tail)
		return 1;

	return 0;
}

/**
 * Get next index of item in the ring buffer.
 * Param : uint16_t 	Current index.
 * Return: uint16_t 	Next index.
 */
uint16_t RingBuffer::nextIndex(uint16_t index)
{
	if(buffer_size == 0)
		return 0;

	if(index == (buffer_size - 1))
		return 0;

	return (index + 1);
}

/**
 * Get previous index of item in the ring buffer.
 * Param : uint16_t 	Current index.
 * Return: uint16_t 	Previous index.
 */
uint16_t RingBuffer::prevIndex(uint16_t index)
{
	if(buffer_size == 0)
		return 0;

	if(index == 0)
		return (buffer_size - 1);

	return (index - 1);
}

/**
 * Add new value to the buffer. Overwrite oldest value if buffer is full.
 * Param : ringbuf_t 	Input value
 * Return: None.
 */
void RingBuffer::push(ringbuf_t value)
{
	if(buffer_size == 0)
		return;

	if(index_head == prevIndex(index_tail))
		pop();

	pBuffer[index_head] = value;

	// Update head
	index_head = nextIndex(index_head);
}

/**
 * Read and remove the oldest value in the buffer.
 * Param : None.
 * Return: ringbuf_t 	Read value.
 */
ringbuf_t RingBuffer::pop(void)
{
	if(buffer_size == 0)
		return 0;

	if(index_tail == index_head)
		return 0;

	// Read value
	ringbuf_t value = pBuffer[index_tail];

	// Update tail
	index_tail = nextIndex(index_tail);

	return value;
}

/**
 * Empty all existing values in the buffer.
 * Param : None.
 * Return: None.
 */
void RingBuffer::empty()
{
	index_head = 0;
	index_tail = 0;
}

/**
 * Get number of elements stored in buffer.
 * Param : None.
 * Return: Number of elements.
 */
uint16_t RingBuffer::length(void)
{
	if(!isValid())
		return 0;
	
	if(isEmpty())
		return 0;

	uint16_t length = 0;
	uint16_t index  = index_tail;
	
	while(1)
	{
		index = nextIndex(index);
		length++;

		if(index == index_head)
		{
			return length;
		}
	}
}

/**
 * Read newest value in the buffer.
 * It does NOT pop the value after read.
 * Param : None.
 * Return: ringbuf_t 	Read value.
 */
ringbuf_t RingBuffer::valueHead(void)
{
	if(buffer_size == 0)
		return 0;

	if(index_tail == index_head)
		return 0;

	// Read value
	ringbuf_t value = pBuffer[prevIndex(index_head)];

	return value;
}

/**
 * Read oldest value in the buffer.
 * It does NOT pop the value after read.
 * Param : None.
 * Return: ringbuf_t 	Read value.
 */
ringbuf_t RingBuffer::valueTail(void)
{
	if(buffer_size == 0)
		return 0;

	if(index_tail == index_head)
		return 0;

	// Read value
	ringbuf_t value = pBuffer[index_tail];

	return value;
}

