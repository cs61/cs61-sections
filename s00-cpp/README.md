# Section Notes 1
## Outline
* [Review](#review)
  - [Segments](#segments)
  - [Size and Alignment](#size-and-alignment)
  - [(Basic) Pointer Arithmetic](#pointer-arithmetic)
  - [Memory Bugs](#memory-bugs)
* [C++ Patterns](#c-patterns)
  - [STL Containers](#standard-template-library-stl-containers)
  - [The `system_allocator<>` class in PSet 1](#understanding-system_allocator-in-pset-1)
  - [Simple C++ Exercises](#simple-c-exercises)
* [Programming Exercises](#programming-exercises)
  - [Greetings!](#greetings)
  - [Image Inverter](#image-inverter)

# Review
## Segments
Place all variables in question into the correct sections of memory and identify the scope of each variable.

```cpp
#include <cstdlib>
#include <cstdio>

#define MY_VALUE 10
int g = 45;                                  // Q#1

const char* a_string = "A fixed string";     // Q#2

void add_helper(int* c, int* d, int* e) {    // Q#3
    *c = *d + *e;                            // Q#4
}

int add(int a, int b) {
    int *answer = (int*) malloc(sizeof(int));  // Q#5
    add_helper(answer, &a, &b);
    int ans = *answer;                       // Q#6
    free(answer);
    return ans;
}

int main() {
    printf("%d\n", add(MY_VALUE, 6));
    return 0;
}
```

What is the construct called and where does it live in memory:
1. `g`
2. `a_string`
3. `add_helper`
4. `c`, `d`, and `e`
5. `*answer`
6. `ans`

|High Addresses | Stack       | Heap     | Data (read/write) | Data (read) | Text     |
|---------------|-------------|----------|-------------------|-------------|----------|
|               |             |          |                   |             |          |

## Size and Alignment
Write down the size and the alignment of the following `struct`s. Hint: draw out how an instance of each `struct` would look in memory.

```c
struct struct1 {
    int i;
};
```
* Alignment:
* Size:

```c
struct struct2 {
    short a;
    short b;
    short c;
};
```
* Alignment:
* Size:

```c
struct struct3 {
    char a;
    int b;
};
```
* Alignment:
* Size:

```c
struct struct4 {
    int b;
    char a;
};
```
* Alignment:
* Size:

```c
struct struct5 {
    char a;
    char b;
    int c;
};
```
* Alignment:
* Size:

```c
struct struct6 {
    char a;
    struct {
        char b;
        int c;
    } s;
};
```
* Alignment:
* Size:

```c
union union1 {
    char a;
    int b;
};
```
* Alignment:
* Size:

```c
struct struct7 {
    char a;
    union {
        char b;
        int c;
    } u;
};
```
* Alignment:
* Size:

## Pointer Arithmetic
Given the following definitions what does each function do, and what do they return?
(Assume the arguments are cast to the right types.)

```c
int sum(int a, int b){
    return a + b;
}

sum(8, 6) = ?
```


```c
char* sum(char* a, int b) {
    return &a[b];
}

char s[20];
sum(s + 8, 6) = ?
```


```c
int* sum(int* a, int b) {
    return &a[b];
}

int x[1000];
sum(&x[8], 6) = ?
```


```c
ptrdiff_t sub(int* a, int* b) {
    return a - b;
}

int x[1000];
sub(&x[996], &x[988]) = ?
```


## Pointer Equivalence
You can think of comparisons in three ways: data/value, point to the same memory, are the same memory.

If we have:
```c
int c, d;
c = 10;
d = 10;
```
clearly `(c == d)` because we are comparing values. If we then say
```c
int* e = &c;
int* f = &d;
```
then `(*e == *f)`, since `(10 == 10)`, but `(e != f)`. Why?

Pointer comparison involves comparing the underlying addresses. Since the pointers point to different objects—`e` points to `c`, and `f` points to `d`—and C/C++ guarantees that different objects have distinct, non-overlapping addresses (except in a union), it follows that `(e != f)`.

## Equivalence Exercises
```cpp
int a = 5;
int b = 5;
int* x = &a;  // x==0xf4dc
int* y = &b;  // y==0xf4d8
int* z = x;
int** p = &z; // p==0xf4d0
int array[10] = { 5, 0 ... 0 };
int yarra[6] = { 1, 2, 3, 4, 5, 6 };
int* w = array + 4;
int* group[3];
group[0] = array;
group[1] = yarra;
group[2] = y;
```

True of false?

1. `(a == b)`
2. `(x == y)`
3. `(y == &a)`
4. `(*z == a)`
5. `(group[0][0] == a)`
6. `(group[1][3] == 1)`
7. `(group[1][3] == 4)`
8. `(group[2][0] == 5)`
9. `(group[0][0] == *group[0])`
10. `(group[0][4] == *(group[0] + 4))`
11. `(group[0][4] == *group[0] + 4)`
12. `(group[0][4] == (*group)[4])`
13. `((*group)[0] == (*(group+1))[4])`
14. `(*w == 4)`
15. `(*w == 0)`
16. `(w == 0)`


Symbol              | Type            | Value
--------------------|-----------------|-------------------
`z`                 |                 |
`p-2`               |                 |
`&z`                |                 |
`yarra[3]`          |                 |
`&b`                |                 |
`group[2][0]`       |                 |
`array[6]`          |                 |
`*p`                |                 |
`**(x-3)`           |                 |
`**(&group[1]-1)`   |                 |
`*w`                |                 |
`group+2`           |                 |
`*(group+3)`        |                 |

## Memory Bugs

Go to `cs61-sections/s01`. For each of the `membug*.cc` files, describe the memory bugs present in each file. Some example bugs include “invalid free”, “invalid free: pointer not on heap”, “double free”, “use of uninitialized pointer.” Before running, predict the effect of the memory bug -- will the program crash?  Or will it fail silently?  Run `make`, then `./membug1`, `./membug2`, etc. to observe the effects of each bug.

* `membug1.cc`:
* `membug2.cc`:
* `membug3.cc`:
* `membug4.cc`:
* `membug5.cc`:
* `membug6.cc`:
* `membug7.cc`:
* `membug8.cc`:

# C++ Patterns

## `new` and `delete` vs. `new ...[]` and `delete ...[]`

C++ uses four operators for allocating and deleting memory. They are:

1. `new T` — dynamically allocates a single new object of type `T`.
2. `delete ptr` — frees the single object `ptr` previously allocated by `new`.
3. `new T[N]` — dynamically allocates an array of `N` objects of type `T`.
4. `delete[] ptr` — frees the array `ptr` previously allocated by `new ...[]`.

Note that you’re supposed to call the right one. If you allocate an array, use
`delete[]` to free it. (This differs from C.)

Advanced `new` syntax can *initialize* an object when it is allocated. For
instance, `new int{3}` (or `new int(3)`) returns a pointer to a
dynamically-allocated `int` initially set to 3.

## Standard Template Library (STL) Containers

STL is just a library full of useful stuff! It comes with a collection of containers, or data structures, that you may notice in the handout code. You may also want to use these data structures yourself.

### Vector (Growable Array)

```cpp
#include <vector>

// A vector of integers
std::vector<int> my_vec = { 1, 2, 3, 4 };

int vec_2 = my_vec[2]; // Reading from vector
my_vec[3] = 4;         // Writing to vector
// The vector `[]` operator is like array dereference: the caller must
// check bounds. But there’s another call that always checks bounds.
vec_2 = my_vec.at(2);
my_vec.at(3) = 4;

my_vec.push_back(5);   // Adding element to the end of the vector
my_vec.back();         // Return the last element of the vector (must not be empty)
my_vec.pop_back();     // Remove element at the end
my_vec.size();         // Return length of vector
my_vec.empty();        // Return true iff `size() == 0`
```

### Iterators

STL containers and algorithms rely on an abstraction called the *iterator*. An iterator is like a “smart pointer” into a data structure. It indicates a current position in the container. In a vector, iterators are like pointers into arrays.

The most important iterator methods are `container.begin()`, which returns an
iterator that points to the “beginning” of the container (in a vector, this is
the first element), and `container.end()`, which returns an interator that
points to the “end” of the container and also represents absent elements (in a
vector, this points one past the last element).

These codes behave the same:

```c++
int my_array[4] = { 1, 2, 3, 4 };
// first iterate using an index
for (int i = 0; i != 4; ++i) {
    printf("%d\n", my_array[i]);
}

// that’s equivalent to iterate using a pointer into the array,
// thanks to pointer arithmetic!!!!!!!!!!!
for (int* a = my_array; a != &my_array[4] /* one past end */; ++a) {
    printf("%d\n", *a);
}

// the C++ vector version looks like the “pointer arithmetic”
// version, and can be just as fast, but safer.
std::vector<int> my_vec = { 1, 2, 3, 4 };
for (auto it = my_vec.begin(); it != my_vec.end(); ++it) {
    printf("%d\n", *it);
}
```

C++’s “for-each” loops also use iterators behind the scenes.

```cpp
for (auto& a : my_vec) {
    printf("%d\n", a);
}
```

### Vector Exercises

Fill in the `?`s!

```cpp
std::vector<int> my_vec = { 1, 2, 3, 4, 5 };

my_vec.size() == ?
my_vec[3] == ?

my_vec.push_back(6);

my_vec.size() == ?
my_vec.back() == ?

my_vec.erase(my_vec.begin(), my_vec.begin() + 1);

my_vec.size() == ?
my_vec.back() == ?
my_vec[0] == ?
```



Can you do this?
```cpp
std::vector<int> my_vec = { 1, 2, 3 };

my_vec[4] = 1;
```



What about this?

```cpp
std::vector<int> my_vec = { 1, 2, 3 };

printf("%d\n", my_vec.at(4));
```

### Map (Ordered Search Tree)

Comparison for key type is required.

```cpp
#include <map>
#include <string>

std::map<int, std::string> my_map;
my_map[1] = "one";                   // Insert into map (with overwrite senamtics)
std::string s = my_map[1];           // Map lookup (inserts default if not found)

// test if key is in map
size_t exists = my_map.count(2);     // 0 if not in map, 1 if in map

// Insert without overwriting (leaves map unchanged if key present)
my_map.insert({1, "ONE"});

// Remove key
my_map.erase(1);

// Number of keys in map
size_t x = my_map.size();
```

Maps can find keys quickly using binary search tree algorithms. The `find`
method returns an iterator.

```cpp
auto it = my_map.find(2);
if (it != my_map.end()) {
    // Then `2` is present in the map as a key.
    assert(it->first == 2);
    // And we can access the value.
    printf("%s\n", it->second.c_str());
} else {
    // it == my_map.end() -- key is not found
}
```

As usual `begin()` and `end()` can iterate over *all* the elements of the map.

### Map Exercises
Fill in the `?`s!

```cpp
std::map<int, int> my_map;

my_map.insert({1, 2});
my_map[1] == ?
my_map.count(1) == ?
my_map.count(2) == ?
my_map.size() == ?

int x = my_map[2];
x == ?
my_map.size() == ?

my_map.insert({1, 3});
my_map[1] == ?

my_map.erase(1);
my_map.size() == ?
my_map.insert({1, 3});
my_map[1] == ?
```



What is printed?

```cpp
std::vector<int> my_vec = { 9, 1, 4, 5, 8, 2, 3, 6, 7 };
std::map<int, int> my_map;
for (auto it = my_vec.begin(); it != my_vec.end(); ++it) {
    my_map.insert({*it, *it});
}
for (auto it = my_map.begin(); it != my_map.end(); ++it) {
    printf("my_map[%d] = %d\n", it->first, it->second);
}
```



### Unordered Map (Hash Table)

Basically the same syntax as `std::map`, except that a hash function and equality checker for the key type are required.

If you see a horrible error like

```
error: static_assert failed "the specified hash does not meet the Hash requirements"
```

or (EUUUUUGGGGGHHHHHHHHH)

```
/usr/include/c++/7/bits/hashtable_policy.h: In instantiation of ‘struct std::__detail::__is_noexcept_hash<std::pair<int, int>, std::hash<std::pair<int, int> > >’:
/usr/include/c++/7/type_traits:143:12:   required from ‘struct std::__and_<std::__is_fast_hash<std::hash<std::pair<int, int> > >, std::__detail::__is_noexcept_hash<std::pair<int, int>, std::hash<std::pair<int, int> > > >’
/usr/include/c++/7/type_traits:154:31:   required from ‘struct std::__not_<std::__and_<std::__is_fast_hash<std::hash<std::pair<int, int> > >, std::__detail::__is_noexcept_hash<std::pair<int, int>, std::hash<std::pair<int, int> > > > >’
/usr/include/c++/7/bits/unordered_map.h:103:66:   required from ‘class std::unordered_map<std::pair<int, int>, int>’
membug8.cc:4:54:   required from here
/usr/include/c++/7/bits/hashtable_policy.h:87:34: error: no match for call to ‘(const std::hash<std::pair<int, int> >) (const std::pair<int, int>&)’
```

that means that the key type has no hash function yet. You can use a `std::map` (which doesn’t require a hash function, but features slower lookup), or write a hash function:

```cpp
namespace std {
     template <> struct hash<MY_TYPE> {
         size_t operator()(const MY_TYPE& x) const {
             return ... whatever ...;
         }
     };
}
```

Here is a pretty good hash function for pairs (based on the one in [Boost](https://www.boost.org/doc/libs/1_68_0/doc/html/hash.html)). Do not ask your TF about it during section but feel free to ask us offline :)

```cpp
namespace std {
    template <typename T, typename U> struct hash<pair<T, U>> {
        size_t operator()(const pair<T, U>& x) const {
            size_t h1 = std::hash<T>{}(x.first);
            size_t h2 = std::hash<U>{}(x.second);
            size_t k = 0xC6A4A7935BD1E995UL;
            h2 = ((h2 * k) >> 47) * k;
            return (h1 ^ h2) * k;
        }
    };
}
```

And here is a garbage hash function. You could use it as a placeholder if you like making your computer work hard.

```cpp
namespace std {
     template <> struct hash<MY_TYPE> {
         size_t operator()(const MY_TYPE& x) const {
             return 0;
         }
     };
}
```

**Q: How would you use a pair of a string and a number (`std::pair<std::string, int>`) as the key type in unordered map, without writing your own hash function?**



## Understanding `system_allocator<>` in Pset 1

There is a class called `system_allocator` in problem set 1’s handout code (in `m61.hh`):

```cpp
/// This magic class lets standard C++ containers use the system allocator,
/// instead of the debugging allocator.
template <typename T>
class system_allocator {
public:
    typedef T value_type;
    system_allocator() noexcept = default;
    template <typename U> system_allocator(system_allocator<U>&) noexcept {}

    T* allocate(size_t n) {
        return reinterpret_cast<T*>((malloc)(n * sizeof(T)));
    }
    void deallocate(T* ptr, size_t) {
        (free)(ptr);
    }
};
```

According to the comments, this code lets C++ STL containers use the system allocator instead of the debugging allcoator. How does it work? Let's take a closer look.

This class defines two methods, `allocate()` and `deallocate()`. Within these method, `malloc` and `free` are invoked. The parentheses around `malloc` and `free` ensure that these are the *system* `malloc` and `free`, not the (possibly-macro-defined) `m61_malloc` and `m61_free`.

Now look at `basealloc.cc` within the pset directory, where STL containers are used. Pay attention to how the contrainers are declared. For example, the vector:

```cpp
static std::vector<base_allocation, system_allocator<base_allocation>> frees;
```

We pass two parameters to `std::vector`. The first one, `base_allocation`, is the element type of the vector: this is a vector of `base_allocation`s. The second one is the `system_allocator` class we just defined! This tells STL to only use the system `malloc`, rather than the m61 allocator you’re writing. Nearly all STL containers take an allocator class as a parameter (which defaults to a class is called [`std::allocate<>`](https://en.cppreference.com/w/cpp/memory/allocator)). The container uses the `allocate()` and `deallocate()` methods defined by the allocator class to manage dynamic memory.

**Q: Which allocator would STL containers use without passing in the `system_allocator` parameter?**



**TL;DR:** This is what you should do if you choose to use STL containers _within your debugging allocator code_ in PSet 1:

```cpp
// If you want to use std::vector
std::vector<T, system_allocator<T>> my_vec;

// If you want to use std::map or std::unordered_map
// It looks a bit awful because of C++ template specialization rules
std::map<K, V, std::less<K>, system_allocator<std::pair<K, V>>> my_map;
std::unordered_map<K, V, std::hash<K>, std::equal_to<K>, system_allocator<std::pair<K, V>>> my_hash;

// Even strings need an allocator! Don’t use `std::string`, use
std::basic_string<char, std::char_traits<char>, system_allocator<char>> my_string;

// Or give these things shorter names!
typedef std::vector<T, system_allocator<T>> my_vec_t;
my_vec_t my_vec;
```

## Additional C++ Resources

There are a lot of online resources for common C++ patterns and STL documentation. [cppreference.com](https://en.cppreference.com) is a good place to look for such information.



# Programming Exercises
## Greetings!

Take a look at `cs61-sections/s01/greet.cc/`. It’s a very short program:

```cpp
#include <cstdio>
#include <cstdlib>

void greet() {
    char buf[16];

    printf("Hello! What is your name?\n");
    scanf("%s", buf);
    printf("Nice to meet you, %s!\n", buf);
}

int main() {
    greet();
    return 0;
}
```

Try running it and see what it does.

**Q: Can you crash this program, without changing the program itself?**



**Q: Why did it crash, and what are the implications?**



**Q: How can you make this program safe?** Hint: `man scanf`!



## Image Inverter

### Goals
* Work with C++ arrays and pointers
* Understand how malformed input can crash a program
* And the security implications of the previous bullet point

### Overview
In this exercise we will be implementing a program that inverts a digital image stored in PPM format.

You can learn more about PPM format [here](http://netpbm.sourceforge.net/doc/ppm.html). Basically, PPM is a uncompressed image format that’s easy for programs to write and read. For our purposes we assume a PPM image file always conforms to the following structure:
1. ASCII characters `"P6"`, magic value for the PPM format
2. Whitespace
3. Width of the image, as ASCII string (decimal representation)
4. Whitespace
5. Height of the image, in ASCII decimal
6. Whitespace
7. Maximum pixel value, in ASCII decimal
8. A single whitespace character
9. Pixel data

Pixel data is just a sequence of bytes. Each pixel in the image is represented by 3 bytes of data (R, G, and B), where each byte takes value 0 to the “max pixel value” defined in the file earlier.

We call the textual portion of the file (before the pixel data) the _header_ of a PPM file. The following is a valid PPM header:

```text
P6
100 100
255
```

Your job is to write a program that reads a PPM file, color-inverts the image, and save the inverted image to a new file.

We’ve provided a skeleton in `inv.cc`, but it’s not complete.

### Invert!
Find image.ppm in the `cs61-sections/s01` directory. You can view your image using the display command:

```bash
display sample.ppm     # Linux
open sample.ppm        # Mac OS X
```

You will see the following image displayed:

![original-image](https://cs61.seas.harvard.edu/wiki/images/5/58/F18-s01-Image.png)

The inverted version of this image can be seen in `sample-inverted.ppm`:

![inverted-image](https://cs61.seas.harvard.edu/wiki/images/f/fb/S01-f18-Image_inv.png)

Finish the program in `inv.cc`. If you run your program as

```bash
make inv && ./inv < sample.ppm > x.ppm
```

you should find that `x.ppm` is identical to `sample-inverted.ppm`.

Your program should color-invert the image pixel by pixel (red should become green, black should become white, and so on). **You can achieve this by replacing each pixel value with its difference from the maximum pixel value.**

If your program works, you should see an output file like this:

### Security

**Q. Can you produce an input that causes `./inv` to crash or abort with a memory error?** (Assertion failures don’t count.)

**Q. Update `inv.cc` so that `./inv` *never* causes a memory error, crash, or abort.** (Again, assertion failures don’t count.)
