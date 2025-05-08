/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_program
*/

#include <parser.h>
#include <interpreter.h>

//todo: gestion d'erreur à approfondir (ex: passe ici si ')' missing)
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
    if (parser->current.type != TT_EOF) {
        fputs("ERROR IN PARSING\n", stderr);
        free_ast(tree);
        return NULL;
    }
    return tree;
}
