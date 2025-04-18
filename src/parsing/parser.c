/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parser
*/

#include <parser.h>

ast_t *parser_parse_program(parser_t *parser)
{
    ast_t *node;

    //todo: switch case selon le type de parser->previous ou parser->current ??

    //todo: parser_parse_[...](node)

}

ast_t *parser_parse_program(parser_t *parser)
{
    ast_t *tree = create_ast(AT_PROGRAM);
    ast_t *current;
    size_t i = 0;

    while (IS_SEPARATOR(parser->current.type)) {
        parser_skip_separators(parser);
        if (parser->current.type == TT_EOF)
            break;
        current = parse_statement(parser);
        current->data.program[i] = current;
        i++;
        if (current->type == AT_ERROR)
            break;
    }
    //todo: gestion d'erreur à mettre ici
    if (parser->current.type != TT_EOF) {
        dprintf(2 , "ERROR IN PARSING\n");
        exit(150);
    }
    return tree;
}

parser_t *parser_get(void)
{
    static parser_t parser = { NULL };

    return &parser;
}

ast_t *parser_parse(lexer_t *lexer)
{
    parser_t *parser = parser_get();
    ast_t *ast;

    parser->prev = get_next_token(&lexer);
    parser->current = parser->prev;
    parser->next = get_next_token(&lexer);
    ast = parser_parse_program(parser);
    return ast;
}
