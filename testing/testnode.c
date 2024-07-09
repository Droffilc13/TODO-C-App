#include "../node.h"
#include <stdio.h>
int main(void) {
    TodoNode *node1 = createNode("This is a task", "27/01/2019", COMPLETED);
    appendNode(&node1, "Hello world", "27/02/1900", PENDING);
    appendNode(&node1, "Hello world 3", "27/02/1900", PENDING);

    removeNode(&node1, 0);
    removeNode(&node1, 1);
    removeNode(&node1, 2);

    while (node1 != NULL) {
        printf("%s\n", node1->description);
        node1 = node1->next;
    }

    return 0;
}
