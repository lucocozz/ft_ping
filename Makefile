# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/30 15:23:20 by lucocozz          #+#    #+#              #
#    Updated: 2023/01/09 15:32:55 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ping

SRCS =	main.c					\
		$(_PING)				\
		$(_DISPLAY)				\
		$(_ICMP)				\
		$(_IP)					\
		$(_OPTIONS)				\
		$(_SYSTEM)				\
		$(_UTILS)				\
		$(_LIBS)

_PING =						\
	ping.c					\
	ping_datagram.c			\
	set_ping_stats.c

_DISPLAY = 					\
	print_ping_header.c		\
	print_ping_result.c		\
	print_ping_stats.c

_ICMP =						\
	create_icmp_socket.c	\
	icmp_datagram.c			\
	send_datagram.c			\
	recv_datagram.c

_IP =						\
	checksum.c				\
	get_ip_address.c		\
	is_ip_format.c			\
	resolve_service.c		\
	is_ip_broadcast.c

_OPTIONS =					\
	flags_handlers.c		\
	get_options.c			\
	parse_options.c

_SYSTEM =					\
	alarm.c					\
	cleanup.c				\
	logs.c					\
	signals.c

_UTILS =					\
	get_elapsed_time.c

_LIBS = libft.c

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
