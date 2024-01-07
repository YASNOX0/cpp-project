#include "expireditems.h"
#include "ui_expireditems.h"
#include <QPixmap>

ExpiredItems::ExpiredItems(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpiredItems)
{
    ui->setupUi(this);
    QPixmap pix(":/assets/img/expiredItem.png");
    ui->expiredItemImage->setPixmap(pix.scaled(150,150,Qt::KeepAspectRatio));
}

ExpiredItems::~ExpiredItems()
{
    delete ui;
}

void ExpiredItems::Show()
{
    updateUI();
    show();
}

void ExpiredItems::updateUI()
{
    qDebug() << "in init()";
    QSqlQueryModel * model = new QSqlQueryModel(this);

    QSqlQuery query( MyDB::getInstance()->getDBInstance());
    query.prepare("select * from cppbuzz_items where Status='Expired'");

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
