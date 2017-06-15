//#include <qsplashscreen.h>
//#include <QWidget>
#include <QApplication>
#include <QSplashScreen>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

#define _GNU_SOURCE
#include <dlfcn.h>

typedef void (*orig_setpixmap_f_type)(const QPixmap &pixmap);
typedef void (QSplashScreen::*orig_setpixmap_f_type)(const QPixmap &pixmap);

void QSplashScreen::setPixmap(const QPixmap &pixmap){
    printf("YO YO YO\n\n\n\n");

    const char* img_path = std::getenv("CM_HACK_NUKE_SPLASH");
    printf(img_path);
    printf("\n");

    QPixmap hacked_pixmap;
    if(!hacked_pixmap.load(img_path)){
        hacked_pixmap = pixmap;
    }

    // OPTION 1: Attempt to grab OG setPixmap function and pass along fake image to that...
    orig_setpixmap_f_type orig_setpixmap;
    orig_setpixmap = (orig_setpixmap_f_type)dlsym(RTLD_NEXT, "_ZN13QSplashScreen9setPixmapERK7QPixmap");
    this->*orig_setpixmap(hacked_pixmap);
}



