# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 12:01:08 by dlu               #+#    #+#              #
#    Updated: 2025/12/30 09:53:40 by dlu              ###   ########.fr        #
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
SRC	:=	ft_char.c ft_mem.c ft_io.c ft_str.c ft_strarr.c \
		ft_num.c ft_printf.c ft_lst.c
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
