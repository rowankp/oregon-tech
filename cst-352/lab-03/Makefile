###################################################
# filename: Makefile
# purpose:  specifies rules for lab 03 stackl code
# notes:	$(opt) enables the use of an optional 
#			stacklc arguement, most commonly -dbg. 
#			To use, at the command line, opt=-dbg 
#			(i.e. make opt=-dbg)
# author:   Rowan parker
###################################################

all: system userlib usercode progam

system: system.c
	~philip.howard/bin/./stacklc -c system.c $(opt)

userlib: userio.c
	~philip.howard/bin/./stacklc -c userio.c $(opt)

usercode: user.c
	~philip.howard/bin/./stacklc -c user.c $(opt)

progam:
	~philip.howard/bin/./slasm system.sl $(opt)
	~philip.howard/bin/./slasm user.sl userio.sl $(opt)

clean:
	rm -f *.slb
	rm -f *.sl
	rm -f *.ast
	rm -f *.dbg