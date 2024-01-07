#include "returneditems.h"
#include "ui_returneditems.h"
#include <QPixmap>

ReturnedItems::ReturnedItems(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReturnedItems)
{
    ui->setupUi(this);
    QPixmap pix(":/assets/img/returnItem.png");
    ui->returnItemImage->setPixmap(pix.scaled(150,150,Qt::KeepAspectRatio));
}

ReturnedItems::~ReturnedItems()
{
    delete ui;
}

void ReturnedItems::Show()
{
    updateUI();
    show();
}

void ReturnedItems::updateUI()
{
    qDebug() << "in init()";
    QSqlQueryModel * model = new QSqlQueryModel(this);

    QSqlQuery query( MyDB::getInstance()->getDBInstance());
    query.prepare("select * from cppbuzz_items where Status='Return'");

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
