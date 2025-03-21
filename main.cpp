/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include <QApplication>
#include <QTranslator>
#include <QLocale>

#include <TApplication.h>

#include "mainwindow.h"

int
main( int argc, char** argv)
{
    TApplication rootapp( "Qt ROOT Application", &argc, argv);
    QApplication app( argc, argv);

//    QTranslator* translator = new QTranslator();
//    translator->load( "Cross2022_" + QLocale::system().name());
//    app.installTranslator(translator);

    MainWindow* window = new MainWindow();
    window->show();

    int res = app.exec();

    delete window;
//    delete translator;

    return res;
}
