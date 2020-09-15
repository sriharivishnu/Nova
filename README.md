# Nova
```
nova>> "Welcome to Nova! :)";
Welcome to Nova! :)
```
## Getting Started
### Linux/MacOS
1. Clone this repository over https or SSH : `git clone https://github.com/sriharivishnu/Nova.git` or `git clone git@github.com:sriharivishnu/Nova.git`
2. Navigate to the directory that was created, and run `make` in the command line. This should generate a build folder, and also a binary called nova.
3. Run the executable from the command line with `./nova` to start the shell, or type in `./nova <filename>.nov` to run a file.
4. Type in `1+1` and it should output `2`

### Windows

- **Option 1** Use GNUWin32 to use make
- **Option 2** Manually build all the source files by installing g++, and compiling all src files.

## Examples
### Current Syntax

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
nova>> var s = "srihari";
srihari
nova>> s * 3;
sriharisriharisrihari
nova>> var b = [1,"srihari", 2.0]
[1, srihari, 2.0]
nova>> [1,2] + [2,3]
[1,2,2,3]
```

### Mutli-line support

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

---

## Description
Input Text -> Lexer -> Parser -> Interpreter -> Output

### Lexer
A standard lexer to parse the string into a stream of tokens such as `plus`, `minus`, `while` etc. Relevant methods, other than the single character tokens, are `makeNumber()`, `makeString()`, `makeIdentifier()` which makes a number, string, and identifier tokens respectively.

### Parser
The function of the parser is more interesting than that of the Lexer. The Parser's task is to turn the stream of tokens outputted by the Lexer into a data structure called an AST (Abstract Syntax Tree), a format that allows the interpreter to execute the code. 

The two main components of the parser are the `parseStatement()` and `parseExpression()` methods. The difference between a statement and an expression is that a Statement does not return a value, while an expression does.

Consider the following statement:
```
while (a < 0) {
   b = a * 10 + 1;
   a--;
}
```
Notice that the while statement does not return a value, however, expressions such as `a<0` or `b = a*10+1` (since assignment returns the assigned value in Nova) return a value.

To parse the above statement, we start with a call to parseStatement(). The parseStatement() recognizes that it is a while statement since it starts with the keyword 'while'. It then looks for an expression for its condition, in this case it is `a<0`. If it does not find a condition/expression, then it throws an error. After the call to parseExpression() returns an expression, the original parseStatement() method now makes a recursive call to parseStatement() to parse the next statement. The '{' signifies a block statement, and it then keeps recursively parsing statements and expressions likewise.

The `parseExpression()` method is more complicated, since one must consider the order of operations as well. Here is a brief description of the Pratt Parsing algorithm: 
- Assign all operators a precedence value.
- Parse a 'prefix expression', which can be (++, a string, number) anything that can occur first in an expression. (if not found, throw error)
- While the precedence of the next 'infix operator' is less than the precedence of the next token, keep parsing the expression.

A hashmap is used to quickly check whether there exists a prefix or infix expression for a given token type respectively.

```
1 + 2 * (5+3)
```

```c++
shared_ptr<Expression> Parser::parseExpression(int precedence) {
    Token token = consume();
    auto it = mPrefixParsables.find(token.type);
    if (it == mPrefixParsables.end()) {
        if (token.is(Token::Type::END)) throw ParseException(token.startPos, "Unexpected End of File while Parsing");
        else if (token.is(Token::Type::ELIF)) throw SyntaxError(token.startPos, "'elif' without an 'if' statement");
        else if (token.is(Token::Type::ELSE)) throw SyntaxError(token.startPos, "'else' without an 'if' statement");
        else if (token.is(Token::Type::STMT_END)) throw SyntaxError(token.startPos, "unexpected end of statement");
        throw SyntaxError(token.startPos, "Could not parse: '" + token.getValue() + "'");
    }

    shared_ptr<PrefixParser> prefix = it->second;
    shared_ptr<Expression> left = prefix->parse(*this, token);
    while (precedence < getPrecedence()) {
        token = consume();
        auto it2 = mInfixParsables.find(token.type);
        if (it2 == mInfixParsables.end()) throw UndefinedOperationException(token.startPos, token.getValue());
        shared_ptr<InfixParser> infix = it2->second;
        left = infix->parse(*this, left, token);
    }
    return left;
}
```

The `parseStatement()` method is much simpler, looking for a keyword such as 'while' or 'for', and if none is found, it goes to the default simple statement, which is just a wrapper for an expression.

### Interpreter

All expressions are implemented with the visitor pattern, implementing an accept method, which directs the parse to a centralized class called a visitor. This makes it very easy to implement new expressions. 

The interpreter goes through all statements, and executes them. Each statement implements an execute() method, which invokes its function. 

## Work in Progress

- For loops
- Functions
- Strings
