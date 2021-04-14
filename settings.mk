# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    settings.mk                                        :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/13 22:09:02 by mraasvel      #+#    #+#                  #
#    Updated: 2021/04/14 16:46:10 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

ifndef SETTINGS_MK
SETTINGS_MK = 1

# Executable
NAME := minishell

# Directories
SDIR := src
ODIR := obj/
DDIR := dep/
IDIR := includes
LDIR := libs

LFTDIR := $(LDIR)/libft

# Files
SRC := $(shell find $(SDIR) -name "*.c" -type f)
OBJ := $(patsubst $(SDIR)/%.c,$(ODIR)%.o,$(SRC))
DEP := $(patsubst $(SDIR)/%.c,$(DDIR)%.d,$(SRC))

# Compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS := -ltermcap -L$(LFTDIR) -lft
IFLAGS := -I$(IDIR) -I$(LFTDIR)
ifeq ($(shell uname -s),Linux)
DFLAGS := -O0 -g -fsanitize=address -fsanitize=leak
else
DFLAGS := -O0 -g -fsanitize=address
endif

# Debug Flags
CFLAGS += $(DFLAGS)

# Commands
RM = rm -f

endif
