# OOZ

OOZ is a function toy language, inspired by Haskell.

## Roadmap

- [ ] Surface syntax (for syntactic sugars)
- [x] Concrete syntax
    + [x] Flex/Bison for LALR grammar
    + [x] Optional semicolon
- [ ] Abstract syntax, core language
    + [x] DBI locally, identifier globally
    + [ ] Representation for evaluation tree
- [ ] Untyped Lambda calculus
    + [ ] C code generation
    + [ ] C as evaluator (register-based VM, inspired by GHC)
        + [ ] Closure design for constructors, thunks, etc.
        + [ ] Runtime library
- [ ] Typed Lambda calculus
    + [ ] Type checking
    + [ ] Type inference
- [ ] System-F
    + [ ] RankNTypes to brute force type inference
- [ ] Dependent types
    + [ ] Brute force the type checker
    + [ ] Optional termination checking

## OOZ?

Shout out to *[Zoo Kid](https://en.wikipedia.org/wiki/King_Krule)*.

## License

MIT
