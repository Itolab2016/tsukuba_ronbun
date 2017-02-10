tsukuba2016:main.o joystick.o navigation.o avoid.o camera.o motor.o tsukuba_time.o tsukuba_tkk.o tsukuba_urg.o  Makefile
	g++ -g -O0 -Wall -o tsukuba2016 main.o joystick.o navigation.o avoid.o camera.o motor.o tsukuba_time.o tsukuba_tkk.o tsukuba_urg.o `pkg-config --libs opencv`  `urg_cpp-config --libs` `urg_cpp-config --libs` 

main.o:main.cpp tsukuba_def.h 
	g++ -g -O0 -Wall -c -o main.o main.cpp  `urg_cpp-config --cflags`
  
navigation.o:navigation.cpp navigation.h
	g++ -g -O0 -Wall -c -o navigation.o navigation.cpp

avoid.o:avoid.cpp avoid.h
	g++ -g -O0 -Wall -c -o avoid.o avoid.cpp
camera.o:camera.cpp camera.h
	g++ -g -O0 -Wall -c -o camera.o camera.cpp
joystick.o:joystick.cpp joystick.h
	g++ -g -O0 -Wall -c -o joystick.o joystick.cpp 
motor.o:motor.cpp motor.h
	g++ -g -O0 -Wall -c -o motor.o motor.cpp
tsukuba_time.o:tsukuba_time.cpp tsukuba_time.h
	g++ -g -O0 -Wall -c -o tsukuba_time.o tsukuba_time.cpp
tsukuba_tkk.o:tsukuba_tkk.cpp tsukuba_tkk.h
	g++ -g -O0 -Wall -c -o tsukuba_tkk.o tsukuba_tkk.cpp 
tsukuba_urg.o:tsukuba_urg.cpp tsukuba_urg.h
	g++ -g -O0 -c -o tsukuba_urg.o tsukuba_urg.cpp `urg_cpp-config --cflags`



clean:
	rm *.o tsukuba2016

