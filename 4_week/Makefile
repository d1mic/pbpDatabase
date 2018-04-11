compound_example : compound_example.sqc
	./prevodjenje compound_example vstud student abcdef
savep_example : savep_example.sqc
	./prevodjenje savep_example vstud student abcdef
	
.PHONY: all clean
all : compound_example savep_example
clean:
	rm -rf *.c *.bnd *.o savep_example compound_example