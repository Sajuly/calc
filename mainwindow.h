#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include "qcustomplot.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    int token_revision();

    int days(int start_month, int start_year);

    int days_all(int start_month, int start_year);

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_tochka_clicked();

    void on_pushButton_acos_clicked();

    void on_pushButton_asin_clicked();

    void on_pushButton_cos_clicked();

    void on_pushButton_sin_clicked();

    void on_pushButton_open_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_tan_clicked();

    void on_pushButton_plus_clicked();

    void on_pushButton_div_clicked();

    void on_pushButton_mod_clicked();

    void on_pushButton_pow_clicked();

    void on_pushButton_sqrt_clicked();

    void on_pushButton_atan_clicked();

    void on_pushButton_ln_clicked();

    void on_pushButton_log_clicked();

    void on_pushButton_x_clicked();

    void on_pushButton_mul_clicked();

    void on_pushButton_minus_clicked();

    void on_pushButton_bs_clicked();

    void on_pushButton_c_clicked();

    void on_btnRavno_clicked();

    void on_pushButton_u_minus_clicked();

    void on_graphic_button_clicked();

    void on_pushButton_kredit_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
