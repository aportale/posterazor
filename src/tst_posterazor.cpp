/*
    PosteRazor - Make your own poster!
    Copyright (C) 2005-2009 by Alessandro Portale
    http://posterazor.sourceforge.net/

    This file is part of PosteRazor

    PosteRazor is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PosteRazor is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PosteRazor; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "mainwindow.h"
#include "controller.h"
#include "posterazorcore.h"
#if defined (FREEIMAGE_LIB)
#   include "imageloaderfreeimage.h"
#else
#   include "imageloaderqt.h"
#endif

#include <QtTest>
#include <QtGui>

#if !defined(QT_SHARED) && !defined(QT_DLL) && !defined(FREEIMAGE_LIB)
Q_IMPORT_PLUGIN(qgif)
Q_IMPORT_PLUGIN(qjpeg)
Q_IMPORT_PLUGIN(qtiff)
#endif

class PosteRazorTests: public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void screenShotterize();

public:
    static QRect cropRect(const QImage &image, const QColor &color);
};

void PosteRazorTests::initTestCase()
{
    QCoreApplication::setApplicationName("PosteRazor");
#if QT_VERSION >= 0x040400
    QCoreApplication::setApplicationVersion("1.9.5");
#endif
    QCoreApplication::setOrganizationName("CasaPortale");
    QCoreApplication::setOrganizationDomain("de.casaportale");
}

void PosteRazorTests::screenShotterize()
{
    const QDir translationDir(":/Translations/");
    const QColor backgroundColor(Qt::white);

    QLabel background;
    QPalette palette = background.palette();
    palette.setColor(QPalette::Window, backgroundColor);
    background.setPalette(palette);
    background.setAutoFillBackground(true);
    background.showFullScreen();
    QTest::qWaitForWindowShown(&background);

    foreach (const QFileInfo &translation, translationDir.entryInfoList(QDir::Files)) {
        const QString localeString(translation.baseName());
        MainWindow window;
        ImageLoaderQt imageLoader;
        PosteRazorCore posteRazorCore(&imageLoader);
        Controller controller(&posteRazorCore, &window);
        controller.loadInputImage("../packaging/iss/wizimage.bmp");
        controller.loadTranslation(localeString);
        window.resize(QSize());
        window.show();
        const QString screenShotFileName =
                QString::fromLatin1("ScreenShot-%1.png").arg(localeString);
        QTest::qWaitForWindowShown(&window);
        QTest::qWait(500); // Wait for fancy effects to finish

        const QImage screenShot =
                QPixmap::grabWindow(QApplication::desktop()->screen()->winId())
                .toImage()
                .convertToFormat(QImage::Format_ARGB32);

        const QRect crop = PosteRazorTests::cropRect(screenShot, backgroundColor);
        screenShot.copy(crop).save(screenShotFileName);
    }
}

static inline bool imageRowHasUniqueColor(const QImage &image, int row, const QColor &color)
{
    const QRgb *rowData = reinterpret_cast<const QRgb*>(image.scanLine(row));
    const QRgb colorRgba = color.rgba();
    for (int i = 0; i < image.width(); ++i)
        if (*(rowData++) != colorRgba)
            return false;
    return true;
}

static inline bool imageColumnHasUniqueColor(const QImage &image, int column, const QColor &color)
{
    const QRgb *bits = reinterpret_cast<const QRgb*>(image.bits()) + column;
    const QRgb colorRgba = color.rgba();
    for (int y = 0; y < image.height(); ++y) {
        if (*bits != colorRgba)
            return false;
        bits += image.width();
    }
    return true;
}

QRect PosteRazorTests::cropRect(const QImage &image, const QColor &color)
{
    QRect result = image.rect();

    int coordinate = 0;
    while (image.height() >= coordinate && imageRowHasUniqueColor(image, coordinate, color))
        coordinate++;
    result.setTop(coordinate);

    coordinate = image.height() - 1;
    while (coordinate >= result.top() && imageRowHasUniqueColor(image, coordinate, color))
        coordinate--;
    result.setBottom(coordinate);

    coordinate = 0;
    while (image.width() >= coordinate && imageColumnHasUniqueColor(image, coordinate, color))
        coordinate++;
    result.setLeft(coordinate);

    coordinate = image.width() - 1;
    while (coordinate >= result.left() && imageColumnHasUniqueColor(image, coordinate, color))
        coordinate--;
    result.setRight(coordinate);

    return result;
}

QTEST_MAIN(PosteRazorTests)
#include "tst_posterazor.moc"
