/*
 * ******* MapEditor - Open Source *******
 * Copyright (C) 2013 Jean-Philippe Boivin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _COPS_MAPEDITOR_MAINWINDOW_H_
#define _COPS_MAPEDITOR_MAINWINDOW_H_

#include <QMainWindow>
#include "common.h"
#include "gamemap.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_mBtnOpen_clicked();

    void on_mBtnLoad_clicked();

    void on_mBtnSave_clicked();

    void on_mBtnBackup_clicked();

    void on_mBtnRestore_clicked();

    void on_mBtnSearch_clicked();

    void on_mListWidget_currentRowChanged(int currentRow);

    void on_mBtnEdit_clicked();

    void on_mBtnDelete_clicked();

    void on_mBtnCreate_clicked();

private:
    Ui::MainWindow *ui;
    GameMap map;
};

#endif // _COPS_MAPEDITOR_MAINWINDOW_H_
