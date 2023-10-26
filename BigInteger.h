
#ifndef flag1
#define flag1 1
struct node
{
    int data;
    struct node*next,*prev;
};
struct BigInteger
{
    struct node*L;
    struct node*R;
    int length;
    int sign;
};
struct BigInteger initialize(char *str);
struct BigInteger add(struct BigInteger,struct BigInteger);
struct BigInteger sub(struct BigInteger,struct BigInteger);
struct BigInteger mul(struct BigInteger,struct BigInteger);
struct BigInteger div1(struct BigInteger,struct BigInteger);
struct BigInteger mod(struct BigInteger,struct BigInteger);
int Larger(struct BigInteger,struct BigInteger);
void display(struct BigInteger);
void AtEnd(struct node**,struct node**,int);
void AtBegining(struct node**,struct node**,int);
int Larger(struct BigInteger,struct BigInteger);
#endif