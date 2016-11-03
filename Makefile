all:
	mkdir -p build;
	cd build && \
	cmake -Wdev .. && \
	make -j4 && \
	./src/examples/RandomRealDemo && \
	./src/lib/CrocTest
