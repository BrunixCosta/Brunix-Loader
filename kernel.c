/* XXX these must be at top */
#include "code16gcc.h"
_asm_ ("jmpl  $0, $main\n");
 


 
#define _NOINLINE  __attribute_((noinline))
#define _REGPARM   __attribute_ ((regparm(3)))
#define _NORETURN  __attribute_((noreturn))




 
/* BIOS interrupts must be done with inline assembly */

void    __NOINLINE __REGPARM print(const char   *s) {

        while(*s) {

                _asm_ _volatile_ ("int  $0x10" : : "a"(0x0E00 | *s), "b"(7));
                s++;
        }
}





/* and for everything else you can use C! Be it traversing the filesystem, or verifying the kernel image etc.*/

 
void __NORETURN main(){

    print("woo hoo!\r\n:)");

    while(1);

}
