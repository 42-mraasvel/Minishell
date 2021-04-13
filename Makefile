# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/13 22:14:27 by mraasvel      #+#    #+#                  #
#    Updated: 2021/04/13 22:23:11 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include settings.mk

.PHONY: all
all:
	$(MAKE) -j4 $(LFTDIR)
	$(MAKE) -j4 $(LVCDIR)
	$(MAKE) -j4 $(NAME)

# Compilation
$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)
$(ODIR)%.o: $(SDIR)%.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)
$(DDIR)%.d: $(SDIR)%.c
	@mkdir -p $(@D)
	$(CC) $< -MM -MF $@ -MT $(ODIR)$*.o $(IFLAGS)


# Cleanup
.PHONY: clean fclean cleanall re
clean:
	$(RM) $(OBJ)
fclean:
	$(MAKE) clean
	$(RM) $(NAME)
cleanall: fclean
	$(RM) -r $(DDIR)
	$(RM) -r $(ODIR)
re: fclean
	$(MAKE) all

# Header dependencies
include $(DEP)
