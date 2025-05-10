/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_program
*/

#include <parser.h>
#include <interpreter.h>

static void print_basic_error_if_needed(parser_t *parser)
{
    if (parser->error_msg == NULL)
        fputs("Input is badly formatted, or an error occured in parsing.\n",
            stderr);
}

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
        print_basic_error_if_needed(parser);
        free_ast(tree);
        return NULL;
    }
    return tree;
}
