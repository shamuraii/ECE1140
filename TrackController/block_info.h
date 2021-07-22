#ifndef BLOCK_INFO_H
#define BLOCK_INFO_H

#include <QWidget>
#include <iostream>
#include "track_control.h"
#include <vector>

namespace Ui {
class block_info;
}

class block_info : public QWidget
{
    Q_OBJECT

public:
    explicit block_info(QWidget *parent = nullptr);
    ~block_info();
    void fillTable(std::string, char);
    void UpdateUI();
    void ShowComponentInfo();

private slots:
    void on_PLCUpload_clicked();

    void on_togglemaintenance_clicked();

private:
    Ui::block_info *ui;
    std::string line;
    char section;
    vector<track_control::Block> block_vector;
    vector<track_control::Block> section_blocks;

};

#endif // BLOCK_INFO_H
