#include "mem.h"
#include <unistd.h>

#define BLOCK_MIN_SIZE 4

const char* message = "This is custom malloc! )\n"; 

static struct mem* heap_start;

// Calcilate suitable size = k * page_size

size_t align(size_t size){

	size_t page_size = sysconf(_SC_PAGESIZE);
	size_t aligned_size = size + (page_size - size % page_size);
	return aligned_size;

}

// Init new chunk with default (maybe not needed)

void* chunk_init(struct mem* const chunk, size_t size){

	chunk->next = NULL;
	chunk->capacity = size;
	chunk->is_free = true;

	return chunk;
}

//Heap-init...

void* heap_init(size_t initial_size){

	//printf("%s\n", "Init-heaping...");

	size_t size = align(initial_size + sizeof(struct mem));
	heap_start = (struct mem*) mmap(HEAP_START, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
	if(heap_start == MAP_FAILED)
		return NULL;
	heap_start = HEAP_START;
	chunk_init(heap_start, size - sizeof(struct mem));
	write(2, message, 25);
	return heap_start;

}

//Main malloc code

void* _malloc(size_t query){

	if (query < BLOCK_MIN_SIZE)
		query = BLOCK_MIN_SIZE;

	if (heap_start != HEAP_START)
		heap_init(query);

	if(!heap_start)
		return NULL;

	//printf("%s\n", "Allocation started");

	struct mem* previous_chunk = NULL;
	struct mem* cur_chunk = heap_start;
	struct mem* split_chunk = NULL;

	//Search for suitable chunk (HIGHLY disoptimised)


	while(cur_chunk){

		if( (cur_chunk->is_free) && (query + sizeof(struct mem) + BLOCK_MIN_SIZE <= cur_chunk->capacity)){

			split_chunk = (struct mem*) ( (int64_t) cur_chunk + query + sizeof(struct mem));
			split_chunk->capacity = cur_chunk->capacity - query - sizeof(struct mem);
			split_chunk->is_free = true;
			split_chunk->next = cur_chunk->next;
			cur_chunk->next = split_chunk;
			cur_chunk->capacity = query;
			cur_chunk->is_free = false;

			//printf("%d\n", cur_chunk->capacity);
			//printf("%s\n", "Done");

			//printf("%ld\n", cur_chunk);

			return (void*) ( (int64_t) cur_chunk + sizeof(struct mem));

		}

		previous_chunk = cur_chunk;
		cur_chunk = cur_chunk->next;

	}

	//printf("%s\n", "No chunks found, trying to mmap");

	//No chiks mmap'ing

	void* end_adress = (void*) ((int64_t)previous_chunk + sizeof(struct mem) + previous_chunk->capacity);

	size_t size = align(query + BLOCK_MIN_SIZE + sizeof(struct mem) - previous_chunk->capacity);

	struct mem* new_chunk = (struct mem*) mmap(end_adress, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS | MAP_FIXED, -1, 0);

	// No chunks at end mmap'ing again


	if(new_chunk == MAP_FAILED){
	//printf("%s\n", "No chunks at the end, mmap'ing again");

	//printf("%d\n", size);

		size = align(sizeof(struct mem) + query);

		struct mem* new_chunk = (struct mem*) mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

		if (new_chunk == MAP_FAILED){
			//printf("%s\n", "No memory for you");
			return NULL;
		}

		previous_chunk->next = new_chunk;
		new_chunk->is_free = false;
		new_chunk->next = NULL;
		new_chunk->capacity = size - sizeof(struct mem);

		return (void*) ( (int64_t) new_chunk + sizeof(struct mem));
	}

	previous_chunk->capacity += size;
	split_chunk = (struct mem*) ( (int64_t) previous_chunk + query + sizeof(struct mem));
	split_chunk->capacity = previous_chunk->capacity - query - sizeof(struct mem);
	split_chunk->is_free = true;
	split_chunk->next = previous_chunk->next;
	previous_chunk->next = split_chunk;
	previous_chunk->capacity = query;
	previous_chunk->is_free = false;

	//printf("%s\n", "Done");

	return (void*) ( (int64_t) previous_chunk + sizeof(struct mem));
}

void merge(struct mem* const chunk){

	struct mem* next_chunk = chunk->next;

	//printf("%s\n", "Try to merge");
	//printf("%ld\n", chunk);
	//printf("%ld\n", next_chunk);

	if (next_chunk != NULL && next_chunk->is_free 
		&& ((int64_t) next_chunk - (int64_t) chunk == sizeof(struct mem) + chunk->capacity)){

		chunk->capacity += sizeof(struct mem) + next_chunk->capacity;
		chunk->next = next_chunk->next;

		merge(chunk);
 
		}	
	}

void _free( void* mem ){

	//printf("%s\n", "Freeing memory");

	struct mem* start_adress = (struct mem*) ( (int64_t) mem - sizeof(struct mem));

	start_adress->is_free = true;

	merge(start_adress);

}