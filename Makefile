# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/30 15:23:20 by lucocozz          #+#    #+#              #
#    Updated: 2023/01/06 01:11:18 by lucocozz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ping

SRCS =	main.c					\
		libft.c					\
		flags_handlers.c		\
		parse_options.c			\
		icmp_datagram.c			\
		logs.c					\
		resolve_service.c		\
		get_ip_address.c		\
		create_icmp_socket.c	\
		signals.c				\
		checksum.c				\
		send_datagram.c			\
		recv_datagram.c			\
		alarm.c					\
		get_options.c			\
		cleanup.c				\
		get_elapsed_time.c		\
		ping.c					\
		ping_datagram.c			\
		print_ping_header.c		\
		print_ping_result.c		\
		is_ip_format.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPENDENCIES = $(OBJS:%.o=%.d)

SRCS_DIR = sources
OBJS_DIR = .objs
INCLUDES_DIR = includes $(LIBS:%=lib%/includes) $(LIBS:%=lib%)

LIBS =

MAKE = make
CC = clang
RM = rm -f
MKDIR = mkdir -p
DEBUG = off

CFLAGS = -MMD -Wall -Wextra -Werror
CXXFLAGS = $(INCLUDES_DIR:%=-I %)
ifeq ($(DEBUG), on)
	CXXFLAGS += -g3
endif
LDFLAGS = $(LIBS:%=-L lib%) $(LIBS:%=-l%)

vpath %.c	$(addprefix $(SRCS_DIR), /. /libs /icmp /options /ip /system /utils /ping /display)

all:
	$(foreach LIB, ${LIBS}, ${MAKE} -C lib${LIB} ;)
	$(MAKE) $(NAME)

scan:
	scan-build $(MAKE)

$(NAME): $(OBJS) | $(LIBS:%=lib%.a)
	$(CC) $(CXXFLAGS) $^ -o $(NAME) $(LDFLAGS)

-include $(DEPENDENCIES)
$(OBJS_DIR)/%.o: %.c $(OBJS_DIR)/debug$(DEBUG) | $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@ 

$(OBJS_DIR):
	$(MKDIR) $(OBJS_DIR)

lib%.a:
	$(MAKE) -C $(@:%.a=%)

$(OBJS_DIR)/debug$(DEBUG): | $(OBJS_DIR)
	$(RM) $(OBJS_DIR)/debug*
	touch $@

clean:
	$(foreach LIB, $(LIBS), $(MAKE) $@ -C lib$(LIB);)
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME) $(foreach LIB, $(LIBS), lib$(LIB)/lib$(LIB).a)

re: fclean all

.PHONY: all clean fclean re scan
