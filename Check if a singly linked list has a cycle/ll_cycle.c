#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {    
    node *s=head;
    node *f=head;

    while (f!=NULL && f->next!=NULL) {
        s=s->next;
        f=f->next->next;
        if (s==f) {
            return 1;
        }
    }
    return 0;

}
