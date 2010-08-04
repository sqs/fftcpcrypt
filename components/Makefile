CXX   = c++
CPPFLAGS +=     -fno-rtti              \
                -fno-exceptions        \
		-fshort-wchar          \
                -shared  

GECKO_SDK_PATH = /home/sqs/src/xulrunner-sdk/

# GCC only define which allows us to not have to #include mozilla-config 
# in every .cpp file.  If your not using GCC remove this line and add 
# #include "mozilla-config.h" to each of your .cpp files. 
GECKO_CONFIG_INCLUDE = -include mozilla-config.h 

GECKO_DEFINES  = -DMOZILLA_STRICT_API

GECKO_INCLUDES = -I $(GECKO_SDK_PATH)/include 

GECKO_LDFLAGS =  -L $(GECKO_SDK_PATH)/lib \
		 -lxpcomglue_s   \
		 -lxpcom         \
                 -lnspr4         \
                 -lplds4      

SRC = tcTcpcryptSocketProvider.cpp tcHttptHandler.cpp tcTcpcryptModule.cpp

OBJ = $(SRC:.cpp=.so)

%.so: %.cpp
	$(CXX) -Wall -Os -o $@ $(CPPFLAGS) $(CXXFLAGS) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $< $(GECKO_LDFLAGS) 
	chmod +x $@
	strip $@

build: $(OBJ)

clean: 
	rm $(OBJ)
