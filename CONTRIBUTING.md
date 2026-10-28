# Contributing Guidelines
All contributions are welcome!

## Prerequisites
Writing or reviewing source code from scoutdir requires basic knowledge of modern C++ and libcurl. Also make sure that you have a GitHub account.

## Add your changes
1. Fork the repository.
2. Create a new branch. The branch name must describe your feature. For example: `optimize-multithreading`.
3. Add and commit your changes on this branch, then push it to your fork.
4. Submit a detailed pull request.

## Rules
1. Do not edit the `master` branch.
2. Be concise and polite in your messages and comments.
3. Do not spam the maintainers. They wont even review your changes at all if you do so.
4. Respect the coding style:
* Function names case: snake_case
```cpp
void processError(); // bad
void process_error(); // good
```
* Local variable names case: snake_case
```cpp
int myVariable = 0; // bad
int my_variable = 0; // good
```
* Public non-function members: snake_case
```cpp
struct Position {
    int xPos; // bad
    int x_pos; // good
};
```
* Private non-function members: snake_case with a `_` suffix
```cpp
struct Position {
private:
    int x; // bad
    int x_; // good
};
```
* Header guard constants: UPPER_SNAKE_CASE with a `_H_` suffix
```cpp
// bad
#ifndef MY_HEADER
#define MY_HEADER
#endif

// good
#ifndef MY_HEADER_H_
#define MY_HEADER_H_
#endif // MY_HEADER_H_
```
* Global variables: snake_case with a `g_` prefix
```cpp
int foo = 0; // bad
int g_foo = 0; // good
```
* Constants: snake_case with a `k_` prefix
```cpp
constexpr limit = 15; // bad
constexpr k_limit = 15; // good
```
* Class, struct, enum and enum class names: PascalCase
```cpp
// bad
class small_vector {
    // ...
};

// good
class SmallVector {
    // ...
};
```
* Template parameters: PascalCase
```cpp
// bad
template<typename KEY, typename VALUE>
class Dict {
    // ...
};

// good
template<typename Key, typename Value>
class Dict {
    // ...
};
```
* Error messages must start with a lowercase character
```cpp
throw std::runtime_error("This is bad");
throw std::runtime_error("this is good");
```
* Put braces on the next line, except for functions
```cpp
if (counter <= 0) {
    std::println("Time elapsed!");
    return EXIT_SUCCESS;
}

int foo()
{
    return 42;
}
```
* If your `if`/`else`/`while`/`for`/`else if` statement contains one instruction, do
not put braces around it and indent the instruction on the next line
```cpp
if (x)
    f();

while (y)
    g();
```
* Do not indent switch cases
```cpp
// bad
switch (expr) {
    case 1:
        break;
    default:
        break;
}

// good
switch (expr) {
case 1:
    break;
default:
    break;
}
```
* Use RAII, references and smart pointers instead of raw pointers
```cpp
// good
struct Context {
    Context();
    Context(const Context &) = delete;
    Context(Context &&) = delete;
    ~Context();
    Context &operator =(const Context &) = delete;
    Context &operator =(Context &&) = delete;
};

Context *ctx; // bad
std::unique_ptr<Context> ctx; // good
```
* Use the STL instead of libc functions
```cpp
// bad
#include <cstdio>
std::printf("Hello, world!\n");

// good
#include <print>
std::println("Hello, world!");
```
* Do not use C++ modules unless if they get allowed. Ask in an issue if you plan to use them
* Put whitespaces on both sides of binary operators
```cpp
3+4 // bad
3 + 4 // good
```
* Put whitespaces between keyword and symbols
```cpp
// bad
if(x){
    // ...
}

// good
if (x) {
    // ...
}
```
* Do not put whitespaces between symbols
```cpp
int a = ( ( 8 + 9 ) / 1 ); // bad
int b = ((8 + 9) / 1), // good
```
* Use PascalCase for enum constants. Always prefer enum classes to enums.
```cpp
// bad
enum Request {
    GET,
    HEAD,
    DELETE
};

// good
enum class Request {
    Get,
    Head,
    Delete
};
```