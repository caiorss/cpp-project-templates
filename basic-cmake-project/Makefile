# GNU Make file script for easier compilation from
# command line

debug:
	cmake -B_build -H. -DCMAKE_BUILD_TYPE=Debug
	cmake --build _build --target

release:
	cmake -B_build -H. -DCMAKE_BUILD_TYPE=Release
	cmake --build _build --target

clean:
	rm -rfv ./_build 

