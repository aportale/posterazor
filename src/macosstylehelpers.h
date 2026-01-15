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

#pragma once

#include <QString>
#include <QPalette>

#ifdef Q_OS_MACOS

namespace MacOSStyleHelpers
{
    struct StyleColors {
        QColor windowColor;
        QColor baseColor;
        QColor buttonColor;
        QColor buttonTextColor;
        QColor highlightColor;
        QColor textColor;
        bool isDarkMode;
        
        QColor panelBgColor;
        QColor groupBoxBgColor;
        QColor borderColor;
        QColor borderColorLight;
    };
    
    StyleColors getStyleColors();
    
    QString getButtonStyleSheet(const StyleColors &colors);
    
    QString getToolButtonStyleSheet(const StyleColors &colors);
    
    QString getGroupBoxStyleSheet(const StyleColors &colors);
    
    QString getPanelStyleSheet(const StyleColors &colors, int borderRadius = 12);
    
    QString getLabelStyleSheet(const StyleColors &colors, int borderRadius = 8);
}

#endif

