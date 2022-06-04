#include "mainwindow.h"
#include "ui_mainwindow.h"


#include<QCoreApplication>

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
    list_finite_field = QStringList() << tr("   Додавання") //xyz
                                      << tr("   Віднімання") //xyz
                                      << tr("   Множення") //xyz
                                      << tr("   Знаходження оберненого") //xyz
                                      << tr("   Ділення") //xyz
                                      << tr("   Швидке піднесення у степінь") //xyz
                                      << tr("   Розклад на множники (Наївний)") //x
                                      << tr("   Розклад на множники (Полард)") //x
                                      << tr("   Обчислення квадратного кореня") //xz
                                      << tr("   Знаходження порядку елемента групи") //xz
                                      << tr("   Чи є елемент генератором?") //xz
                                      << tr("   Знаходження функції Ейлера") //xz
                                      << tr("   Знаходження функції Кармайкла") //xz
                                      << tr("   Перевірка числа на простоту") //xk(z)
                                      ;

    list_polynomial_field = QStringList() << tr("   Додавання") //xyzi
                                          << tr("   Віднімання") //xyzi
                                          << tr("   Множення") //xyzi
                                          << tr("   Нормування многочлена") //xz
                                          << tr("   Швидке піднесення у степінь") //xyzi
                                          << tr("   Чи є многочлен незвідним?") //xz
                                          << tr("   Знаходження оберненого") //xzi
                                          ;

    list_polynomial_ring = QStringList() << tr("   Додавання") //xyz
                                         << tr("   Віднімання") //xyz
                                         << tr("   Множення") //xyz
                                         << tr("   Знаходження похідної") //xz
                                         << tr("   Знаходження значення многочлена у точці") //xyz
                                         << tr("   Знаходження частки") //xyz
                                         << tr("   Знаходження остачі") //xyz
                                         << tr("   Знаходження НСД") //xyz
                                         << tr("   Знаходження кругового многочлена") //xz
                                         ;


    ui->comboBox->addItems(list_finite_field);
    ui->radioButton->setChecked(1);
    ui->lineEdit_2->setVisible(true);
    ui->lineEdit_3->setVisible(true);
    ui->label_3->setVisible(true);
    ui->lineEdit_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    f_group = "finite_field";
    //QPixmap pixmap("../Interface_w/One_Ring_Blender_Render.png");
    QPixmap pixmap("../System_of_modular_arithmetic/One_Ring_Blender_Render.png");
    ui->pic_1->setPixmap(pixmap);
    ui->pic_1->setVisible(false);
    reset();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset(){
//    ui->pushButton->setStyleSheet("background-color: rgb(71, 71, 71);border-radius: 10px;color:#fff;");
//    ui->pushButton->setText("Порахувати");
  ui->pic_1->setVisible(false);
}

void MainWindow::on_pushButton_clicked()
{

    reset();
    try {
        if(f_name == "   Додавання"){
            if (f_group == "finite_field")
                ui->label->setText(ff_addition(ui->lineEdit->text(),ui->lineEdit_2->text(), ui->lineEdit_3->text()));
            else if (f_group == "polynomial_field")
                ui->label->setText(pf_addition(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->lineEdit_4->text()));
            else if (f_group == "polynomial_ring")
                ui->label->setText(pr_addition(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
        }
        else if(f_name == "   Віднімання"){
            if (f_group == "finite_field")
                ui->label->setText(ff_subtraction(ui->lineEdit->text(),ui->lineEdit_2->text(), ui->lineEdit_3->text()));
            else if (f_group == "polynomial_field")
                    ui->label->setText(pf_subtraction(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->lineEdit_4->text()));
            else if (f_group == "polynomial_ring")
                ui->label->setText(pr_subtraction(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
        }
        else if(f_name == "   Множення"){
            if (f_group == "finite_field")
                ui->label->setText(ff_multiply(ui->lineEdit->text(),ui->lineEdit_2->text(), ui->lineEdit_3->text()));
            else if (f_group == "polynomial_field")
                ui->label->setText(pf_multiply(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->lineEdit_4->text()));
            else if (f_group == "polynomial_ring")
                ui->label->setText(pr_multiply(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
        }
        //mikita here was problem
        else if(f_name == "   Знаходження оберненого"){
            if (f_group == "finite_field")
                ui->label->setText(ff_inverse(ui->lineEdit->text(),ui->lineEdit_2->text(), ui->lineEdit_3->text()));
            else if (f_group == "polynomial_field")
                ui->label->setText(pf_inverse(ui->lineEdit->text(),ui->lineEdit_3->text(),ui->lineEdit_4->text()));
        }
        else if(f_name == "   Швидке піднесення у степінь"){
            if (f_group == "finite_field")
                ui->label->setText(ff_pow(ui->lineEdit->text(),ui->lineEdit_2->text(), ui->lineEdit_3->text()));
            else if (f_group == "polynomial_field")
                ui->label->setText(pf_fast_pow(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->lineEdit_4->text()));
        }    
        else if(f_name == "   Ділення"){
            ui->label->setText(ff_division(ui->lineEdit->text(),ui->lineEdit_2->text(), ui->lineEdit_3->text()));
        }
        else if(f_name == "   Розклад на множники (Наївний)"){
            ui->label->setText(ff_facrorization_naive(ui->lineEdit->text()));
        }
        else if(f_name == "   Розклад на множники (Полард)"){
            ui->label->setText(ff_facrorization_polard(ui->lineEdit->text()));
        }
        else if(f_name == "   Обчислення квадратного кореня"){
            ui->label->setText(ff_sqrt(ui->lineEdit->text(), ui->lineEdit_3->text()));
        }
        else if(f_name == "   Знаходження порядку елемента групи"){
            ui->label->setText(ff_order(ui->lineEdit->text(),ui->lineEdit_3->text()));
        }
        else if(f_name == "   Чи є елемент генератором?"){
            ui->label->setText(ff_generator(ui->lineEdit->text(),ui->lineEdit_3->text()));
        }   
        else if(f_name == "   Знаходження функції Ейлера"){
            ui->label->setText(ff_euler(ui->lineEdit->text(), ui->lineEdit_3->text()));
        }
        else if(f_name == "   Знаходження функції Кармайкла"){
            ui->label->setText(ff_carmaicle(ui->lineEdit->text(), ui->lineEdit_3->text()));
        }    
        else if(f_name == "   Перевірка числа на простоту"){
            ui->label->setText(ff_prime(ui->lineEdit->text(),ui->lineEdit_3->text()));
        }


        else if(f_name == "   Нормування многочлена"){
            ui->label->setText(pf_normality(ui->lineEdit->text(),ui->lineEdit_3->text()));
        }
        else if(f_name == "   Чи є многочлен незвідним?"){
            ui->label->setText(pf_is_irred(ui->lineEdit->text(),ui->lineEdit_3->text()));
        }


        else if(f_name == "   Знаходження похідної"){
            ui->label->setText(pr_derivative(ui->lineEdit->text(),ui->lineEdit_3->text()));
        }
        else if(f_name == "   Знаходження значення многочлена у точці"){
            ui->label->setText(pr_value_in_point(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
        }
        else if(f_name == "   Знаходження частки"){
                    ui->label->setText(pr_ring_divide(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
        }
        else if(f_name == "   Знаходження остачі"){
            ui->label->setText(pr_ring_reminder(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
        }
        else if(f_name == "   Знаходження НСД"){
            ui->label->setText(pr_ring_gcd(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text()));
        }
        else if(f_name == "   Знаходження кругового многочлена"){
            ui->label->setText(pr_get_cycled(ui->lineEdit->text(),ui->lineEdit_3->text()));
        }
    }
    catch(const std::invalid_argument& e)
    {
        ui->label->setText(e.what());
    }
    catch(...)
    {
        ui->label->setText("Помилка");
    }

   // ui->pushButton->setStyleSheet("border-radius: 10px;color:#FFFFFF; background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:0  #005BBB, stop: 0.70  #005BBB, stop:0.71 #FFD500, stop:1 #FFD500);");
    //ui->pushButton->setText("Слава Україні!");
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{

    reset();
    f_name = arg1;

    //no y
    if ( f_name=="   Розклад на множники (Наївний)" 
    || f_name=="   Розклад на множники (Полард)"
    || f_name=="   Обчислення квадратного кореня"
    || f_name=="   Перевірка числа на простоту" 
    || f_name=="   Знаходження похідної" 
    || f_name=="   Нормування многочлена"
    || f_name=="   Чи є многочлен незвідним?"
    || f_name=="   Знаходження порядку елемента групи"
    || f_name=="   Знаходження оберненого"
    || f_name=="   Чи є елемент генератором?" //xz
    || f_name=="   Знаходження функції Ейлера" //xz
    || f_name=="   Знаходження функції Кармайкла"
    || f_name=="   Знаходження функції Ейлера"){
        ui->lineEdit_2->clear();
        ui->lineEdit_2->setVisible(false);
        ui->lineEdit_2->setReadOnly(true);
    }    
    else{
        ui->lineEdit_2->setVisible(true);
        ui->lineEdit_2->setReadOnly(false);
    }

    //no i
    if(f_group == "polynomial_field"){
        if ( f_name=="   Нормування многочлена" 
        || f_name=="   Чи є многочлен незвідним?"){
            ui->lineEdit_4->clear();
            ui->lineEdit_4->setVisible(false);
            ui->lineEdit_4->setReadOnly(true);
            ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);        
        }    
        else{
            ui->lineEdit_4->setVisible(true);
            ui->lineEdit_4->setReadOnly(false);
            ui->label_5->setVisible(true);
            ui->label_6->setVisible(true);
        }
    }

    //no z
    if(f_group == "finite_field"){
        if ( f_name=="   Розклад на множники (Наївний)"
             || f_name=="   Розклад на множники (Полард)"
        ){
            ui->lineEdit_3->clear();
            ui->lineEdit_3->setVisible(false);
            ui->lineEdit_3->setReadOnly(true);
            ui->label_3->setVisible(false);

        }
        else {
            ui->lineEdit_3->setVisible(true);
            ui->lineEdit_3->setReadOnly(false);
            ui->label_3->setVisible(true);
        }
    }

    if(f_name=="   Перевірка числа на простоту")
    {
        ui->lineEdit_3->setVisible(true);
        ui->lineEdit_3->setReadOnly(false);
        ui->label_3->setVisible(true);
        ui->label_3->setText("Ітератор");
    }
    else{
        ui->label_3->setText("Модуль");
    }

}

void MainWindow::on_radioButton_clicked()
{
    reset();
    f_group = "finite_field";
    ui->comboBox->clear();
    ui->comboBox->addItems(list_finite_field);

    ui->lineEdit_3->setVisible(true);
    ui->lineEdit_3->setReadOnly(false);
    ui->label_3->setVisible(true);

    ui->lineEdit_4->clear();
    ui->lineEdit_4->setVisible(false);
    ui->lineEdit_4->setReadOnly(true);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);

}

void MainWindow::on_radioButton_2_clicked()
{
    reset();
    f_group = "polynomial_field";
    ui->comboBox->clear();
    ui->comboBox->addItems(list_polynomial_field);

    ui->lineEdit_3->setVisible(true);
    ui->lineEdit_3->setReadOnly(false);
    ui->label_3->setVisible(true);

    ui->lineEdit_4->setVisible(true);
    ui->lineEdit_4->setReadOnly(false);
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(true);

}


void MainWindow::on_radioButton_3_clicked()
{
    reset();
    f_group = "polynomial_ring";
    ui->comboBox->clear();
    ui->comboBox->addItems(list_polynomial_ring);

    ui->lineEdit_3->setVisible(true);
    ui->lineEdit_3->setReadOnly(false);
    ui->label_3->setVisible(true);

    //ui->pic_1->setVisible(true);

    ui->lineEdit_4->clear();
    ui->lineEdit_4->setVisible(false);
    ui->lineEdit_4->setReadOnly(true);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);

    
}

void MainWindow::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    reset();
}

void MainWindow::on_lineEdit_2_cursorPositionChanged(int arg1, int arg2)
{
    reset();
}

void MainWindow::on_lineEdit_3_cursorPositionChanged(int arg1, int arg2)
{
    reset();
}

void MainWindow::on_pushButton_2_clicked()
{
    TestRunner();
}

