/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parser
*/

#include <parser.h>

ast_t *create_ast(ast_type_t type)
{
    ast_t *ast = malloc(sizeof(ast_t));

    ast->type = type;
    return ast;
}

// ast_t *parse_statement(parser_t *parser)
// {
//     switch (parser->current.type) {
//     case TT_REDIRECT_IN:
//     case TT_REDIRECT_OUT:
//     case TT_APPEND:
//     case TT_HEREDOC:
//         return parser_parse_redirect(parser);
//     case TT_SMCL:
//         return parse_parse_
//     }
// }

static token_type_t get_operation_type(const parser_t *parser)
{
    switch (parser->current.type) {
    case TT_AND:
        return AT_AND;
    case TT_OR:
        return AT_OR;
    case TT_PIPE:
        return AT_PIPE;
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
    // if (parser->current.type != TT_RPAREN)
        // return make_ast_error(node, current, ERR_PAREN)
    parser_next(parser);
    return node;
}

ast_t *parse_expression(parser_t *parser)
{
    if (parser->current.type == TT_LPAREN)
        return parse_parentheses(parser);
    return parse_command(parser);
}

//TODO later: replace parse_expression with parse_pipeline
ast_t *parse_binary_operation(parser_t *parser)
{
    ast_t *left = parse_expression(parser);
    ast_type_t op_type = get_operation_type(parser);
    ast_t *right;
    ast_t *operation;

    while (op_type != AT_ERROR) {
        parser_next(parser);
        right = parse_expression(parser);
        operation = create_ast(op_type);
        operation->data.binary_operation = malloc(sizeof(ast_t *) * 2);
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
    return ast;
}
