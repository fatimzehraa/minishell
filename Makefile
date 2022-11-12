CC = cc
CFLAGS += -Wall -Wextra -Werror

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	LDFLAGS += -lreadline -ltermcap
else
	LDFLAGS = -lreadline -ltinfo
endif

INCLUDES = -I./inc
BUILD_DIR = build

HEADER_FILES = $(addprefix inc/, cmd.h exec.h list.h minishell.h parser.h str.h token.h utils.h vector.h)

MANDATORY_OBJ = main.o signals.o exec.o env.o heredoc.o heredoc_utils.o tokenizer/tokenizer.o tokenizer/utils.o \
	tokenizer/scanner.o str/core_utils.o str/core.o utils/ft_lib.o utils/str.o utils/str_extra.o utils/str_extra_extra.o utils/ft_itoa.o \
	utils/vector.o utils/vector_extra.o utils/expand.o\
	parser/expand.o parser/parser.o parser/join.o parser/asterisk.o parser/check_syntax.o parser/template.o \
	execute/execute.o execute/execute_utils.o execute/builtins.o execute/builtins_utils.o execute/redirections.o \
	execute/execute_env.o execute/execute_echo.o execute/execute_exit.o \
	lists/ft_lstadd_back.o lists/ft_lstclear.o lists/ft_lstiter.o \
	lists/ft_lstmap.o lists/ft_lstsize.o lists/ft_lstadd_front.o \
	lists/ft_lstdelone.o lists/ft_lstlast.o lists/ft_lstnew.o lists/ft_delete.o

M_OBJ = $(addprefix $(BUILD_DIR)/, $(MANDATORY_OBJ))

NAME = minishell

all : $(NAME)

$(NAME) : $(M_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: src/%.c $(HEADER_FILES)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean : 
	rm -rf $(BUILD_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re 
