SOURCE_SDK:=/pool/Game/TF2/source-sdk-2013

sizeof: sizeof.cpp
	g++ -m32 -DGNUC -DPOSIX -DLINUX -D_LINUX -I"$(SOURCE_SDK)/mp/src/public" -I"$(SOURCE_SDK)/mp/src/public/tier0" -o $@ $<
