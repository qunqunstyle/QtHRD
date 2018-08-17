/********************************************************************************
** Form generated from reading UI file 'mirror.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIRROR_H
#define UI_MIRROR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MirrorClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *Main_HLayout_Bottom;
    QVBoxLayout *Weather_VLayout_BottomLeft;
    QHBoxLayout *horizontalLayout_2;
    QLabel *city;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *todayTemp;
    QVBoxLayout *verticalLayout;
    QLabel *todayTempFLAG;
    QHBoxLayout *horizontalLayout;
    QLabel *windType;
    QLabel *windPower;
    QHBoxLayout *ForeCast_HLayout_BottomRight;
    QVBoxLayout *ForeCast1_verticalLayout;
    QVBoxLayout *verticalLayout_6;
    QLabel *forecast_0_date;
    QVBoxLayout *verticalLayout_5;
    QLabel *forecast_0_icon;
    QVBoxLayout *verticalLayout_4;
    QLabel *forecast_0_temp;
    QVBoxLayout *ForeCast4_verticalLayout;
    QVBoxLayout *verticalLayout_9;
    QLabel *forecast_1_date;
    QVBoxLayout *verticalLayout_7;
    QLabel *forecast_1_icon;
    QVBoxLayout *verticalLayout_8;
    QLabel *forecast_1_temp;
    QVBoxLayout *ForeCast3_verticalLayout;
    QVBoxLayout *verticalLayout_12;
    QLabel *forecast_2_date;
    QVBoxLayout *verticalLayout_10;
    QLabel *forecast_2_icon;
    QVBoxLayout *verticalLayout_11;
    QLabel *forecast_2_temp;
    QVBoxLayout *ForeCast2_verticalLayout;
    QVBoxLayout *verticalLayout_15;
    QLabel *forecast_3_date;
    QVBoxLayout *verticalLayout_14;
    QLabel *forecast_3_icon;
    QVBoxLayout *verticalLayout_13;
    QLabel *forecast_3_temp;
    QHBoxLayout *main_HLayout_Top;
    QVBoxLayout *verticalLayout_TopLeft;
    QVBoxLayout *Face_VLayout;
    QLabel *FaceCover;
    QVBoxLayout *clock_VLayout;
    QVBoxLayout *date_VLayout;
    QLabel *dateLabel;
    QVBoxLayout *time_VLayout;
    QLabel *timeLabel;
    QVBoxLayout *HR_VLayout_TopRight;
    QHBoxLayout *HRValue_HLayout;
    QVBoxLayout *HRShow_VLayout;
    QLabel *HR_ValueLabel;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_21;
    QVBoxLayout *verticalLayout_20;
    QVBoxLayout *verticalLayout_19;
    QVBoxLayout *verticalLayout_18;
    QPushButton *exitButton;
    QVBoxLayout *verticalLayout_16;
    QLabel *HR_ICON;
    QVBoxLayout *verticalLayout_17;
    QLabel *BPM_Label;
    QHBoxLayout *HR_Plot_HLayout;
    QCustomPlot *HR_Plot;

    void setupUi(QWidget *MirrorClass)
    {
        if (MirrorClass->objectName().isEmpty())
            MirrorClass->setObjectName(QStringLiteral("MirrorClass"));
        MirrorClass->resize(1440, 900);
        QIcon icon;
        icon.addFile(QStringLiteral("HRD_ICO.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MirrorClass->setWindowIcon(icon);
        MirrorClass->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        gridLayout = new QGridLayout(MirrorClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Main_HLayout_Bottom = new QHBoxLayout();
        Main_HLayout_Bottom->setSpacing(6);
        Main_HLayout_Bottom->setObjectName(QStringLiteral("Main_HLayout_Bottom"));
        Weather_VLayout_BottomLeft = new QVBoxLayout();
        Weather_VLayout_BottomLeft->setSpacing(6);
        Weather_VLayout_BottomLeft->setObjectName(QStringLiteral("Weather_VLayout_BottomLeft"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        city = new QLabel(MirrorClass);
        city->setObjectName(QStringLiteral("city"));
        city->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        city->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(city);


        Weather_VLayout_BottomLeft->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        todayTemp = new QLabel(MirrorClass);
        todayTemp->setObjectName(QStringLiteral("todayTemp"));
        todayTemp->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 75 100pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        todayTemp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_3->addWidget(todayTemp);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        todayTempFLAG = new QLabel(MirrorClass);
        todayTempFLAG->setObjectName(QStringLiteral("todayTempFLAG"));
        todayTempFLAG->setStyleSheet(QStringLiteral("color:rgb(255, 255, 255)"));
        todayTempFLAG->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(todayTempFLAG);


        horizontalLayout_3->addLayout(verticalLayout);


        Weather_VLayout_BottomLeft->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        windType = new QLabel(MirrorClass);
        windType->setObjectName(QStringLiteral("windType"));
        windType->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        windType->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        horizontalLayout->addWidget(windType);

        windPower = new QLabel(MirrorClass);
        windPower->setObjectName(QStringLiteral("windPower"));
        windPower->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 75 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        windPower->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        horizontalLayout->addWidget(windPower);


        Weather_VLayout_BottomLeft->addLayout(horizontalLayout);

        Weather_VLayout_BottomLeft->setStretch(0, 15);
        Weather_VLayout_BottomLeft->setStretch(1, 70);
        Weather_VLayout_BottomLeft->setStretch(2, 15);

        Main_HLayout_Bottom->addLayout(Weather_VLayout_BottomLeft);

        ForeCast_HLayout_BottomRight = new QHBoxLayout();
        ForeCast_HLayout_BottomRight->setSpacing(0);
        ForeCast_HLayout_BottomRight->setObjectName(QStringLiteral("ForeCast_HLayout_BottomRight"));
        ForeCast1_verticalLayout = new QVBoxLayout();
        ForeCast1_verticalLayout->setSpacing(0);
        ForeCast1_verticalLayout->setObjectName(QStringLiteral("ForeCast1_verticalLayout"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        forecast_0_date = new QLabel(MirrorClass);
        forecast_0_date->setObjectName(QStringLiteral("forecast_0_date"));
        forecast_0_date->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 75 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        forecast_0_date->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_6->addWidget(forecast_0_date);


        ForeCast1_verticalLayout->addLayout(verticalLayout_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        forecast_0_icon = new QLabel(MirrorClass);
        forecast_0_icon->setObjectName(QStringLiteral("forecast_0_icon"));
        forecast_0_icon->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(forecast_0_icon);


        ForeCast1_verticalLayout->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        forecast_0_temp = new QLabel(MirrorClass);
        forecast_0_temp->setObjectName(QStringLiteral("forecast_0_temp"));
        forecast_0_temp->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 75 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        forecast_0_temp->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_4->addWidget(forecast_0_temp);


        ForeCast1_verticalLayout->addLayout(verticalLayout_4);

        ForeCast1_verticalLayout->setStretch(0, 10);
        ForeCast1_verticalLayout->setStretch(1, 75);
        ForeCast1_verticalLayout->setStretch(2, 15);

        ForeCast_HLayout_BottomRight->addLayout(ForeCast1_verticalLayout);

        ForeCast4_verticalLayout = new QVBoxLayout();
        ForeCast4_verticalLayout->setSpacing(0);
        ForeCast4_verticalLayout->setObjectName(QStringLiteral("ForeCast4_verticalLayout"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        forecast_1_date = new QLabel(MirrorClass);
        forecast_1_date->setObjectName(QStringLiteral("forecast_1_date"));
        forecast_1_date->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 75 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        forecast_1_date->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_9->addWidget(forecast_1_date);


        ForeCast4_verticalLayout->addLayout(verticalLayout_9);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        forecast_1_icon = new QLabel(MirrorClass);
        forecast_1_icon->setObjectName(QStringLiteral("forecast_1_icon"));
        forecast_1_icon->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(forecast_1_icon);


        ForeCast4_verticalLayout->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        forecast_1_temp = new QLabel(MirrorClass);
        forecast_1_temp->setObjectName(QStringLiteral("forecast_1_temp"));
        forecast_1_temp->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 75 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        forecast_1_temp->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_8->addWidget(forecast_1_temp);


        ForeCast4_verticalLayout->addLayout(verticalLayout_8);

        ForeCast4_verticalLayout->setStretch(0, 10);
        ForeCast4_verticalLayout->setStretch(1, 75);
        ForeCast4_verticalLayout->setStretch(2, 15);

        ForeCast_HLayout_BottomRight->addLayout(ForeCast4_verticalLayout);

        ForeCast3_verticalLayout = new QVBoxLayout();
        ForeCast3_verticalLayout->setSpacing(0);
        ForeCast3_verticalLayout->setObjectName(QStringLiteral("ForeCast3_verticalLayout"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        forecast_2_date = new QLabel(MirrorClass);
        forecast_2_date->setObjectName(QStringLiteral("forecast_2_date"));
        forecast_2_date->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 75 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        forecast_2_date->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_12->addWidget(forecast_2_date);


        ForeCast3_verticalLayout->addLayout(verticalLayout_12);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        forecast_2_icon = new QLabel(MirrorClass);
        forecast_2_icon->setObjectName(QStringLiteral("forecast_2_icon"));
        forecast_2_icon->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(forecast_2_icon);


        ForeCast3_verticalLayout->addLayout(verticalLayout_10);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        forecast_2_temp = new QLabel(MirrorClass);
        forecast_2_temp->setObjectName(QStringLiteral("forecast_2_temp"));
        forecast_2_temp->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 75 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        forecast_2_temp->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_11->addWidget(forecast_2_temp);


        ForeCast3_verticalLayout->addLayout(verticalLayout_11);

        ForeCast3_verticalLayout->setStretch(0, 10);
        ForeCast3_verticalLayout->setStretch(1, 75);
        ForeCast3_verticalLayout->setStretch(2, 15);

        ForeCast_HLayout_BottomRight->addLayout(ForeCast3_verticalLayout);

        ForeCast2_verticalLayout = new QVBoxLayout();
        ForeCast2_verticalLayout->setSpacing(0);
        ForeCast2_verticalLayout->setObjectName(QStringLiteral("ForeCast2_verticalLayout"));
        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        forecast_3_date = new QLabel(MirrorClass);
        forecast_3_date->setObjectName(QStringLiteral("forecast_3_date"));
        forecast_3_date->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 75 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        forecast_3_date->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_15->addWidget(forecast_3_date);


        ForeCast2_verticalLayout->addLayout(verticalLayout_15);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        forecast_3_icon = new QLabel(MirrorClass);
        forecast_3_icon->setObjectName(QStringLiteral("forecast_3_icon"));
        forecast_3_icon->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(forecast_3_icon);


        ForeCast2_verticalLayout->addLayout(verticalLayout_14);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        forecast_3_temp = new QLabel(MirrorClass);
        forecast_3_temp->setObjectName(QStringLiteral("forecast_3_temp"));
        forecast_3_temp->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 75 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        forecast_3_temp->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_13->addWidget(forecast_3_temp);


        ForeCast2_verticalLayout->addLayout(verticalLayout_13);

        ForeCast2_verticalLayout->setStretch(0, 10);
        ForeCast2_verticalLayout->setStretch(1, 75);
        ForeCast2_verticalLayout->setStretch(2, 15);

        ForeCast_HLayout_BottomRight->addLayout(ForeCast2_verticalLayout);


        Main_HLayout_Bottom->addLayout(ForeCast_HLayout_BottomRight);

        Main_HLayout_Bottom->setStretch(0, 3);
        Main_HLayout_Bottom->setStretch(1, 7);

        gridLayout->addLayout(Main_HLayout_Bottom, 1, 0, 1, 1);

        main_HLayout_Top = new QHBoxLayout();
        main_HLayout_Top->setSpacing(6);
        main_HLayout_Top->setObjectName(QStringLiteral("main_HLayout_Top"));
        verticalLayout_TopLeft = new QVBoxLayout();
        verticalLayout_TopLeft->setSpacing(6);
        verticalLayout_TopLeft->setObjectName(QStringLiteral("verticalLayout_TopLeft"));
        Face_VLayout = new QVBoxLayout();
        Face_VLayout->setSpacing(6);
        Face_VLayout->setObjectName(QStringLiteral("Face_VLayout"));
        FaceCover = new QLabel(MirrorClass);
        FaceCover->setObjectName(QStringLiteral("FaceCover"));
        FaceCover->setFrameShape(QFrame::NoFrame);
        FaceCover->setAlignment(Qt::AlignCenter);

        Face_VLayout->addWidget(FaceCover);


        verticalLayout_TopLeft->addLayout(Face_VLayout);

        clock_VLayout = new QVBoxLayout();
        clock_VLayout->setSpacing(6);
        clock_VLayout->setObjectName(QStringLiteral("clock_VLayout"));
        date_VLayout = new QVBoxLayout();
        date_VLayout->setSpacing(6);
        date_VLayout->setObjectName(QStringLiteral("date_VLayout"));
        dateLabel = new QLabel(MirrorClass);
        dateLabel->setObjectName(QStringLiteral("dateLabel"));
        dateLabel->setStyleSheet(QString::fromUtf8("font: 75 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:rgb(255, 255, 255);"));
        dateLabel->setAlignment(Qt::AlignCenter);

        date_VLayout->addWidget(dateLabel);


        clock_VLayout->addLayout(date_VLayout);

        time_VLayout = new QVBoxLayout();
        time_VLayout->setSpacing(6);
        time_VLayout->setObjectName(QStringLiteral("time_VLayout"));
        timeLabel = new QLabel(MirrorClass);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));
        timeLabel->setStyleSheet(QString::fromUtf8("font: 75 36pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:rgb(255, 255, 255);"));
        timeLabel->setAlignment(Qt::AlignCenter);

        time_VLayout->addWidget(timeLabel);


        clock_VLayout->addLayout(time_VLayout);


        verticalLayout_TopLeft->addLayout(clock_VLayout);

        verticalLayout_TopLeft->setStretch(0, 7);
        verticalLayout_TopLeft->setStretch(1, 3);

        main_HLayout_Top->addLayout(verticalLayout_TopLeft);

        HR_VLayout_TopRight = new QVBoxLayout();
        HR_VLayout_TopRight->setSpacing(6);
        HR_VLayout_TopRight->setObjectName(QStringLiteral("HR_VLayout_TopRight"));
        HRValue_HLayout = new QHBoxLayout();
        HRValue_HLayout->setSpacing(6);
        HRValue_HLayout->setObjectName(QStringLiteral("HRValue_HLayout"));
        HRShow_VLayout = new QVBoxLayout();
        HRShow_VLayout->setSpacing(6);
        HRShow_VLayout->setObjectName(QStringLiteral("HRShow_VLayout"));
        HR_ValueLabel = new QLabel(MirrorClass);
        HR_ValueLabel->setObjectName(QStringLiteral("HR_ValueLabel"));
        HR_ValueLabel->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 75 150pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        HR_ValueLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        HRShow_VLayout->addWidget(HR_ValueLabel);


        HRValue_HLayout->addLayout(HRShow_VLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));

        horizontalLayout_4->addLayout(verticalLayout_21);

        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));

        horizontalLayout_4->addLayout(verticalLayout_20);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));

        horizontalLayout_4->addLayout(verticalLayout_19);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        exitButton = new QPushButton(MirrorClass);
        exitButton->setObjectName(QStringLiteral("exitButton"));

        verticalLayout_18->addWidget(exitButton);


        horizontalLayout_4->addLayout(verticalLayout_18);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 1);
        horizontalLayout_4->setStretch(2, 1);
        horizontalLayout_4->setStretch(3, 1);

        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        HR_ICON = new QLabel(MirrorClass);
        HR_ICON->setObjectName(QStringLiteral("HR_ICON"));
        HR_ICON->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 24pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        HR_ICON->setAlignment(Qt::AlignCenter);

        verticalLayout_16->addWidget(HR_ICON);


        verticalLayout_2->addLayout(verticalLayout_16);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(-1, 0, -1, 0);
        BPM_Label = new QLabel(MirrorClass);
        BPM_Label->setObjectName(QStringLiteral("BPM_Label"));
        BPM_Label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_17->addWidget(BPM_Label);


        verticalLayout_2->addLayout(verticalLayout_17);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 6);
        verticalLayout_2->setStretch(2, 3);

        HRValue_HLayout->addLayout(verticalLayout_2);

        HRValue_HLayout->setStretch(0, 5);
        HRValue_HLayout->setStretch(1, 2);

        HR_VLayout_TopRight->addLayout(HRValue_HLayout);

        HR_Plot_HLayout = new QHBoxLayout();
        HR_Plot_HLayout->setSpacing(6);
        HR_Plot_HLayout->setObjectName(QStringLiteral("HR_Plot_HLayout"));
        HR_Plot = new QCustomPlot(MirrorClass);
        HR_Plot->setObjectName(QStringLiteral("HR_Plot"));
        HR_Plot->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        HR_Plot_HLayout->addWidget(HR_Plot);


        HR_VLayout_TopRight->addLayout(HR_Plot_HLayout);

        HR_VLayout_TopRight->setStretch(0, 55);
        HR_VLayout_TopRight->setStretch(1, 45);

        main_HLayout_Top->addLayout(HR_VLayout_TopRight);

        main_HLayout_Top->setStretch(0, 3);
        main_HLayout_Top->setStretch(1, 7);

        gridLayout->addLayout(main_HLayout_Top, 0, 0, 1, 1);

        gridLayout->setRowStretch(0, 65);
        gridLayout->setRowStretch(1, 35);

        retranslateUi(MirrorClass);

        QMetaObject::connectSlotsByName(MirrorClass);
    } // setupUi

    void retranslateUi(QWidget *MirrorClass)
    {
        MirrorClass->setWindowTitle(QApplication::translate("MirrorClass", "Mirror", Q_NULLPTR));
        city->setText(QString());
        todayTemp->setText(QString());
        todayTempFLAG->setText(QApplication::translate("MirrorClass", "<html><head/><body><p><span style=\" font-size:80pt; color:#ffffff;\">\342\204\203</span></p></body></html>", Q_NULLPTR));
        windType->setText(QString());
        windPower->setText(QString());
        forecast_0_date->setText(QString());
        forecast_0_icon->setText(QString());
        forecast_0_temp->setText(QString());
        forecast_1_date->setText(QString());
        forecast_1_icon->setText(QString());
        forecast_1_temp->setText(QString());
        forecast_2_date->setText(QString());
        forecast_2_icon->setText(QString());
        forecast_2_temp->setText(QString());
        forecast_3_date->setText(QString());
        forecast_3_icon->setText(QString());
        forecast_3_temp->setText(QString());
        FaceCover->setText(QString());
        dateLabel->setText(QString());
        timeLabel->setText(QString());
        HR_ValueLabel->setText(QString());
        exitButton->setText(QApplication::translate("MirrorClass", "PushButton", Q_NULLPTR));
        HR_ICON->setText(QString());
        BPM_Label->setText(QApplication::translate("MirrorClass", "<html><head/><body><p><span style=\" font-size:40pt; font-weight:600; color:#ffffff;\">(\346\254\241/\345\210\206\351\222\237)</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MirrorClass: public Ui_MirrorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIRROR_H
