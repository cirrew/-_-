#ifndef CAMERS_H
#define CAMERS_H
#include <fstream>
#include <QFile>
#include <QMainWindow>
#include <QListWidget>
#include <QTextStream>
#include <vector>
QT_BEGIN_NAMESPACE
namespace Ui { class camers; }
QT_END_NAMESPACE

class birds
{
private:
    QString specie;
    int age;
    int cam_num;
    int vent_status;
    int food;
    int clear_status;
public:
    birds()
    {
        specie="";
        cam_num=0;
        vent_status=0;
        age=0;
        food=0;
        clear_status=0;
    }
    birds(QString s, int a, int c, int v, int f, int cl)
    {
        specie=s;
        cam_num=c;
        vent_status=v;
        age=a;
        food=f;
        clear_status=cl;
    }
    QString get_specie()
    {
        return specie;
    }
    int get_age()
    {
        return age;
    }
    int get_cam_num()
    {
        return cam_num;
    }
    int get_vent_status()
    {
        return vent_status;
    }
    int get_food_status()
    {
        return food;
    }
    int get_clear_status()
    {
        return clear_status;
    }
    void set_age(int ag)
    {
        age=ag;
    }
    void set_species(QString spec)
    {
        specie=spec;
    }
    void set_cam_num(int a)
    {
        cam_num=a;
    }
    ~birds(){}
    void fix_vent()
    {
        vent_status=100;
    }
    void give_food()
    {
        food=100;
    }
    void clean_camera()
    {
        clear_status=100;
    }
};

class camers : public QMainWindow
{
    Q_OBJECT

public:
    camers(QWidget *parent = nullptr);
    ~camers();
private:
    Ui::camers *ui;
public slots:
    void button_clear();
    void button_food();
    void button_vent();
    void button_current_list_item();
    void button_deletion();
    void button_save_to_f();
    void button_add_new();
};
#endif // CAMERS_H
