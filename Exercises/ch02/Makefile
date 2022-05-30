CC := g++

INCLUDES := -I../../Definitions/ch02_LinerList/CircList
INCLUDES += -I../../Definitions/ch02_LinerList/DblList
INCLUDES += -I../../Definitions/ch02_LinerList/LinkedList
INCLUDES += -I../../Definitions/ch02_LinerList/SeqList
INCLUDES += -I../../Definitions/ch02_LinerList/StaticList

%: %.cpp
	$(CC) $^ -o $@ $(INCLUDES)

clean:
	del *.exe