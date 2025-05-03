/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parser
*/

#include <parser.h>
#include <interpreter.h>

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
    if (parser->error_msg != NULL) {
        printf("%s\n", parser->error_msg);
        free_ast(ast);
        return NULL;
    }
    return ast;
}
