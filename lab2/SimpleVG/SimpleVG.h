#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimpleVG.h"

class SimpleVG : public QMainWindow
{
	Q_OBJECT

public:
	SimpleVG(QWidget *parent = Q_NULLPTR);

private:
	Ui::SimpleVGClass ui;
};
