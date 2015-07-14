/********************************************************************************
** Form generated from reading UI file 'main.ui'
**
** Created: Wed Jun 26 14:58:13 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qttreepropertybrowser.h"
#include "uicanvas.h"

QT_BEGIN_NAMESPACE

class Ui_EditorClass
{
public:
    QAction *actionFileNew;
    QAction *actionFileOpen;
    QAction *actionFileSave;
    QAction *actionUndo;
    QAction *actionReDo;
    QAction *actionSelect;
    QAction *actionControlPreviousFrame;
    QAction *actionControlNextFrame;
    QAction *actionControlPlayOrPuase;
    QAction *actionTestWhat;
    QAction *actionMovieCutting;
    QAction *actionScale;
    QAction *actionRotate;
    QAction *actionShowCoordinateOrignal;
    QAction *actionLeftToolbarPipette;
    QWidget *mainBoard;
    QHBoxLayout *horizontalLayout;
    QFrame *frameLeft;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QScrollArea *scrollAreaCanvas;
    UICanvas *widgetCanvas;
    QFrame *frameRight;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *RightPanelTopTab;
    QWidget *tabInfo;
    QFrame *line;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *labelInfoMouseR;
    QLabel *labelInfoMouseG;
    QLabel *labelInfoMouseB;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *labelInfoMouseX;
    QLabel *labelInfoMouseY;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_10;
    QLabel *label_13;
    QLineEdit *lineEditInfoWidth;
    QLineEdit *lineEditInfoHeight;
    QLineEdit *lineEditInfoPositionY;
    QLineEdit *lineEditInfoPositionX;
    QPushButton *pushButtonInfoToOriginal;
    QWidget *tabColorPick;
    QWidget *tabLayout;
    QFrame *lineRightPanel;
    QTabWidget *RightPanelBottomTab;
    QWidget *tabResource;
    QVBoxLayout *verticalLayout;
    QWidget *widgetActorPreview;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBoxActorFilter;
    QLabel *label_6;
    QTreeWidget *treeWidgetResource;
    QWidget *tabProperty;
    QVBoxLayout *verticalLayout_3;
    QtTreePropertyBrowser *treePropertyBrowser;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QToolBar *toolBarTop;

    void setupUi(QMainWindow *EditorClass)
    {
        if (EditorClass->objectName().isEmpty())
            EditorClass->setObjectName(QString::fromUtf8("EditorClass"));
        EditorClass->resize(1676, 847);
        EditorClass->setCursor(QCursor(Qt::ArrowCursor));
        EditorClass->setAcceptDrops(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Fuck/iconApplation.png"), QSize(), QIcon::Normal, QIcon::Off);
        EditorClass->setWindowIcon(icon);
        EditorClass->setAutoFillBackground(false);
        actionFileNew = new QAction(EditorClass);
        actionFileNew->setObjectName(QString::fromUtf8("actionFileNew"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/main/icon/iconFileNew.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFileNew->setIcon(icon1);
        actionFileOpen = new QAction(EditorClass);
        actionFileOpen->setObjectName(QString::fromUtf8("actionFileOpen"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/main/icon/iconFileOpen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFileOpen->setIcon(icon2);
        actionFileSave = new QAction(EditorClass);
        actionFileSave->setObjectName(QString::fromUtf8("actionFileSave"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/main/icon/incoFileSave.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFileSave->setIcon(icon3);
        actionUndo = new QAction(EditorClass);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/main/icon/iconUnDo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon4);
        actionReDo = new QAction(EditorClass);
        actionReDo->setObjectName(QString::fromUtf8("actionReDo"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/main/icon/iconReDo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReDo->setIcon(icon5);
        actionSelect = new QAction(EditorClass);
        actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
        actionSelect->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/main/icon/iconArrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelect->setIcon(icon6);
        actionControlPreviousFrame = new QAction(EditorClass);
        actionControlPreviousFrame->setObjectName(QString::fromUtf8("actionControlPreviousFrame"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/main/icon/iconControlPrevious.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionControlPreviousFrame->setIcon(icon7);
        actionControlNextFrame = new QAction(EditorClass);
        actionControlNextFrame->setObjectName(QString::fromUtf8("actionControlNextFrame"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/main/icon/iconControlNextFrame.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionControlNextFrame->setIcon(icon8);
        actionControlPlayOrPuase = new QAction(EditorClass);
        actionControlPlayOrPuase->setObjectName(QString::fromUtf8("actionControlPlayOrPuase"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/main/icon/iconControlStart.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon9.addFile(QString::fromUtf8(":/Fuck/iconControlPrevious.png"), QSize(), QIcon::Normal, QIcon::On);
        actionControlPlayOrPuase->setIcon(icon9);
        actionTestWhat = new QAction(EditorClass);
        actionTestWhat->setObjectName(QString::fromUtf8("actionTestWhat"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/main/icon/iconQuestion.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTestWhat->setIcon(icon10);
        actionMovieCutting = new QAction(EditorClass);
        actionMovieCutting->setObjectName(QString::fromUtf8("actionMovieCutting"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/main/icon/iconComponentMovieCutting.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMovieCutting->setIcon(icon11);
        actionScale = new QAction(EditorClass);
        actionScale->setObjectName(QString::fromUtf8("actionScale"));
        actionScale->setCheckable(true);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/main/icon/iconAdjustSize.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionScale->setIcon(icon12);
        actionRotate = new QAction(EditorClass);
        actionRotate->setObjectName(QString::fromUtf8("actionRotate"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/main/icon/iconRotate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotate->setIcon(icon13);
        actionShowCoordinateOrignal = new QAction(EditorClass);
        actionShowCoordinateOrignal->setObjectName(QString::fromUtf8("actionShowCoordinateOrignal"));
        actionShowCoordinateOrignal->setCheckable(true);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/main/icon/iconMousePosition.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShowCoordinateOrignal->setIcon(icon14);
        actionLeftToolbarPipette = new QAction(EditorClass);
        actionLeftToolbarPipette->setObjectName(QString::fromUtf8("actionLeftToolbarPipette"));
        actionLeftToolbarPipette->setCheckable(true);
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/main/icon/iconPipette.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLeftToolbarPipette->setIcon(icon15);
        mainBoard = new QWidget(EditorClass);
        mainBoard->setObjectName(QString::fromUtf8("mainBoard"));
        horizontalLayout = new QHBoxLayout(mainBoard);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setContentsMargins(5, 5, 5, 5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frameLeft = new QFrame(mainBoard);
        frameLeft->setObjectName(QString::fromUtf8("frameLeft"));
        frameLeft->setMinimumSize(QSize(261, 0));
        frameLeft->setFrameShape(QFrame::StyledPanel);
        verticalLayout_2 = new QVBoxLayout(frameLeft);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(frameLeft);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);


        horizontalLayout->addWidget(frameLeft);

        scrollAreaCanvas = new QScrollArea(mainBoard);
        scrollAreaCanvas->setObjectName(QString::fromUtf8("scrollAreaCanvas"));
        scrollAreaCanvas->setMinimumSize(QSize(1024, 768));
        scrollAreaCanvas->setMaximumSize(QSize(1024, 900));
        scrollAreaCanvas->setWidgetResizable(false);
        widgetCanvas = new UICanvas();
        widgetCanvas->setObjectName(QString::fromUtf8("widgetCanvas"));
        widgetCanvas->setGeometry(QRect(0, 0, 3200, 1800));
        scrollAreaCanvas->setWidget(widgetCanvas);

        horizontalLayout->addWidget(scrollAreaCanvas);

        frameRight = new QFrame(mainBoard);
        frameRight->setObjectName(QString::fromUtf8("frameRight"));
        frameRight->setMinimumSize(QSize(361, 0));
        frameRight->setFrameShape(QFrame::StyledPanel);
        verticalLayout_4 = new QVBoxLayout(frameRight);
        verticalLayout_4->setSpacing(1);
        verticalLayout_4->setContentsMargins(5, 5, 5, 5);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        RightPanelTopTab = new QTabWidget(frameRight);
        RightPanelTopTab->setObjectName(QString::fromUtf8("RightPanelTopTab"));
        RightPanelTopTab->setMaximumSize(QSize(16777215, 159));
        RightPanelTopTab->setTabPosition(QTabWidget::North);
        RightPanelTopTab->setTabShape(QTabWidget::Rounded);
        RightPanelTopTab->setUsesScrollButtons(false);
        RightPanelTopTab->setTabsClosable(false);
        RightPanelTopTab->setMovable(true);
        tabInfo = new QWidget();
        tabInfo->setObjectName(QString::fromUtf8("tabInfo"));
        line = new QFrame(tabInfo);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(2, 70, 210, 3));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(tabInfo);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 9, 16));
        label_2 = new QLabel(tabInfo);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 30, 9, 16));
        label_3 = new QLabel(tabInfo);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 50, 9, 16));
        labelInfoMouseR = new QLabel(tabInfo);
        labelInfoMouseR->setObjectName(QString::fromUtf8("labelInfoMouseR"));
        labelInfoMouseR->setGeometry(QRect(50, 10, 21, 16));
        labelInfoMouseG = new QLabel(tabInfo);
        labelInfoMouseG->setObjectName(QString::fromUtf8("labelInfoMouseG"));
        labelInfoMouseG->setGeometry(QRect(50, 30, 21, 16));
        labelInfoMouseB = new QLabel(tabInfo);
        labelInfoMouseB->setObjectName(QString::fromUtf8("labelInfoMouseB"));
        labelInfoMouseB->setGeometry(QRect(50, 50, 21, 16));
        label_8 = new QLabel(tabInfo);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(110, 10, 9, 16));
        label_9 = new QLabel(tabInfo);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(110, 30, 9, 16));
        labelInfoMouseX = new QLabel(tabInfo);
        labelInfoMouseX->setObjectName(QString::fromUtf8("labelInfoMouseX"));
        labelInfoMouseX->setGeometry(QRect(130, 10, 31, 16));
        labelInfoMouseY = new QLabel(tabInfo);
        labelInfoMouseY->setObjectName(QString::fromUtf8("labelInfoMouseY"));
        labelInfoMouseY->setGeometry(QRect(130, 30, 31, 16));
        label_11 = new QLabel(tabInfo);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(3, 10, 21, 16));
        label_12 = new QLabel(tabInfo);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(80, 10, 21, 16));
        label_4 = new QLabel(tabInfo);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 80, 9, 16));
        label_5 = new QLabel(tabInfo);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 100, 9, 16));
        label_10 = new QLabel(tabInfo);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(90, 80, 9, 16));
        label_13 = new QLabel(tabInfo);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(90, 100, 9, 16));
        lineEditInfoWidth = new QLineEdit(tabInfo);
        lineEditInfoWidth->setObjectName(QString::fromUtf8("lineEditInfoWidth"));
        lineEditInfoWidth->setEnabled(false);
        lineEditInfoWidth->setGeometry(QRect(30, 78, 41, 16));
        lineEditInfoHeight = new QLineEdit(tabInfo);
        lineEditInfoHeight->setObjectName(QString::fromUtf8("lineEditInfoHeight"));
        lineEditInfoHeight->setEnabled(false);
        lineEditInfoHeight->setGeometry(QRect(30, 98, 41, 16));
        lineEditInfoPositionY = new QLineEdit(tabInfo);
        lineEditInfoPositionY->setObjectName(QString::fromUtf8("lineEditInfoPositionY"));
        lineEditInfoPositionY->setEnabled(false);
        lineEditInfoPositionY->setGeometry(QRect(110, 98, 41, 16));
        lineEditInfoPositionX = new QLineEdit(tabInfo);
        lineEditInfoPositionX->setObjectName(QString::fromUtf8("lineEditInfoPositionX"));
        lineEditInfoPositionX->setEnabled(false);
        lineEditInfoPositionX->setGeometry(QRect(110, 78, 41, 16));
        pushButtonInfoToOriginal = new QPushButton(tabInfo);
        pushButtonInfoToOriginal->setObjectName(QString::fromUtf8("pushButtonInfoToOriginal"));
        pushButtonInfoToOriginal->setGeometry(QRect(170, 78, 71, 23));
        RightPanelTopTab->addTab(tabInfo, QString());
        tabColorPick = new QWidget();
        tabColorPick->setObjectName(QString::fromUtf8("tabColorPick"));
        RightPanelTopTab->addTab(tabColorPick, QString());
        tabLayout = new QWidget();
        tabLayout->setObjectName(QString::fromUtf8("tabLayout"));
        RightPanelTopTab->addTab(tabLayout, QString());

        verticalLayout_4->addWidget(RightPanelTopTab);

        lineRightPanel = new QFrame(frameRight);
        lineRightPanel->setObjectName(QString::fromUtf8("lineRightPanel"));
        lineRightPanel->setFrameShape(QFrame::HLine);
        lineRightPanel->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(lineRightPanel);

        RightPanelBottomTab = new QTabWidget(frameRight);
        RightPanelBottomTab->setObjectName(QString::fromUtf8("RightPanelBottomTab"));
        RightPanelBottomTab->setFocusPolicy(Qt::StrongFocus);
        RightPanelBottomTab->setAcceptDrops(false);
        RightPanelBottomTab->setElideMode(Qt::ElideNone);
        RightPanelBottomTab->setMovable(true);
        tabResource = new QWidget();
        tabResource->setObjectName(QString::fromUtf8("tabResource"));
        verticalLayout = new QVBoxLayout(tabResource);
        verticalLayout->setSpacing(1);
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widgetActorPreview = new QWidget(tabResource);
        widgetActorPreview->setObjectName(QString::fromUtf8("widgetActorPreview"));
        widgetActorPreview->setMinimumSize(QSize(0, 110));

        verticalLayout->addWidget(widgetActorPreview);

        widget_2 = new QWidget(tabResource);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(0, 10));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        comboBoxActorFilter = new QComboBox(widget_2);
        comboBoxActorFilter->setObjectName(QString::fromUtf8("comboBoxActorFilter"));
        comboBoxActorFilter->setEditable(true);

        horizontalLayout_2->addWidget(comboBoxActorFilter);

        label_6 = new QLabel(widget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMaximumSize(QSize(32, 32));

        horizontalLayout_2->addWidget(label_6);

        label_6->raise();
        comboBoxActorFilter->raise();

        verticalLayout->addWidget(widget_2);

        treeWidgetResource = new QTreeWidget(tabResource);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidgetResource->setHeaderItem(__qtreewidgetitem);
        treeWidgetResource->setObjectName(QString::fromUtf8("treeWidgetResource"));
        treeWidgetResource->setAcceptDrops(true);
        treeWidgetResource->setDragEnabled(true);
        treeWidgetResource->setColumnCount(2);
        treeWidgetResource->header()->setVisible(false);
        treeWidgetResource->header()->setDefaultSectionSize(135);

        verticalLayout->addWidget(treeWidgetResource);

        RightPanelBottomTab->addTab(tabResource, QString());
        tabProperty = new QWidget();
        tabProperty->setObjectName(QString::fromUtf8("tabProperty"));
        tabProperty->setFocusPolicy(Qt::StrongFocus);
        verticalLayout_3 = new QVBoxLayout(tabProperty);
        verticalLayout_3->setSpacing(1);
        verticalLayout_3->setContentsMargins(5, 5, 5, 5);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        treePropertyBrowser = new QtTreePropertyBrowser(tabProperty);
        treePropertyBrowser->setObjectName(QString::fromUtf8("treePropertyBrowser"));
        treePropertyBrowser->setFocusPolicy(Qt::StrongFocus);

        verticalLayout_3->addWidget(treePropertyBrowser);

        RightPanelBottomTab->addTab(tabProperty, QString());

        verticalLayout_4->addWidget(RightPanelBottomTab);


        horizontalLayout->addWidget(frameRight);

        EditorClass->setCentralWidget(mainBoard);
        menuBar = new QMenuBar(EditorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1676, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        EditorClass->setMenuBar(menuBar);
        toolBarTop = new QToolBar(EditorClass);
        toolBarTop->setObjectName(QString::fromUtf8("toolBarTop"));
        toolBarTop->setMovable(false);
        toolBarTop->setIconSize(QSize(32, 32));
        EditorClass->addToolBar(Qt::TopToolBarArea, toolBarTop);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionFileNew);
        menuFile->addAction(actionFileOpen);
        menuFile->addAction(actionFileSave);
        menuFile->addSeparator();
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionReDo);
        menuEdit->addSeparator();
        toolBarTop->addAction(actionFileNew);
        toolBarTop->addAction(actionFileOpen);
        toolBarTop->addAction(actionFileSave);
        toolBarTop->addSeparator();
        toolBarTop->addAction(actionUndo);
        toolBarTop->addAction(actionReDo);
        toolBarTop->addSeparator();
        toolBarTop->addAction(actionShowCoordinateOrignal);
        toolBarTop->addSeparator();
        toolBarTop->addAction(actionSelect);
        toolBarTop->addAction(actionScale);
        toolBarTop->addAction(actionRotate);
        toolBarTop->addSeparator();

        retranslateUi(EditorClass);

        tabWidget->setCurrentIndex(0);
        RightPanelTopTab->setCurrentIndex(0);
        RightPanelBottomTab->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(EditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditorClass)
    {
        EditorClass->setWindowTitle(QApplication::translate("EditorClass", "UI Animation 2012 Professional", 0, QApplication::UnicodeUTF8));
        actionFileNew->setText(QApplication::translate("EditorClass", "\346\226\260\345\273\272", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionFileNew->setToolTip(QApplication::translate("EditorClass", "\346\226\260\345\273\272\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionFileNew->setShortcut(QApplication::translate("EditorClass", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionFileOpen->setText(QApplication::translate("EditorClass", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionFileOpen->setToolTip(QApplication::translate("EditorClass", "\346\211\223\345\274\200\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionFileOpen->setShortcut(QApplication::translate("EditorClass", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionFileSave->setText(QApplication::translate("EditorClass", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionFileSave->setToolTip(QApplication::translate("EditorClass", "\344\277\235\345\255\230\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionFileSave->setShortcut(QApplication::translate("EditorClass", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionUndo->setText(QApplication::translate("EditorClass", "\346\222\244\351\224\200", 0, QApplication::UnicodeUTF8));
        actionUndo->setShortcut(QApplication::translate("EditorClass", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
        actionReDo->setText(QApplication::translate("EditorClass", "\351\207\215\345\201\232", 0, QApplication::UnicodeUTF8));
        actionReDo->setShortcut(QApplication::translate("EditorClass", "Ctrl+Shift+Z", 0, QApplication::UnicodeUTF8));
        actionSelect->setText(QApplication::translate("EditorClass", "\351\200\211\346\213\251\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSelect->setToolTip(QApplication::translate("EditorClass", "\351\200\211\346\213\251\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionControlPreviousFrame->setText(QApplication::translate("EditorClass", "\345\220\216\351\200\200\344\270\200\345\270\247", 0, QApplication::UnicodeUTF8));
        actionControlPreviousFrame->setShortcut(QApplication::translate("EditorClass", ",", 0, QApplication::UnicodeUTF8));
        actionControlNextFrame->setText(QApplication::translate("EditorClass", "\345\211\215\350\277\233\344\270\200\345\270\247", 0, QApplication::UnicodeUTF8));
        actionControlNextFrame->setShortcut(QApplication::translate("EditorClass", ".", 0, QApplication::UnicodeUTF8));
        actionControlPlayOrPuase->setText(QApplication::translate("EditorClass", "\346\222\255\346\224\276", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionControlPlayOrPuase->setToolTip(QApplication::translate("EditorClass", "\346\222\255\346\224\276", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionControlPlayOrPuase->setShortcut(QApplication::translate("EditorClass", "Ctrl+Return", 0, QApplication::UnicodeUTF8));
        actionTestWhat->setText(QApplication::translate("EditorClass", "TestWhat", 0, QApplication::UnicodeUTF8));
        actionMovieCutting->setText(QApplication::translate("EditorClass", "\345\275\261\347\211\207\345\211\252\350\276\221", 0, QApplication::UnicodeUTF8));
        actionScale->setText(QApplication::translate("EditorClass", "\347\274\251\346\224\276\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
        actionScale->setIconText(QApplication::translate("EditorClass", "\345\217\230\345\275\242\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionScale->setToolTip(QApplication::translate("EditorClass", "\347\274\251\346\224\276\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionRotate->setText(QApplication::translate("EditorClass", "\346\227\213\350\275\254\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRotate->setToolTip(QApplication::translate("EditorClass", "\346\227\213\350\275\254\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionShowCoordinateOrignal->setText(QApplication::translate("EditorClass", "\346\230\276\347\244\272\345\235\220\346\240\207\345\216\237\347\202\271", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionShowCoordinateOrignal->setToolTip(QApplication::translate("EditorClass", "\346\230\276\347\244\272\345\235\220\346\240\207\345\216\237\347\202\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionLeftToolbarPipette->setText(QApplication::translate("EditorClass", "\345\220\270\347\256\241\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionLeftToolbarPipette->setToolTip(QApplication::translate("EditorClass", "\345\220\270\347\256\241\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("EditorClass", "\345\234\272\346\231\257\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("EditorClass", "\345\200\231\350\241\245\351\230\237\345\221\230", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("EditorClass", "R:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("EditorClass", "G:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("EditorClass", "B:", 0, QApplication::UnicodeUTF8));
        labelInfoMouseR->setText(QApplication::translate("EditorClass", "---", 0, QApplication::UnicodeUTF8));
        labelInfoMouseG->setText(QApplication::translate("EditorClass", "---", 0, QApplication::UnicodeUTF8));
        labelInfoMouseB->setText(QApplication::translate("EditorClass", "---", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("EditorClass", "X:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("EditorClass", "Y:", 0, QApplication::UnicodeUTF8));
        labelInfoMouseX->setText(QApplication::translate("EditorClass", "----", 0, QApplication::UnicodeUTF8));
        labelInfoMouseY->setText(QApplication::translate("EditorClass", "----", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("EditorClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\256\213\344\275\223'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/main/icon/iconPipetteS.png\" /></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("EditorClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\256\213\344\275\223'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/main/icon/iconMousePosition.png\" /></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("EditorClass", "W:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("EditorClass", "H:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("EditorClass", "X:", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("EditorClass", "Y:", 0, QApplication::UnicodeUTF8));
        lineEditInfoWidth->setText(QApplication::translate("EditorClass", "----", 0, QApplication::UnicodeUTF8));
        lineEditInfoHeight->setText(QApplication::translate("EditorClass", "----", 0, QApplication::UnicodeUTF8));
        lineEditInfoPositionY->setText(QApplication::translate("EditorClass", "----", 0, QApplication::UnicodeUTF8));
        lineEditInfoPositionX->setText(QApplication::translate("EditorClass", "----", 0, QApplication::UnicodeUTF8));
        pushButtonInfoToOriginal->setText(QApplication::translate("EditorClass", "\345\256\232\344\275\215\345\210\260\345\216\237\347\202\271", 0, QApplication::UnicodeUTF8));
        RightPanelTopTab->setTabText(RightPanelTopTab->indexOf(tabInfo), QApplication::translate("EditorClass", "\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        RightPanelTopTab->setTabText(RightPanelTopTab->indexOf(tabColorPick), QApplication::translate("EditorClass", "\350\260\203\350\211\262\346\235\277", 0, QApplication::UnicodeUTF8));
        RightPanelTopTab->setTabText(RightPanelTopTab->indexOf(tabLayout), QApplication::translate("EditorClass", "\345\257\271\351\275\220", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("EditorClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\256\213\344\275\223'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/main/icon/iconFind.png\" /></p></body></html>", 0, QApplication::UnicodeUTF8));
        RightPanelBottomTab->setTabText(RightPanelBottomTab->indexOf(tabResource), QApplication::translate("EditorClass", "\350\247\222\350\211\262", 0, QApplication::UnicodeUTF8));
        RightPanelBottomTab->setTabText(RightPanelBottomTab->indexOf(tabProperty), QApplication::translate("EditorClass", "\345\261\236\346\200\247", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("EditorClass", "\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("EditorClass", "\347\274\226\350\276\221", 0, QApplication::UnicodeUTF8));
        toolBarTop->setWindowTitle(QApplication::translate("EditorClass", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditorClass: public Ui_EditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
