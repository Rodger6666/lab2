#include "replacedialog.h"
#include "ui_replacedialog.h"
#include <QMessageBox>

ReplaceDialog::ReplaceDialog(QWidget *parent,QPlainTextEdit* textEdit)
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    pTextEdit = textEdit;

    ui->rbDown->setChecked(true);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::on_pbFindNext_clicked()
{

    if (pTextEdit == nullptr) return;

    QString target = ui->searchText->text().trimmed();

    if (target.isEmpty()) {
        QMessageBox::information(this, "提示", "请输入要查找的内容！");
        ui->searchText->setFocus(); // 聚焦输入框，方便用户输入
        return;
    }

    QString text = pTextEdit->toPlainText();
    QTextCursor c = pTextEdit->textCursor();
    int index = -1;

    if(ui->rbDown->isChecked()){

        index = text.indexOf(target, c.position(),ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index >= 0){
            c.setPosition(index);
            c.setPosition(index + target.length(), QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(c);

            pTextEdit->ensureCursorVisible();

        }
    }
    else if(ui->rbUp->isChecked()){
        index = text.lastIndexOf(target, c.position() - text.length() - 1,ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index >= 0){
            c.setPosition(index + target.length());
            c.setPosition(index , QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(c);

            pTextEdit->ensureCursorVisible();

        }

    }
    if(index < 0){
        QMessageBox msg(this);
        msg.setWindowTitle("jishiben");
        msg.setText(QString("找不到") + target);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}


void ReplaceDialog::on_pbReplace_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->targetText->text();

    if((pTextEdit != nullptr ) && (target != "") && (to != "")){
        QString selText = pTextEdit->textCursor().selectedText();

        if(selText == target){
            pTextEdit->insertPlainText(to);
        }

        on_pbFindNext_clicked();
    }
}


void ReplaceDialog::on_pbAllReplace_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->targetText->text();

    if((pTextEdit != nullptr ) && (target != "") && (to != "")){
        QString text = pTextEdit->toPlainText();

        text.replace(target,to,ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

        pTextEdit->clear();

        pTextEdit->insertPlainText(text);
    }

}


void ReplaceDialog::on_pbCancel_clicked()
{
    accept();
}

