# Pong Clone
A simple Pong clone written in C using SDL3.

## Requirements
- SDL3 development libraries
- GCC or Clang (or another C compiler)
- Make
- Doxygen (optional, for documentation generation)
- MkDocs (optional, for documentation generation)

## Building the Project
To compile the game:

```bash
make
```

This will build the project and place the executable inside `bin` folder

## Building documentation
### Using Doxygen
To generate documentation:

```bash
doxygen
```

This will generate a generic documentation based on the JAVADOC-styled comments in the code.

The documentation will be created in the `html/` directory (or as specified in the `Doxyfile`).

### Using MkDocs
MkDocs is different from Doxygen, and doesn't read source files, instead it reads Markdown files inside the `docs/` folder, this gives a more detailed (and hand-written), but less technical documentation.

To preview documentation:

```bash
mkdocs serve
```

This will start a local server to preview your documentation as a website.

To build documentation:

```bash
mkdocs build
```

This will generate the documentation as HTML inside the `site/` folder.


## License
This project is released under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments
- [SDL3](https://github.com/libsdl-org/SDL) for the graphics and input handling
- Classic Pong game by Atari as inspiration
