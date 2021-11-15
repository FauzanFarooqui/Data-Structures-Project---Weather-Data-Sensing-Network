#include<stdio.h>
#include<stdlib.h>
#include "declrns.h"

extern Boolean_type taller_AQI;
extern Boolean_type taller_AQI_repo;

AQI_node *AQI_RotateLeft(AQI_node *p)
{
    AQI_node *temp = p;
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
AQI_node *AQI_RotateRight(AQI_node *p)
{
    AQI_node *temp = p;
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

AQI_node *AQI_RightBalance (AQI_node *root, Boolean_type *taller)
{

    AQI_node *rs = root->right;
    AQI_node * ls; 

    switch (rs->bf)
    {
        case RH:
            root->bf = rs->bf = EH ;
            root = AQI_RotateLeft(root);
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
            root ->right = AQI_RotateRight(rs) ;
            root = AQI_RotateLeft (root) ;
            * taller = FALSE;
            break;
    }
    return root;
}

AQI_node *AQI_LeftBalance (AQI_node *root, Boolean_type *taller)
{

    AQI_node *rs ;
    AQI_node * ls= root->left; 

    switch (ls->bf)
    {
        case RH:
            root->bf = ls->bf = EH ;
            root = AQI_RotateLeft(root);
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
            root ->left = AQI_RotateLeft(ls) ;
            root = AQI_RotateRight (root) ;
            * taller = FALSE;
            break;
    }
    return root;
}

AQI_node *AQI_Insert(AQI_node *root, AQI_node *newnode, Boolean_type *taller) //Insert new node starting at root
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
        root->left = AQI_Insert (root->left, newnode, taller);
        if ( *taller) 
            switch (root->bf)
            {
                case LH: 
                    root = AQI_LeftBalance ( root, taller);
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
        root->right = AQI_Insert (root->right, newnode, taller);
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
                    root = AQI_RightBalance ( root, taller) ;
                    break;
            }
    }
    return root;
}

AQI_node *AQI_GetNode() //get a new node with data for BT
{
    AQI_node *nptr = NULL;    
    nptr =(AQI_node*)malloc(sizeof(AQI_node));
    printf("\n ID: "); scanf("%d", &nptr->ID); 
    printf("\n Station/Location: "); getchar(); scanf("%c", &nptr->sensor_station);
    printf("Enter time interval for 6 quantities: PM10, PM 2.5, nitrogen dioxide, sulphur dioxide, carbon monoxide, ground level ozone");
    for(int j=0; j<6; j++)
    {
        printf("\n Time Interval %d: ", j+1);
        nptr->interval[j]=ip_time(nptr->interval[j]);
    }
   
    nptr->left = nptr->right = NULL;
    return nptr;
}

AQI_node* create_AQI_node(AQI_node *root, Boolean_type *taller) //makes a BST and returns the root
{
    AQI_node *p;
    p = AQI_GetNode();
    if(p!= NULL) //if malloc doesn't fail
        root = AQI_Insert(root, p, taller);

    return root;
}

void max_AQI(record *root, float* max, int* max_mnt) //Traversal
{
    if(root)
    {
        max_AQI(root->left, max, max_mnt);
        if(root->data > *max)
        {
            *max = root->data;
            *max_mnt = root->dt.mnt;
        }
        max_AQI(root->right, max, max_mnt);
    }
    
}

int hazardous_dates(record *root) //Traversal
{
    int h=0;
    if(root)
    {
        hazardous_dates(root->left);
        if(root->data>=501)
        {
            op_date(root->dt);
            h = 1;
        }
        hazardous_dates(root->right);
    }
    return h;
}