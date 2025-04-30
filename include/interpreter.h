/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** interpreter
*/

#ifndef INTERPRETER_H_
    #define INTERPRETER_H_
    #include <parser.h>
    #include <my_sh.h>


typedef int (*interpret_fnc_t)(const ast_t *ast, shell_t *shell);


int interpret(const ast_t *ast, shell_t *shell);
int interpret_program(const ast_t *ast, shell_t *shell);
int interpret_paren(const ast_t *ast, shell_t *shell);
int interpret_command(const ast_t *ast, shell_t *shell);
int interpret_pipe(const ast_t *ast, shell_t *shell);
int interpret_or(const ast_t *ast, shell_t *shell);
int interpret_and(const ast_t *ast, shell_t *shell);
int interpret_argument(const ast_t *ast, shell_t *shell);
int interpret_redirect(const ast_t *ast, shell_t *shell);
int interpret_error(UNUSED const ast_t *ast, UNUSED shell_t *shell);

#endif
