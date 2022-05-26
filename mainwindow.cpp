#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(10);
    effect->setColor(QColor(0, 0, 0, 70)) ;
    effect->setOffset(0,3);
    ui->pushButton->setGraphicsEffect(effect);
    list_finite_field = QStringList() << tr("   Додавання")<< tr("   Віднімання") << tr("   Множення") << tr("   Знаходження оберненого") << tr("   Ділення")
                                      << tr("   Швидке піднесення у степінь") << tr("   Розклад на множники (Наївний)") << tr("   Розклад на множники (Полард)")
                                      << tr("   Обчислення квадратного кореня") << tr("   Перевірка числа на простоту");

    list_polynomial_field = QStringList() << tr("   Додавання")<< tr("   Віднімання") << tr("   Множення")
                                          //<< tr("   Знаходження оберненого")
                                          << tr("   Нормування многочлена")
                                          << tr("   Швидке піднесення у степінь");

    list_polynomial_ring = QStringList() << tr("   Додавання")<< tr("   Віднімання") << tr("   Множення") << tr("   Знаходження похідної")
                                         << tr("   Знаходження значення многочлена у точці")
                                         <<   tr("   Додавання за модулем")<< tr("   Віднімання за модулем") << tr("   Множення за модулем");

    ui->comboBox->addItems(list_finite_field);
    ui->radioButton->setChecked(1);
    ui->lineEdit_3->setVisible(false);
    ui->label_3->setVisible(false);
    f_group = "finite_field";

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    if(f_name == "   Додавання"){
        if (f_group == "finite_field")
            ui->label->setText(ff_addition(ui->lineEdit->text(),ui->lineEdit_2->text()));
        else if (f_group == "polynomial_field")
            try {
                    ui->label->setText(pf_addition(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
                }  catch (...) {
                    ui->label->setText("Невірний модуль");
                }
              else if (f_group == "polynomial_ring")
            ui->label->setText(pr_addition(ui->lineEdit->text(),ui->lineEdit_2->text()));
    }
    else if(f_name == "   Віднімання"){
        if (f_group == "finite_field")
            ui->label->setText(ff_subtraction(ui->lineEdit->text(),ui->lineEdit_2->text()));
        else if (f_group == "polynomial_field")
            try {
            ui->label->setText(pf_subtraction(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
                     }  catch (...) {
                    ui->label->setText("Невірний модуль");
                }
             else if (f_group == "polynomial_ring")
            ui->label->setText(pr_subtraction(ui->lineEdit->text(),ui->lineEdit_2->text()));
    }

    else if(f_name == "   Множення"){
        if (f_group == "finite_field")
            ui->label->setText(ff_multiply(ui->lineEdit->text(),ui->lineEdit_2->text()));
        else if (f_group == "polynomial_field")
            try {
            ui->label->setText(pf_multiply(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
                            }  catch (...) {
                    ui->label->setText("Невірний модуль");
                }
               else if (f_group == "polynomial_ring")
            ui->label->setText(pr_multiply(ui->lineEdit->text(),ui->lineEdit_2->text()));
    }

    else if(f_name == "   Знаходження оберненого"){
        if (f_group == "finite_field")
            ui->label->setText(ff_inverse(ui->lineEdit->text(),ui->lineEdit_2->text()));
        //else if (f_group == "polynomial_field")
            //ui->label->setText(pf_inverse(ui->lineEdit->text(),ui->lineEdit_2->text()));
    }

    else if(f_name == "   Ділення"){
        ui->label->setText(ff_division(ui->lineEdit->text(),ui->lineEdit_2->text()));
    }
    else if(f_name == "   Швидке піднесення у степінь"){
        if (f_group == "finite_field")
            ui->label->setText(ff_pow(ui->lineEdit->text(),ui->lineEdit_2->text()));
               else if (f_group == "polynomial_field")
            try {
            ui->label->setText(pf_fast_pow(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
                       }  catch (...) {
                    ui->label->setText("Невірний модуль");
                }
    }
    else if(f_name == "   Розклад на множники(Наївний)"){
        ui->label->setText(ff_facrorization_naive(ui->lineEdit->text()));
    }
    else if(f_name == "   Розклад на множники(Полард)"){
        ui->label->setText(ff_facrorization_polard(ui->lineEdit->text()));
    }
    else if(f_name == "   Обчислення квадратного кореня"){
        ui->label->setText(ff_sqrt(ui->lineEdit->text()));
    }
    else if(f_name == "   Перевірка числа на простоту"){
        ui->label->setText(ff_prime(ui->lineEdit->text()));
    }

    else if(f_name == "   Нормування многочлена"){
        ui->label->setText(pf_normality(ui->lineEdit->text(),ui->lineEdit_3->text()));
    }

    else if(f_name == "   Знаходження похідної"){
        ui->label->setText(pr_derivative(ui->lineEdit->text()));
    }

    else if(f_name == "   Знаходження значення многочлена у точці"){
        ui->label->setText(pr_value_in_point(ui->lineEdit->text(),ui->lineEdit_2->text()));
    }

    else if(f_name == "   Додавання за модулем"){
        ui->label->setText(pr_addition_mod(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
    }
    else if(f_name == "   Віднімання за модулем"){
        ui->label->setText(pr_subtraction_mod(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
    }
    else if(f_name == "   Множення за модулем"){
        ui->label->setText(pr_multiply_mod(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
    }
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    f_name = arg1;
    if (f_name=="   Розклад на множники(Наївний)" || f_name=="   Розклад на множники(Полард)"|| f_name=="   Обчислення квадратного кореня"
            || f_name=="   Перевірка числа на простоту" || f_name=="   Знаходження похідної" || f_name=="   Нормування многочлена"){
         ui->lineEdit_2->clear();
         ui->lineEdit_2->setVisible(false);
        ui->lineEdit_2->setReadOnly(true);
    }    
    else{
        ui->lineEdit_2->setVisible(true);
        ui->lineEdit_2->setReadOnly(false);
    }

    if (f_group == "polynomial_ring"){
        if(f_name=="   Додавання за модулем" || f_name=="   Віднімання за модулем"|| f_name=="   Множення за модулем"){
            ui->lineEdit_3->setVisible(true);
            ui->lineEdit_3->setReadOnly(false);
            ui->label_3->setVisible(true);
        }
        else {
            ui->lineEdit_3->clear();
            ui->lineEdit_3->setVisible(false);
           ui->lineEdit_3->setReadOnly(true);
           ui->label_3->setVisible(false);
        }
    }

}

void MainWindow::on_radioButton_clicked()
{
    f_group = "finite_field";
    ui->comboBox->clear();
    ui->comboBox->addItems(list_finite_field);
    ui->lineEdit_3->clear();
    ui->lineEdit_3->setVisible(false);
   ui->lineEdit_3->setReadOnly(true);
   ui->label_3->setVisible(false);
}

void MainWindow::on_radioButton_2_clicked()
{
    f_group = "polynomial_field";
    ui->comboBox->clear();
    ui->comboBox->addItems(list_polynomial_field);
    ui->lineEdit_3->setVisible(true);
    ui->lineEdit_3->setReadOnly(false);
    ui->label_3->setVisible(true);
}


void MainWindow::on_radioButton_3_clicked()
{
    f_group = "polynomial_ring";
    ui->comboBox->clear();
    ui->comboBox->addItems(list_polynomial_ring);
    ui->lineEdit_3->clear();
    ui->lineEdit_3->setVisible(false);
   ui->lineEdit_3->setReadOnly(true);
   ui->label_3->setVisible(false);
}




//    if(ui->radioButton->isChecked()){
//        if (ui->lineEdit_2->isReadOnly()){
//            ui->label->setText(ui->lineEdit->text()+" -> 1");
//        }
//        else{
//            ui->label->setText(ui->lineEdit->text()+ui->lineEdit_2->text()+" -> 1");
//        }

//    }
//    else if(ui->radioButton_2->isChecked()){
//        if (ui->lineEdit_2->isReadOnly()){
//            ui->label->setText(ui->lineEdit->text()+" -> 2");
//        }
//        else{
//            ui->label->setText(ui->lineEdit->text()+ui->lineEdit_2->text()+" -> 2");
//        }
//    }
//    else if(ui->radioButton_3->isChecked()){
//        if (ui->lineEdit_2->isReadOnly()){
//            ui->label->setText(ui->lineEdit->text()+" -> 3");
//        }
//        else{
//            ui->label->setText(ui->lineEdit->text()+ui->lineEdit_2->text()+" -> 3");
//        }
//    }
//    else{
//        if (ui->lineEdit_2->isReadOnly()){
//            ui->label->setText(ui->lineEdit->text());
//        }
//        else{
//            ui->label->setText(ui->lineEdit->text()+ui->lineEdit_2->text());
//        }
//    }
