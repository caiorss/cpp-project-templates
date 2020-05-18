debug:
	cmake -B_build -H. -DCMAKE_BUILD_TYPE=Debug
	cmake --build _build --target

release:
	cmake -B_build -H. -DCMAKE_BUILD_TYPE=Release
	cmake --build _build --target

clean:
	rm -rfv ./_build ./bin

# Build docker image encapsulating development dependencies
docker-image:
	docker build -f wx-build.dockerfile -t wx-build .

# Run bash shell REPL on the container with X11 (Xorg Enabled) and map this directory to /cwd
#
docker-shell:
	xhost +local:docker
	docker run -it --rm --user "$(shell id -u):$(shell id -g)" \
	-v $(shell pwd):/cwd \
	-w /cwd \
	-e DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v ${HOME}/.Xauthority:/root/.Xauthority \
	wx-build 

# 	--env HOST_UID=$(shell id -u) --env HOST_GID=$(shell id -g) \

# Compile project within the container
docker-compile:
	xhost +local:docker
	docker run -it --rm --user "$(shell id -u):$(shell id -g)" \
	-v $(shell pwd):/cwd \
	-w /cwd \
	-e DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v ${HOME}/.Xauthority:/root/.Xauthority \
	wx-build make

