# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/20 18:21:35 by fquist            #+#    #+#              #
#    Updated: 2022/03/12 01:43:34 by dmontema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_bonus

CC			= gcc
CFLAGS		=  -Wall -Werror -Wextra -g

SDIR		= src/*
SRCS		= main.c \
			  utils.c \
			  parser.c \
			  init_data.c \
			  print_utils.c \
			  times_and_utils.c \
			  routine.c \
			  eating.c \
			  reaper_thread.c
			  
INCLUDES	= -I./include
ODIR		= obj
OBJS		= $(addprefix $(ODIR)/, $(SRCS:.c=.o))

# COLORS
COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m
UP = "\033[A"
CUT = "\033[K"

# **************************************************************************** #
#	RULES																	   #
# **************************************************************************** #

.PHONY: all
all: $(NAME)

header:
	@printf "$(COM_COLOR)==================== $(OBJ_COLOR)$(NAME)$(COM_COLOR) ====================$(NO_COLOR)\n"

# Linking
$(NAME): $(ODIR) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@printf $(UP)$(CUT)
	@printf "%-54b %b" "$(OK_COLOR)$(NAME) compiled successfully!" "$(G)[✓]$(X)$(NO_COLOR)\n"

# Compiling
$(ODIR)/%.o: $(SDIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf $(UP)$(CUT)
	@printf "%-61b %b" "$(COM_COLOR)compiling: $(OBJ_COLOR)$@" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

$(ODIR):
	@mkdir -p $(ODIR)

.PHONY: clean
clean: header
	@$(RM) -r $(ODIR) $(CHECK_ODIR)
	@printf "%-54b %b" "$(ERROR_COLOR)$(NAME) cleaned!" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

.PHONY: fclean
fclean: header clean
	@$(RM) $(NAME)
	@$(RM) -r src/$(NAME) src/*.dSYM
	@printf "%-54b %b" "$(ERROR_COLOR)$(NAME) fcleaned!" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

.PHONY: re
re: fclean all

norm:
	@norminette -R CheckForbiddenSourceHeader include/*.h | grep --color=always 'Error!\|Error:' || echo "$(OK_COLOR)Everything is OK!$(NO_COLOR)" >&1
	@norminette -R CheckForbiddenSourceHeader src/*/*.c | grep --color=always 'Error!\|Error:' || echo "$(OK_COLOR)Everything is OK!$(NO_COLOR)" >&1