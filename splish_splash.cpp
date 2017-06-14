#include <QApplication>
#include <QSplashScreen>
#include <stdio.h>
#include <stdlib.h>

void QSplashScreen::setPixmap(const QPixmap &pixmap){
    printf("hello world!");
    QSplashScreen::setPixmap(pixmap);
}
