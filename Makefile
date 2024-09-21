# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajehle <ajehle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/02 15:17:19 by ajehle            #+#    #+#              #
#    Updated: 2024/03/09 13:48:36 by ajehle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER			:= server
CLIENT			:= client
CC				:= cc
REMOVE			:= rm -rf
OBJ_DIR			:= ./obj
SRC_DIR			:= src
INC_DIR			:= include
CFLAGS			:= -Wall -Werror -Wextra -I $(INC_DIR)

# looking for files in subdirectories
vpath %.c $(SRC_DIR)
vpath %.h $(INC_DIR)

# INTERNAL FUNCTIONS
SERVER_FUNC		:=	server.c

CLIENT_FUNC		:=	client.c \

# INTERNAL OBJECT
SERVER_OBJ		:= $(addprefix $(OBJ_DIR)/, $(notdir $(SERVER_FUNC:.c=.o)))
CLIENT_OBJ		:= $(addprefix $(OBJ_DIR)/, $(notdir $(CLIENT_FUNC:.c=.o)))

# EXTERNAL LIBRARYS START
# FT_PRINTF Resources
FT_PRINTF_DIR	:= libs/ft_printf
FT_PRINTF		:= $(FT_PRINTF_DIR)/libftprintf.a

# FT_LIBFT Resources
FT_LIBFT_DIR	:= libs/libft
FT_LIBFT		:= $(FT_LIBFT_DIR)/libft.a

# EXTERNAL LIBRARY
LIB_FT_PRINTF	:= -L$(FT_PRINTF_DIR) -lftprintf
LIB_FT_LIBFT	:= -L$(FT_LIBFT_DIR) -lft

# ALL LIBS
LIBS			:= $(LIB_FT_PRINTF) $(LIB_FT_LIBFT)
LIBS_NAME		:= $(FT_PRINTF) $(FT_LIBFT)
LIBS_DIR		:= $(FT_PRINTF_DIR) $(FT_LIBFT_DIR)
# EXTERNAL LIBRARYS END

all : $(SERVER) $(CLIENT)

# INTERNAL RULE
$(SERVER) : $(LIBS_NAME) $(SERVER_OBJ)
	$(CC) $(SERVER_OBJ) $(LIBS) -o $(SERVER)

$(CLIENT) : $(LIBS_NAME) $(CLIENT_OBJ)
	$(CC) $(CLIENT_OBJ) $(LIBS) -o $(CLIENT)

# EXTERNAL LIBRARYS RULE (1 for each lib)
$(FT_PRINTF) :
	$(MAKE) -C $(FT_PRINTF_DIR)
$(FT_LIBFT) :
	$(MAKE) bonus -C $(FT_LIBFT_DIR)

# DIRECTORY
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(MAKE) -C $(FT_LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	$(REMOVE) $(SERVER_OBJ) $(CLIENT_OBJ)
	$(REMOVE) $(OBJ_DIR)

fclean : clean
	$(MAKE) -C $(FT_LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean
	$(REMOVE) $(SERVER)	$(CLIENT)
	$(REMOVE) $(OBJ_DIR)

re : fclean all

.PHONY : all, clean, fclean, re