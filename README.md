# Nova

- Work In Progress
- Run `make` in the CLI to build
- ./nova to run

- [ ] Lexer
- Converts text into tokens.
- [ ] Parser
- Converts tokens into an Abstract Syntax Tree. Constructed the Tree with Pratt Parsing Algorithm
- [ ] Interpretor
- Evaluates an expression, implementing Visitor pattern.

## Current Syntax

```
nova>> var a = var b = 10;
10
nova>> ++a;
11
nova>> fun inc() -> a++;
nova>> inc();
11
nova>> inc();
12
nova>> a;
13
nova>> while (a > 0) a--;
nova>> a;
0
nova>> var res = if (a < 0) 20 elif (a == 10) 10 else -100;
-100
```

## Mutli-line support

```
fun add(a, b) {
    a + b;
}
//While loop
var a = 10;
while (a > 0) {
    a--;
}
a;
-----------------
output: 0
```

## Work in Progress

- For loops
- Functions
- Strings
