<p align="center">
    <img width="240" height="120" src="resources/steadlang.gif">
</p>
steadlang - a simple in-development toy language written in C, only planned to be interpreted.

# build tests
![Linux](https://github.com/cristeigabriel/steadlang/workflows/CMake/badge.svg)

# in-development
there's currently no 'language', the tokenizer is in development, and so is the krates system.

# contributing
if you see anything that you believe should be subject to change, and have motivations for the change you're providing, please proceed to create a [pull request](https://github.com/cristeigabriel/steadlang/pulls). if you're unsure as to if you should open a pull request with what you've done, or if you want to work on a feature but are not sure if it would fit in the steadlang system, proceed to create an [issue](https://github.com/cristeigabriel/steadlang/issues) which will allow us to discuss the matter.

to start contributing, please first take on the next steps to get yourself set with steadlang.

# build locally
first, do:
```
git clone https://github.com/cristeigabriel/steadlang.git
```

then, do:
```
$ steadlang-master/: cmake .
```

after that's done, proceed to do this:
```
$ steadlang-master/: make
```

then, you should have a 'stead' binary, that you can run by doing:
```
$ steadlang-master/: ./stead
```

which'll inform you that you also have to pass a file next to the command.


if you have troubles though, refer to the [build test configuration](https://github.com/cristeigabriel/steadlang/blob/main/.github/workflows/cmake.yml).

# cleaning up
considering you've proceeded to build steadlang locally, and by that, have also used the tips aforementioned, you should have a ``Makefile`` in the same folder as with your binary, and considering that's the case, you can just run:
```
$ steadlang-master/: make clean
```

to get rid of the junk created by the compilation (and that includes the stead binary).

# customizations
refer to [main.c](https://github.com/cristeigabriel/steadlang/blob/main/main.c) to see all available ``[item]_settings`` customizations.

# krate
krate is the in-the-plans binding system from C to steadlang. more information to come with development.

# implementation
check [main.c](https://github.com/cristeigabriel/steadlang/blob/main/main.c).

# external libraries
for ease, I use:
- [a C, small, vector library by Mashpoe](https://github.com/Mashpoe/c-vector)

all external libraries go to /vendor/, and will be credited here accordingly.

note: there might be modifications to the aforementioned libraries within this project to fit our use scenarios.

**note: steadlang uses the GNU libc by default.**

# immediate to-dos (that i shouldn't forget)
make ``_krate_instance's char **files``  a hashmap instead of a vector container.

note for others: it was made a vector for testing.
