# Multiple Server Usage

PROJECT := SERVER

MK_DIR= ../mk/

OBJ_DIR := obj/

# General behavior

NAME_BIN := libmsu.a

LIB_DIR := ../lib/

SRC_GENDIR := src/
OBJ_GENDIR := $(OBJ_DIR)src/

SRC_GEN = \
	core.cpp

OBJ_GEN = $(addprefix $(OBJ_GENDIR), $(SRC_GEN:.cpp=.o))

# Utility

INCDIR := ./include/
SHARED_INCDIR := ../shared/
INC := -I$(INCDIR) -I$(SHARED_INCDIR)

CC = g++

AR = ar

CP = cp -r

FLAGS = -W -Werror -Wextra -Wall

# if debug is activated
FLAGS += $(DEBUG)
FLAGS += -std=c++11

CXXFLAGS = $(FLAGS) $(INC)

RM		:= rm -rf

include $(MK_DIR)colors.mk $(MK_DIR)defs.mk

# Rules

all:
	@make --no-print-directory $(NAME_BIN) DEBUG='-DDEBUG=0'

intro:
	@$(PRINTF) "$(YELLOW_R) ---- MULTIPLE SERVER USAGE ---- $(CLEAR)\n"
# debug: FLAGS += -DDEBUG -g
debug: fclean
	@make --no-print-directory $(NAME_BIN) DEBUG='-DDEBUG=1 -g3'

shared:
	@mkdir -p $(SHARED_INCDIR)
	@$(CP) $(INCDIR)* $(SHARED_INCDIR)

$(OBJ_GENDIR)%.o: $(SRC_GENDIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CC) -o $@ -c $< $(CXXFLAGS) $(ERRLOG)
	@$(PRINTF) "$(GREEN_R)$(ECHO) $(CLEAR)\t$<\n"

$(NAME_BIN): intro $(OBJ_GEN) shared
	@$(AR) rs $(NAME_BIN) $(OBJ_GEN)
	@mkdir -p $(LIB_DIR)
	@$(CP) $(NAME_BIN) $(LIB_DIR)
	@$(PRINTF) "$(GREEN_R)Done $(CLEAR)\n"

clean:
	@$(RM) $(OBJ_DIR)
	@$(PRINTF) "$(RED_R)Cleaning...$(CLEAR) \n"

fclean:	clean
	@$(RM) $(NAME_BIN) $(LIB_DIR)$(NAME_BIN)
	@$(PRINTF) "$(RED_R)Dusting...$(CLEAR) \n"

re: fclean all

.PHONY: all debug $(NAME_BIN) clean fclean re debug
