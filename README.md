# steadlang
simple in-development toy language written in C, only planned to be interpreted.

# in-development
currently, there's only a lexer with a set of settings, with a concept implementation, that's passed argv[1], a modular logger, and file helpers (currently there's only extension checker).

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

note: there might be modifications to the libraries used to fit our use scenarios.
