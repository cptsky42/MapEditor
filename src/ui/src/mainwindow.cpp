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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    char about[1024];
    sprintf(about, ui->mLblAbout->text().toLatin1(),
            TARGET_SYSTEM, TARGET_ARCH, QT_VERSION_STR, __TIMESTAMP__);
    ui->mLblAbout->setText(about);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mBtnOpen_clicked()
{
    QString path = QFileDialog::getOpenFileName(
                       this, tr("Open GameMap.dat"), "~/",
                       tr("TQ GameMap (gamemap.dat)"));

    if (path.size() > 0)
    {
        ui->mTxtFile->setText(path);
    }
}

void MainWindow::on_mBtnLoad_clicked()
{
    if (ui->mTxtFile->text().size() > 0)
    {
        map.load(ui->mTxtFile->text().toStdString());

        vector<int32_t> list;
        list = map.getMapUIDs();

        int row = 0;
        ui->mListWidget->clear();
        for (vector<int32_t>::iterator
             it = list.begin(), end = list.end();
             it != end; ++it)
        {
            char buf[256];
            sprintf(buf, "%d", *it);

            ui->mListWidget->insertItem(row++, buf);
        }
    }
}

void MainWindow::on_mBtnSave_clicked()
{
    if (ui->mTxtFile->text().size() > 0)
    {
        map.save(ui->mTxtFile->text().toStdString());
    }
}

void MainWindow::on_mBtnBackup_clicked()
{
    if (ui->mTxtFile->text().size() > 0 &&
        ui->mTxtBackup->text().size() > 0)
    {
        QFileInfo info(ui->mTxtFile->text());
        QString path = info.dir().canonicalPath();

        #ifdef _WIN32
        path += "\\";
        #else
        path += "/";
        #endif

        path += ui->mTxtBackup->text();

        char buf[4096] = { 0 };
        size_t read = 0;

        FILE* src = fopen(ui->mTxtFile->text().toUtf8(), "rb");
        FILE* dest = fopen(path.toUtf8(), "wb");

        if (src != nullptr && dest != nullptr)
        {
            while ((read = fread(buf, sizeof(char), sizeof(buf), src)) > 0)
            {
                fwrite(buf, sizeof(char), read, dest);
            }
        }
        else
        {
            sprintf(buf, "Can't open the source (%s) or the destination (%s) file to backup...",
                    ui->mTxtFile->text().toUtf8().data(), path.toUtf8().data());

            QMessageBox msg(QMessageBox::Warning, "Error !", buf);
            msg.exec();
        }

        fclose(src);
        fclose(dest);
    }
}

void MainWindow::on_mBtnRestore_clicked()
{
    if (ui->mTxtFile->text().size() > 0 &&
        ui->mTxtRestore->text().size() > 0)
    {
        QFileInfo info(ui->mTxtFile->text());
        QString path = info.dir().canonicalPath();

        #ifdef _WIN32
        path += "\\";
        #else
        path += "/";
        #endif

        path += ui->mTxtRestore->text();

        char buf[4096] = { 0 };
        size_t read = 0;

        FILE* src = fopen(path.toUtf8(), "rb");
        FILE* dest = fopen(ui->mTxtFile->text().toUtf8(), "wb");

        if (src != nullptr && dest != nullptr)
        {
            while ((read = fread(buf, sizeof(char), sizeof(buf), src)) > 0)
            {
                fwrite(buf, sizeof(char), read, dest);
            }
        }
        else
        {
            sprintf(buf, "Can't open the source (%s) or the destination (%s) file to restore...",
                    path.toUtf8().data(), ui->mTxtFile->text().toUtf8().data());

            QMessageBox msg(QMessageBox::Warning, "Error !", buf);
            msg.exec();
        }

        fclose(src);
        fclose(dest);

        on_mBtnLoad_clicked();
    }
}

void MainWindow::on_mBtnSearch_clicked()
{
    if (ui->mTxtSearch->text().size() > 0)
    {
        int32_t uniqID = atoi(ui->mTxtSearch->text().toStdString().c_str());

        GameMap::MapInfo* info = map.getMapInfo(uniqID);
        if (info != nullptr)
        {
            char buf[1024];

            sprintf(buf, "%d", info->UniqID);
            ui->mTxtUniqId->setText(buf);

            ui->mTxtPath->setText(info->Path.c_str());

            sprintf(buf, "%d", info->PuzzleSize);
            ui->mTxtPuzzle->setText(buf);
        }
    }
}

void MainWindow::on_mListWidget_currentRowChanged(int aRow)
{
    LOG("Current row=%d", aRow);

    if (aRow >= 0)
    {
        QListWidgetItem* item = ui->mListWidget->item(aRow);
        int uniqID = atoi(item->text().toStdString().c_str());

        GameMap::MapInfo* info = map.getMapInfo(uniqID);
        if (info != nullptr)
        {
            char buf[1024];

            sprintf(buf, "%d", info->UniqID);
            ui->mTxtUniqId->setText(buf);

            ui->mTxtPath->setText(info->Path.c_str());

            sprintf(buf, "%d", info->PuzzleSize);
            ui->mTxtPuzzle->setText(buf);
        }
    }
}

void MainWindow::on_mBtnEdit_clicked()
{
    if (ui->mTxtUniqId->text().size() > 0 &&
        ui->mTxtPath->text().size() > 0 &&
        ui->mTxtPuzzle->text().size() > 0)
    {
        int uniqID = atoi(ui->mTxtUniqId->text().toStdString().c_str());
        LOG("Editing map=%d", uniqID);

        GameMap::MapInfo* info = map.getMapInfo(uniqID);
        if (info != nullptr)
        {
            info->Path = ui->mTxtPath->text().toStdString();
            info->PuzzleSize = atoi(ui->mTxtPuzzle->text().toStdString().c_str());
        }
    }
}

void MainWindow::on_mBtnDelete_clicked()
{
    if (ui->mTxtUniqId->text().size() > 0)
    {
        int uniqID = atoi(ui->mTxtUniqId->text().toStdString().c_str());
        LOG("Removing map=%d", uniqID);

        if (!IS_SUCCESS(map.remove(uniqID)))
        {
            char buf[1024];
            sprintf(buf, "An error occured while trying to delete the map %d...", uniqID);

            QMessageBox msg(QMessageBox::Warning, "Error !", buf);
            msg.exec();
        }

        QList<QListWidgetItem*> items = ui->mListWidget->findItems(ui->mTxtUniqId->text(), Qt::MatchExactly);
        for (QList<QListWidgetItem*>::Iterator
             it = items.begin(), end = items.end();
             it != end; ++it)
        {
            SAFE_DELETE(*it);
        }
    }
}

void MainWindow::on_mBtnCreate_clicked()
{
    if (ui->mTxtNewUniqId->text().size() > 0 &&
        ui->mTxtNewPath->text().size() > 0 &&
        ui->mTxtNewPuzzle->text().size() > 0)
    {
        int uniqID = atoi(ui->mTxtNewUniqId->text().toStdString().c_str());
        LOG("Creating map=%d", uniqID);

        GameMap::MapInfo* info = new GameMap::MapInfo();
        info->UniqID = uniqID;
        info->Path = ui->mTxtNewPath->text().toStdString();
        info->PuzzleSize = atoi(ui->mTxtNewPuzzle->text().toStdString().c_str());

        if (!IS_SUCCESS(map.add(&info)))
        {
            char buf[1024];
            sprintf(buf, "An error occured while trying to create the map %d...", uniqID);

            QMessageBox msg(QMessageBox::Warning, "Error !", buf);
            msg.exec();
        }
        else
        {
            vector<int32_t> list;
            list = map.getMapUIDs();

            int row = 0;
            ui->mListWidget->clear();
            for (vector<int32_t>::iterator
                 it = list.begin(), end = list.end();
                 it != end; ++it)
            {
                char buf[256];
                sprintf(buf, "%d", *it);

                ui->mListWidget->insertItem(row++, buf);
            }
        }
    }
}
