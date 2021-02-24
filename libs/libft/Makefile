# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/13 10:06:53 by mraasvel      #+#    #+#                  #
#    Updated: 2020/12/28 16:38:10 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# names
NAME = libft.a
SRC = $(shell find $(SRCDIR) -name "*.c")
OBJ = $(addprefix $(OBJDIR)/, $(shell basename -a $(SRC:.c=.o)))

# directories
OBJDIR = obj
SRCDIR = main_part extra_functions extra_functions/math_functions
IDIR = .

#compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I $(IDIR) -I include

#VPATH
VPATH = $(SRCDIR)

.PHONY: all clean fclean re
all: $(NAME)

$(OBJDIR):
	@mkdir -p obj

$(NAME): $(OBJ) libft.h
	@echo -n "\033[032;1m"
	ar rcs $@ $(OBJ)
	@echo -n "\033[0m"
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) -o $@ -c $(CFLAGS) $< $(IFLAGS)

clean:
	@echo "\033[031;1m"
	rm -f $(OBJ)
	@echo "\033[0m"
fclean: clean
	rm -f $(NAME)
re: fclean all
