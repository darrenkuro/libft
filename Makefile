# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 12:01:08 by dlu               #+#    #+#              #
#    Updated: 2025/12/30 07:55:43 by dlu              ###   ########.fr        #
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
SRC	:=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
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
OBJ	:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

# ------------------------ Toolchain & Flags
CC		:=	cc
AR		:=	ar
ARFLAGS	:=	rcs
RM		:=	rm -f
CFLAGS	:=	-Wall -Wextra -Werror -MMD -MP
CPPFLAGS:=	-I $(INCDIR)

# ------------------------ Build Settings
.DEFAULT_GOAL	:= all

PAD		?=	0 # Inherited label length for alignment
PAD2	:=	10
DEBUG	?=	0

ifeq ($(DEBUG),1)
CFLAGS	+=	-g
endif

# ------------------------ Colors & Format
RESET	:=	\033[0m
GREEN 	:=	\033[32m

define log
printf "%-*s %-*s %s..." $(PAD) "[$(NAME)]" $(PAD2) "$(1)" "$(2)"
endef

define logok
printf " %b\n" "$(GREEN)[OK]$(RESET)"
endef

# ------------------------ Rules & Targets
.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	@if [ -d "$(OBJDIR)" ]; then \
		$(call log,Removing:,$(OBJDIR)/); \
		$(RM) -r $(OBJDIR); \
		$(call logok); \
	fi

.PHONY: fclean
fclean: clean
	@if [ -f "$(TARGET)" ]; then \
		$(call log,Removing:,$(TARGET)); \
		$(RM) $(TARGET); \
		$(call logok); \
	fi

.PHONY: re
re: fclean all

$(OBJDIR):
	@$(call log,Creating:,$@/)
	@mkdir -p $@
	@$(call logok)

$(TARGET): $(OBJ)
	@$(call log,Building:,$@)
	@$(AR) $(ARFLAGS) $@ $^
	@$(call logok)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(call log,Compiling:,$(notdir $<))
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	@$(call logok)

.DELETE_ON_ERROR:     # Delete target build that's incomplete
-include $(OBJ:.o=.d) # Dependency injection
