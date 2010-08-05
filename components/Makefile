CXX   = c++
CFLAGS += -Wall -W -Wno-unused -Wpointer-arith -Wcast-align -W -pedantic -Wno-long-long -fno-strict-aliasing -pthread -pipe -DDEBUG -D_DEBUG -DTRACING -g
CPPFLAGS +=     -fno-rtti              \
                -fno-exceptions        \
		-fshort-wchar          \
		-fmessage-length=0     \
                -shared  

INCLUDES=-I../../tcpcrypt/code/user -I../../tcpcrypt/code/user/tcpcrypt
LIBS=-L../../tcpcrypt/code/user/lib -ltcpcrypt

#GECKO_SDK_PATH = /home/sqs/src/xulrunner-sdk/
GECKO_SDK_PATH = /home/sqs/src/mozilla-central/objdir-ff-debug/dist/sdk

# GCC only define which allows us to not have to #include mozilla-config 
# in every .cpp file.  If your not using GCC remove this line and add 
# #include "mozilla-config.h" to each of your .cpp files. 
GECKO_CONFIG_INCLUDE = -include mozilla-config.h 

GECKO_DEFINES  = -DMOZILLA_STRICT_API

GECKO_INCLUDES = -I $(GECKO_SDK_PATH)/include \
                 -I /home/sqs/src/mozilla-central/objdir-ff-debug/dist/include

GECKO_LDFLAGS =  -L $(GECKO_SDK_PATH)/lib \
		 -lxpcomglue_s   \
		 -L/home/sqs/src/mozilla-central/objdir-ff-debug/dist/bin \
		 -lmozalloc      \
		 -lxpcom         \
                 -lnspr4         \
                 -lplds4 -lplc4 -ldl -Wl,-Bsymbolic

SRC = tcTcpcryptSocketProvider.cpp tcTcpcryptModule.cpp

OBJ = tcTcpcryptSocketProvider.so

$(OBJ): $(SRC)
	$(CXX) -Wall -Os -o $@ $(CPPFLAGS) $(CFLAGS) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(INCLUDES) $(SRC) $(GECKO_LDFLAGS) $(LIBS)
	chmod +x $@
#	strip $@

build: $(OBJ)

clean: 
	rm $(OBJ)
