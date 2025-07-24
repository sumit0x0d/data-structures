#include <stdlib.h>
#include <time.h>

#include <circular-buffer.h>

int main()
{
     srand((int)time(NULL));
     struct circular_buffer *cBuffer = CircularBuffer_Create(sizeof (int), 20);
     (void)cBuffer;
     return 0;
}
