/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parser
*/

#ifndef PARSER_H_
    #define PARSER_H_
    #include "lexer.h"


typedef enum {
    AT_ERROR,    // ? Use in case of error found in ast.
    AT_COMMAND,  // ? []
    AT_PROGRAM,  // ? commands separated by ';' or '\n'
    AT_REDIRECT, // ? [argument] <REDIRECTION_TYPE> [argument]
    AT_PIPE,     // ? command | command
    AT_OR,       // ? command || command
    AT_AND,      // ? command && command
    AT_COUNT,    // ? keep last
} ast_type_t;

typedef struct {
    token_t left;
    token_t right;
} pipe_node_t;

typedef enum {
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    REDIR_HEREDOC
} redir_type_t;

typedef struct {
    char *path;
    redir_type_t red_type;
} redir_node_t;

// ? Maybe replace error_msg by an error enum,
// ? that would be interpreted in an error handler function.
typedef struct {
    char *error_msg;
    token_t error_token; // ? For debug purposes (permit to print the token)
} error_node_t;

typedef struct {
    lexer_t lexer;
    token_t current;
    token_t prev;
    token_t next;
} parser_t;

typedef struct ast_s {
    ast_type_t type;
    ast_data_t data;
} ast_t;

typedef struct {
    ast_t **data;
    size_t count;
    size_t capacity;
} ast_list_t;

typedef union {
   redir_node_t redirect;
    struct ast_s **binary_operation;
    ast_list_t program;
} ast_data_t;


void ast_list_append(ast_list_t *list, ast_t *node);


ast_t *parser_parse(lexer_t *lexer);
void parser_next(parser_t *parser);
void parser_skip_separators(parser_t *parser);

#endif
