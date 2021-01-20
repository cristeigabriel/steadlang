<p align="center">
    <img width="240" height="120" src="resources/steadlang.gif">
</p>
steadlang - a simple in-development toy language written in C, only planned to be interpreted.

# in-development
the language is currently in early development. it is not yet a language due to tokenizer being in the works. that means, it is not yet usable. it does not yet have a clear syntax outside of the current, subject to change, default settings, but a 'feature' will be the modularity of the tokenizer system, as you're able to pass a tokenizer_settings instance to your tokenizer_instance, to process files to your desire. the language, though, will be built with the default settings in mind, so irregularities are not guaranteed to be accounted for, although we'd appreciate if you took from your time to test out different scenarios with different tokenizer settings to allow for stability of the project, to thus make it worthwhile.

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
if you're too lazy to check [main.c](https://github.com/cristeigabriel/steadlang/blob/main/main.c), here's how a base initialization *should* look:
```
  struct _lexer_settings lexer_settings;
  lexer_settings.file_expected_extension = ".sl";
  lexer_settings.file_extension_mismatch = warning;
  lexer_settings.file_read_safety = true;
  lexer_settings.file_read_sizes_mismatch = error;
  lexer_settings.file_size_too_big_error = true;

  struct _lexer_instance *lexer_instance =
      (struct _lexer_instance *)malloc(sizeof(struct _lexer_instance));

  if (lexer_instance == NULL) {
    logger_log(error,
               "failed to initialize lexer instance (%p), returned NULL\n",
               &lexer_instance);
    return 0;
  }

  lexer_instance->lexer_settings = lexer_settings;

  struct _tokenizer_settings tokenizer_settings;
  tokenizer_settings.krate = "krate";
  tokenizer_settings.scope = "scope";
  tokenizer_settings.scope_delimiter = "::";

  struct _tokenizer_instance *tokenizer_instance =
      (struct _tokenizer_instance *)malloc(sizeof(struct _tokenizer_instance));

  if (tokenizer_instance == NULL) {
    logger_log(error,
               "failed to initialize tokenizer instance (%p), returned NULL\n",
               &tokenizer_instance);
    return 0;
  }

  tokenizer_instance->tokenizer_settings = tokenizer_settings;
  tokenizer_instance->lexer = lexer_instance;

  if (lexer_initialize(lexer_instance, argv[1]))
    printf("%s\n", lexer_instance->file);
  else {
    logger_log(error, "lexer initializer returned false\n");
    return 0;
  }

  if (tokenizer_initialize(tokenizer_instance))
    ;
  else {
    logger_log(error, "tokenizer initializer returned false");
    return 0;
  }

  free(lexer_instance->file);
  free(lexer_instance);
  free(tokenizer_instance);
  logger_flush();

```

# external libraries
for ease, I use:
- [a C, small, vector library by Mashpoe](https://github.com/Mashpoe/c-vector)

all external libraries go to /vendor/, and will be credited here accordingly.

note: there might be modifications to the aforementioned libraries within this project to fit our use scenarios.

**note: steadlang uses the GNU libc by default.**
