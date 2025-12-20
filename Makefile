# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 12:01:08 by dlu               #+#    #+#              #
#    Updated: 2025/06/22 10:14:04 by dlu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------ Project Metadata
NAME	:=	libft
TARGET	:=	libft.a

# ------------------------ Directories
SRCDIR	:=	src
OBJDIR	:=	obj
INCDIR	:=	include

# ------------------------ Files
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
			ft_printf_print.c ft_printf_utils.c ft_gnl.c ft_gnl_utils.c \
			ft_read_file.c ft_strarrlen.c ft_strarrcpy.c
SRC		:=	$(addprefix $(SRCDIR)/, $(_SRC))
OBJ		:=	$(addprefix $(OBJDIR)/, $(_SRC:.c=.o))

# ------------------------ Toolchain & Flags
CC		:=	cc
AR		:=	ar rcs
RM		:=	rm -f
CFLAGS	:=	-Wall -Wextra -Werror -MMD -MP
CPPFLAGS:=	-I $(INCDIR)

# ------------------------ Build Settings
.DEFAULT_GOAL	:= all

PAD		?=	0 # Inherited label length for alignment
DEBUG	?=	0
ifeq ($(DEBUG),1)
	CFLAGS	+=	-g
endif

# ------------------------ Rules & Targets
.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	@if [ -d "$(OBJDIR)" ]; then \
		printf "%-*s 🧹 Removing $(OBJDIR)/..." $(PAD) "[$(NAME)]"; \
		$(RM) -r $(OBJDIR); \
		echo " ✅ "; \
	fi

.PHONY: fclean
fclean: clean
	@if [ -f "$(TARGET)" ]; then \
		printf "%-*s 🗑️ Removing $(TARGET)..." $(PAD) "[$(NAME)]"; \
		$(RM) $(TARGET); \
		echo " ✅ "; \
	fi

.PHONY: re
re: fclean all

$(OBJDIR):
	@printf "%-*s 📂 Creating: $@ directory..." $(PAD) "[$(NAME)]"
	@mkdir -p $@
	@echo " ✅ "

$(TARGET): $(OBJ)
	@printf "%-*s 📦 Building: $@" $(PAD) "[$(NAME)]"
	@$(AR) $@ $^
	@echo " ✅ "

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@printf "%-*s ⚙️ Compiling: $<..." $(PAD) "[$(NAME)]"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	@echo " ✅ "

.DELETE_ON_ERROR:     # Delete target build that's incomplete
-include $(OBJ:.o=.d) # Dependency injection
