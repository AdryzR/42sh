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

ast_t *parser_parse_redirect(parser_t *parser)
{
    ast_t *node = create_ast(AT_REDIRECT);
    redir_node_t redir;

    switch (parser->current.type)
    {
    case TT_REDIRECT_OUT:
        redir.red_type = REDIR_OUT;
        redir.path = get_token_value(&parser->current);
        node->data.redirect = redir;
        break;
    default:
        break;
    }
}

ast_t *parse_statement(parser_t *parser)
{
    switch (parser->current.type) {
    case TT_REDIRECT_IN:
    case TT_REDIRECT_OUT:
    case TT_APPEND:
    case TT_HEREDOC:
        return parser_parse_redirect(parser);
    default:
        break;
    }
}

ast_t *parser_parse_program(parser_t *parser)
{
    ast_t *tree = create_ast(AT_PROGRAM);
    ast_t *current;

    while (IS_SEPARATOR(parser->current.type)) {
        parser_skip_separators(parser);
        if (parser->current.type == TT_EOF)
            break;
        current = parse_statement(parser);
        ast_list_append(&tree->data.program, current);
        if (current->type == AT_ERROR)
            break;
    }
    //todo: gestion d'erreur à mettre ici
    if (parser->current.type != TT_EOF) {
        fputs("ERROR IN PARSING\n", stderr);
        exit(150);
    }
    return tree;
}

parser_t *parser_get(void)
{
    static parser_t parser = { NULL };

    return &parser;
}

/**
 * Dans le main: créer lexer et initialiser pos et start à 0 avant de call ça
**/
ast_t *parser_parse(lexer_t *lexer)
{
    parser_t *parser = parser_get();
    ast_t *ast;

    parser->prev = (token_t){ TT_EOF, 0 };
    parser->current = get_next_token(&lexer);
    parser->next = get_next_token(&lexer);
    ast = parser_parse_program(parser);
    return ast;
}
