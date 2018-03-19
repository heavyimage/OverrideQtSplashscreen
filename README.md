This repo contains a tiny bit (~30 lines) of c++ which compile to a .so
file that allows you to dynamically change a Qt application's
QSplashScreen::setPixmap() method to use an image you provide via the
OVERRIDE_QT_SPLASH environment variable.

I created this because I was annoyed that it was impossible to change
Nuke's opening splash screen the same way you can in other DCC apps like
Maya and Houdini!

## Instructions:
* Download code and cd into repo
* run make
* setenv OVERRIDE_QT_SPLASH $NEW_SPLASH
* env LD_PRELOAD=$PWD/libsplish_splash.so.so.1.0.0 $APP

where:
* $NEW_SPLASH is a silly other image
* $APP is a qt application that draws a splash screen using this method

## Caveats:
* Might only work for nuke 10.0v5
* Will only work on linux / places where LD_PRELOAD is supported
* Might not work at all

## LD_PRELOAD
The heart of this trick involves using LD_PRELOAD.  For an explanation of this powerful feature of the dynamic linker, check out [this writeup](https://rafalcieslak.wordpress.com/2013/04/02/dynamic-linker-tricks-using-ld_preload-to-cheat-inject-features-and-investigate-programs/).

For more advanced LD_PRELOAD tricks, including some of the stuff used by this prank, check [this out](http://www.goldsborough.me/c/low-level/kernel/2016/08/29/16-48-53-the_-ld_preload-_trick/).

## Process:
* nm -D /path/to/libnuke.so (+ studio?) -- grep for splash
* use c++filt -n to unmask function names
* explore header:
    * /usr/include/Qt/qsplashscreen.h
    * QSplashScreen::qt_metacall(QMetaObject::Call, int, void**)
    * QSplashScreen::qt_metacast(char const*)
    * QSplashScreen::showMessage(QString const&, int, QColor const&)
    * QSplashScreen::drawContents(QPainter*)
    * QSplashScreen::mousePressEvent(QMouseEvent*)
    * QSplashScreen::event(QEvent*)
    * QSplashScreen::setPixmap(QPixmap const&)
    * QSplashScreen::QSplashScreen(QPixmap const&, QFlags<Qt::WindowType>)
    * QSplashScreen::~QSplashScreen()
    * Nuke::setSplashScreen(QSplashScreen*)
    * QSplashScreen::metaObject() const
    * typeinfo for QSplashScreen
    * typeinfo for Foundry::About::NukeAboutScreenT<QSplashScreen>
    * typeinfo for Foundry::About::NukeSplashScreen
    * typeinfo name for Foundry::About::NukeAboutScreenT<QSplashScreen>
    * typeinfo name for Foundry::About::NukeSplashScreen
    * vtable for Foundry::About::NukeAboutScreenT<QSplashScreen>
    * vtable for Foundry::About::NukeSplashScreen
* put function signature into own file
* Get some help with the c++ metaprogramming stuff...
* setenv QMAKESPEC /usr/lib64/qt4/mkspecs/linux-g++
* Generate pro file
* TODO: explain changes to .pro file (disable linking)
* generate a makefile from the .pro file also using qmake

## TODO:
* stop with the ln'ing
