#################### VARIABLES
NAME = MattDaemon
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -g $(if $(BONUS),-DBONUS)
LDFLAGS = -lcurl -lz #-fsanitize=thread -fno-omit-frame-pointer -pthread

SRC_DIR = src
OBJ_DIR = obj

INCLUDES = $(addprefix -I,$(shell find include -type d))

SRCS = $(wildcard $(SRC_DIR)/**/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

MATT_SHELL= matt_shell
GUI_PATH= ./mattD_gui/build/Desktop_Qt_6_9_3-Debug/

#################### RULES

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

bonus:
	make $(NAME) BONUS=1
	mkdir -p $(GUI_PATH).qm
	make -C $(MATT_SHELL)
	make -C $(GUI_PATH)

clean:

clean:
	rm -rf $(OBJ_DIR)
	make -C $(MATT_SHELL) clean
	make -C $(GUI_PATH) clean
	rm -f "$(GUI_PATH)Ben_AFK"

fclean: clean
	rm -rf $(NAME)
	rm -f $(MATT_SHELL)/MattShell

re: fclean all

gui:
	sh -c "$(GUI_PATH)Ben_AFK"



.PHONY: all clean fclean re
