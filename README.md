
# BigInteger

Peform basic operation like addition, subtraction, multiplication, division, modulas on BigInteger



## Deployment

Assuming you have the BigInteger.c and BigInteger.h files in your project directory, and you want to compile your C program using the BigInteger library, you can use the following command :

```bash
  gcc -o app.exe your_source_file.c BigInteger.c
```
and then run the executable using :
```bash
  ./app.exe
```

## Usage/Examples

```c
#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

int main()
{
    char str1[1000],str2[1000];
    scanf("%s",str1);//input any number(positive/negitive)
    scanf("%s",str2);//input any number(positive/negitive)
    struct BigInteger a=initialize(str1);
    struct BigInteger b=initialize(str2);
    printf("Addition\n");
    struct BigInteger c=add(a,b);
    display(c);
    printf("\n");
    printf("Subtraction\n");
    struct BigInteger d=sub(a,b);
    display(d);
    printf("\n");
    printf("Multiplication\n");
    struct BigInteger e=mul(a,b);
    display(e);
    printf("\n");
    printf("Division\n");
    struct BigInteger f=div1(a,b);
    display(f);
    printf("\n");
    printf("Modulus\n");
    struct BigInteger g=mod(a,b);
    display(g);
    return 0;
}
```


## Authors

- [Nikhil Nawani](https://github.com/2004-Nikhil)

