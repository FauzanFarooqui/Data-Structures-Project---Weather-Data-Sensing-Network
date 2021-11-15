#include<stdio.h>
#include<stdlib.h>
#include "declrns.h"

extern Boolean_type taller_repo;

record *repo_RotateLeft(record *p)
{
    record *temp = p;
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
record *repo_RotateRight(record *p)
{
    record *temp = p;
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

record *repo_RightBalance (record *root, Boolean_type *taller)
{

    record *rs = root->right;
    record * ls; 

    switch (rs->bf)
    {
        case RH:
            root->bf = rs->bf = EH ;
            root = repo_RotateLeft(root);
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
            root ->right = repo_RotateRight(rs) ;
            root = repo_RotateLeft (root) ;
            * taller = FALSE;
            break;
    }
    return root;
}

record *repo_LeftBalance (record *root, Boolean_type *taller)
{

    record *rs ;
    record * ls= root->left; 

    switch (ls->bf)
    {
        case RH:
            root->bf = ls->bf = EH ;
            root = repo_RotateLeft(root);
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
            root ->left = repo_RotateLeft(ls) ;
            root = repo_RotateRight (root) ;
            * taller = FALSE;
            break;
    }
    return root;
}
record *repo_Insert(record *root, record *newnode, Boolean_type *taller) //Insert new node starting at root
{
    if(!root)
    {
        root = newnode;
        root->bf = EH;
        root->left = root->right = NULL;
        *taller = TRUE;
    }
    else
    if (newnode->dt.yr <= root->dt.yr && newnode->dt.mnt <= root->dt.mnt && newnode->dt.day < root->dt.day) //"Key" here is the date
    {
        root->left = repo_Insert(root->left, newnode, taller);
        if ( *taller) 
            switch (root->bf)
            {
                case LH: 
                    root = repo_LeftBalance( root, taller);
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
        root->right = repo_Insert(root->right, newnode, taller);
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
                    root = repo_RightBalance( root, taller) ;
                    break;
            }
    }
    return root;
}

record *repo_GetNode() //get a new node with data for BT
{
    record *p = NULL;    
    p =(record*)malloc(sizeof(record));
    printf("\n ID: "); scanf("%d", &p->ID);
    printf("\n Date: "); p->dt= ip_date(p->dt);
    printf("\n Time: "); p->tm= ip_time(p->tm);
    printf("\n Data: "); scanf("%f", &p->data);
   
    p->left = p->right = NULL;
    return p;
}
record* add_central_repo(record *root, Boolean_type *taller) //makes a BST and returns the root
{
    record *p;
    p = repo_GetNode();
    if(p!= NULL) //if malloc doesn't fail
        root = repo_Insert(root, p, taller);

    return root;
}

void print_record(record* nptr)
{
    printf("\n ID: %d", nptr->ID);
    printf("\n Date: "); op_date(nptr->dt);
    printf("\n Time: "); op_time(nptr->tm);
    printf("\n Data: %f", nptr->data);
}
sensor_node* SnSearch(sensor_node *x, int ID) //Search
{
    sensor_node* p = x;
    while (p && (ID != p->ID))
        if (ID < p->ID)
            p = p->left;
        else
            p = p->right;
    return p;
}
void RepoSearch(record *x, sensor_node* sn_root, date d, char* type) //Search
{
    record* p = x;
    sensor_node* s;
    int fnd = 0;
    while (p && (d.yr != p->dt.yr && d.mnt != p->dt.mnt && d.day != p->dt.day))
    {
        s = SnSearch(sn_root, p->ID);
        if(s->sensor_type==type)
        {
            print_record(p);
            fnd = 1;
        }
        if (d.yr <= p->dt.yr && d.mnt <= p->dt.mnt && d.day < p->dt.day)
            p = p->left;
        else
            p = p->right;
    }
    if(!fnd)
        printf("\nNo such match.");
}
void retrieve_info(record* repo_root, sensor_node* sn_root)
{
    char type[15];
    date d;
    printf("\nEnter sensor type: "); getchar();
    gets(type);
    printf("\nEnter date till you want to retrieve: ");
    d = ip_date(d);
    RepoSearch(repo_root, sn_root, d, type);
    
}