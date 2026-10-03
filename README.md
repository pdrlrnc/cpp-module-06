# C++ Casting (C++98)

C++ has four named casts, plus the C-style cast you should avoid. All examples below are valid C++98 (compile with `-std=c++98`).

## 1. `static_cast<T>(expr)`

The default choice. It does compile-time-checked conversions that are "reasonable".

```cpp
#include <string>

// Numeric conversions
double d = 3.14;
int i = static_cast<int>(d);          // 3 (truncates)

// void* back to the original pointer type
void* p = &i;
int* ip = static_cast<int*>(p);

// Enum <-> int
enum Color { RED, GREEN };
Color c = static_cast<Color>(1);

// Upcast (derived -> base) and downcast (base -> derived)
class Base {};
class Derived : public Base {};
Derived dv;
Base* b = &dv;
Derived* dp = static_cast<Derived*>(b);   // OK only if b really points to a Derived

// Invoking a constructor
std::string s = static_cast<std::string>("hi");
```

- Downcasting with `static_cast` is **not checked at runtime**. If the object isn't actually a `Derived`, you get undefined behavior.
- It can also invoke constructors and conversion operators.
- It refuses unrelated pointer types: `static_cast<int*>(some_double_ptr)` won't compile.

## 2. `dynamic_cast<T>(expr)`

Safe downcasting/crosscasting in polymorphic hierarchies. It is checked at **runtime** using RTTI.

```cpp
#include <typeinfo>   // std::bad_cast

class Base { public: virtual ~Base() {} };   // needs at least one virtual function
class A : public Base {};
class B : public Base {};

Base* b = new A;

A* a = dynamic_cast<A*>(b);     // OK, non-NULL
B* bb = dynamic_cast<B*>(b);    // fails -> NULL

// With references, failure throws std::bad_cast
try {
    B& br = dynamic_cast<B&>(*b);
    (void)br;
} catch (std::bad_cast& e) {
    // handle it
}

delete b;
```

- **Pointers:** return `NULL` on failure (C++98, so `NULL`, not `nullptr`).
- **References:** throw `std::bad_cast` on failure, since there's no "null reference".
- The base class must be **polymorphic** (have a virtual function), otherwise it won't compile.
- It costs a bit at runtime, but it is the right tool when you don't know the dynamic type.

## 3. `const_cast<T>(expr)`

Adds or removes `const` (and `volatile`). It is the only cast that can do this.

```cpp
void legacyFunc(char* s);            // badly-written API that doesn't modify s

const char* msg = "hello";
legacyFunc(const_cast<char*>(msg));  // OK as long as legacyFunc doesn't write
```

- Casting away `const` is only safe if the underlying object was **not originally declared const**. Modifying a truly const object through a `const_cast`'d pointer is undefined behavior.
- It can't change the underlying type, only the cv-qualifiers.
- If you find yourself using it often, your design probably needs a rethink (or you want `mutable`).

## 4. `reinterpret_cast<T>(expr)`

Low-level reinterpretation of the bits. It is the most dangerous cast.

```cpp
int n = 42;
int* p = &n;

// Pointer <-> integer
unsigned long addr = reinterpret_cast<unsigned long>(p);
int* p2 = reinterpret_cast<int*>(addr);

// Treating raw bytes as a struct
struct Data { int a; char b; };
unsigned char buffer[sizeof(Data)];
Data* d = reinterpret_cast<Data*>(buffer);         // alignment/aliasing risks
```

- No checks and no conversion, it just tells the compiler "trust me".
- Typical uses: serialization, hardware/low-level code, pointer <-> integer.
- Results are largely implementation-defined, and violating strict aliasing is undefined behavior.
- It can't remove `const` (use `const_cast` for that).

> **C++98 note on pointer <-> integer:** C++98 has no `uintptr_t` (it arrives with C99 / C++11 via `<stdint.h>` / `<cstdint>`). `unsigned long` is the usual stand-in, but it is **not guaranteed** to be large enough to hold a pointer. For example, it is 32 bits on 64-bit Windows and would truncate the address. On typical 64-bit Linux/macOS it is 64 bits and works fine.

## 5. C-style and functional casts (avoid)

```cpp
int i = (int)3.14;     // C-style
int j = int(3.14);     // functional style
```

A C-style cast tries `const_cast`, then `static_cast`, then `static_cast` + `const_cast`, then `reinterpret_cast`, and silently picks the first that compiles. This means it can do dangerous things without you noticing, and it's hard to grep for. That is why the named casts exist.

## Quick decision guide

| You want to... | Use |
|---|---|
| Convert between related/numeric types | `static_cast` |
| Safely downcast with polymorphic classes | `dynamic_cast` |
| Add/remove `const` | `const_cast` |
| Reinterpret raw bits / pointer <-> integer | `reinterpret_cast` |

A rough rule is to try `static_cast` first. Reach for `dynamic_cast` when the type is only known at runtime, and treat `const_cast` and `reinterpret_cast` as red flags that deserve a comment explaining why.

## Related things worth knowing

- **Implicit conversions** happen without any cast (int -> double, derived* -> base*, etc.). The `explicit` keyword on constructors prevents unwanted implicit conversions.
- **Conversion operators** (`operator int() const`) let your class define its own casts.
- **Narrowing** (double -> int, long -> short) is where most subtle bugs hide. Making it explicit with `static_cast` documents the intent.
- **`dynamic_cast` and `typeid`** both rely on RTTI, so the base class needs virtual functions for either to work meaningfully.
