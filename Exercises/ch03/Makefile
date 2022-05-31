CC := g++

INCLUDES := -I../../Definitions/ch03_Stack_Queue/Queue/LinkedDeque
INCLUDES += -I../../Definitions/ch03_Stack_Queue/Queue/LinkedQueue
INCLUDES += -I../../Definitions/ch03_Stack_Queue/Queue/PQueue
INCLUDES += -I../../Definitions/ch03_Stack_Queue/Queue/SeqDeque
INCLUDES += -I../../Definitions/ch03_Stack_Queue/Queue/SeqQueue
INCLUDES += -I../../Definitions/ch03_Stack_Queue/Stack/LinkedStack
INCLUDES += -I../../Definitions/ch03_Stack_Queue/Stack/SeqStack

%: %.cpp
	$(CC) $^ -o $@ $(INCLUDES)

clean:
	del *.exe