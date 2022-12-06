
S = src/
O = obj/

SOURCES = $Sphilo_main.c $Sphilo.c $Sactions.c $Stime.c $Sfree_death.c

OBJS = $(SOURCES:$S%=$O%.o)

CC = gcc
RM = rm -rf
CFLAGS = -pthread -Wall -Wextra -Werror -g

NAME = philo

all: $(NAME)

$O:
	@mkdir $@

$(OBJS): | $O

$(OBJS): $O%.o: $S%
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS)  $^ -o $@
	@echo "\033[0;32m Compilation complétée"
clean: 
		@$(RM) $(OBJS)
		@$(RM) $O
		@echo "\033[0;31m Fichiers .o supprimés"

fclean:	clean

	@$(RM) $(NAME)
	@echo "\033[0;31m executable supprimé "


re:	fclean $(NAME)