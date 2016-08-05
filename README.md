# RingBuffer

Features
------------

* Advantages

 - Can be use with any data types: char, int, float, long,...
 - Compatible with Arduino or any general purpose C++ compilers.

```C++ 
typedef float ringbuf_t;
```

* Functions

```C++
	void push(ringbuf_t value);
	ringbuf_t pop(void);

	void empty(void);

	uint16_t length(void);

	uint8_t isEmpty(void);
	uint8_t isValid(void);

	// Read values without pop from buffer
	ringbuf_t valueTail(void);
	ringbuf_t valueHead(void);
```

Contributors
------------

* Tran Tuan