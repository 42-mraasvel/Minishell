# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/24 13:22:04 by mraasvel      #+#    #+#                  #
#    Updated: 2021/03/11 10:14:55 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = a.out
SRC = $(shell find $(SRCDIR) -name "*.c" -type f -exec basename {} \;)
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
HEADERS = $(shell find $(IDIR) -name "*.h" -type f)
DEPS = $(HEADERS) Makefile

# LIBS
LIBFT = $(LIBFTDIR)/libft.a
LIBVECT = $(LIBVECTDIR)/libvect.a

# DIRS
OBJDIR = obj
SRCDIR = src
IDIR = includes
LIBDIR = libs
LIBFTDIR = $(LIBDIR)/libft
LIBVECTDIR = $(LIBDIR)/libvect
vpath %.c $(SRCDIR)
vpath %.o $(OBJDIR)
vpath %.h $(IDIR)

# compilation
CC = gcc
IFLAGS = -I$(IDIR)
DFLAGS = -O0 -g -fsanitize=address

# -Werror is annoying for development
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra
LIBFLAGS = -L$(LIBFTDIR) -lft -L$(LIBVECTDIR) -lvect

ifdef DEBUG
CFLAGS += DFLAGS
else
# Set dflags by default for development
# CFLAGS += -O0
CFLAGS += $(DFLAGS)
endif


.PHONY: all
all:
	$(MAKE) -C $(LIBFTDIR)
	$(MAKE) -C $(LIBVECTDIR)
	$(MAKE) $(NAME)


$(NAME): $(OBJ) $(LIBFT)
	$(CC) -o $@ $(CFLAGS) $(OBJ) $(LIBFLAGS)
$(OBJDIR)/%.o: %.c $(DEPS) | $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(IFLAGS)
$(OBJDIR)/main.o: main.c
	$(CC) -c $< -o $@ $(CFLAGS) $(IFLAGS) -D DEF="\"proto.h\""

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)
$(LIBVECT):
	$(MAKE) -C $(LIBVECTDIR)

$(OBJDIR):
	mkdir -p $@

.PHONY: re fclean clean debug
clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFTDIR)
	$(MAKE) clean -C $(LIBVECTDIR)
fclean:
	$(MAKE) clean
	$(MAKE) fclean -C $(LIBFTDIR)
	$(MAKE) fclean -C $(LIBVECTDIR)
	rm -f $(NAME)
re:
	$(MAKE) fclean
	$(MAKE) all
# debug adds fsanitizer flags
debug:
	$(MAKE) re DEBUG=1
