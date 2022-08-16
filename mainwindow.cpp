#include "simple_list.h"
#include "simple_stack.h"
#include "parser.h"
#include "rpn_executor.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::token_revision() {
    int code = 0;
    QString str = ui->lineEdit->text();
    if (str.length() != 0) {
        QChar a = str[str.length()-1];
        if (a == '-' || a == '+' || a == '*' || a == '/' || a == '.') {
            code = 1;
        }
     }
    return code;
}
int MainWindow::days(int start_month, int start_year) {
    int a = start_month;
    int days = 0;

    if (a != 2) {
        if (a == 1 || a == 3 || a == 5 || a == 7 || a == 8 || a == 10 || a == 12) {
            days = 31;
        } else {
            days = 30;
        }
    } else {
        days = ((start_year % 4) == 0) ? 29 : 28;
    }
    return days;
}

int MainWindow::days_all(int start_month, int start_year) {
    int all_days = 0;
    int srok = ui->lineEdit_srok_vklad->text().toInt();
    if (ui->year_Box_2->currentIndex() == 0) {
        all_days = srok;
    }
    if (ui->year_Box_2->currentIndex() == 1) {
        for (int i = 0; i < srok; ++i) {
            int c = MainWindow::days(start_month, start_year);
            all_days += c;
            start_month++;
            if (start_month > 12) {
                start_month = 1;
            }
        }
    }
    if (ui->year_Box_2->currentIndex() == 2) {
        all_days = srok * 365;
    }
    return all_days;
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'1');
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'2');
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'3');
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'4');
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'5');
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'6');
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'7');
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'8');
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'9');
}

void MainWindow::on_pushButton_0_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'0');
}

void MainWindow::on_pushButton_tochka_clicked()
{
    if (token_revision() == 0) {
        ui->lineEdit->setText(ui->lineEdit->text()+'.');
    }
}

void MainWindow::on_pushButton_acos_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"acos(");
}

void MainWindow::on_pushButton_asin_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"asin(");
}

void MainWindow::on_pushButton_cos_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"cos(");
}

void MainWindow::on_pushButton_sin_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"sin(");
}

void MainWindow::on_pushButton_open_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+'(');
}

void MainWindow::on_pushButton_close_clicked()
{
    if (token_revision() == 1) {
        ui->lineEdit->text();
    } else {
        ui->lineEdit->setText(ui->lineEdit->text()+')');
    }
}

void MainWindow::on_pushButton_tan_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+ "tan(");
}

void MainWindow::on_pushButton_plus_clicked()
{
    if (token_revision() == 1) {
        ui->lineEdit->text();
    } else {
        ui->lineEdit->setText(ui->lineEdit->text()+'+');
    }
}

void MainWindow::on_pushButton_div_clicked()
{
    if (token_revision() == 1) {
        ui->lineEdit->text();
    } else {
        ui->lineEdit->setText(ui->lineEdit->text()+'/');
    }
}

void MainWindow::on_pushButton_mod_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+ '%');
}

void MainWindow::on_pushButton_pow_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"^");
}

void MainWindow::on_pushButton_sqrt_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"sqrt(");
}

void MainWindow::on_pushButton_atan_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"atan(");
}

void MainWindow::on_pushButton_ln_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"ln(");
}

void MainWindow::on_pushButton_log_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"log(");
}

void MainWindow::on_pushButton_x_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"x");
}

void MainWindow::on_pushButton_mul_clicked()
{
    if (token_revision() == 1) {
        ui->lineEdit->text();
    } else {
        ui->lineEdit->setText(ui->lineEdit->text()+'*');
    }
}

void MainWindow::on_pushButton_minus_clicked()
{
    if (token_revision() == 1) {
        ui->lineEdit->text();
    } else {
        ui->lineEdit->setText(ui->lineEdit->text()+'-');
    }
}

void MainWindow::on_pushButton_bs_clicked()
{
    QString old = ui->lineEdit->text();
    ui->lineEdit->setText(old.mid(0,old.length()-1));
}

void MainWindow::on_pushButton_c_clicked()
{
    ui->lineEdit->setText("");
    ui->result_label->setText("");
}

void MainWindow::on_btnRavno_clicked()
{
    struct list parsed_list;
    struct list rpn_list;
    QString str1 = ui->lineEdit->text();
    QByteArray ba = str1.toLocal8Bit();
    char *func = ba.data();

    parsed_list = parse_source(func);
//    list_debug_print(&parsed_list);
    int err = check_parse_errors(&parsed_list);
    if (err) {
        ui->result_label->setText("Unknown lexema");
    } else {
        rpn_list = rpn(&parsed_list);
        double result = executor(&rpn_list, 0);
        char res[50];
        sprintf(res, "%.7lf", result);
        ui->result_label->setText(res);
    }
}

void MainWindow::on_pushButton_u_minus_clicked()
{
    if (token_revision() == 1) {
        ui->lineEdit->text();
    } else {
        ui->lineEdit->setText(ui->lineEdit->text()+'~');
    }
}

void MainWindow::on_graphic_button_clicked()
{
   ui->graphicsView->clearGraphs();
   ui->graphicsView->xAxis->setRange(-50, 50);
   ui->graphicsView->yAxis->setRange(-20, 20);
   ui->graphicsView->addGraph();

   double x = -100;
   double y = 0;
   double delta = 0.1;
   struct list parsed_list;
   struct list rpn_list;
   QString str1 = ui->lineEdit->text();
   QByteArray ba = str1.toLocal8Bit();
   char *func = ba.data();

   parsed_list = parse_source(func);
   int err = check_parse_errors(&parsed_list);
   if (err) {
       ui->result_label->setText("Unknown lexema");
   } else {
       rpn_list = rpn(&parsed_list);

       for (int i = 0; i < 2000; i++) {
           y = executor(&rpn_list, x);
           ui->graphicsView->graph(0)->addData(x, y);
           x += delta;
       }
   }
   ui->graphicsView->replot();
}

void MainWindow::on_pushButton_kredit_clicked()
{
    QDate today = QDate::currentDate();   // today data
    QDate next0, next1;

    long double ann_ep;
    long double percent;
    long double all_summ;
    double sz = ui->lineEdit_sz->text().toDouble();
    double stavka = ui->lineEdit_stavka->text().toDouble();
    double srok = ui->lineEdit_srok->text().toDouble();
    if (ui->year_Box->currentIndex() == 0) {
        srok *= 12;
    }
    if (ui->type_box->currentIndex() == 0) {
        stavka /= 1200;
        long double x = pow((1+stavka),srok);
        ann_ep = sz*(stavka * x/(x-1));
        all_summ = ann_ep * srok;
        percent = all_summ - sz;

        char res[50];
        sprintf(res, "%.2Lf", ann_ep);
        ui->result_label_month_plata->setText(res);
        sprintf(res, "%.2Lf", percent);
        ui->result_label_pereplata->setText(res);
        sprintf(res, "%.2Lf", all_summ);
        ui->result_label_allsumm->setText(res);
    }
    if (ui->type_box->currentIndex() == 1) {
        int days;
        long double diff2, first_pl;
        long double percent_total = 0;
        stavka /= 100;
        long double y = sz / srok;
        for (int i = 1; i <= srok; i++) {
            next0 = today.addMonths(i-1);  // start data
            next1 = today.addMonths(i);     // finish data for month i
            days = next0.daysTo(next1);  // kol-vo days for month i
            long double Q2 = sz - (y * (i -1));
            long double pereplata_per_month = (Q2*stavka*30.41666)/365;
            diff2 = y + pereplata_per_month;
            if (i == 1) {
                first_pl = diff2;
            }
            percent_total +=pereplata_per_month;
            printf("%d\n", days);
        }

        char res[50];
        sprintf(res, "%.2Lf... %.2Lf", first_pl, diff2);
        ui->result_label_month_plata->setText(res);
        sprintf(res, "%.2Lf", percent_total);
        ui->result_label_pereplata->setText(res);
        sprintf(res, "%.2Lf", percent_total+sz);
        ui->result_label_allsumm->setText(res);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QDate start_date = ui->dateEdit->date();
    int start_month = start_date.month();
    int start_year = start_date.year();
    long double count_per = 0;
    long double percent = 0, temp_vklad = 0, temp_percent;
    int temp_srok = 0;
    long double sum_vklad = ui->lineEdit_sum_vklad->text().toDouble();
    long double stavka = ui->lineEdit_procent_vklad->text().toDouble();
    int srok = ui->lineEdit_srok_vklad->text().toInt();  // days
    long double popoln = ui->lineEdit_spisok_popolnen->text().toDouble();
    long double spisan = ui->lineEdit_spisok_spisat->text().toDouble();
    int days_in_month = MainWindow::days(start_month, start_year);
    int year_days;
    int stop = 0;
    int c = days_in_month;
    long double nalog = 0;
    long double rate_CB = 80000;
    year_days = ((start_year % 4) == 0) ? 366 : 365;

    if (sum_vklad > 0 && srok > 0 && stavka > 0 && popoln >= 0 && spisan >= 0) {
        if (ui->periodik_box->currentIndex() == 0 && ui->capital_Box->currentIndex() == 1) {   // раз в месяц
            sum_vklad += popoln;
            sum_vklad -= spisan;
            if (ui->year_Box_2->currentIndex() == 2) {   // года
                temp_srok = srok*12;
            }
            if (ui->year_Box_2->currentIndex() == 1) {   // мес
                temp_srok = srok;
                srok *= days_in_month;
            }
            if (ui->year_Box_2->currentIndex() == 0) {   // дни
                ui->lineEdit_srok_vklad->setText("только месяц/год");
                stop = 1;
            }
            temp_vklad = sum_vklad;
            for (int i= 0; i < temp_srok; i++) {
                temp_percent = (temp_vklad*stavka*c/year_days)/100;
                temp_vklad += temp_percent;
                count_per += temp_percent;
                start_month++;
                if (start_month > 12) {
                    start_month = 1;
                    start_year++;
                }
                c = MainWindow::days(start_month, start_year);
            }
        }

         if (ui->periodik_box->currentIndex() == 1 && ui->capital_Box->currentIndex() == 1) {    // раз в год
             sum_vklad += popoln;
             sum_vklad -= spisan;
             int count_years = 0;
             if (ui->year_Box_2->currentIndex() == 2) {   // года
                 temp_srok = srok*12;
             }
             if (ui->year_Box_2->currentIndex() == 1) {   // мес
                 temp_srok = srok;
                 srok *= days_in_month;
             }
             if (ui->year_Box_2->currentIndex() == 0) {   // дни
                 temp_srok = srok/365*12;
             }
             temp_vklad = sum_vklad;
             for (int i= 0; i < temp_srok; i++) {
                 temp_percent = (sum_vklad*stavka*c/year_days)/100;
                 temp_vklad += temp_percent;
                 count_per += temp_percent;
                 start_month++;
                 if (start_month > 12) {
                     start_month = 1;
                     start_year++;
                 }
                 c = MainWindow::days(start_month, start_year);
                 count_years++;
                 if (count_years == 12) {
                     sum_vklad = temp_vklad;
                     count_years = 0;
                 }
             }
         }

        if (ui->capital_Box->currentIndex() == 1 && ui->periodik_box->currentIndex() != 2) {    // с капитализацией
            if (ui->year_Box_2->currentIndex() == 0) {
                if (srok < MainWindow::days(start_month, start_year)) {
                    percent = (sum_vklad*stavka*srok/year_days)/100;
                }
            } else {
                sum_vklad = temp_vklad;
                percent = count_per;
            }
        }
        if (ui->capital_Box->currentIndex() == 0 || ui->periodik_box->currentIndex() == 2) {    //  без капитализации
            sum_vklad += popoln;
            sum_vklad -= spisan;
            if (ui->year_Box_2->currentIndex() == 2) {
                temp_srok = srok*12;
            }
            if (ui->year_Box_2->currentIndex() == 1) {
                temp_srok = srok;
                srok *= days_in_month;
            }
            if (ui->year_Box_2->currentIndex() == 0) {
                percent = (sum_vklad*stavka*srok/year_days)/100;
            } else {
                for (int i= 0; i < temp_srok; i++) {
                    temp_percent = (sum_vklad*stavka*c/year_days)/100;
                    count_per += temp_percent;
                    start_month++;
                    if (start_month > 12) {
                        start_month = 1;
                        start_year++;
                    }
                    c = MainWindow::days(start_month, start_year);
                    percent = count_per;
                }
            }
        }
        if (ui->year_Box_2->currentIndex() == 2) {
            rate_CB *= srok;
        }
        int cb = percent - rate_CB;
        if (cb > 0) {
            nalog = cb *0.13;
        }
            char res[50];
        if (stop != 1) {
            sprintf(res, "%.2Lf", percent);
            ui->result_label_procent_vklad->setText(res);
            sprintf(res, "%.2Lf", sum_vklad);
            ui->result_label_summ_end->setText(res);
            sprintf(res, "%.2Lf", nalog);
            ui->result_label_nalog->setText(res);
        } else {
            ui->result_label_procent_vklad->setText("0");
            ui->result_label_summ_end->setText("0");
            ui->result_label_nalog->setText("0");
        }
    } else {
        ui->result_label_procent_vklad->setText("0");
        ui->result_label_summ_end->setText("0");
        ui->result_label_nalog->setText("0");
    }
}

