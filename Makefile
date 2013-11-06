TARGET		= pngout
OBJECTS 	= pngout.o images.o dots_img.o no_dots_img.o point.o
#######################################################################################
# -I/usr/local/opt/libpng12/include
# -L/usr/local/opt/libpng12/lib

#CFLAGS   = -g -Wall -DNO_FREETYPE -I/usr/local/include 
CXXFLAGS = -g -Wall -DNO_FREETYPE -I/usr/local/include
ASFLAGS  = -Wall
LDFLAGS  = -g -Wall -L/usr/local/opt/libpng12/lib -L/usr/local/lib -lpng -lpngwriter -lz

CC = gcc
AS = gcc
CXX = g++

########################################################################################
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

pngout.o: images.h point.h
images.o: images.h
dots_img.o: images.h
no_dots_img.o: images.h
point.o: point.h

clean: 
	rm -f $(OBJECTS) $(TARGET)