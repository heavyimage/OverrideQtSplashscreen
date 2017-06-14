#include <QApplication>
#include <QSplashScreen>
#include <stdio.h>
#include <stdlib.h>

void QSplashScreen::setPixmap(QPixmap const&){
    printf("hello world!");
}
