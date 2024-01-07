#include "updateitem.h"
#include "ui_updateitem.h"
#include <QPixmap>

UpdateItem::UpdateItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateItem)
{
    ui->setupUi(this);
    QPixmap pix(":/assets/img/updateItem.png");
    ui->updateItemImage->setPixmap(pix.scaled(150,150,Qt::KeepAspectRatio));
}

UpdateItem::~UpdateItem()
{
    delete ui;
}

void UpdateItem::updateUI()
{

}

void UpdateItem::Show()
{
    updateUI();
    this->show();
}

void UpdateItem::on_pushButton_clicked()
{
    ui->lblInfo->clear();
    QString sId = ui->txtId->text();
    QString sStatus = ui->cmbStatus->currentText();

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.clear();
    query.prepare("UPDATE cppbuzz_items SET Status = :sStatus WHERE Id = :sId" );
    query.bindValue(":sStatus" , sStatus);
    query.bindValue(":sId" , sId);

    if(!query.exec())
    {
       qDebug() << query.lastError().text() << query.lastQuery();
       ui->lblInfo->setText("Unable to update Item" + query.lastError().text());
    }
    else{
       if(query.numRowsAffected()>0)
       {
            qDebug() << "Item Updated Successfully!";
            ui->lblInfo->setText("Item Updated Successfully!");
       }
       else
       {
        qDebug() << " Unable to update Item";
        ui->lblInfo->setText("Unable to Update Item");
      }
    }
}

