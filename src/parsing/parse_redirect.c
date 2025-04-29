/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_redirect
*/

#include <parser.h>

static redir_node_t get_redir_node(redir_type_t type, parser_t *parser)
{
    redir_node_t redir;

    redir.red_type = type;
    redir.path = get_token_value(&parser->next); //* Vérifier ? command "" path/file et current == command ?
    return redir;
}

ast_t *parse_redirect(parser_t *parser)
{
    ast_t *node = create_ast(AT_REDIRECT);
    redir_node_t redir;

    switch (parser->current.type)
    {
    case TT_APPEND:
        node->data.redirect = get_redir_node(REDIR_APPEND, parser);
        return node;
    case TT_REDIRECT_OUT:
        node->data.redirect = get_redir_node(REDIR_OUT, parser);
        return node;
    case TT_REDIRECT_IN:
        node->data.redirect = get_redir_node(REDIR_IN, parser);
        return node;
    case TT_HEREDOC:
        node->data.redirect = get_redir_node(REDIR_HEREDOC, parser);
    }
    //TODO: add the heredoc (first have to handle it)
}