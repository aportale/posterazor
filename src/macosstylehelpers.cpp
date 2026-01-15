/*
    PosteRazor - Make your own poster!
    Copyright (C) 2005-2018 by Alessandro Portale
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

#include "macosstylehelpers.h"

#ifdef Q_OS_MACOS

#include <QApplication>
#include <QPalette>
#include <QColor>

namespace MacOSStyleHelpers
{
    StyleColors getStyleColors()
    {
        QPalette palette = QApplication::palette();
        StyleColors colors;
        
        colors.windowColor = palette.color(QPalette::Window);
        colors.baseColor = palette.color(QPalette::Base);
        colors.buttonColor = palette.color(QPalette::Button);
        colors.buttonTextColor = palette.color(QPalette::ButtonText);
        colors.highlightColor = palette.color(QPalette::Highlight);
        colors.textColor = palette.color(QPalette::WindowText);
        colors.isDarkMode = colors.windowColor.lightness() < 128;
        
        colors.panelBgColor = colors.isDarkMode 
            ? QColor(30, 30, 30, 230) 
            : QColor(255, 255, 255, 240);
        colors.groupBoxBgColor = colors.isDarkMode 
            ? QColor(40, 40, 40, 200) 
            : QColor(250, 250, 250, 220);
        colors.borderColor = colors.isDarkMode 
            ? QColor(60, 60, 60) 
            : QColor(220, 220, 220);
        colors.borderColorLight = colors.isDarkMode 
            ? QColor(70, 70, 70) 
            : QColor(210, 210, 210);
        
        return colors;
    }
    
    QString getButtonStyleSheet(const StyleColors &colors)
    {
        QColor hoverBg = colors.isDarkMode 
            ? QColor(colors.buttonColor.lighter(110)) 
            : QColor(colors.buttonColor.darker(105));
        QColor hoverBorder = colors.isDarkMode 
            ? QColor(80, 80, 80) 
            : QColor(150, 150, 150);
        QColor pressedBg = colors.isDarkMode 
            ? QColor(colors.buttonColor.darker(120)) 
            : QColor(colors.buttonColor.lighter(110));
        QColor disabledBg = colors.isDarkMode 
            ? QColor(40, 40, 40) 
            : QColor(240, 240, 240);
        QColor disabledText = colors.isDarkMode 
            ? QColor(100, 100, 100) 
            : QColor(180, 180, 180);
        QColor disabledBorder = colors.isDarkMode 
            ? QColor(50, 50, 50) 
            : QColor(200, 200, 200);
        
        return QLatin1String(
            "QPushButton {"
            "    background-color: %1;"
            "    color: %2;"
            "    border: 1px solid %3;"
            "    border-radius: 6px;"
            "    padding: 6px 16px;"
            "    font-size: 13px;"
            "    min-height: 30px;"
            "}"
            "QPushButton:hover {"
            "    background-color: %4;"
            "    border-color: %5;"
            "}"
            "QPushButton:pressed {"
            "    background-color: %6;"
            "}"
            "QPushButton:disabled {"
            "    background-color: %7;"
            "    color: %8;"
            "    border-color: %9;"
            "}"
        ).arg(colors.buttonColor.name())
         .arg(colors.buttonTextColor.name())
         .arg(colors.borderColor.name())
         .arg(hoverBg.name())
         .arg(hoverBorder.name())
         .arg(pressedBg.name())
         .arg(disabledBg.name())
         .arg(disabledText.name())
         .arg(disabledBorder.name());
    }
    
    QString getToolButtonStyleSheet(const StyleColors &colors)
    {
        QColor hoverBg = colors.isDarkMode 
            ? QColor(60, 60, 60, 150) 
            : QColor(220, 220, 220, 150);
        QColor pressedBg = colors.isDarkMode 
            ? QColor(80, 80, 80, 200) 
            : QColor(200, 200, 200, 200);
        
        return QLatin1String(
            "QToolButton {"
            "    background-color: transparent;"
            "    border: 1px solid transparent;"
            "    border-radius: 6px;"
            "    padding: 4px 8px;"
            "    min-height: 24px;"
            "}"
            "QToolButton:hover {"
            "    background-color: %1;"
            "}"
            "QToolButton:pressed {"
            "    background-color: %2;"
            "}"
            "QToolButton:checked {"
            "    background-color: %3;"
            "    border-color: %4;"
            "}"
        ).arg(hoverBg.name(QColor::HexArgb))
         .arg(pressedBg.name(QColor::HexArgb))
         .arg(colors.highlightColor.name())
         .arg(colors.highlightColor.darker(120).name());
    }
    
    QString getGroupBoxStyleSheet(const StyleColors &colors)
    {
        return QLatin1String(
            "QGroupBox {"
            "    background-color: %1;"
            "    border: 1px solid %2;"
            "    border-radius: 10px;"
            "    margin-top: 12px;"
            "    padding-top: 16px;"
            "    font-weight: 600;"
            "    color: %3;"
            "}"
            "QGroupBox::title {"
            "    subcontrol-origin: margin;"
            "    subcontrol-position: top left;"
            "    left: 12px;"
            "    padding: 0px 8px 0px 8px;"
            "    background-color: %4;"
            "    border-radius: 4px;"
            "}"
        ).arg(colors.groupBoxBgColor.name(QColor::HexArgb))
         .arg(colors.borderColorLight.name())
         .arg(colors.textColor.name())
         .arg(colors.groupBoxBgColor.name(QColor::HexArgb));
    }
    
    QString getPanelStyleSheet(const StyleColors &colors, int borderRadius)
    {
        return QLatin1String(
            "QFrame {"
            "    background-color: %1;"
            "    border-radius: %2px;"
            "    border: 1px solid %3;"
            "}"
        ).arg(colors.panelBgColor.name(QColor::HexArgb))
         .arg(borderRadius)
         .arg(colors.borderColor.name());
    }
    
    QString getLabelStyleSheet(const StyleColors &colors, int borderRadius)
    {
        return QLatin1String(
            "QLabel {"
            "    background-color: %1;"
            "    border: 1px solid %2;"
            "    border-radius: %3px;"
            "    padding: 8px 12px;"
            "    color: %4;"
            "}"
        ).arg(colors.baseColor.name())
         .arg(colors.borderColor.name())
         .arg(borderRadius)
         .arg(colors.textColor.name());
    }
}

#endif

