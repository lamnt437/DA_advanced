/* Uses red-black trees to sort like sort -n -- i.e. it treats each
   line as an integer, and sorts it that way.  If the lines are not
   integers, or there are duplicate lines, anything goes.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/fields.h"

int main()
{
  JRB b;
  JRB bn;
  b = make_jrb();

  jrb_insert_str(b, "11", new_jval_s("Hello, world11"));
  jrb_insert_str(b, "12", new_jval_s("Hello, world12"));
  jrb_insert_str(b, "19", new_jval_s("Hello, world19"));
  jrb_insert_str(b, "1", new_jval_s("Hello, world1"));

  jrb_traverse(bn, b) {
    printf("%s ", jval_s(bn->val));
  }

  bn = jrb_find_str(b, "11");
  printf("Search result: %s ", jval_s(bn->val));
  exit(0);
}