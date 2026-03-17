#ifndef TOKENS_H
#define TOKENS_H

enum TokenType {

    /* Types */
    INT = 256,
    DOUBLE,
    FLOAT,
    CHAR,
    STRING,

    /* Control */
    FOR,
    WHILE,
    DO,
    IF,
    ELSE,
    RETURN,

    /* Operators */
    EQ,
    NEQ,
    GE,
    LE,
    AND,
    OR,

    PLUS,
    MINUS,
    MUL,
    DIV,
    MOD,
    ASSIGN,
    GT,
    LT,

    /* Others */
    NUM,
    ID
};

#endif