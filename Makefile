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
CC = gcc

all: $(SERVER) $(CLIENT)

$(SERVER):
	$(CC) -g $(FLAGS) $(LIBFT) server.c -o $(SERVER)

$(CLIENT):
	$(CC) -g $(FLAGS) $(LIBFT) client.c -o $(CLIENT)

fclean:
	rm -f $(SERVER) $(CLIENT)

re: fclean all