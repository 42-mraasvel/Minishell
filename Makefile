# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/24 13:22:04 by mraasvel      #+#    #+#                  #
#    Updated: 2021/02/24 18:49:18 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = a.out
SRC = $(shell find $(SRCDIR) -name "*.c" -type f -exec basename {} \;)
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
HEADERS = $(shell find $(IDIR) -name "*.h" -type f)
DEPS = $(HEADERS) Makefile
LIBFT = $(LIBDIR)/libft.a

# DIRS
OBJDIR = obj
SRCDIR = src
IDIR = includes
LIBDIR = libs
LIBFTDIR = $(LIBDIR)/libft
vpath %.c $(SRCDIR)
vpath %.o $(OBJDIR)
vpath %.h $(IDIR)

# compilation
CC = gcc
IFLAGS = -I$(IDIR)
DFLAGS = -O0 -g -fsanitize=address
CFLAGS = -Wall -Wextra
LIBFLAGS = -L$(LIBDIR) -lft

ifdef DEBUG
CFLAGS += DFLAGS
else
CFLAGS += -O0
endif


.PHONY: all
all:
	$(MAKE) -C $(LIBDIR)/libft
	$(MAKE) $(NAME)


$(NAME): $(OBJ) $(LIBFT)
	$(CC) -o $@ $(CFLAGS) $(OBJ) $(LIBFLAGS)
$(OBJDIR)/%.o: %.c $(DEPS) | $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(IFLAGS)

$(LIBFT):
	cp $(LIBDIR)/libft/libft.a $(LIBDIR)

$(OBJDIR):
	mkdir -p $@

.PHONY: re fclean clean
clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFTDIR)
fclean:
	$(MAKE) clean
	$(MAKE) fclean -C $(LIBFTDIR)
	rm -f $(NAME)
re:
	$(MAKE) fclean
	$(MAKE) all