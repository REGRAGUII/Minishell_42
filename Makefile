CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address -g3

MINI_FLAGS = -lreadline 

NAME = minishell

SRC = 	./source/parce.c\
		./source/utils/dups.c\
		./source/utils/ft_split.c\
		./source/utils/libft_utils.c\
		./source/utils/more_utils.c\
		./source/utils/ft_split_char.c\
		./source/error.c\
		./source/utils/strlen.c\
		./source/utils/ft_itoa.c\
		./source/main.c\
		./source/checkers.c\
		./source/space.c\
		./source/parce_utils.c\
		./source/lists.c\
		./source/lists2.c\
		./source/checker_utils.c\
		./source/lexer.c\
		./source/lexer_utils.c\
		./source/expand.c\
		./source/expand_utils.c\
		./source/expand_utils2.c\
		./source/expand_utils3.c\
		./source/add_node.c\
		./source/handle_quotes.c\

EXEC = 	./source/builtins/pwd.c\
		./source/builtins/echo.c\
		./source/builtins/cd.c\
		./source/builtins/exit.c\
		./source/builtins/env.c\
		./source/builtins/unset.c\
		./source/builtins/export.c\
		./source/builtins/export_utils.c\
		./source/builtins/export_utils_2.c\
		./source/redirection.c\
		./source/heredoc.c\
		./source/heredoc_utils.c\
		./source/get_path.c\
		./source/ft_pipe.c\
		./source/execute_utils.c\
		./source/execute_utils2.c\
		./source/execute_utils3.c\
		./source/signals.c\
		./source/execute.c\
		./source/redirection2.c\
		

OBJ = $(SRC:.c=.o) $(EXEC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MINI_FLAGS) -o $(NAME)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

fclean : clean
	rm -rf $(NAME)

clean :
	rm -rf $(OBJ)

re : fclean all
