FROM debian:stable
RUN  apt-get update 
RUN  apt-get -y install build-essential mingw-w64 
RUN  apt-get -y install cmake ninja-build
RUN  apt-get install -y  libwxgtk3.0-dev wx3.0-examples wx3.0-doc

WORKDIR /cwd 
# ENTRYPOINT /bin/bash
