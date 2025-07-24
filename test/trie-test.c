#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "trie.h"

int
main()
{
     srand((int)time(NULL));

     Trie *trie = Trie_Create();

     Trie_Destroy(trie);

     return 0;
}
