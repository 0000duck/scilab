#include "scicos_block.h"

void scicos_free(void *p)
{
  return free(p);
}
