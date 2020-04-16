# Korlang
A programming language

Group Members: 
Ege Yıldır,
Ahmetcan Özcan,
Kenan Abbak

Korlang is a memory first dynamic language. It is easy to implement but with extra effort it allows you better memory management. It is easy to learn and easy to read. It has dynamic typing, types are associated with values not variables.


## Syntax
### Variables
```go
var a = 1;
var b = "korlang";
var c = true;
var b = [1,"ahmet",false];
```

### Object
```go
var person = {
    name : "Kenan",
    age : 22,
    isOfAge: func(){
        return person.age > 18;
    }
};

print(person.name, person.age, person.isOfAge());
// kenan 22 true
```
-   #### Constructors
    ```go
    func newPerson(name,age){
        var person = {
            name : "Kenan",
            age : 22,
            isOfAge: func(){
                return person.age > 18;
            }
        };
        return person;
    }

    var businessMan = newPerson("Jeff Bezos",56);
    print(businessMan.age);
    // 56
    ```
### Assign Operations;
```go
var a = 1;
// a = 1
a += 1;
// a = a + 1
a -= 1;
// a = a -1
a *= 2;
// a = a * 2
a /= 2;
// a = a / 2
a %= 2;
// a = a % 2
```

### Post Increment/Decrement
```go
var i = 0;
print("i =",i++);
// i = 0
print("i =",i);
// i = 1

var x = 1;
print("x =",x--);
// x = 1
print("x =",x);
// x = 0

```

### Logical Operations
- #### Primitive Operations
  ```go
  1 < 2;
  // true
  1 > 2;
  // false
  1 <= 2;
  1 >= 2;
  1 == 2;
  1 != 2;
  true && true;
  // true
  true || false;
    ```
- #### If Else Statements
  ```go
  if 1 < 2 {
      print(1,"less than",2);
  }

  if 1 > 2 {
      print(1,"greater than",2);
  }else {
      print(1,"less than",2);
  }
    ```
### Loops
 ```go

for{
    print("infinite loop");
}
for code == true{
    print("korlang is the best");
}
for var a = 0; a < 10; a++;{
    print(a);
}
 ```
- #### Breaking loop
    ```go
    var i = 0;
    for {
        i++;
        break; // Breaks the infinite loop
    }
    print("i =",i);
    // i = 1
    ```
### Functions
```go
func messanger (message,from){
    print("you got message: " , message ," from: " , from );
}

func sum(x,y) {
    return x+y;
}

messanger("hi","korlang");
/*
you got message: hi
from: korlang
*/
sum(1+2);
// 3
```

## kor{} Statement

It has "kor{}" statement lets you conserve variables in curly brackets.

```go
kor{
var x = 5;
var y = 10;

var z = x+y;
extract z;
}

print(z); // result 15

print(x); // Variable not found.
print(y); // Variable not found.
 ```

 "kor" statement can be used for deleting external scope objects

 ```go
 var externalVar = "Hello";
 kor externalVar // can be used inline syntax

 var anotherExternalVar = "Hi, again";
 kor {
     anotherExternalVar;
     var internalVar = "Hi, from kor";
     extract internalVar;
 }

 print(externalVar); // Variable Not Found!!
 print(anotherExternalVar); // Variable Not Found!!
 print(internalVar); // Result: Hi, from kor
 ```
 ## Error Handling
 ```go
var a = 0;
try{
    b = a;   // error occurs because b wasn't declared. 
             // Program will continue with catch block.
    a += 10; // This block wont be executed.
}catch{
    a += 20;
}
print("a equals : ",a);
// a equals : 20

 ```

 ## System Functions

- print : prints message to stdout with newline.
    ```go
    print(4,"THE", "CODING");
    // 4 THE CODING
    ```

- input : takes input from user through stdin.
    ```go
    var name = input("What is your name : ");
    print("Your name is : ",name);
    ```
- array : creates an array with given size.
     ```go
    var myArray = array(5);
    print(myArray);
    // [ 0 0 0 0 0 ]
    ```

- len : return length of an array or a string.
  ```go
    var myArray = [1, "ahmet", true];
    print(len(myArray));
    // 3
    ```
- panic : occurs an error.
   ```go
    try{
        panic("panic");
    }catch{
        print("panic occurs : ", err);
    }
    ```
## Import
```go
import "math/rand.kor"

var randomNumber = randomInt(0,100);
// randomNumber = random integer between 0 and 100
```


## Example Programs

- Factorial
```bash
make factorial
```
- Fibonacci
```bash
make fibonacci
```
- Prime
```bash
make prime
```
- All Examples
```bash
make examples
 ````
