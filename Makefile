all:
	#gcc -I/usr/include/Qt -I/usr/includeQtGui -shared -fPIC splish_splash.cpp -o splish_splash.so
	gcc -shared -fPIC splish_splash.cpp -o splish_splash.so
