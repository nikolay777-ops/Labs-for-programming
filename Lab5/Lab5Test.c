#include "Lab5.h"
#include <assert.h>

void FirstTest()
{
    Queue* queue;
    int i;
    queue = (Queue*)malloc(sizeof(Queue));
    Init(queue);
    Push(queue, 50, 20, 30);
    Push(queue, 17, 19, 25);
    Push(queue, 21, 40, 36);
    Push(queue, 51, 152, 53);
    Push(queue, 66, 25, 512);
    Push(queue, 35, 24, 24);
    Push(queue, 2, 20, 54);
    Push(queue, 241, 25, 63);
    Push(queue, 73, 21, 531);
    Push(queue, 21, 41, 21);
    Push(queue, 23, 64, 21);
    Push(queue, 124, 23, 63);
    Push(queue, 50, 21, 63);
    assert(queue->size == 13);
    for (i = 12; i >= 0; i++)
    {
        Pop(queue);
        assert(queue->size == i - 1);
    }
    free(queue);
}

void SecondTest()
{
    Queue* queue;
    queue = (Queue*)malloc(sizeof(Queue));
    int i;
    Init(queue);
    for (i = 0; i < 30; i++)
    {
        Push(queue, rand() % 20, rand () % 30, rand() % 40);
    }
    Clear(queue);
    assert(queue == NULL);
    free(queue);
}

int main()
{
    void FirstTest();
    void SecondTest();
    printf("Tests are done successfully!");
    return 0;
}