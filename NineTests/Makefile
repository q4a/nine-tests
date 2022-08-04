# curl -o visual.h -L https://raw.githubusercontent.com/wine-mirror/wine/master/dlls/d3d9/tests/visual.c
# sed -i "/^#include.*/d" wine/visual.h
# sed -i "s/LPDWORD/DWORD*/g" visual.h
# inject our includes
# remove create_window function
# remove StartTest(visual)
# remove test_sample_attached_rendertarget, test_fetch4, test_pointsize, test_map_synchronization, test_desktop_window
#
# REMOVE THIS ....
D3DADAPTER9_LOCATION="/lib/x86_64-linux-gnu/d3d/d3dadapter9.so"
#D3DADAPTER9_LOCATION="/install/lib/d3d/d3dadapter9.so" # for Mesa3D CI
CC=gcc -g
CXX=g++ -g

# 32 bits
#D3DADAPTER9_LOCATION="/usr/lib32/d3d/d3dadapter9.so"
#CC=gcc -g -m32
#CXX=g++ -g -m32

D3DADAPTER9_WITHDRI2=0

XNINE=Xnine.o dri3.o
XNINE_LINK=-ldl -lX11 -lXext -lxcb -lxcb-present -lxcb-dri3 -lxcb-xfixes -lX11-xcb

ifneq ($(D3DADAPTER9_WITHDRI2), 0)
 XNINE_LINK+=-lEGL -lGL
endif

EXEC=NineTests

all: $(EXEC)

Xnine.o: ../Xnine.c
	$(CC) -c ../Xnine.c -o Xnine.o -I ../include/D3D9 -I ../include -DD3DADAPTERPATH='$(D3DADAPTER9_LOCATION)' -DD3DADAPTER9_WITHDRI2=$(D3DADAPTER9_WITHDRI2)
dri3.o: ../dri3.c
	$(CC) -c ../dri3.c -o dri3.o -I ../include/D3D9 -DD3DADAPTER9_WITHDRI2=$(D3DADAPTER9_WITHDRI2)
NineTests: $(XNINE) NineTests.c
	$(CC) NineTests.c $(XNINE) $(XNINE_LINK) -I ../include/D3D9 -I ../include -I .. -o NineTests
clean:
	rm -f $(XNINE) $(SDLNINE)
	rm -f $(EXEC)

