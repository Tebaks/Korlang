# Korlang
A programming language

### Group Members:
- Ahmetcan ÖZCAN
- Kenan ABBAK
- Ege YILDIR



## Table of Contents

<details>
<summary>Click to expand</summary>

- [Korlang](#korlang)
    - [Group Members:](#group-members)
  - [Table of Contents](#table-of-contents)
  - [About](#about)
  - [Install](#install)
  - [Syntax](#syntax)
    - [Variables](#variables)
    - [Assign Operations;](#assign-operations)
    - [Post Increment/Decrement](#post-incrementdecrement)
    - [Logical Operations](#logical-operations)
    - [Loops](#loops)
    - [Functions](#functions)
    - [Objects](#objects)
  - [kor{} Statements](#kor-statements)
  - [Import](#import)
  - [Error Handling](#error-handling)
  - [System Functions](#system-functions)
  - [Standard Libraries](#standard-libraries)
  - [Example Programs](#example-programs)
- [LICENSE](#license)

</details>

## About
Korlang is a memory first dynamic language. It is easy to implement but with extra effort it allows you better memory management. It is easy to learn and easy to read. It has dynamic typing, types are associated with values not variables.

## Install

```bash
# firstly, clone the repository
$ git clone http://github.com/Tebaks/Korlang
# then open directory
$ cd Korlang
# then build source code using:
$ make

```

## Syntax
### Variables
```go
var a = 1; // integers
var b = "korlang"; // strings
var c = 1.5; // floats
var d = true; // booleans
var e = [1,"ahmet",false]; // arrays

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
  "kenan" != "ahmet";
  // true
  "jeff" = "jeff";
  //true
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

Korlang functions are first-class functions. They can be used as a argument of an another function, or a return value

```go
func messenger (message,from){
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
- #### Functions as parameter
  ```go
    func doItNTimes(f,n){
        for var i = 0; i < n ; i++; {
            f();
        }
    }

    doItNTimes(func(n){
        print("selam");
    },5);
   
    /* output:
    * selam
    * selam
    * selam
    * selam
    * selam
    */

  ```

- #### Closuring

   ```go
   func getCounter(){
       var  i = 0;   // variable 'i' can not be accesible 
                    // outside of this block.
       func helper(){
           i++;
           return i;
       }
       return helper;
   }
   
   var counter = getCounter();
   print(counter());
   // output: 1
   print(i);

   ```


### Objects
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
        name : name,
        age : age,
        isOfAge: func(){
            return person.age > 18;
        },
        greet : func (){
            print("Hi there, I'm ",person.name);
        }
    };
    return person;
    }

    var businessMan = newPerson("Jeff Bezos",56);
    var isAgeOf= businessMan.isOfAge();
    if isAgeOf {
        businessMan.greet();
    }
    // Hi there, I'm Jeff Bezos
    ```
## kor{} Statements

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
## Import

Korlang has own module system. 

```go
import "math/rand.kor" // import rand standart library

var randomNumber = randomInt(0,100);
// randomNumber = random integer between 0 and 100
```
- #### Custom modules
    Korlang allows to write abstracted modules.
    
    ```go
    // Define a constructor.
    func NewDog(name){
        var res = {
            name :name,
            makeNoise : func(){
                print("Woof, Woof");
            }
        };
        return res;
    }
    // Extract contructor
    extract NewDog;
    // then contructor function can be used
    // outside of this module.
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
- append : append a value to end of an array.
    ```go
    var myBFs = ["Hannah Montana", "Joe Jonas", "Demi Lovato"];
    // after 12 years
    append(myBFs,"Billie Eilish");
    print(myBFs);
    //  ["Hannah Montana", "Joe Jonas", "Demi Lovato", "Billie Eilish"]
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
- rand : generate a random integer between 0 to 2147483647
    > **WARNING**: math/rand.kor standard library suggested.
    > instead of using this directly.
    ```go
    var a = rand();
    var l = a % 10;
    // l is a int between 0 and 10
    ```

- int : cast string or float to int
    ```go
    var str = "10";
    var ival = int(str);
    for var x = 0; x < ival; x++;{print(x);}
    // writes numbers from  0 to 10.
    ```
- float: cast string or integers to float.
    ```go
    var str = "10";
    var fval = flaot(str);
    for var x = 0; x < ival; x++;{print(x);}
    // writes numbers from  0 to 10.
    ```

##

## Standard Libraries

- ### math/rand.kor
    - **RandInt(start,end)** : generate a random integer between start and end.  
    - **RandFloat(start,end)** : generate a random float between start and end.

- ### math/power.kor
    - **Sqrt(number)** : takes the square root of given number.
    - **Pow(number,power)** : takes the power of given number.

- ### math/round.kor
    - **Floor(number)** : rounds the float number to upper integer.
    - **Ceil(number)** : rounds the float number to lower integer.
    - **Round(number)** : rounds the float number to closest integer.

- ### event/emitter.kor
    - class **EventEmitter**:
        - **on(name,handler)** : listen given event and invokes function when the event emitted.
        - **emit(name)**  : emit an event.


## Example Programs

- Recursively factorial computation.
```bash
make factorial
```
- Calculate n-th fibonacci number with bottom up principles
```bash
make fibonacci
```
- Calculate a number is prime or not.
```bash
make prime
```
- Up and down game example
```bash
make updowngame
```
- List example
```bash
make list
```
- All Examples
```bash
make examples
 ````

# LICENSE

MIT licence
