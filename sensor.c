#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declrns.h"

extern Boolean_type taller_sensor;

sensor_node *RotateLeft(sensor_node *p)
{
    sensor_node *temp = p;
    if (p == NULL)
        printf("Cannot rotate an empty tree");
    else if (p->right == NULL)
        printf("Cannot rotate left") ;
    else
    {
        temp = p->right;
        p->right = temp->left;
        temp->left = p;
    }

    return temp;
}
sensor_node *RotateRight(sensor_node *p)
{
    sensor_node *temp = p;
    if (p == NULL)
        printf("Cannot rotate an empty tree");
    else if (p->left == NULL)
        printf("Cannot rotate right") ;
    else
    {
        temp = p->left;
        p->left = temp->right;
        temp->right = p;
    }
     
    return temp;
}

sensor_node *RightBalance (sensor_node *root, Boolean_type *taller)
{

    sensor_node *rs = root->right;
    sensor_node * ls; 

    switch (rs->bf)
    {
        case RH:
            root->bf = rs->bf = EH ;
            root = RotateLeft(root);
            * taller = FALSE;
            break;

        case EH:
            printf( "Tree is already balanced" );
            break;

        case LH: 
            ls = rs ->left;
            switch ( ls->bf)
            {
                case RH:
                    root->bf = LH ;
                    rs->bf = EH;
                    break;
                case EH:
                    root ->bf = rs->bf = EH;
                    break;
                case LH:
                    root->bf = EH;
                    rs->bf = RH;
                    break;
            }
            ls->bf = EH;
            root ->right = RotateRight(rs) ;
            root = RotateLeft (root) ;
            * taller = FALSE;
            break;
    }
    return root;
}

sensor_node *LeftBalance (sensor_node *root, Boolean_type *taller)
{

    sensor_node *rs ;
    sensor_node * ls= root->left; 

    switch (ls->bf)
    {
        case RH:
            root->bf = ls->bf = EH ;
            root = RotateLeft(root);
            * taller = FALSE;
            break;

        case EH:
            printf( "Tree is already balanced" );
            break;

        case LH: 
            rs = ls ->left;
            switch ( rs->bf)
            {
                case RH:
                    root->bf = LH ;
                    ls->bf = EH;
                    break;
                case EH:
                    root ->bf = ls->bf = EH;
                    break;
                case LH:
                    root->bf = EH;
                    ls->bf = RH;
                    break;
            }
            rs->bf = EH;
            root ->left = RotateLeft(ls) ;
            root = RotateRight (root) ;
            * taller = FALSE;
            break;
    }
    return root;
}

sensor_node *Insert(sensor_node *root, sensor_node *newnode, Boolean_type *taller) //Insert new node starting at root
{
    if(!root)
    {
        root = newnode;
        root->bf = EH;
        root->left = root->right = NULL;
        *taller = TRUE;
    }
    else if(newnode->ID == root->ID)
        printf("Duplicate ID in binary tree");
    else if (newnode->ID < root->ID) //"Key" is ID, assumed station is also input so
    {
        root->left = Insert (root->left, newnode, taller);
        if ( *taller) 
            switch (root->bf)
            {
                case LH: 
                    root = LeftBalance ( root, taller);
                    break;
                case EH:
                    root->bf = LH;
                    break;
                case RH:
                    root->bf = EH; 
                    * taller = FALSE;
                    break;
            }
    
    }else
    {
        root->right = Insert (root->right, newnode, taller);
        if ( *taller)
            switch (root->bf)
            {
                case LH:
                    root->bf = EH; 
                    *taller = FALSE;
                    break;
                case EH:
                    root->bf = RH;
                    break;
                case RH:
                    root = RightBalance ( root, taller) ;
                    break;
            }
    }
    return root;
}

sensor_node *GetNode() //get a new node with data for BT
{
    sensor_node *p = NULL;    
    p =(sensor_node*)malloc(sizeof(sensor_node));
    printf("\n ID (Any natural number): "); scanf("%d", &p->ID); getchar();
    printf("\n Type (temperature, sound, humidity, wind, etc.): "); gets(p->sensor_type);
    printf("\n Station/Location: (Single character: A, B, etc.) "); scanf("%c", &p->sensor_station);
    printf("\n Time Interval: ");
    p->interval=ip_time(p->interval);
   
    p->left = p->right = NULL;
    return p;
}

sensor_node* create_sensor_node(sensor_node *root, Boolean_type *taller) //makes a BST and returns the root
{
    sensor_node *p;
    p = GetNode();
    if(p!= NULL) //if malloc doesn't fail
        root = Insert(root, p, taller);

    return root;
}

int TreeSearch_stn(sensor_node *x, char stn, char* type) //Search - assume that station, like ID is stored in order.
{
    sensor_node* p = x;
    while (p && (stn != p->sensor_station)) //finds first record of req station
        if (stn < p->sensor_station)
            p = p->left;
        else
            p = p->right;
    int fnd =0;
    while(!fnd && p!=NULL && stn==p->sensor_station)
        if(p->sensor_type==type)
            fnd = 1;
        else
            p=p->right; //same stations can only be to the right
    if(!fnd)
        printf("Sensor type %s isn't at sensor station %c.", type, stn);
        
    return fnd;
}
sensor_node* Install_new_Sensor(sensor_node *root, Boolean_type *taller) //makes a BST and returns the root
{
    sensor_node *p;
    p = GetNode();
    
    if(p!= NULL) //if malloc doesn't fail
        if(!TreeSearch_stn(p, p->sensor_station, p->sensor_type))    
        {
            root = Insert(root, p, taller);
            printf("New sensor installed.");
        }
        else
            printf("The station already has this type.");
    else
        printf("All stations are in full capacity.");

    return root;
}
void print_snsr(sensor_node* p)
{
    printf("\n\nSensor ID no. %d info: ", p->ID);
    printf("\n Type : %s", p->sensor_type);
    printf("\n Station/Location: %c", p->sensor_station);
    printf("\n Time Interval: ");
    op_time(p->interval);
}
void Inorder(sensor_node *root, int l_ID, int u_ID) //Traversal
{
    if (root)
    {
        Inorder ( root->left, l_ID, u_ID) ;
        if(root->ID>=l_ID && root->ID<=u_ID)
            print_snsr(root);
        Inorder (root->right, l_ID, u_ID);
    }
    
}
void sensors_in_between(sensor_node* root)
{
    printf("\nEnter lower limit ID: ");
    int l_ID, u_ID;
    scanf("%d", &l_ID);
    printf("\nEnter upper limit ID: ");
    scanf("%d", &u_ID);
    Inorder(root, l_ID, u_ID);

}

int repo_Inorder(record* repo_root, int ID, int curr_mnt) //Traversal
{
    int fnd=0;
    if(repo_root)
    {
        repo_Inorder (repo_root->left, ID, curr_mnt);
        if(repo_root->ID == ID)
            if(repo_root->dt.mnt< curr_mnt-2)
                fnd=1;
            else
                fnd = 0;
        repo_Inorder (repo_root->right, ID, curr_mnt);
    }
    return fnd;
}

void Delete(sensor_node **p, sensor_node *root, Boolean_type *taller) //call xBalance when x side is taller. 
{
    sensor_node * q; 
    if ( *p == NULL)
        printf("Cannot delete empty node" );
    else if ((*p)->right == NULL)
    {
        q = *p;
        *p = (*p)->left; 
        free(q);
        *taller = TRUE;
        root->bf = RH;
        if ( *taller)
            switch (root->bf)
            {
                case LH:
                    root->bf = EH; 
                    *taller = FALSE;
                    break;
                case EH:
                    root->bf = RH;
                    break;
                case RH:
                    root = RightBalance ( root, taller) ;
                    break;
            }

    }
    else if ((*p)->left == NULL)
    {
        q = *p;
        *p = ( *p) ->right; 
        free(q);
        *taller = TRUE;
        root->bf = LH;
        if ( *taller) 
            switch (root->bf)
            {
                case LH: 
                    root = LeftBalance ( root, taller);
                    break;
                case EH:
                    root->bf = LH;
                    break;
                case RH:
                    root->bf = EH; 
                    * taller = FALSE;
                    break;
            }
    }
    else
    {
        for (q = (*p)->right; q->left; q = q->left)
            q->left = (*p) ->left; 
        q = *p;
        *p = (*p) ->right;
        free(q);
        *taller=TRUE;
        root = LeftBalance(root, taller);
        root = RightBalance(root, taller);
    }
    
}

int sn_Inorder(sensor_node* sn_root, sensor_node* sn_node, record* repo_root, int curr_mnt, Boolean_type* taller) //Traversal
{
    int dlt=0;
    if(sn_node)
    {
        sn_Inorder(sn_root, sn_node->left, repo_root, curr_mnt, taller) ;
        if(repo_Inorder(repo_root, sn_node->ID, curr_mnt)==1)
        {
            printf("\nDeleting sensor of ID %d ", sn_node->ID);
            Delete(&sn_node, sn_root, taller);
            dlt=1;
        }
        sn_Inorder(sn_root, sn_node->right, repo_root, curr_mnt, taller);
    }
    return dlt;
}
sensor_node* idle_delete(sensor_node* sn_root, record* repo_root, Boolean_type* taller)
{
    int curr_mnt;
    printf("\nEnter current month (no.): ");
    scanf("%d", &curr_mnt);
    int dlt = sn_Inorder(sn_root, sn_root, repo_root, curr_mnt, taller);
    if(!dlt)
        printf("\nNo sensor is idle.");
    return sn_root;
}

