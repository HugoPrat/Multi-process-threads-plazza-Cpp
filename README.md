# :octocat: Multi-process-threads-plazza-Cpp
Simulation of a restaurant with process as kitchen and threads as cooks

[![License](https://img.shields.io/github/license/IamBlueSlime/TalkOpenSource.svg?style=flat-square)](LICENSE.txt)

## Introduction

The goal of this project is to familiarise with the notion of threads and process

### Building

How to build the application

```
make re
```

### Using

```
./plazza 2 5 2000
```

* The first parameter is a multiplier for the cooking time of the pizzas. It is used to examine your programmore easily.

* The second parameter is the number of cooks per kitchen.

* The third parameter is the time in milliseconds, used by the kitchen stock to replace ingredients.



### Pizza ordering

TYPE  SIZE  NUMBER  [; TYPE  SIZE  NUMBER ]
* TYPE = [a..zA..Z]
* SIZE = S|M|L|XL|XXL
* NUMBER  := x[1..9][0..9]

example

```
regina XXL x2; fantasia M x3; margarita S x1
```

## License

This software is licensed under the ISC license (see [LICENSE.txt](LICENSE.txt)).


## Author

* Hugo Prat (<hugo.prat@epitech.eu>)