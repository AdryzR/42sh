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
    AT_REDIRECT, // ? command <REDIRECTION_TYPE> command
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
} op_type_t;

typedef struct {
    token_type_t type;
    op_node_t left;
    char *left_value;
    op_node_t right;
    char *right_value;
} op_node_t;

// ? Maybe replace error_msg by an error enum,
// ? that would be interpreted in an error handler function.
typedef struct {
    char *error_msg;
    token_t error_token; // ? For debug purposes (permit to print the token)
} error_node_t;

typedef union {
    pipe_node_t *pipe_node;
    redir_node_t *redirect;
    token_t *command;
} ast_data_t;


typedef struct {
    ast_type_t type;
    ast_data_t data;
} ast_t;

typedef struct {
    ast_node_t **ast_list;
} ast_t;

#endif
