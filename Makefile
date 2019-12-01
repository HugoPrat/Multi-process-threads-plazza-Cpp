##
## EPITECH PROJECT, 2018
## CCP_plazza_2018
## File description:
## Makefile
##

CXX	:=	g++

RM	:=	rm -rf

CPPFLAGS	:=	-I./include/

CXXFLAGS	:=	-W -Wall -Wextra -pthread

BIN_NAME	:=	plazza

SRC	:=	./src/main.cpp	\
		./src/Reception.cpp	\
		./src/Parser.cpp	\
		./src/Cooks.cpp	\
		./src/Kitchen.cpp	\
		./src/Sync_cout.cpp	\
		./src/Pizza/Americana.cpp	\
		./src/Pizza/Fantasia.cpp	\
		./src/Pizza/Margarita.cpp	\
		./src/Pizza/Pizza.cpp	\
		./src/Pizza/Regina.cpp

OBJ	:=	$(SRC:.cpp=.o)

all:	$(BIN_NAME)

$(BIN_NAME):	$(OBJ)
		$(CXX) -o $(BIN_NAME) $(CPPFLAGS) $(CXXFLAGS) $(OBJ)

clean:
		rm -rf $(OBJ)

fclean:	clean
		rm -rf $(BIN_NAME)

re:	fclean all