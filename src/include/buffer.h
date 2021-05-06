#ifndef TOOLBOX_BUFFER_H
#define TOOLBOX_BUFFER_H

const char *BUFFER_M_NAME = "toolbox.buffer";

#define toolbox_checkbuffer(L, i) (Buffer *)luaL_checkudata(L, i, BUFFER_M_NAME)

#define MIN(a, b) a > b ? b : a
#define MAX(a, b) a > b ? a : b

#define BUFFER_MIN_CAPACITY 50

// Writes to the buffer shall copy data in the data field. If the data to be
// written is larger than the (capacity - write_cursor) then an allocation is
// made to grow the size of data such that the new write will fit. The
// write_cursor is updated to next writable byte.

// Reads from the buffer shall copy data from the read_cursor up to the smaller
// of the destination or the number of bytes to the write cursor. The data
// behind the read_cursor shall never again be accessible. Reallocations caused
// by a write may reclaim the data behind the read_cursor.

typedef struct Buffer {
  size_t capacity;
  size_t write_cursor;
  size_t read_cursor;
  char *data;
} Buffer;

#endif
