NAME	= minishell
CC		= cc
CFLAGS	= -g -Wall -Wextra -Werror
SRCS	= main.c arr_utils.c cd.c cmd_utils.c expand_str.c expand_str_utils.c  \
			expand_str_utils_2.c env_utils.c echo.c signal.c \
			env.c errors.c exit.c get_replaced_string.c \
			get_var_name_arr.c export_utils.c export.c free.c \
			helpers.c history.c list_utils.c parse_input.c str_utils.c \
			tocken_utils.c var_split.c unset.c pwd.c execute.c get_path.c \
			heredoc.c run_command.c run_cmd_utils.c 

LIBFT	= libft
OBJS	= $(SRCS:.c=.o)

all:	$(NAME)
$(NAME): $(OBJS)
		@make -C $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) -L./$(LIBFT) -lft -lreadline -fsanitize=address -o $(NAME)
#-fsanitize=address
clean:
	rm -rf $(OBJS)
	rm -rf $(LIBFT)/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/libft.a

re: fclean all
