#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QMessageBox>
#include <QTextCursor>

SearchDialog::SearchDialog(QWidget *parent,QPlainTextEdit *textEdit):
    QDialog(parent)
    ,ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    pTextEdit = textEdit;
    ui->rbDown->setChecked(true);


    if (pTextEdit == nullptr) {
        QMessageBox::warning(this, "警告", "未关联文本编辑框！");
        ui->btfindNext->setEnabled(false); // 禁用查找按钮
    }
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_btfindNext_clicked()
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

void SearchDialog::on_btCancel_clicked()
{
    accept();
}
