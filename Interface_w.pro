QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    all_func.cpp \
    all_func_call.cpp \
    all_func_low.cpp \
    main.cpp \
    mainwindow.cpp \
    tests.cpp \

HEADERS += \
    BigInteger.h \
    Euler_and_Karmayr.h \
    Factorization.h \
    MillerRabinTest.h \
    all_func.h \
    all_func_call.h \
    big_integers/bigint.h \
    big_integers/mod_bigint.h \
    bigint.h \
    findingCircularPolynomial.h \
    finding_the_order.h \
    inverse.h \
    mainwindow.h \
    mod_bigint.h \
    mod_sqrt.h \
    montgomery_form.h \
    polynomial.h \
    polynomial_field.h \
    polynomial_ring.h \
    polynomials/polynomial.h \
    tests.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    Euler_and_Karmayr.h.gch \
    Interface_w.pro.user \
    One_Ring_Blender_Render.png \
    README.md \
    polynomial_field.h.gch
