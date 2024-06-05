#include "camers.h"
#include "ui_camers.h"
std::vector<birds> v;
birds curren;
birds defaul;
camers::camers(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::camers)
{
    ui->setupUi(this);
    ui->clear_fixat->setEnabled(false);
    ui->vent_fixat->setEnabled(false);
    ui->food_fixat->setEnabled(false);
    ui->sohran_v_file->setEnabled(false);
    ui->del_el_from_l->setEnabled(false);
    //ui->age_output->setText(QString::number(defaul.get_age()));
    //ui->species_output->setText(defaul.get_specie());
    //ui->clear_output->setText(QString::number(defaul.get_clear_status()));
    //ui->food_output->setText(QString::number(defaul.get_food_status()));
    //ui->vent_output->setText(QString::number(defaul.get_vent_status()));
    ui->age_output->setText("Не выбрана особь");
    ui->species_output->setText("");
    ui->clear_output->setText("");
    ui->food_output->setText("");
    ui->vent_output->setText("");
    QFile file("bird_cams.txt");
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream steram(&file);
        while (!steram.atEnd())
        {
            QString l1, l2, l3, l4, l5, l6;
            l1 = steram.readLine();
            l2 = steram.readLine();
            l3 = steram.readLine();
            l4 = steram.readLine();
            l5 = steram.readLine();
            l6 = steram.readLine();
            QString ltemp = l1+" ("+l3+")";
            birds temp(l1, l2.toInt(), l3.toInt(), l4.toInt(),l5.toInt(),l6.toInt());
            v.push_back(temp);
            ui->list_cams->addItem(ltemp);
        }
        file.close();
    }
    connect(ui->choose_cur, &QPushButton::clicked, this, &camers::button_current_list_item);
    connect(ui->clear_fixat, &QPushButton::clicked, this, &camers::button_clear);
    connect(ui->food_fixat, &QPushButton::clicked, this, &camers::button_food);
    connect(ui->vent_fixat, &QPushButton::clicked, this, &camers::button_vent);
    connect(ui->del_el_from_l, &QPushButton::clicked, this, &camers::button_deletion);
    connect(ui->add_el_to_list, &QPushButton::clicked, this, &camers::button_add_new);
    connect(ui->sohran_v_file, &QPushButton::clicked, this, &camers::button_save_to_f);
}
void camers::button_current_list_item()
{
    int ind = ui->list_cams->currentRow();
    curren = v.at(ind);
    ui->age_output->setText("Возраст: " + QString::number(curren.get_age()));
    ui->species_output->setText("Вид: " + curren.get_specie());
    ui->clear_output->setText(QString::number(curren.get_clear_status()));
    ui->food_output->setText(QString::number(curren.get_food_status()));
    ui->vent_output->setText(QString::number(curren.get_vent_status()));
    if (curren.get_clear_status()<40)
    {
        ui->clear_fixat->setEnabled(true);
    }
    if (curren.get_food_status()<15)
        ui->food_fixat->setEnabled(true);
    if (curren.get_vent_status()<35)
        ui->vent_fixat->setEnabled(true);
    ui->sohran_v_file->setEnabled(true);
    ui->del_el_from_l->setEnabled(true);
}
void camers::button_food()
{
    curren.give_food();
    ui->food_output->setText(QString::number(curren.get_food_status()));
    ui->food_fixat->setEnabled(false);
}
void camers::button_clear()
{
    curren.clean_camera();
    ui->clear_output->setText(QString::number(curren.get_clear_status()));
    ui->clear_fixat->setEnabled(false);
}
void camers::button_vent()
{
    curren.fix_vent();
    ui->vent_output->setText(QString::number(curren.get_vent_status()));
    ui->vent_fixat->setEnabled(false);
}
void camers::button_deletion()
{
    unsigned int ind = ui->list_cams->currentRow();
    delete ui->list_cams->takeItem(ind);
    for (unsigned int i=ind; i<v.size() - 1; i++)
    {
        v.at(i)=v.at(i+1);
    }
    v.pop_back();
    //ui->age_output->setText("Возраст: " + QString::number(defaul.get_age()));
    //ui->species_output->setText("Вид: " + defaul.get_specie());
    //ui->clear_output->setText(QString::number(defaul.get_clear_status()));
    //ui->food_output->setText(QString::number(defaul.get_food_status()));
    //ui->vent_output->setText(QString::number(defaul.get_vent_status()));
    ui->age_output->setText("Не выбрана особь");
    ui->species_output->setText("");
    ui->clear_output->setText("");
    ui->food_output->setText("");
    ui->vent_output->setText("");
    ui->clear_fixat->setEnabled(false);
    ui->vent_fixat->setEnabled(false);
    ui->food_fixat->setEnabled(false);
    ui->sohran_v_file->setEnabled(false);
    ui->del_el_from_l->setEnabled(false);
}
void camers::button_save_to_f()
{
    QFile file("bird_cams.txt");
    if (file.open(QIODevice::ReadWrite|QIODevice::Truncate|QIODevice::Text))
    {
        QTextStream steram(&file);
        for (unsigned int i=0; i<v.size(); i++)
        {
            steram<<v[i].get_specie()<<endl;
            steram<<v[i].get_age()<<endl;
            steram<<v[i].get_cam_num()<<endl;
            steram<<v[i].get_vent_status()<<endl;
            steram<<v[i].get_food_status()<<endl;
            steram<<v[i].get_clear_status()<<endl;
        }
        file.close();
    }
}

void camers::button_add_new()
{
    int num_to_add;
    QString text_to_add;
    bool ok1, ok2, ok3;
    birds temp_bird;
    text_to_add = QInputDialog::getText(this, "Ввести", "Вид особи: ", QLineEdit::Normal, "", &ok1);
    if (ok1 && !text_to_add.isEmpty())
    {
        temp_bird.set_species(text_to_add);
        num_to_add=QInputDialog::getInt(this, "Ввести", "Возраст особи: ", 0, 0, 60, 1, &ok2);
        if (ok2)
        {
            temp_bird.set_age(num_to_add);
            num_to_add=QInputDialog::getInt(this, "Ввести", "Номер камеры: ", 1, 1, 122345, 1, &ok3);
            if (ok3)
            {
                temp_bird.set_age(num_to_add);
                v.push_back(temp_bird);
                ui->list_cams->addItem(text_to_add+" ("+QString::number(num_to_add)+")");
            }
        }
    }
}

camers::~camers()
{
    delete ui;
}
