# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tadey <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/16 15:29:50 by tadey             #+#    #+#              #
#    Updated: 2018/05/16 15:33:58 by tadey            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SERVER = server
CLIENT = client
FLAGS = -Wall -Wextra -Werror
LIBFT = -L libft/ -lft
CLI = cli/*.c
SRV = srv/*.c
CC = gcc

all: $(SERVER) $(CLIENT)

$(SERVER):
	$(CC) -g $(FLAGS) $(LIBFT) server.c $(SRV) -o $(SERVER)

$(CLIENT):
	$(CC) -g $(FLAGS) $(LIBFT) client.c $(CLI) -o $(CLIENT)
	mv client client_env

fclean:
	rm -f $(SERVER) $(CLIENT)

re: fclean all