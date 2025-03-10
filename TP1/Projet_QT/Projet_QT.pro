#-------------------------------------------------
#
# Project created by QtCreator 2017-02-26T16:39:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet_QT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Vue/main.cpp \
    Vue/SelectionOptimisation.cpp \
    Vue/SolutionOptimisation.cpp \
    Vue/MainWindow.cpp \
    Modele/Algo.cpp \
    Modele/Arene.cpp \
    Modele/Graphe.cpp \
    Modele/Pokemon.cpp \
    Modele/Pokestop.cpp \
    Modele/Sommet.cpp

HEADERS  += mainwindow.h \
    Vue/SelectionOptimisation.h \
    Vue/SolutionOptimisation.h \
    Vue/MainWindow.h \
    Modele/Algo.h \
    Modele/Arene.h \
    Modele/Chemin.h \
    Modele/Graphe.h \
    Modele/Pokemon.h \
    Modele/Pokestop.h \
    Modele/Sommet.h \
    Modele/Depart.h

FORMS    += mainwindow.ui
