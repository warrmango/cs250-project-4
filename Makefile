
goal: git-commit qsort-test

qsort-test: qsort-test.c qsort-c.c qsort-asm.s
	gcc -g -o qsort-test qsort-test.c qsort-c.c qsort-asm.s

clean:
	rm -f qsort-test

.PHONY: git-commit
git-commit:
	git checkout master >> .local.git.out || echo
	git add *.c *.s Makefile >> .local.git.out  || echo
	git commit -a -m  \\"Commit qsort\\" >> .local.git.out ||     echo
	git push origin master

