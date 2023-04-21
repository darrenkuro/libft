NAME=libft.a
SRC=ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	ft_memset.c ft_memchr.c ft_memcpy.c ft_memmove.c ft_memcmp.c \
	ft_strncmp.c ft_itoa.c ft_atoi.c ft_bzero.c ft_strmapi.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c \
	ft_strdup.c ft_strlcat.c ft_strlcpy.c
SRC_REST=ft_strncmp.c ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_strdup.c \
	ft_bzero.c ft_atoi.c ft_calloc.c
SRC_BONUS=ft_lstnew.c ft_lstsize.c ft_lstadd_front.c ft_lstadd_back.c \
	ft_lstlast.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c
CC=cc
RM=/bin/rm -f
CFLAGS=-Wall -Wextra -Werror
OBJ=$(SRC:.c=.o)
OBJ_BONUS=$(SRC_BONUS:.c=.o)
AR=ar rcs

$(NAME): $(OBJ)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

bonus: $(OBJ) $(OBJ_BONUS)
	$(AR) $(NAME) $^

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
