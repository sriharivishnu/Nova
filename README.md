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
nova>> 1+5
6
nova>> 1-5
-4
nova>> 2*(2+5)
14
nova>> 2^(2+5)
128
nova>> var a = 10       //var is optional
10
nova>> a = 11
11
nova>> a * 2
22
nova >> b = 10
10
nova >> a = false
0
nova >> a + 10
10
nova >> 10 >= 0
1
nova >> !a
1
nova>> a = if (a < 0) 12 elif (a == 5) 123 else -1
123
nova>> a = 1
1
nova>>a++
1
nova>>a
2
```
