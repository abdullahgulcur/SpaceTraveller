#include "pch.h"
#include "AndroidApplication.h"

android_app* AndroidApplication::application;

void AndroidApplication::init(android_app *app_){
    application = app_;
}


