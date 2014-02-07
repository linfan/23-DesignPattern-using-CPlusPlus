all:
	for f in `ls -l | grep '^d' | grep -v '\(UML\|ignore\)' | awk '{print $$NF}'`; do cd $$f; rm -f main build.log; g++ -o main main.cc > build.log 2>&1; if [ -x main ]; then echo "[Done]: $$f"; else echo "[Fail]: $$f"; fi; cd ..; done

clean:
	find . -name 'main' | xargs rm -f
	find . -name 'build.log' | xargs rm -f

