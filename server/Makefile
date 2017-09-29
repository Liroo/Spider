# Server

PROJECT := SERVER

MK_DIR= ../mk/

OBJ_DIR := obj/

# General behavior

NAME_BIN := server

SRC_GENDIR := src/
OBJ_GENDIR := $(OBJ_DIR)src/

SRC_GEN = \
	main.cpp

OBJ_GEN = $(addprefix $(OBJ_GENDIR), $(SRC_GEN:.cpp=.o))

# Utility

INCDIRS := -I./include -I../shared
LIBS := -L../lib -lmsu

CXX = g++

FLAGS = -W -Werror -Wextra -Wall

# if debug is activated
FLAGS += $(DEBUG)
FLAGS += -std=c++11

CXXFLAGS := $(INCDIRS)

RM		:= rm -rf

include $(MK_DIR)colors.mk $(MK_DIR)defs.mk

# Rules

all:
	@make --no-print-directory $(NAME_BIN) DEBUG='-DDEBUG=0'

intro:
	@$(PRINTF) "$(YELLOW_R) ---- SERVER ---- $(CLEAR)\n"
# debug: FLAGS += -DDEBUG -g
debug: fclean
	@make --no-print-directory $(NAME_BIN) DEBUG='-DDEBUG=1 -g3'

$(OBJ_GENDIR)%.o: $(SRC_GENDIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) -o $@ -c $< $(CXXFLAGS) $(ERRLOG)
	@$(PRINTF) "$(GREEN_R)$(ECHO) $(CLEAR)\t$<\n"

$(NAME_BIN): intro $(OBJ_GEN)
	@$(CXX) -o $(NAME_BIN) $(LIBS) $(OBJ_GEN) $(CXXFLAGS)
	@$(PRINTF) "$(GREEN_R)Done $(CLEAR)\n"

clean:
	@$(RM) $(OBJ_DIR)
	@$(PRINTF) "$(RED_R)Cleaning...$(CLEAR) \n"

fclean:	clean
	@$(RM) $(NAME_BIN)
	@$(PRINTF) "$(RED_R)Dusting...$(CLEAR) \n"

re: fclean all

.PHONY: all debug $(NAME_BIN) clean fclean re debug
