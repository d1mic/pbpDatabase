repetableRead : repetableRead.sqc
	./prevodjenje repetableRead vstud student abcdef
readStability : readStability.sqc
	./prevodjenje readStability vstud student abcdef
cursorStability : cursorStability.sqc
	./prevodjenje cursorStability vstud student abcdef
testInsert: testInsert.sqc
	./prevodjenje testInsert vstud student abcdef
testUpdate: testUpdate.sqc
	./prevodjenje testUpdate vstud student abcdef

.PHONY: clean all

all: testInsert testUpdate cursorStability repetableRead readStability

clean: 
	rm -rf *.bnd *.o *.c *~ testInsert testUpdate cursorStability repetableRead readStability