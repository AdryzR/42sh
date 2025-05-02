/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parser
*/

#include <parser.h>

ast_t *create_ast(ast_type_t type)
{
    ast_t *ast = calloc(1, sizeof(ast_t));

    ast->type = type;
    return ast;
}

static token_type_t get_operation_type(const parser_t *parser)
{
    switch (parser->current.type) {
    case TT_AND:
        return AT_AND;
    case TT_OR:
        return AT_OR;
    default:
        return AT_ERROR;
    }
}

ast_t *parse_parentheses(parser_t *parser)
{
    ast_t *node = create_ast(AT_PAREN);
    ast_t *current;

    parser_next(parser);
    while (!is_paren_end(parser)) {
        current = parse_statement(parser);
        ast_list_append(&node->data.paren, current);
        while (parser->current.type == TT_SMCL)
            parser_next(parser);
    }
    // TODO: Rajouter gestion d'erreur ici
    if (parser->current.type != TT_RPAREN)
        parser->error_msg = "R_PAREN missing.";
    parser_next(parser);
    return node;
}

ast_t *parse_expression(parser_t *parser)
{
    if (parser->current.type == TT_LPAREN)
        return parse_parentheses(parser);
    return parse_command(parser);
}

ast_t *parse_pipeline(parser_t *parser)
{
    ast_t *expr = parse_expression(parser);
    ast_t *node;

    if (parser->current.type != TT_PIPE)
        return expr;
    node = create_ast(AT_PIPELINE);
    ast_list_append(&node->data.pipeline, expr);
    while (parser->current.type == TT_PIPE) {
        parser_next(parser);
        expr = parse_expression(parser);
        ast_list_append(&node->data.pipeline, expr);
    }
    return node;
}

ast_t *parse_binary_operation(parser_t *parser)
{
    ast_t *left = parse_pipeline(parser);
    ast_type_t op_type = get_operation_type(parser);
    ast_t *right;
    ast_t *operation;

    while (op_type != AT_ERROR) {
        parser_next(parser);
        right = parse_pipeline(parser);
        operation = create_ast(op_type);
        operation->data.binary_operation = malloc(sizeof(ast_t *) * 2);
        if (!operation->data.binary_operation) {
            parser->error_msg = "Malloc failed";
            return left;
        }
        operation->data.binary_operation[0] = left;
        operation->data.binary_operation[1] = right;
        left = operation;
        op_type = get_operation_type(parser);
    }
    return left;
}

//TODO: ajouter les if, while et foreach (scripting)
ast_t *parse_statement(parser_t *parser)
{
    return parse_binary_operation(parser);
}

ast_t *parse_program(parser_t *parser)
{
    ast_t *tree = create_ast(AT_PROGRAM);
    ast_t *current;

    do {
        parser_skip_separators(parser);
        if (parser->current.type == TT_EOF)
            break;
        current = parse_statement(parser);
        ast_list_append(&tree->data.program, current);
        if (current->type == AT_ERROR)
            break;
    } while (IS_SEPARATOR(parser->current.type));
    //todo: gestion d'erreur à mettre ici
    if (parser->current.type != TT_EOF)
        fputs("ERROR IN PARSING\n", stderr);
    return tree;
}

/**
 * Dans le main: créer lexer et initialiser pos et start à 0 avant de call ça
**/
ast_t *parser_parse(lexer_t *lexer)
{
    parser_t *parser = create_parser();
    ast_t *ast;

    parser->error_msg = NULL;
    parser->lexer = *lexer;
    parser->prev = (token_t){ TT_EOF, 0 };
    parser->current = get_next_token(&parser->lexer);
    parser->next = get_next_token(&parser->lexer);
    ast = parse_program(parser);
    if (parser->error_msg != NULL)
        printf("%s\n", parser->error_msg);
    return ast;
}
