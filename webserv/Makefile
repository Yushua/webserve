# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rdrazsky <rdrazsky@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/04 13:52:48 by rdrazsky      #+#    #+#                  #
#    Updated: 2022/10/04 14:50:12 by rdrazsky      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME      := webserv
FLAGS     := -Wall -Wextra -Werror -std=c++98 -pedantic -fsanitize=address
INC       := inc
SRC       := src
OBJ       := obj
BIN       := bin

SHELL     := bash
ARGS      := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))

INCLUDES  := $(foreach i,$(INC),-I $(i))
FILES     := $(foreach i,$(SRC),$(shell find $(i) -iname "*.cpp"))
OBJ_FILES := $(FILES:.cpp=.o)
OBJ_FILES := $(OBJ_FILES:$(SRC)/%=$(OBJ)/%)
SRC_DIRS  := $(shell find $(SRC) -type d -mindepth 1)
OBJ_DIRS  := $(OBJ) $(SRC_DIRS:$(SRC)/%=$(OBJ)/%)

# -~={ Colors }=~- #
BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

# -~={ Compilation }=~- #
all:
	@$(MAKE) $(NAME) -j4

$(NAME): $(OBJ_DIRS) $(OBJ_FILES)
	@mkdir -p $(BIN) $(BIN)/root
	@cp -R root $(BIN)
	@c++ -o $(BIN)/$(NAME) $(FLAGS) $(OBJ_FILES) $(DEBUG)
	@printf "[$(CYAN)webserv$(RESET)] $(GREEN)Done!$(RESET)\n"

$(OBJ_DIRS):
	@mkdir -p $(OBJ_DIRS)

$(OBJ)/%.o: $(SRC)/%.cpp
	@c++ $(FLAGS) $(INCLUDES) -c $< -o $@ $(DEBUG)
	@printf "[$(CYAN)webserv$(RESET)] $(BOLD)compiled: $(RESET)%s\n" $<

# -~={ Clean up }=~- #
clean:
	@rm -rf $(OBJ)/*
	@printf "[$(CYAN)webserv$(RESET)] $(RED)cleared obj folder$(RESET)\n"

fclean: clean
	@rm -rf $(BIN)/*
	@printf "[$(CYAN)webserv$(RESET)] $(RED)cleared bin folder$(RESET)\n" $<

re: fclean all

# -~={ Debug }=~- #
run: all
	@echo
	@$(BIN)/$(NAME) $(ARGS)

rerun: re run

debug:
	$(MAKE) re DEBUG="-D DEBUG"

debugrun: debug run

$(ARGS):
	@exit

.PHONY: all clean fclean re run
.SUFFIXES:
