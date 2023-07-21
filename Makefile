# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/07 22:35:09 by arasal            #+#    #+#              #
#    Updated: 2022/08/19 00:44:04 by arasal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler Variables
NAME	= pipex
B_NAME	= pipex_bonus
CFLAGS	= -Werror -Wall -Wextra
LIBFT	= ./Libft

# File Variables
HEADERS	= -I $(LIBFT)
LIBS	= $(LIBFT)/libft.a
SRCS	= pipex.c pipex_utils.c error.c
B_SRCS	= pipex_bonus.c pipex_utils_bonus.c get_next_line_bonus.c  error_bonus.c \
		  get_next_line_utils_bonus.c
OBJS	= ${SRCS:.c=.o}
B_OBJS	= ${B_SRCS:.c=.o}

BOLD	= \033[1m
BLACK	= \033[30;1m
RED		= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
BLUE	= \033[34;1m
MAGENTA	= \033[35;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m

# //= Recipes =//

all: $(NAME)

bonus: $(B_NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "$(MAGENTA)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

$(NAME): $(OBJS)
	@$(MAKE) --silent -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(BOLD)\033[32mPipex is Compiled! ༺ (\033[31m♥\033[32m_\033[31m♥\033[32m)༻\n"

$(B_NAME): $(B_OBJS)
	@$(MAKE) --silent -C $(LIBFT)
	@$(CC) $(CFLAGS) $(B_OBJS) $(LIBS) $(HEADERS) -o $(B_NAME)
	@echo "$(BOLD)\033[32mPipex bonus is Compiled! ༺ (\033[31m♥\033[32m_\033[31m♥\033[32m)༻\n"

clean:
	@rm -f $(OBJS) $(B_OBJS)
	@$(MAKE) --silent -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME) $(B_NAME)
	@$(MAKE) --silent -C $(LIBFT) fclean
	@echo "$(BOLD)\033[32mEverything is fcleaned! ✓ (\033[31m>_<\033[32m)\n"

re: clean all

.PHONY: all, clean, fclean, re, libft