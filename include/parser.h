/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parser
*/

#ifndef PARSER_H_
    #define PARSER_H_
    #define UNUSED __attribute__((unused))
    #include <lexer.h>

typedef enum {
    AT_ERROR,    // ? Use in case of error found in ast.
    AT_COMMAND,  // ? []
    AT_PROGRAM,  // ? commands separated by ';' or '\n'
    AT_PAREN,    // ? Used for parentheses.
    AT_REDIRECT, // ? [argument] <REDIRECTION_TYPE> [argument]
    AT_PIPELINE, // ? command [| command]+
    AT_OR,       // ? command || command
    AT_AND,      // ? command && command
    AT_ARGUMENT, // ? argument for a command.
    AT_COUNT,    // ? keep last
} ast_type_t;

typedef struct {
    token_t left;
    token_t right;
} pipe_node_t;

typedef enum {
    REDIR_IN,       // ? <
    REDIR_OUT,      // ? >
    REDIR_APPEND,   // ? >>
    REDIR_HEREDOC   // ? <<
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
    const char *error_msg;
} parser_t;

typedef struct ast_s ast_t;

typedef struct {
    ast_t **data;
    size_t count;
    size_t capacity;
} ast_list_t;

typedef union {
    ast_list_t command;
    char *arg;
    redir_node_t redirect;
    struct ast_s **binary_operation;
    ast_list_t pipeline;
    ast_list_t paren;
    ast_list_t program;
} ast_data_t;


typedef struct ast_s {
    ast_type_t type;
    ast_data_t data;
} ast_t;

void ast_list_append(ast_list_t *list, ast_t *node);

static inline bool is_paren_end(parser_t *parser)
{
    return
        parser->current.type == TT_NEWLINE ||
        parser->current.type == TT_RPAREN ||
        parser->current.type == TT_EOF;
}

static inline bool is_a_redirect(const parser_t *parser)
{
    return
        parser->current.type == TT_REDIRECT_IN ||
        parser->current.type == TT_REDIRECT_OUT ||
        parser->current.type == TT_APPEND ||
        parser->current.type == TT_HEREDOC;
}

ast_t *parser_parse(lexer_t *lexer);

ast_t *parse_statement(parser_t *parser);
ast_t *parse_program(parser_t *parser);
ast_t *parse_redirect(parser_t *parser);
ast_t *parse_binary_operation(parser_t *parser);
ast_t *parse_expression(parser_t *parser);
ast_t *parse_parentheses(parser_t *parser);
ast_t *parse_command(parser_t *parser);
ast_t *parse_pipeline(parser_t *parser);

parser_t *create_parser(void);
void parser_next(parser_t *parser);
void parser_skip_separators(parser_t *parser);
void print_ast_node(const ast_t *ast, unsigned short depth);
void print_ast(const ast_t *ast);
bool contains_argument_node(const ast_t *node);
ast_t *create_ast(ast_type_t type);

#endif
