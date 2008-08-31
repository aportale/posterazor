/*
    PosteRazor - Make your own poster!
    Copyright (C) 2005-2008 by Alessandro Portale
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

#include "wizardcontroller.h"
#include <QCoreApplication>

WizardController::WizardController(QObject *wizardDialog, QObject *parent)
    : QObject(parent)
    , m_wizardStep(WizardStepInputImage)
    , m_imageWasLoaded(false)
{
    connect(this, SIGNAL(wizardStepChanged(int)), wizardDialog, SLOT(setWizardStep(int)));
    connect(this, SIGNAL(wizardStepDescriptionChanged(const QString&, const QString&)), wizardDialog, SLOT(setWizardStepDescription(const QString&, const QString&)));
    connect(this, SIGNAL(prevButtonEnabled(bool)), wizardDialog, SLOT(setPrevButtonEnabled(bool)));
    connect(this, SIGNAL(nextButtonEnabled(bool)), wizardDialog, SLOT(setNextButtonEnabled(bool)));
    connect(this, SIGNAL(previewStateChanged(const QString&)), wizardDialog, SLOT(setPreviewState(const QString&)));
    connect(wizardDialog, SIGNAL(imageLoaded()), SLOT(handleImageLoaded()));
    connect(wizardDialog, SIGNAL(prevButtonPressed()), SLOT(handlePrevButtonPressed()));
    connect(wizardDialog, SIGNAL(nextButtonPressed()), SLOT(handleNextButtonPressed()));

    updateDialogWizardStep();
}

void WizardController::handleImageLoaded()
{
    m_imageWasLoaded = true;
    updateDialogWizardStep();
}

void WizardController::handlePrevButtonPressed()
{
    m_wizardStep =
        m_wizardStep == WizardStepSavePoster?WizardStepPosterSize
        :m_wizardStep == WizardStepPosterSize?WizardStepOverlapping
        :m_wizardStep == WizardStepOverlapping?WizardStepPaperSize
        :/* m_wizardStep == WizardStepPaperSize? */WizardStepInputImage;

    updateDialogWizardStep();
}

void WizardController::handleNextButtonPressed()
{
    m_wizardStep =
        m_wizardStep == WizardStepInputImage?WizardStepPaperSize
        :m_wizardStep == WizardStepPaperSize?WizardStepOverlapping
        :m_wizardStep == WizardStepOverlapping?WizardStepPosterSize
        :/* m_wizardStep == WizardStepPosterSize? */WizardStepSavePoster;

    updateDialogWizardStep();
}

void WizardController::updateDialogWizardStep()
{
    emit wizardStepChanged(m_wizardStep);
    emit previewStateChanged(
        m_wizardStep == WizardStepInputImage?QLatin1String("image")
        :m_wizardStep == WizardStepOverlapping?QLatin1String("overlapping")
        :m_wizardStep == WizardStepPaperSize?QLatin1String("paper")
        :m_wizardStep == WizardStepPosterSize?QLatin1String("poster")
        :QLatin1String("poster")
    );
    emit prevButtonEnabled(m_wizardStep != WizardStepInputImage);
    emit nextButtonEnabled(
        m_wizardStep != WizardStepSavePoster
        && m_imageWasLoaded
    );
    updateDialogWizardStepDescription();
}

void WizardController::updateDialogWizardStepDescription()
{
    emit wizardStepDescriptionChanged(
        QCoreApplication::translate("Help", "Step %1 of %2:").arg((int)m_wizardStep + 1).arg((int)m_wizardStepsCount),
        m_wizardStep == WizardStepInputImage?  QCoreApplication::translate("Help", "Load an input image")
        :m_wizardStep == WizardStepPaperSize?  QCoreApplication::translate("Help", "Printer paper format")
        :m_wizardStep == WizardStepOverlapping?QCoreApplication::translate("Help", "Image tile overlapping")
        :m_wizardStep == WizardStepPosterSize? QCoreApplication::translate("Help", "Final poster size")
        :                                      QCoreApplication::translate("Help", "Save the Poster")
    );
}
