#include <QApplication>
#include <QSplashScreen>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

#define _GNU_SOURCE
#include <dlfcn.h>

const char* FUNC_SYMBOL = "_ZN13QSplashScreen9setPixmapERK7QPixmap";
const char* ENV_VAR_NAME = "OVERRIDE_QT_SPLASH";
typedef void (*orig_setpixmap_f_type)(QSplashScreen *, const QPixmap &pixmap);

void QSplashScreen::setPixmap(const QPixmap &pixmap){

    const char* img_path = std::getenv(ENV_VAR_NAME);

    // At least let people know something is afoot...
    printf("hacked splash: %s\n", img_path);

    // If loading the hacked pixmap doesn't work, fall back on the original
    QPixmap hacked_pixmap;
    if(!hacked_pixmap.load(img_path)){
        hacked_pixmap = pixmap;
    }

    // Use some nuts function pointer black magic to replace the
    // compiled QSplashScreen::setPixmap() with ours...
    orig_setpixmap_f_type orig_setpixmap;
    orig_setpixmap = (orig_setpixmap_f_type)dlsym(RTLD_NEXT, FUNC_SYMBOL);
    orig_setpixmap(this, hacked_pixmap);
}
