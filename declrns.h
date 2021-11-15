#ifndef DECLRNS_H_INCLUDED
#define DECLRNS_H_INCLUDED

//declrns.h: Contains all structure declarations and date-time input-output functions.

typedef enum balancefactor_tag { LH, EH, RH } BalanceFactor_type;
typedef enum boolean_tag {FALSE, TRUE } Boolean_type;

typedef struct date
{
    int day, mnt, yr;
}date;
typedef struct time
{
    int hrs, mins;
}time;
typedef struct sensor
{
    int ID; //sensor_ID
    char sensor_type[15];
    char sensor_station;
    time interval;

    BalanceFactor_type bf;
    struct sensor *left;
    struct sensor *right;
}sensor_node;

typedef struct central_repo
{
    int ID; //sensor ID
    date dt;
    time tm;
    float data; //Any data like wind speed, humidity, Final AQI, etc.
    BalanceFactor_type bf;
    struct central_repo *left;
    struct central_repo *right;
}record;

typedef struct AQI_sensor //previous structure adapted for AQI - has an array for interval as AQI sensor type records multiple quantities, no need of sensor_type as it is "AQI" implied
{
    int ID;
    char sensor_station;
    struct time interval[6]; //6 quantities: PM10, PM 2.5, nitrogen dioxide, sulphur dioxide, carbon monoxide, ground level ozone
   
    BalanceFactor_type bf;
    struct AQI_sensor *left;
    struct AQI_sensor *right;
}AQI_node;

//Additional date-time functions:
time ip_time(time t);
date ip_date(date d);
void op_time(time t);
void op_date(date d);

//sensor.h: Functions related to sensor database. Contains answers to Qn 1(Sensor part), Qn2, Qn3 and Qn5.

sensor_node *RotateLeft(sensor_node *p);
sensor_node *RotateRight(sensor_node *p);

sensor_node *RightBalance (sensor_node *root, Boolean_type *taller);

sensor_node *LeftBalance (sensor_node *root, Boolean_type *taller);

sensor_node *Insert(sensor_node *root, sensor_node *newnode, Boolean_type *taller); //Insert new node starting at root

sensor_node *GetNode(); //get a new node with data for BT

sensor_node* create_sensor_node(sensor_node *root, Boolean_type *taller); //makes a BST and returns the root

int TreeSearch_stn(sensor_node *x, char stn, char* type); //Search - assume that station, like ID is stored in order.

sensor_node* Install_new_Sensor(sensor_node *root, Boolean_type *taller); //makes a BST and returns the root

void print_snsr(sensor_node* p);
void Inorder(sensor_node *root, int l_ID, int u_ID); //Traversal

void sensors_in_between(sensor_node* root);

int repo_Inorder(record* repo_root, int ID, int curr_mnt); //Traversal

void Delete(sensor_node **p, sensor_node *root, Boolean_type *taller); //call xBalance when x side is taller. 

int sn_Inorder(sensor_node* sn_root, sensor_node* sn_node, record* repo_root, int curr_mnt, Boolean_type* taller); //Traversal

sensor_node* idle_delete(sensor_node* sn_root, record* repo_root, Boolean_type* taller);


//repo.h: Functions related to central repository. Contains answers to Qn 1(Repository part) and Qn4.

record *repo_RotateLeft(record *p);
record *repo_RotateRight(record *p);

record *repo_RightBalance (record *root, Boolean_type *taller);

record *repo_LeftBalance (record *root, Boolean_type *taller);

record *repo_Insert(record *root, record *newnode, Boolean_type *taller); //Insert new node starting at root

record *repo_GetNode(); //get a new node with data for BT

record* add_central_repo(record *root, Boolean_type *taller); //makes a BST and returns the root

void print_record(record* nptr);
sensor_node* SnSearch(sensor_node *x, int ID); //Search

void RepoSearch(record *x, sensor_node* sn_root, date d, char* type); //Search

void retrieve_info(record* repo_root, sensor_node* sn_root);

//AQI.h: Functions related to both AQI sensor database and AQI repository. Contains answers to Qn 6.

AQI_node *AQI_RotateLeft(AQI_node *p);
AQI_node *AQI_RotateRight(AQI_node *p);

AQI_node *AQI_RightBalance (AQI_node *root, Boolean_type *taller);

AQI_node *AQI_LeftBalance (AQI_node *root, Boolean_type *taller);

AQI_node *AQI_Insert(AQI_node *root, AQI_node *newnode, Boolean_type *taller); //Insert new node starting at root

AQI_node *AQI_GetNode(); //get a new node with data for BT

AQI_node* create_AQI_node(AQI_node *root, Boolean_type *taller); //makes a BST and returns the root

void max_AQI(record *root, float* max, int* max_mnt); //Traversal

int hazardous_dates(record *root); //Traversal

#endif // DECLRNS_H_INCLUDED