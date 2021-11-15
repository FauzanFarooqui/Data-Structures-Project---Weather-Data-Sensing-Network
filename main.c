/*
Name: Fauzan Nayeem Farooqui
Program: Weather Data Sensing Network 
Concept illustration: AVL Trees Data Structure
This project was done as part of the "Data Structures and Program Design - 2" course at VNIT, Nagpur, India. 
Date: 18/4/2021
Please refer to the README for the command line compilation command. 
Some explanations and assumptions:
1) There are 4 main placeholders in the database, 2 for each type, Normal sensor type(Wind, Humidity, etc) and AQI type(PM10, CO2, etc.).
   1 stores information about sensor (sensor/AQI data) and 1 stores information FROM these sensors i.e the central repo.

2) Date and time are structure type. Hence, input and output functions for them are so defined.
3) Files:
    declrns.h: Contains all structure and function declarations
    declrns.c: Additional Date-time input/output function definitions.
    sensor.c: Functions related to sensor database. 
    repo.c: Functions related to central repository.
    AQI.c: Functions related to both AQI sensor database and AQI repository.
    main.c: This main file contains only the driver code needed to demonstrate the above.
      
4) Sensor type is a string that stores type of data eg: "Wind speed", "Humidity", "AQI", etc.
5) Sensor station or location is 1 character type eg: 'A', 'B', etc.
*/

#include<stdio.h>
#include<stdlib.h>
#include "declrns.h"

int main()
{
        Boolean_type taller_sensor=TRUE;
        Boolean_type taller_repo=TRUE;
        Boolean_type taller_AQI=TRUE;
        Boolean_type taller_AQI_repo=TRUE;
        Boolean_type dlt_sn_taller=TRUE;

    int choice, ch, h;
    char c;
    sensor_node* sensor_data = NULL;
    AQI_node* AQI_data = NULL;
    record *sensor_repo = NULL, *AQI_repo = NULL;
    float max;
    int max_mnt;
    printf("--- SENSOR NETWORK ---");
    printf("\nProcedure of use: Please enter information first before implementing other functions. AQI structure has seperate records.\nSo, choose Option 1 and Option 2 as many times as the number of nodes you want to store.\nHowever, adding new AQI sensor (Option 1->sub-Option 2) does not affect the program and is just for the sake of completeness.");
    do
    {
        printf("\nChoose an action:\n1 - Enter sensors' info\n2 - Enter central record data\n3 - Search data by sensor type and date\n4 - AQI Search\n5 - Install a sensor in-between\n6 - Remove Idle sensors\n7 - View sensors info within ID range\n8 - Exit program\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: printf("\n1 - Normal\n2 - AQI"); scanf("%d", &ch);
                    switch(ch)
                    {
                        case 1: sensor_data = create_sensor_node(sensor_data, &taller_sensor);
                                break;
                        case 2: AQI_data = create_AQI_node(AQI_data, &taller_AQI);
                                break;
                        default: printf("Wrong choice. Please restart.");
                    }
                    break;
            case 2: printf("\n1 - Normal\n2 - AQI"); scanf("%d", &ch);
                    switch(ch)
                    {
                        case 1: sensor_repo = add_central_repo(sensor_repo, &taller_repo);
                                break;
                        case 2: AQI_repo = add_central_repo(AQI_repo, &taller_AQI_repo);
                                break;
                        default: printf("Wrong choice. Please restart.");
                    }
                    break;
            case 3: retrieve_info(sensor_repo, sensor_data);
                    break;
                    
            case 4: printf("\n1 - Highest AQI ever recorded\n2 - Hazardous health status days");
                    scanf("%d", &ch);
                    switch(ch)
                    {
                        case 1: max_AQI(AQI_repo, &max, &max_mnt);
                                printf("\nHighest AQI %f is recorded in month %d.", max, max_mnt);
                                break;
            
                        case 2: h = hazardous_dates(AQI_repo);
                                if(!h)
                                        printf("\nNo days were hazardous.");
                                break;
                        default: printf("\nWrong choice. Please restart.");

                    }
                    break;
            case 5: getchar();
                    sensor_data = Install_new_Sensor(sensor_data, &taller_sensor);
                    break;
            case 6: sensor_data = idle_delete(sensor_data, sensor_repo, &dlt_sn_taller);
                    break;
            case 7: sensors_in_between(sensor_data); break;
            case 8: c='n'; break;
            default: printf("\nWrong choice. Please restart.");

        }
    if(c!='n')
    {
        printf("\nDo you want to do any more operations? (y/n): ");
        getchar();
        scanf("%c", &c);
    }
    }while(c=='y');

    printf("\nThank you.");


    return 0;
}