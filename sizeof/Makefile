SOURCE:=/pool/Game/TF2/source-sdk-2013/mp/src
INCLUDES:=-I$(SOURCE)/game/shared -I$(SOURCE)/game/server -I$(SOURCE)/public -I$(SOURCE)/public/tier0 -I$(SOURCE)/public/tier1

sizeof: sizeof.cpp
	g++ -m32 -DGNUC -DPOSIX -DLINUX -D_LINUX $(INCLUDES) -o $@ $<
