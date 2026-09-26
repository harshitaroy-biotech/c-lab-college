//String palndrome
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char string1[20];
    int i, length;
    int flag = 0;

    cout << "Enter a string: "; cin >> string1;

    length = strlen(string1);

    for (i=0; i < length ;i++) {
        if (string1[i] != string1[length-i-1]) {
            flag = 1;
            break;
        }
    }

    if (flag) {
        cout << string1 << " is not a palindrome" << endl;
    }
    else {
        cout << string1 << " is a palindrome" << endl;
    }
    return 0;
}
```[cite: 1]

---

### 2. Number Palindrome Program
```cpp
//Palindrome of number:
#include <iostream>
using namespace std;
int main()
{
    int n,r,sum=0,temp;
    cout<<"Enter the Number=";
    cin>>n;
    temp=n;
    while (n>0)
    {
        r=n%10;
        sum=(sum*10)+r;
        n=n/10;
    }
    if (temp==sum)
    cout<<"Number is Palindrome.";
    else
    cout<<"Number is not Palindrome.";
    return 0;
}
```[cite: 2]