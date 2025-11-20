#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(QWidget *parent = nullptr,QPlainTextEdit* textEdit=nullptr);
    ~ReplaceDialog();

private slots:
    void on_pbFindNext_clicked();

    void on_pbReplace_clicked();

    void on_pbAllReplace_clicked();

    void on_pbCancel_clicked();

private:
    Ui::ReplaceDialog *ui;
    QPlainTextEdit *pTextEdit;
};

#endif // REPLACEDIALOG_H
