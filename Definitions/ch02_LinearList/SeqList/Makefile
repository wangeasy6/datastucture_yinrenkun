Main: SeqList.h main.cpp
	g++ $^ -o $@

Test: SeqList.h test.cpp
	g++ $^ -o $@

SetOp: SeqList.h SeqListSetOp.cpp
	g++ $^ -o $@

clean:
	del Main.exe Test.exe SetOp.exe