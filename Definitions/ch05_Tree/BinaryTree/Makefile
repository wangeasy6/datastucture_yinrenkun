CC := g++

INCLUDES += -I../../ch03_Stack_Queue/Queue/LinkedQueue
INCLUDES += -I../../ch03_Stack_Queue/Stack/LinkedStack

%: %.cpp
	$(CC) $^ -o $@ $(INCLUDES)

clean:
	del *.exe