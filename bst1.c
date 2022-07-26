#include<stdio.h>
#include<stdlib.h>
typedef struct tree//definition of structure
{
  int info;
  //char *Name;  
  struct tree *left;
  struct tree *right;
}tree;


int main()
{
  int flag;
  int choice1,item,noc;
  char ch;

  int main_menu(int *choice1);
  int insert(tree **root, int item,int *);
  int transplant(tree **root,tree *ptr1,tree *u,tree *v);
  int inorder_successor(tree *ptr, tree **y,tree **yparent);
  int delete(tree **root,  tree *ptr,tree *ptr1);
  int search(tree *root, int item,int *flag, tree **ptr,tree **ptr1,int *noc);
  int display(tree *root);
  
 
  tree *root,*ptr,*ptr1;	

  root =NULL;
  
  
  while(1)
  {
    //system("clear");
    
    
    main_menu(&choice1);//calling function to display original menu list

    switch(choice1)
    {
       case 1:printf("\nEnter number to be inserted:");
       scanf("%d",&item);
       
       noc=0;
       
       insert(&root,item, &noc);
       
       printf("The number of comparisons required is: %d",noc);
       break;
       case 2:printf("\nEnter number to be deleted:");
       scanf("%d",&item);
       printf("\n%d",root->info);
       noc=0;
       search(root, item, &flag, &ptr, &ptr1 , &noc);
       if(flag==0)
            printf("\nnot found  ");
       else
            delete(&root, ptr,ptr1);
            printf("The number of comparisons required is: %d",noc);
       break;
       case 3:printf("\nEnter number to be searched:");
       scanf("%d",&item);
       noc=0;
       search(root,item,&flag, &ptr,&ptr1, &noc);
        printf("The number of comparisons required is: %d",noc);
       if(flag==1)
            printf("\nfound at node ");
       else
            printf("\n not found ");

       break;
       case 4: //printf("\nTerminating code.....");
       display(root);
      //return(1);
      break;
      
       default: printf("\nInvalid choice!!");
       break;


    }
    getchar();
   
    printf("\nEnter y to continue");
    ch=getchar();
    if((ch!='y')&&(ch!='Y'))
    break;
   }
   return(1);
 }

int main_menu(int *choice1)
{

  printf("\t\tThe main menu of operations are listed below ");//showing menu

  printf("\n1.insert a value.\n2.delete a value.\n3.search a value \n4.display");

  printf("\n\nEnter choice:");
  scanf("%d",&*choice1);//taking choice of user as input
  return(1);
}

int getnode(int item,tree **new)//function to create node and returning node pointer
{
  //tree *p;
  (*new)=(tree*)malloc(sizeof(tree));
  
  (*new)->right=NULL;
  (*new)->left=NULL;

  (*new)->info=item;
 
  return(1);
}


int insert(tree **root, int item,int *noc)
{
  tree *ptr,*ptr1,*new;
  int flag;
  
  
  flag=0;
  getnode(item,&new);
  if(*root==NULL)
  {
     *root=new;
     (*root)->left=NULL;
     (*root)->right=NULL;
  }
  else
  {
     ptr= *root;
     while(( ptr!=NULL)&& (flag==0))
     { 
     
        *noc=*noc+1;
        

        ptr1=ptr;
        if(item<ptr->info)
        { 
       
           ptr=ptr->left;
        }
        else if(ptr->info==item)
        {   
           flag=1;
      	    printf("\nalready present");
           return(1);
        }
    
        else if(item>ptr->info)
       {
      
          ptr=ptr->right;
       }
    }
 
        if(ptr1->info<item)
        {
           ptr1->right=new;
        }

        else
        {
           ptr1->left=new;
        }
   }  
 
return(1);
}

int search(tree *root, int item,int *flag, tree **ptr,tree **ptr1, int *noc)
{
  
 //tree *ptr,*ptr1;
 // int flag;
  
  (*ptr)=root;
  *flag=0;
  
  while(( (*ptr)!=NULL)&& (*flag== 0))
  {

     *noc=*noc+1;

     if(item < (*ptr)->info)
     {
       (*ptr1)=(*ptr);
      (*ptr)=(*ptr)->left;
     }
     else if((*ptr)->info==item)
     {
      *flag=1;
      //printf("\nalready present");
     }
  
     else 
     {
       (*ptr1)=(*ptr);
       (*ptr)=(*ptr)->right;
     }
  }

  
return(1);
}
//-----------------------------------------------------------------------------
int transplant(tree **root,tree *ptr1,tree *ptr,tree *v)
{
    if((ptr->info)==((*root)->info))
    {
       (*root)=v;
    }
    else if(ptr1->left==ptr)
    {
       ptr1->left=v;
    }
    else
    {
       ptr1->right=v;
    }
    return(1);
}
int delete(tree **root, tree *ptr,tree *ptr1)
{
   tree *y, *yparent;
  int flag,item1,type;
  
  int inorder_successor(tree *ptr, tree **y,tree **yparent);
  
  if(ptr->left ==NULL)
  {
     transplant(&(*root),ptr1,ptr,ptr->right);
  }
  else if(ptr->right ==NULL)
  {
     transplant(&(*root),ptr1,ptr,ptr->left);
  }
  else
  {
     yparent=ptr;
     inorder_successor(ptr, &y, &yparent);
     
     if(yparent!= ptr)
     {
         transplant(&(*root), yparent , y ,y->right);
         y->right=ptr->right;
     }
     transplant(&(*root), ptr1, ptr, y);
     y->left=ptr->left;
  }
  return(1);
}
int inorder_successor(tree *ptr, tree **y,tree **yparent)
{
   *y=ptr->right;
   if((*y)!=NULL)
   {
      
      while((*y)->left!=NULL)
      {
         (*yparent)=(*y);
         (*y)=(*y)->left;
      }
   }
   return(1);
}
//-----------------------------------------------------------------------
int display(tree *root)
{
  
  //printf("\n111111");
  if(root!=NULL)
  {
    display(root->left);
    printf(" %d ",root->info);
    display(root->right);
  }
  return(1);
}












