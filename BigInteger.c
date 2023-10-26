#include<stdio.h>
#include<stdlib.h>
#include<string.h>  
#include"BigInteger.h"


void AtEnd(struct node**head,struct node**tail,int data)
{
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->data=data;
    temp->next=NULL;
    temp->prev=NULL;
    if(*head==NULL)
    {
        *head=temp;
        *tail=temp;
    }
    else
    {
        (*tail)->next=temp;
        temp->prev=*tail;
        *tail=temp;
    }
}

void AtBegining(struct node**head,struct node**tail,int data)
{
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->data=data;
    temp->next=NULL;
    temp->prev=NULL;
    if(*head==NULL)
    {
        *head=temp;
        *tail=temp;
    }
    else
    {
        (*head)->prev=temp;
        temp->next=*head;
        *head=temp;
    }
}

struct BigInteger initialize(char *str)
{
    struct BigInteger big;
    big.L=NULL;
    big.R=NULL;
    big.length=0;
    big.sign=1;
    int i=0;
    if(str[0]=='-')
    {
        big.sign=-1;
        i++;
    }
    for(;str[i]!='\0';i++)
    {
        AtEnd(&big.L,&big.R,str[i]-'0');
        big.length++;
    }
    return big;
}

int Larger(struct BigInteger a, struct BigInteger b) 
{
    if(a.length>b.length)
        return 1;
    else if(a.length<b.length)
        return 0;
    else
    {
        struct node*itr1=a.L;
        struct node*itr2=b.L;
        while(itr1)
        {
            if(itr1->data>itr2->data)
                return 1;
            else if(itr1->data<itr2->data)
                return 0;
            itr1=itr1->next;
            itr2=itr2->next;
        }
        return 1;
    }
}

struct BigInteger add(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger c;
    c.L=NULL;
    c.R=NULL;
    c.length=0;
    c.sign=1;
    if(a.sign==-1&&b.sign==-1)
        c.sign=-1;
    else if(a.sign==-1&&b.sign==1)
    {
        a.sign=1;
        c=sub(b,a);
        return c;
    }
    else if(a.sign==1&&b.sign==-1)
    {
        b.sign=1;
        c=sub(a,b);
        return c;
    }
    else if(a.sign==1&&b.sign==1)
        c.sign=1;
    
    int carry=0;
    struct node*itr1=a.R;
    struct node*itr2=b.R;
    while(itr1||itr2)
    {
        int sum=carry;
        if(itr1)
        {
            sum+=itr1->data;
            itr1=itr1->prev;
        }
        if(itr2)
        {
            sum+=itr2->data;
            itr2=itr2->prev;
        }
        carry=sum/10;
        sum=sum%10;
        AtBegining(&c.L,&c.R,sum);
        c.length++;
    }
    if(carry)
    {
        AtBegining(&c.L,&c.R,carry);
        c.length++;
    }
    return c;
}

struct BigInteger sub(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger c;
    c.L=NULL;
    c.R=NULL;
    c.length=0;
    c.sign=1;
    if(a.sign==-1&&b.sign==-1)
    {
        if(Larger(a,b)==0)
        {
            c=sub(b,a);
            c.sign=1;
            return c;
        }
        else
            c.sign=-1;
    }
    else if(a.sign==-1&&b.sign==1)
    {
        b.sign=-1;
        c=add(a,b);
        return c;
    }
    else if(a.sign==1&&b.sign==-1)
    {
        b.sign=1;
        c=add(a,b);
        return c;
    }
    else if(a.sign==1&&b.sign==1)
    {
        if(Larger(a,b)==0)
        {
            c=sub(b,a);
            c.sign=-1;
            return c;
        }
        else
            c.sign=1;
    }
    int borrow=0;
    struct node*itr1=a.R;
    struct node*itr2=b.R;

    while(itr1||itr2)
    {
        int diff=borrow;
        if(itr1)
        {
            diff+=itr1->data;
            itr1=itr1->prev;
        }
        if(itr2)
        {
            diff-=itr2->data;
            itr2=itr2->prev;
        }
        if(diff<0)
        {
            diff+=10;
            borrow=-1;
        }
        else
            borrow=0;
        AtBegining(&c.L,&c.R,diff);
        c.length++;
    }
    while((c.L->data==0)&&(c.length>1))
    {
        c.L=c.L->next;
        c.length--;
    }
    return c;
}

struct BigInteger mul(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger c;
    c.L=NULL;
    c.R=NULL;
    c.length=0;
    c.sign=1;
    if(a.sign==-1&&b.sign==-1)
        c.sign=1;
    else if(a.sign==-1||b.sign==-1)
    {
        c.sign=-1;
    }
    else if(a.sign==1&&b.sign==1)
        c.sign=1;
    a.sign=1;
    b.sign=1;

    struct node*itr1=a.R;
    struct node*itr2=b.R;
    int i=0;
    while(itr2)
    {
        struct BigInteger temp;
        temp.L=NULL;
        temp.R=NULL;
        temp.length=0;
        temp.sign=1;
        int carry=0;
        for(int j=0;j<i;j++)
        {
            AtEnd(&temp.L,&temp.R,0);
            temp.length++;
        }
        while(itr1)
        {
            int prod=itr2->data*itr1->data+carry;
            carry=prod/10;
            prod=prod%10;
            AtBegining(&temp.L,&temp.R,prod);
            temp.length++;
            itr1=itr1->prev;
        }
        if(carry)
        {
            AtBegining(&temp.L,&temp.R,carry);
            temp.length++;
        }
        c=add(c,temp);
        itr2=itr2->prev;
        itr1=a.R;
        i++;
    }
    return c;
}

struct BigInteger div1(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger temp=initialize("");
    temp.sign=1;
    if(a.sign==-1&&b.sign==-1)
        temp.sign=1;
    else if(a.sign==-1||b.sign==-1)
    {
        temp.sign=-1;
    }
    else if(a.sign==1&&b.sign==1)
        temp.sign=1;
    a.sign=1;
    b.sign=1;
    if(Larger(a,b)==0)
    {
        AtBegining(&temp.L,&temp.R,0);
        temp.length++;
        temp.sign=1;
        return temp;
    }
    // use a - b + 1
    // while(((a.length))>(mul(b,temp).length))
    // {
    //     AtBegining(&temp.L,&temp.R,0);
    //     temp.length++;
    //     printf("%d\n",temp.length);
    //     printf("%d\n",a.length);
    //     printf("%d\n",b.length);
    // }
    int i=0;
    while(i<=(a.length-b.length))
    {
        AtBegining(&temp.L,&temp.R,0);
        temp.length++;
        i++;
    }
    struct node *itr=temp.L;
    while(itr)
    {
        itr->data=7;
        if(Larger(a,mul(b,temp))==0)
        {
            itr->data=4;
        }
        if(Larger(a,mul(b,temp))==0)
        {
            itr->data=1;
        }
        while(Larger(a,mul(b,temp)))
        {
            itr->data++;
        }
        itr->data--;
        itr=itr->next;
    }
    while((temp.L->data==0)&&(temp.length>1))
    {
        temp.L=temp.L->next;
        temp.length--;
    }
    return temp;
}

struct BigInteger mod(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger rem=initialize("");
    if(a.sign==-1)
        rem.sign=-1;
    else
        rem.sign=1;
    a.sign=1;
    b.sign=1;
    int sign=rem.sign;
    struct BigInteger qui=div1(a,b);
    struct BigInteger pro=mul(qui,b);
    rem=sub(a,pro);
    rem.sign=sign;
    if(rem.length==1&&rem.L->data==0)
        rem.sign=1;
    return rem;
}

void display(struct BigInteger big)
{
    if(big.sign==-1)
        printf("-");
    struct node*itr=big.L;
    while(itr!=NULL)
    {
        printf("%d",itr->data);
        itr=itr->next;
    }
    printf("\n");
}
