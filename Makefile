# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 12:01:08 by dlu               #+#    #+#              #
#    Updated: 2025/06/22 00:52:59 by dlu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	libft
PROJECT	:=	$$YELLOW[$(NAME)]$$RESET
TARGET	:=	libft.a

SRCDIR	:=	src
_SRC	:=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_strlen.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
			ft_memset.c ft_memchr.c ft_memcpy.c ft_memmove.c ft_memcmp.c \
			ft_calloc.c ft_itoa.c ft_atoi.c ft_bzero.c ft_strmapi.c \
			ft_strncmp.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strnstr.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c \
			ft_lstnew.c ft_lstdelone.c ft_lstadd_front.c ft_lstadd_back.c \
			ft_lstlast.c ft_lstsize.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
			ft_printf.c ft_printf_parse_format.c ft_printf_parse_nbr.c \
			ft_printf_print.c ft_printf_utils.c ft_gnl.c ft_gnl_utils.c
SRC		:=	$(addprefix, $(SRCDIR)/, $(_SRC))

OBJDIR	:=	obj
OBJ		:=	$(addprefix $(OBJDIR)/, $(_SRC:.c=.o))

INCDIR	:=	include

CC			:=	cc
AR			:=	ar rcs
RM			:=	/bin/rm -f
CFLAGS		:=	-Wall -Wextra -Werror -g -MMD -MP
CPPFLAGS	:=	-I $(INCDIR)

PAD_WIDTH	?=	18	# Strlen counting escaping sequences

.DEFAULT_GOAL := all

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	@printf "%-*s 🧹 Removing object files..." $(PAD_WIDTH) "$(PROJECT)"
	@$(RM) -r $(OBJDIR)
	@echo " ✅ "

.PHONY: fclean
fclean: clean
	@printf "%-*s 🗑️ Removing binary..." $(PAD_WIDTH) "$(PROJECT)"
	@$(RM) $(TARGET)
	@echo " ✅ "

.PHONY: re
re: fclean all

$(OBJDIR):
	@printf "%-*s 📁 Creating obj directory..." $(PAD_WIDTH) "$(PROJECT)"
	@mkdir -p $@
	@echo " ✅ "

$(TARGET): $(OBJ)
	@printf "%-*s 📦 Building archive: $@" $(PAD_WIDTH) "$(PROJECT)"
	@$(AR) $@ $^
	@echo " ✅ "

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@printf "%-*s ⚙️ Compiling: $<..." $(PAD_WIDTH) "$(PROJECT)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	@echo " ✅ "

-include $(OBJ:.o=.d)
