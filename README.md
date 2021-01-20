# steadlang
simple in-development toy language written in C, only planned to be interpreted.

# in-development
currently, there's only a lexer with a set of settings, with a concept implementation, that's passed argv[1], a modular logger, and file helpers (currently there's only extension checker).

# build locally
first, do:
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

# cleaning up
considering you've proceeded to build steadlang locally, and by that, have also used the tips aforementioned, you should have a ``Makefile`` in the same folder as with your binary, and considering that's the case, you can just run:
```
$ steadlang-master/: make clean
```

to get rid of the junk created by the compilation (and that includes the stead binary).

# customizations
you're currently able to customize the expected file extension, and a warning level on mismatch. if you make the extension mismatch level 'error', you'll intrerupt the parsing, which'll proceed to free the lexer instance and flush buffers.
you're also able to ask for read safety, which'll check if the file size is bigger than the lexer read size. upon that, if you proceed to set it to true, it'll log a warning.
