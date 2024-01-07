#include "availableitems.h"
#include "ui_availableitems.h"
#include <QPixmap>

AvailableItems::AvailableItems(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AvailableItems)
{
    ui->setupUi(this);
    QPixmap pix(":/assets/img/availableItem.png");
    ui->availableItemImage->setPixmap(pix.scaled(150,150,Qt::KeepAspectRatio));
}

AvailableItems::~AvailableItems()
{
    delete ui;
}

void AvailableItems::Show()
{
    updateUI();
    show();
}

void AvailableItems::updateUI()
{
    qDebug() << "in init()";
    QSqlQueryModel * model = new QSqlQueryModel(this);

    QSqlQuery query( MyDB::getInstance()->getDBInstance());
    query.prepare("select * from cppbuzz_items where Status='Available'");

    if(!query.exec())
       qDebug() << query.lastError().text() << query.lastQuery();
    else
       qDebug() << "== success query fetch()";

    while(query.next())
    qDebug()<<query.value(0).toString();

    model->setQuery(query);
    ui->tableView->setModel(model);
    qDebug() << "rows are : " << model->rowCount();
    ui->tableView->show();

}
