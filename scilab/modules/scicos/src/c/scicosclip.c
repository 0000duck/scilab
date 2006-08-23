#include "machine.h"
#include <math.h>
#include "core_math.h" 
#include "../../graphics/includes/Graphics.h"
#include "../../graphics/includes/PloEch.h"
#include "../../graphics/includes/Xcall1.h"

void C2F(scicosclip)(int *n)
{
  if(*n==1){
    C2F(dr1)("xset","clipgrf",PI0,PI0,PI0,PI0, PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
  }
  else{
    C2F(dr1)("xset","clipoff",PI0,PI0,PI0,PI0, PI0,PI0,PD0,PD0,PD0,PD0,0L,0L);
  }
}
