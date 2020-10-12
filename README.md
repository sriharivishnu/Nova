![nova_logo_2 0](https://user-images.githubusercontent.com/37857112/95665390-b3986c00-0b1d-11eb-8870-a33562fa6332.png)

![build status](https://github.com/sriharivishnu/Nova/workflows/build/badge.svg)
```
nova>> print("Welcome to Nova! :)");
Welcome to Nova! :)
```
## Getting Started (Release)
For a detailed description of the usage of Nova, please visit the [Nova Wiki](https://github.com/sriharivishnu/Nova/wiki)
### Linux/MacOS
1. Download the [latest release](https://github.com/sriharivishnu/Nova/releases/latest) from Github releases 
2. Untar with `tar -xf nova-<latest-version>.tar.gz`
3. Configure for your system with `./configure`
4. Install to your system with `make install` (if permission denied, try `sudo make install`)
5. Run nova: `nova <filename>.nov` or `nova` to enter the shell
### Windows test
Compiling/Building:
- **Option 1**: Use GNUWin32 to use make
- **Option 2**: Install make.exe from the GNU website
- **Option 3**: Install `chocolatey` and the run `choco install make`
- **Option 4**: Manually build all the source files by installing g++, and compiling all src files.

The steps in the Linux/MacOS section can now be followed

## Contributing
### Linux/MacOS
1. Clone this repository over https or SSH : `git clone https://github.com/sriharivishnu/Nova.git` or `git clone git@github.com:sriharivishnu/Nova.git`
2. Navigate to the directory that was created
3. run `autoreconf --install`
4. run `./configure`
5. run `make` to create a binary in the current directory or `make install` to install it to your system
6. Run the executable from the command line with `./nova` (or `nova` if installed) to start the shell, or type in `./nova <filename>.nov` to run a file.

### Windows
- Please follow the steps above after installing the necessary GNU tools (autoreconf, make etc.)

### Syntax
- For a detailed description of the current syntax, please view the [Nova Wiki](https://github.com/sriharivishnu/Nova/wiki)
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

```
1 + 2 * (5+3)
```

```c++
shared_ptr<Expression> Parser::parseExpression(int precedence) {
    Token token = consume();
    shared_ptr<Expression> left = getPrefixExpression(token);
    while (precedence < getPrecedence()) {
        token = consume();
        left = getInfixExpression(left, token);
    }
    return left;
}
```

The `parseStatement()` method is much simpler, looking for a keyword such as 'while' or 'for', and if none is found, it goes to the default simple statement, which is just a wrapper for an expression.

### Interpreter

All expressions are implemented with the visitor pattern, implementing an accept method, which directs the parse to a centralized class called a visitor. This makes it very easy to implement new expressions. 

The interpreter goes through all statements, and executes them. Each statement implements an execute() method, which invokes its function. 

## Potential Cool Unique Features to Add:
- User-defined operations

